/* AFK
 *    -> Auther: Angels-D
 *
 * LastChange
 *    -> 2025/02/12 18:56
 *    -> 1.0.0
 *
 * Build
 *    -> g++ -shared -static -Os -Wall -o AFK.dll -x c++ .\libs\AFK.hpp
 */

#ifndef _AFK_HPP_
#define _AFK_HPP_

// AFK.h

#include <vector>
#include <string>
#include <unordered_set>
#include <random>

namespace AHK
{
    // 输入状态跟踪器（RAII模式）
    class InputState
    {
    private:
        std::unordered_set<WORD> pressedKeys_;
        std::unordered_set<DWORD> pressedMouseButtons_;
        static thread_local std::mt19937 randGen_;

    public:
        ~InputState();

        // 键盘操作
        void KeyDown(WORD vkCode, bool extended = false);
        void KeyUp(WORD vkCode, bool extended = false);
        void KeyPress(WORD vkCode, bool extended = false, int delay = 15);

        // 鼠标操作
        void MouseMove(int x, int y, HWND hWnd = nullptr);
        void MouseDown(DWORD button, HWND hWnd = nullptr);
        void MouseUp(DWORD button, HWND hWnd = nullptr);
        void MouseClick(DWORD button, int times = 1, HWND hWnd = nullptr);

        // 组合功能
        void SendText(const wchar_t *text, int interval = 30, int jitter = 5);
        void ReleaseAll();

        // 坐标转换
        static POINT ScreenToClient(HWND hWnd, int x, int y);

        static int GetJitter(int base, int jitter);
    };

    // 独立函数接口
    void SimulateKeyPress(WORD vkCode,
                          int times = 1,
                          int pressDuration = 15,
                          int interval = 50,
                          int jitter = 0);

    void SimulateMouseClick(DWORD button,
                            int times = 1,
                            int pressDuration = 15,
                            int interval = 50,
                            int x = INT_MIN,
                            int y = INT_MIN,
                            int jitter = 0,
                            HWND hWnd = nullptr);

    void SimulateTextInput(const wchar_t *text,
                           int interval = 30,
                           int jitter = 5);
}

// AFK.cpp

#include <Windows.h>
#include <cmath>

namespace AHK
{
    // 线程安全的随机数生成器
    thread_local std::mt19937 InputState::randGen_(std::random_device{}());

    // RAII自动释放
    InputState::~InputState()
    {
        ReleaseAll();
    }

    // 坐标转换（包含DPI缩放处理）
    POINT InputState::ScreenToClient(HWND hWnd, int x, int y)
    {
        POINT pt = {x, y};
        if (hWnd)
        {
            ::ScreenToClient(hWnd, &pt);
            const UINT dpi = ::GetDpiForWindow(hWnd);
            pt.x = static_cast<int>(std::round(pt.x * 96.0 / dpi));
            pt.y = static_cast<int>(std::round(pt.y * 96.0 / dpi));
        }
        return pt;
    }

    int InputState::GetJitter(int base, int jitter)
    {
        if (jitter <= 0)
            return base;
        std::uniform_int_distribution<> dist(-jitter, jitter);
        return base + dist(randGen_);
    }

    // 键盘按下
    void InputState::KeyDown(WORD vkCode, bool extended)
    {
        if (pressedKeys_.count(vkCode))
            return;
        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = vkCode;
        input.ki.dwFlags = KEYEVENTF_SCANCODE;
        if (extended)
            input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
        if (::SendInput(1, &input, sizeof(INPUT)) == 1)
            pressedKeys_.insert(vkCode);
    }

    // 键盘释放（带状态验证）
    void InputState::KeyUp(WORD vkCode, bool extended)
    {
        if (!pressedKeys_.count(vkCode))
            return;
        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = vkCode;
        input.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
        if (extended)
            input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
        if (::SendInput(1, &input, sizeof(INPUT)) == 1)
            pressedKeys_.erase(vkCode);
    }

    // 高精度等待（误差<1ms）
    void PrecisionSleep(int ms, int jitter = 0)
    {
        if (jitter > 0)
            ms = (std::max)(InputState::GetJitter(ms, jitter), 1);
        LARGE_INTEGER frequency, start, end;
        ::QueryPerformanceFrequency(&frequency);
        ::QueryPerformanceCounter(&start);
        do
        {
            if (ms > 50)
                ::Sleep(ms / 2);
            ::QueryPerformanceCounter(&end);
        } while (((end.QuadPart - start.QuadPart) * 1000 / frequency.QuadPart) < ms);
    }

    // 独立按键模拟
    void SimulateKeyPress(WORD vkCode, int times, int pressDuration, int interval, int jitter)
    {
        InputState state;
        for (int i = 0; i < times; ++i)
        {
            state.KeyDown(vkCode);
            PrecisionSleep(pressDuration, jitter);
            state.KeyUp(vkCode);
            if (i < times - 1)
                PrecisionSleep(interval, jitter);
        }
    }

    // 增强版鼠标点击
    void SimulateMouseClick(DWORD button, int times, int pressDuration, int interval, int x, int y, int jitter, HWND hWnd)
    {
        InputState state;
        POINT originPos;
        ::GetCursorPos(&originPos);
        for (int i = 0; i < times; ++i)
        {
            if (x != INT_MIN && y != INT_MIN)
            {
                POINT target = InputState::ScreenToClient(hWnd, x, y);
                state.MouseMove(target.x, target.y, hWnd);
            }
            state.MouseDown(button, hWnd);
            PrecisionSleep(pressDuration, jitter);
            state.MouseUp(button, hWnd);
            if (i < times - 1)
                PrecisionSleep(interval, jitter);
        }
        ::SetCursorPos(originPos.x, originPos.y);
    }
}

#endif