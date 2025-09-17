/* Module
 *    -> Author: Angels-D
 *
 * LastChange
 *    -> 2025/09/16 18:30
 *    -> 1.0.0
 */

#ifndef _DECLARATIOM_HPP_
#define _DECLARATIOM_HPP_

#include <Windows.h>
#include <string>

class CopyrightNotice
{
public:
    static void Show(const std::wstring &authorName, const std::wstring &appName, const std::wstring &srcUrl)
    {
        bool isChinese = (PRIMARYLANGID(langID) == LANG_CHINESE);

        if (!IsFirstRun(appName))
            return;

        HWND hDialog = CreateDialogWindow(authorName, srcUrl, isChinese);
        if (!hDialog)
            return;

        g_countdown = 5;
        SetTimer(hDialog, TIMER_ID, 1000, nullptr);
        RunMessageLoop(hDialog);

        KillTimer(hDialog, TIMER_ID);
        DestroyWindow(hDialog);
        SetFirstRunFlag(appName);
    }

private:
    static const int TIMER_ID = 1;
    static const int IDC_MESSAGE = 1001;
    static const int IDC_COUNTDOWN = 1002;
    static const int IDC_CONFIRM_BUTTON = 1003;
    static const int IDC_CANCEL_BUTTON = 1004;
    static LANGID langID;
    static int g_countdown;

    static LANGID GetSystemLanguage()
    {
        return GetUserDefaultUILanguage();
    }

    static bool IsFirstRun(const std::wstring &appName)
    {
        HKEY hKey;
        DWORD flagValue = 0, dataSize = sizeof(DWORD);
        std::wstring regPath = L"Software\\" + appName;

        if (RegOpenKeyExW(HKEY_CURRENT_USER, regPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
        {
            if (RegQueryValueExW(hKey, L"NoticeShown", NULL, NULL,
                                 reinterpret_cast<LPBYTE>(&flagValue), &dataSize) == ERROR_SUCCESS)
            {
                RegCloseKey(hKey);
                return (flagValue == 0);
            }
            RegCloseKey(hKey);
        }
        return true;
    }

    static void SetFirstRunFlag(const std::wstring &appName)
    {
        HKEY hKey;
        DWORD flagValue = 1;
        std::wstring regPath = L"Software\\" + appName;

        if (RegCreateKeyExW(HKEY_CURRENT_USER, regPath.c_str(), 0, NULL,
                            REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS)
        {
            RegSetValueExW(hKey, L"NoticeShown", 0, REG_DWORD,
                           reinterpret_cast<const BYTE *>(&flagValue), sizeof(DWORD));
            RegCloseKey(hKey);
        }
    }

    static HWND CreateDialogWindow(const std::wstring &authorName, const std::wstring &srcUrl, bool isChinese)
    {
        HWND hDialog = CreateWindowExW(
            WS_EX_DLGMODALFRAME,
            L"STATIC",
            isChinese ? L"软件版权声明" : L"Software Copyright Notice",
            WS_POPUP | WS_CAPTION | WS_VISIBLE | DS_MODALFRAME,
            CW_USEDEFAULT, CW_USEDEFAULT, 590, 190,
            NULL, NULL, GetModuleHandle(NULL), NULL);

        if (!hDialog)
            return NULL;

        std::wstring message;
        if (isChinese)
        {
            message = L"本软件由" + authorName + L"开发并开源、免费提供。\n" +
                      L"任何倒卖行为均属侵权，请通过官方渠道获取，并举报侵权者！\n" +
                      L"官方地址: " + srcUrl;
        }
        else
        {
            message = L"This software is developed by " + authorName + L" and provided as open source, completely free.\n" +
                      L"Any resale is an infringement. Please obtain it through official channels and report infringers!\n" +
                      L"Official Url: " + srcUrl;
        }

        CreateWindowW(L"STATIC", message.c_str(),
                      WS_VISIBLE | WS_CHILD | SS_CENTER,
                      20, 20, 550, 60, hDialog, (HMENU)IDC_MESSAGE,
                      GetModuleHandle(NULL), NULL);

        wchar_t buttonText[50];
        swprintf_s(buttonText, isChinese ? L"我已知晓 (%d)" : L"I understand (%d)", 5);

        CreateWindowW(L"BUTTON", buttonText,
                      WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON | WS_DISABLED,
                      150, 90, 120, 30, hDialog, (HMENU)IDC_CONFIRM_BUTTON,
                      GetModuleHandle(NULL), NULL);

        CreateWindowW(L"BUTTON",
                      isChinese ? L"取消" : L"Cancel",
                      WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON,
                      300, 90, 120, 30, hDialog, (HMENU)IDC_CANCEL_BUTTON,
                      GetModuleHandle(NULL), NULL);

        CenterWindow(hDialog);
        return hDialog;
    }

    static void CenterWindow(HWND hWnd)
    {
        RECT rc;
        GetWindowRect(hWnd, &rc);
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;

        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        SetWindowPos(hWnd, NULL,
                     (screenWidth - width) / 2,
                     (screenHeight - height) / 2,
                     0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    static LRESULT CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_TIMER:
            if (wParam == TIMER_ID)
            {
                g_countdown--;

                SetDlgItemInt(hWnd, IDC_COUNTDOWN, g_countdown, FALSE);

                bool isChinese = (PRIMARYLANGID(langID) == LANG_CHINESE);
                wchar_t buttonText[50];
                if (g_countdown > 0)
                {
                    swprintf_s(buttonText, isChinese ? L"我已知晓 (%d)" : L"I understand (%d)", g_countdown);
                }
                else
                {
                    wcscpy_s(buttonText, isChinese ? L"我已知晓" : L"I understand");
                }
                SetDlgItemTextW(hWnd, IDC_CONFIRM_BUTTON, buttonText);

                if (g_countdown <= 0)
                {
                    HWND hButton = GetDlgItem(hWnd, IDC_CONFIRM_BUTTON);
                    EnableWindow(hButton, TRUE);
                    SetFocus(hButton);
                }
            }
            return 0;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDC_CONFIRM_BUTTON)
            {
                PostQuitMessage(0);
                return 0;
            }
            else if (LOWORD(wParam) == IDC_CANCEL_BUTTON)
            {
                TerminateProcess(GetCurrentProcess(), 0);
                return 0;
            }
            break;

        case WM_CLOSE:
            if (g_countdown > 0)
            {
                MessageBeep(MB_ICONEXCLAMATION);
                return 0;
            }
            break;
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORSTATIC:
            SetBkColor((HDC)wParam, RGB(255, 255, 255));
            return (LRESULT)GetStockObject(WHITE_BRUSH);
        }

        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    static void RunMessageLoop(HWND hDialog)
    {
        SetWindowLongPtrW(hDialog, GWLP_WNDPROC,
                          reinterpret_cast<LONG_PTR>(DialogProc));

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
};

int CopyrightNotice::g_countdown = 5;
LANGID CopyrightNotice::langID = CopyrightNotice::GetSystemLanguage();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        CopyrightNotice::Show(L"Angels-D", L"TroveAuto", L"https://github.com/Angels-D/TroveAuto");
    }
    return TRUE;
}

#endif