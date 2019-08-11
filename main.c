#include <stdio.h>
#include <windows.h>
#include <tchar.h>



LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

HWND lblTxtRAM,lblTxtRAMPercent,lblTxtRAMValue;

int tmp = 0;

HINSTANCE Hinstance;

void UpdateLabelValue(void)
{
    MEMORYSTATUSEX statex;
    GlobalMemoryStatus(&statex);
    printf("%lu",statex.);
    SetWindowTextW(lblTxtRAMValue,statex.dwTotalVirtual);

}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    HWND Form;
    MSG msg;
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "ClassWin";

    if(!RegisterClass(&wc)) return FALSE;

    Form = CreateWindow("ClassWin", "Windows", WS_POPUPWINDOW,1800, 980, 120, 60,NULL, NULL, hinstance, NULL);
    if (!Form) return FALSE;

    //FreeConsole();
    ShowWindow(Form, nCmdShow);
    UpdateWindow(Form);


    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
/****************************************************************************/

LRESULT CALLBACK MainWndProc(HWND Form, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


    switch (uMsg)
    {
        case WM_CREATE:
            lblTxtRAM =CreateWindowW(L"Static", L"Memory", WS_VISIBLE | WS_CHILD, 10 ,5,100,100,Form,1,NULL,NULL);
            lblTxtRAMPercent =CreateWindowW(L"Static", L"0%",  WS_VISIBLE | WS_CHILD | WM_SETTEXT, 50 ,20,100,100,Form,2,NULL,NULL);
            lblTxtRAMValue =CreateWindowW(L"Static", L"0 / 0 GB", WS_VISIBLE | WS_CHILD, 10 ,35,100,100,Form,3,NULL,NULL);
            //BOOL t = SetDlgItemTextW(lblTxtRAMValue, 3, L"Test");

            //SetTextColor(GetDC(lblTxtRAMValue),RGB(192,192,192));
            SetTimer(Form,5,250,(TIMERPROC)NULL);

            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_TIMER:
            switch (wParam)
            {
            case 5:
                UpdateLabelValue();

                return 0;
            }


            break;

        default:
            return DefWindowProc(Form, uMsg, wParam, lParam);
    }
}




