/* WindowInput
 *    -> Author: Angels-D
 *
 * LastChange
 *    -> 2025/04/16 04:40
 *    -> 0.0.0
 *
 * Build
 *    -> g++ -shared -static -Os -Wall -o WindowInput.dll -x c++ ./libs/WindowInput.hpp
 */

#ifndef _WINDOWINPUT_HPP_
#define _WINDOWINPUT_HPP_

// WindowInput.h

#include <Windows.h>
#include <vector>
#include <string>
#include <unordered_set>
#include <random>
#include <thread>

namespace WindowInput
{

    // 窗口输入上下文（RAII管理线程附加）
    class InputContext
    {
    private:
        DWORD targetThreadId_ = 0;
        DWORD currentThreadId_ = GetCurrentThreadId();
        bool attached_ = false;
        HWND lastForeground_ = nullptr;

        // 禁止拷贝
        InputContext(const InputContext &) = delete;
        InputContext &operator=(const InputContext &) = delete;

    public:
        explicit InputContext(HWND hWnd);
        ~InputContext();
    };

    // 核心输入功能类
    class InputEngine
    {
    public:
        // 键盘操作
        static void SendKey(HWND hWnd, WORD vkCode,
                            bool extended = false,
                            int duration = 50,
                            int jitter = 0);

        static void SendKeyCombo(HWND hWnd,
                                 const std::vector<WORD> &keys,
                                 int interval = 30,
                                 int jitter = 5);

        // 鼠标操作
        static void SendMouseClick(HWND hWnd,
                                   int x, int y,
                                   DWORD button = MOUSEEVENTF_LEFTDOWN,
                                   int times = 1,
                                   int pressDuration = 50,
                                   int interval = 100,
                                   int jitter = 0);

        // 文本输入
        static void SendText(HWND hWnd,
                             const std::wstring &text,
                             int interval = 30,
                             int jitter = 5);

        // 窗口控制
        static bool IsWindowActive(HWND hWnd);
        static void BringToFront(HWND hWnd);

    private:
        // 坐标转换
        static POINT ConvertToWindowSpace(HWND hWnd, int x, int y);

        // 时间控制
        static void PrecisionDelay(int ms, int jitter = 0);

        // 输入状态跟踪
        static thread_local std::unordered_set<WORD> pressedKeys_;
        static thread_local std::unordered_set<DWORD> pressedMouseBtns_;

        // 随机引擎
        static thread_local std::mt19937 randGen_;
    };
}

// WindowInput.cpp

#include <cmath>
#include <algorithm>

namespace WindowInput
{

    // 线程本地存储初始化
    thread_local std::unordered_set<WORD> InputEngine::pressedKeys_;
    thread_local std::unordered_set<DWORD> InputEngine::pressedMouseBtns_;
    thread_local std::mt19937 InputEngine::randGen_(std::random_device{}());

    // InputContext实现 ------------------------------------------------
    InputContext::InputContext(HWND hWnd)
    {
        if (!hWnd || !IsWindow(hWnd))
            return;

        targetThreadId_ = GetWindowThreadProcessId(hWnd, nullptr);
        if (targetThreadId_ == currentThreadId_)
            return;

        // 保存当前前台窗口
        lastForeground_ = GetForegroundWindow();

        // 附加到目标线程
        attached_ = AttachThreadInput(currentThreadId_, targetThreadId_, TRUE);

        // 临时激活窗口（不改变Z序）
        if (attached_ && (lastForeground_ != hWnd))
        {
            SetForegroundWindow(hWnd);
            SetFocus(hWnd);
            BringWindowToTop(hWnd);
        }
    }

    InputContext::~InputContext()
    {
        if (attached_)
        {
            // 恢复前台窗口
            if (lastForeground_ && IsWindow(lastForeground_))
            {
                SetForegroundWindow(lastForeground_);
            }
            AttachThreadInput(currentThreadId_, targetThreadId_, FALSE);
        }
    }

    // InputEngine实现 ------------------------------------------------
    POINT InputEngine::ConvertToWindowSpace(HWND hWnd, int x, int y)
    {
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);

