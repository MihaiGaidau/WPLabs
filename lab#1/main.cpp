#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>

#define ID_CLOSE 2
#define Show_Dream 3
#define STATIC_TEXT 4
#define WM_GETMINMAXINFO 0x0024
#define STATIC_TEXT_EDIT 5



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OwnerControl(HWND);
void DisplayToCenter(HWND);


bool bk = true, resized = false;
HWND hMark, hModel, hRegistration, hOut, hQuitButton, hText, hMarkButton, hModelButton, hRegistrationButton, hOutButton, hPowerButton, hPower, hColorButton, hColor;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    HWND hwnd = {0};
    WNDCLASSEX wndClass = {0};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = hInst;
    wndClass.lpszClassName = "Window Class";
    wndClass.lpfnWndProc = WndProc;
    MSG msg = {0};


    if(!RegisterClassEx(&wndClass))
    {
        MessageBox(NULL, "Class was not registered", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, "Window Class", "PPE-#1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hInst, NULL);

    ShowWindow (hwnd, ncmdshow) ;
    UpdateWindow (hwnd) ;

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = {0};
	PAINTSTRUCT ps = {0};
	RECT rect = {0};

	LPDRAWITEMSTRUCT pdis = {0};
	static HFONT hFont = {0};
	static int cxClient, cyClient;
	GetClientRect(hwnd, &rect);
	LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;


     switch(msg)
    	{
            case WM_CREATE:
            {
                OwnerControl(hwnd);
                DisplayToCenter(hwnd);
                break;
            }

            case WM_SIZE:
                cxClient = LOWORD(lParam);
            {
                cyClient = HIWORD(lParam);
                if(resized)
                {
                    MoveWindow(hText, cxClient/2-200, cyClient/2-15, 400, 30, TRUE);
                    MoveWindow(hMarkButton, cxClient/2 - 300, cyClient/2-200,100,25,TRUE);
                    MoveWindow(hMark, cxClient/2 - 300, cyClient/2-150,100,25,TRUE);
                    MoveWindow(hModelButton, cxClient/2- 150, cyClient/2-200,100,25,TRUE);
                    MoveWindow(hModel, cxClient/2 - 150, cyClient/2-150,100,25,TRUE);
                    MoveWindow(hRegistrationButton, cxClient/2, cyClient/2-200,100,35,TRUE);
                    MoveWindow(hRegistration, cxClient/2, cyClient/2-150,100,25,TRUE);
                    MoveWindow(hPowerButton, cxClient/2+150, cyClient/2-200,100,25,TRUE);
                    MoveWindow(hPower, cxClient/2+150, cyClient/2-150,100,25,TRUE);
                    MoveWindow(hColorButton, cxClient/2+300, cyClient/2-200,100,25,TRUE);
                    MoveWindow(hColor, cxClient/2+300, cyClient/2-150,100,25,TRUE);
                    MoveWindow(hOutButton, cxClient/2-50, cyClient/2-12,100,25,TRUE);
                    MoveWindow(hOut, cxClient/2-115, cyClient/2+25,250,150,TRUE);
                    MoveWindow(hQuitButton, cxClient-cxClient+10, cyClient - 50 ,50,50, TRUE);




                }
                else
                    resized = true;

                break;
            }

            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                HBITMAP hBackgroundImg;
                HDC hMemDC = CreateCompatibleDC(hdc);
                GetClientRect(hwnd, &rect);
                if(bk)
                    hBackgroundImg = (HBITMAP)LoadImage(NULL, "logo1.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

                HBITMAP hOldBm;
                hOldBm = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);

                LONG x = 0;
                while (x < width)
                {
                    LONG y = 0;
                    while (y < height)
                    {
                        BitBlt(hdc, x, y, 100,100, hMemDC, 0, 0, SRCCOPY);
                        y += 100;
                    }
                    x += 100;
                }

                SelectObject(hMemDC, hOldBm);
                DeleteObject(hBackgroundImg);
                DeleteDC(hMemDC);

                EndPaint(hwnd, &ps);
                break;
            }

             case WM_CTLCOLORSTATIC:
            {
                HWND hStatic = (HWND)lParam;
                HDC hdcStatic = (HDC) wParam;
                if(GetDlgCtrlID(hStatic) == STATIC_TEXT)
                {

                    SetTextColor(hdcStatic, RGB(153, 204, 255));
                    SetBkMode(hdcStatic, TRANSPARENT);
                    return (INT_PTR)CreateSolidBrush(RGB(51, 0, 0));
                }
                break;

            }
            case WM_CTLCOLOREDIT:
            {

                HWND hedit = (HWND)lParam;
                HDC hdcedit = (HDC) wParam;
                if(GetDlgCtrlID(hedit) == STATIC_TEXT_EDIT)
                {
                    SetTextColor(hdcedit,RGB(255,0,0));
                    SetBkColor(hdcedit,RGB(0,255,0));
                }


                return TRUE;
                break;
            }

            case WM_COMMAND:
            {
                if(LOWORD(wParam) == Show_Dream)
                {
                    char mark[30], model[30], registration[15], out[100], power[15], color[30];
                    GetWindowText(hMark, mark, 30);
                    GetWindowText(hModel, model, 30);
                    GetWindowText(hRegistration, registration, 15);
                    GetWindowText(hPower,power,15);
                    GetWindowText(hColor,color,30);
                    strcpy(out, mark);
                    strcat(out, " \r\n ");
                    strcat (out, model);
                    strcat(out, " \r\n ");
                    strcat(out, registration);
                    strcat(out,"\r\n");
                    strcat(out,power);
                    strcat(out,"\r\n");
                    strcat(out,color);

                    SetWindowText(hOut, out);


                }
                if(LOWORD(wParam) == ID_CLOSE)
                {
                     DestroyWindow(hwnd);
                }
                break;
            }
            case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
                lpMMI->ptMinTrackSize.x = 900;
                lpMMI->ptMinTrackSize.y = 600;
            }

            case WM_DRAWITEM:
            {
                pdis = (LPDRAWITEMSTRUCT) lParam;

                if (pdis->hwndItem == hQuitButton)
                {
                    FillRect(pdis->hDC, &pdis->rcItem, (HBRUSH)CreateSolidBrush(RGB(64, 255, 0)));
                    FrameRect(pdis->hDC, &pdis->rcItem, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
                    SetTextColor(pdis->hDC, RGB(0, 32, 84));
                    hFont = CreateFont(30,0,0,0,0,0,TRUE,0,0,0,0, 0, 0,TEXT("Impact"));
                    SelectObject(pdis->hDC, hFont);
                    SetBkMode(pdis->hDC, TRANSPARENT);
                    DrawText(pdis->hDC, "Quit", -1, &pdis->rcItem, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
                }

                break;
            }
            case WM_CLOSE:
            {
                int ret = MessageBox(hwnd, "Are you sure to quit?", "Close", MB_OKCANCEL);
                    if(ret == IDOK)
                        MessageBox(hwnd,"Serious, find the Quit button","Close",MB_OKCANCEL);
                break;
            }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    return 0;
}

void DisplayToCenter(HWND hwnd)
{
	RECT rect = {0};
	GetWindowRect(hwnd, &rect);
	int w_weight = rect.right - rect.left;
	int w_height = rect.bottom - rect.top;

	int screen_weight = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(hwnd, HWND_TOP, (screen_weight - w_weight)/2, 	(screen_height - w_height)/2, 0, 0, SWP_NOSIZE);

}

void OwnerControl(HWND hwnd)
{


    hText = CreateWindowW(L"Static", L"Dream Car", WS_VISIBLE | WS_CHILD | SS_CENTER, 250, 50, 400, 30, hwnd, (HMENU)STATIC_TEXT, NULL, NULL);
    static HFONT hFont = CreateFont(30, 0, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Italic");
    SendMessage(GetDlgItem(hwnd, STATIC_TEXT), WM_SETFONT, (WPARAM)hFont, TRUE);

    hMarkButton = CreateWindowW(L"STATIC", L"Mark:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 100, 100, 25, hwnd, NULL, NULL, NULL);
    hMark = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 100, 150, 100, 25, hwnd, (HMENU)STATIC_TEXT_EDIT, NULL, NULL);
    static HFONT hFont1 = CreateFont(20, 0, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Italic");
    SendMessage(GetDlgItem(hwnd, STATIC_TEXT_EDIT), WM_SETFONT, (WPARAM)hFont1, TRUE);

    hModelButton = CreateWindowW(L"STATIC", L"Model:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 100, 100, 25, hwnd, NULL, NULL, NULL);
    hModel = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 250, 150, 100, 25, hwnd, NULL, NULL, NULL);

    hRegistrationButton = CreateWindowW(L"STATIC", L"1st Registration:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 400, 100, 100, 35, hwnd, NULL, NULL, NULL);
    hRegistration = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 400, 150, 100, 25, hwnd, NULL, NULL, NULL);

    hPowerButton = CreateWindowW(L"STATIC", L"Power:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 550, 100, 100, 35, hwnd, NULL, NULL, NULL);
    hPower = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 550, 150, 100, 25, hwnd, NULL, NULL, NULL);

    hColorButton = CreateWindowW(L"STATIC", L"Color:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 700, 100, 100, 35, hwnd, NULL, NULL, NULL);
    hColor = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 700, 150, 100, 25, hwnd, NULL, NULL, NULL);

    hOutButton = CreateWindowW(L"Button", L"Show Dream", WS_VISIBLE | WS_CHILD | WS_BORDER, 375, 250, 100, 25, hwnd, (HMENU)Show_Dream, NULL, NULL);
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 300, 300, 250, 150, hwnd, NULL, NULL, NULL);

    hQuitButton = CreateWindowW(L"Button", L"Quit", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 500, 50, 50, hwnd, (HMENU)ID_CLOSE, NULL, NULL);



}