        POINT pt = {x, y};
        ScreenToClient(hWnd, &pt);

        // 处理DPI缩放
        const float dpiScale = GetDpiForWindow(hWnd) / 96.0f;
        pt.x = static_cast<int>(pt.x * dpiScale);
        pt.y = static_cast<int>(pt.y * dpiScale);

        // 限制在窗口范围内
        pt.x = std::clamp(pt.x, LONG(0), clientRect.right - 1);
        pt.y = std::clamp(pt.y, LONG(0), clientRect.bottom - 1);

        return pt;
    }

    void InputEngine::PrecisionDelay(int ms, int jitter)
    {
        if (jitter > 0)
        {
            std::uniform_int_distribution<> dist(-jitter, jitter);
            ms += dist(randGen_);
            ms = (std::max)(ms, 1);
        }

        auto start = std::chrono::high_resolution_clock::now();
        while (true)
        {
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            if (elapsed >= ms)
                break;
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
    }

    void InputEngine::SendKey(HWND hWnd, WORD vkCode, bool extended, int duration, int jitter)
    {
        InputContext ctx(hWnd);

        INPUT input[2] = {0};
        // KEY DOWN
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = vkCode;
        input[0].ki.dwFlags = KEYEVENTF_SCANCODE;
        if (extended)
            input[0].ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;

        // KEY UP
        input[1] = input[0];
        input[1].ki.dwFlags |= KEYEVENTF_KEYUP;

        SendInput(2, input, sizeof(INPUT));

        // 如果目标窗口不是前台窗口，发送窗口消息
        if (!IsWindowActive(hWnd))
        {
            PostMessage(hWnd, WM_KEYDOWN, vkCode, 0x00000001);
            PrecisionDelay(duration, jitter);
            PostMessage(hWnd, WM_KEYUP, vkCode, 0xC00000001);
        }

        pressedKeys_.insert(vkCode);
    }

    void InputEngine::SendMouseClick(HWND hWnd, int x, int y, DWORD button,
                                     int times, int pressDuration,
                                     int interval, int jitter)
    {
        InputContext ctx(hWnd);

        const POINT targetPos = ConvertToWindowSpace(hWnd, x, y);
        const LPARAM lParam = MAKELPARAM(targetPos.x, targetPos.y);

        for (int i = 0; i < times; ++i)
        {
            // 物理移动鼠标（需要管理员权限）
            SetCursorPos(x, y);

            // 发送硬件事件
            INPUT input[2] = {0};
            input[0].type = INPUT_MOUSE;
            input[0].mi.dwFlags = button;
            input[1] = input[0];
            input[1].mi.dwFlags |= (button << 1); // 转换DOWN到UP

            SendInput(2, input, sizeof(INPUT));

            // 发送窗口消息
            UINT downMsg = 0, upMsg = 0;
            switch (button)
            {
            case MOUSEEVENTF_LEFTDOWN:
                downMsg = WM_LBUTTONDOWN;
                upMsg = WM_LBUTTONUP;
                break;
            case MOUSEEVENTF_RIGHTDOWN:
                downMsg = WM_RBUTTONDOWN;
                upMsg = WM_RBUTTONUP;
                break;
            case MOUSEEVENTF_MIDDLEDOWN:
                downMsg = WM_MBUTTONDOWN;
                upMsg = WM_MBUTTONUP;
                break;
            }

            PostMessage(hWnd, downMsg, 0, lParam);
            PrecisionDelay(pressDuration, jitter);
            PostMessage(hWnd, upMsg, 0, lParam);

            if (i < times - 1)
            {
                PrecisionDelay(interval, jitter);
            }
        }
    }

    bool InputEngine::IsWindowActive(HWND hWnd)
    {
        return GetForegroundWindow() == hWnd;
    }

    void InputEngine::BringToFront(HWND hWnd)
    {
        if (!IsWindowVisible(hWnd))
            return;

        InputContext ctx(hWnd);
        // 使用多种方式确保窗口激活
        ShowWindow(hWnd, SW_RESTORE);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
}

#endif