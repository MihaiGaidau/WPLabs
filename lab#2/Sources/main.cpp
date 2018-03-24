#include <windows.h>
#include "colors.h"
#include "resources.h"


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ColorScrDlg (HWND, UINT, WPARAM, LPARAM);
HWND hDlgModeless ;
HWND hMark, hModel, hRegistration, hOut,hText, hMarkButton, hModelButton, hRegistrationButton, hOutButton, hPowerButton, hPower, hColorButton, hColor;

void OwnerControl(HWND hwnd);
void ShowMenu(HWND hwnd);
void ChangeFont(HWND hwnd);
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Colors");
    HWND hwnd ;
    MSG msg ;
    WNDCLASS wndclass ;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc ;
    wndclass.cbClsExtra = 0 ;
    wndclass.cbWndExtra = 0 ;
    wndclass.hInstance = hInstance ;
    wndclass.hIcon =(HICON)LoadImage(NULL,"./second.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
    //wndclass.hIconSm = NULL;
    wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = CreateSolidBrush (0L) ;
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName ;
    if (!RegisterClass (&wndclass))
    {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"),
        szAppName, MB_ICONERROR) ;
        return 0 ;
    }
    hwnd = CreateWindow (szAppName, TEXT ("Windows Application"),WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL,10, 10,900, 600,NULL, NULL, hInstance, NULL) ;
    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd);
    hDlgModeless = CreateDialog (hInstance, TEXT ("ColorScrDlg"),hwnd, ColorScrDlg);
    while (GetMessage (&msg, NULL, 0, 0))
    {
        if (hDlgModeless == 0 || !IsDialogMessage (hDlgModeless, &msg))
            {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
            }
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hWndHorzColorScroll, hWndHorzMoveScroll, hWndHorzWidthScroll;
	HWND hWndVertMoveScroll, hWndVertHeightScroll;
	HWND hWndRemoveButton;
	int xNewPos;
        switch (message)
        {
        case WM_CREATE:
            OwnerControl(hwnd);
            ShowMenu(hwnd);
            SetScrollRange(hwnd, SB_HORZ, 0, 4, TRUE);
            SetScrollPos(hwnd, SB_HORZ, 3, TRUE);

            SetScrollRange(hwnd, SB_VERT, 0, 4, TRUE);
            SetScrollPos(hwnd, SB_VERT, 3, TRUE);

            hWndHorzColorScroll = CreateWindow("SCROLLBAR",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,10,10,215,20,hwnd,(HMENU)SCROLL_BAR_HORZ_COLOR,NULL,NULL);
            SetScrollRange(hWndHorzColorScroll, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hWndHorzColorScroll, SB_CTL, 0, TRUE);

            hWndHorzMoveScroll = CreateWindow("SCROLLBAR",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,10,40,215,20,hwnd,(HMENU) SCROLL_BAR_HORZ_MOVE,NULL,NULL);

            SetScrollRange(hWndHorzMoveScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndHorzMoveScroll, SB_CTL, 0, TRUE);

            hWndHorzWidthScroll = CreateWindow("SCROLLBAR",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,10,70,215,20,hwnd,(HMENU)SCROLL_BAR_HORZ_WIDTH,NULL,NULL);

            SetScrollRange(hWndHorzWidthScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndHorzWidthScroll, SB_CTL, 0, TRUE);

            hWndVertMoveScroll = CreateWindow("SCROLLBAR",NULL,WS_CHILD | WS_VISIBLE | SBS_VERT,10,100,20,215,hwnd,(HMENU) SCROLL_BAR_VERT_MOVE,NULL,NULL);

            SetScrollRange(hWndVertMoveScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndVertMoveScroll, SB_CTL, 0, TRUE);

            hWndVertHeightScroll = CreateWindow("SCROLLBAR",NULL,WS_CHILD | WS_VISIBLE | SBS_VERT,50,100,20,215,hwnd,(HMENU)SCROLL_BAR_VERT_HEIGHT,NULL,NULL);

            SetScrollRange(hWndVertHeightScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndVertHeightScroll, SB_CTL, 0, TRUE);
            hWndRemoveButton = CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Delete from list",WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,600,300,200,20,hwnd,(HMENU)BUTTON_DELETE,NULL,NULL);
            break;
            case WM_HSCROLL:
		    if(wParam)
            {
                int nScrollCode = (int)LOWORD(wParam);
                int nPos = (short int)HIWORD(wParam);

                SCROLLINFO si = {sizeof(SCROLLINFO),
                                 SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS, 0, 0, 0, 0,
                                 0};
                GetScrollInfo (hwnd, SB_HORZ, &si);

                int nNewPos = si.nPos;

                switch (nScrollCode)
                {
                    case SB_LINELEFT:
                        nNewPos--;
                    break;

                    case SB_LINERIGHT:
                        nNewPos++;
                    break;

                    case SB_THUMBPOSITION:
                        nNewPos = nPos + si.nMin;
                    break;
                }

                si.fMask = SIF_POS;
                si.nPos = nNewPos;
                SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            }

		    if(lParam)
            {
                int iScrollId = GetDlgCtrlID((HWND)lParam);

                switch(iScrollId)
                {
                    case SCROLL_BAR_HORZ_COLOR:
                        hWndHorzColorScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndHorzColorScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }

                        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(xNewPos, xNewPos, xNewPos)));
                                InvalidateRect(hwnd, NULL, TRUE);
                                UpdateWindow(hwnd);
                        SetScrollPos(hWndHorzColorScroll, SB_CTL, xNewPos, TRUE);
                    break;

                    case SCROLL_BAR_HORZ_MOVE:
                        hWndHorzMoveScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndHorzMoveScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10 + xNewPos * 100, 10, 600, 360, TRUE);
                        }
                        SetScrollPos(hWndHorzMoveScroll, SB_CTL, xNewPos, TRUE);
                    break;

                    case SCROLL_BAR_HORZ_WIDTH:
                        hWndHorzWidthScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndHorzWidthScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10, 10, 600 + xNewPos * 100, 360, TRUE);
                        }
                        SetScrollPos(hWndHorzWidthScroll, SB_CTL, xNewPos, TRUE);
                    break;
                }
            }
        break;

        case WM_VSCROLL:
		    if(wParam)
            {
                int nScrollCode = (int)LOWORD(wParam);
                int nPos = (short int)HIWORD(wParam);

                SCROLLINFO si = {sizeof(SCROLLINFO),
                                 SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS, 0, 0, 0, 0,
                                 0};
                GetScrollInfo (hwnd, SB_VERT, &si);

                int nNewPos = si.nPos;

                switch (nScrollCode)
                {
                    case SB_LINELEFT:
                        nNewPos--;
                    break;

                    case SB_LINERIGHT:
                        nNewPos++;
                    break;

                    case SB_THUMBPOSITION:
                        nNewPos = nPos + si.nMin;
                    break;
                }

                si.fMask = SIF_POS;
                si.nPos = nNewPos;
                SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            }

		    if(lParam)
            {
                int iscrollid = GetDlgCtrlID((HWND)lParam);

                switch(iscrollid)
                {
                    case SCROLL_BAR_VERT_MOVE:
                        hWndVertMoveScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndVertMoveScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10, 10 + xNewPos * 100, 600, 360, TRUE);
                        }
                        SetScrollPos(hWndVertMoveScroll, SB_CTL, xNewPos, TRUE);
                    break;

                    case SCROLL_BAR_VERT_HEIGHT:
                        hWndVertHeightScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndVertHeightScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10, 10, 600, 360 + xNewPos * 100, TRUE);
                        }
                        SetScrollPos(hWndVertHeightScroll, SB_CTL, xNewPos, TRUE);
                    break;
                }
            }

        break;
        case WM_COMMAND:
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


                    int sendToList = SendDlgItemMessage(hwnd, LIST_BOX, LB_ADDSTRING, 0, (LPARAM)out);
                    SendDlgItemMessage(hwnd, LIST_BOX, LB_SETITEMDATA, (WPARAM)sendToList, NULL);

                }

                if (LOWORD(wParam) == IDD_CHANGEFONT)
                {
                    ChangeFont(hwnd);
                }
                if(LOWORD(wParam) == BUTTON_DELETE)
                {
                    int iElemID = SendDlgItemMessage(hwnd, LIST_BOX, LB_GETCURSEL, 0, 0);
                    if(iElemID != LB_ERR)
                            {
                                SendDlgItemMessage(hwnd, LIST_BOX, LB_DELETESTRING, iElemID, 0);
                            }
                }

                if(LOWORD(wParam) == IDD_INFO)
                {
                       MessageBox(hwnd,"This laboratory work was performed by Student of FAF-161\nThis project is based on Event Driven Programming techniques", "Information",MB_APPLMODAL);
                }
                switch (LOWORD(wParam))
                {
                    case QUIT_OPTION:
                        {
                            PostQuitMessage(0);
                        }
                    case NEW_OPTION:
                        {
                            MessageBox(hwnd,"For new option I must write a little bit more code" , "Continued",MB_RIGHT);
                        }
                }
                break;
        case WM_KEYDOWN:

                switch(wParam)
                {
                    case VK_F3:
                    {
                        ChangeFont(hwnd);
                    }
                        break;

                    case VK_F2:
                    {
                        MessageBox(hwnd,"This laboratory work was performed by Student of FAF-161\nThis project is based on Event Driven Programming techniques", "Information",MB_APPLMODAL);
                    }
                        break;

                    case VK_F1:
                    {
                       PostQuitMessage(0);
                    }
                       break;

                }
                break;



        case WM_DESTROY :
                DeleteObject ((HGDIOBJ) SetClassLong (hwnd, GCL_HBRBACKGROUND,
                (LONG) GetStockObject (WHITE_BRUSH))) ;
                PostQuitMessage (0) ;
                return 0 ;
                break;

        }
        return DefWindowProc (hwnd, message, wParam, lParam) ;
    }
void OwnerControl(HWND hwnd)
{
//    PlaySoundW(L"candilejas.wav",NULL, SND_ASYNC | SND_FILENAME);


    hText = CreateWindowW(L"Static", L"Dream Car", WS_VISIBLE | WS_CHILD | SS_CENTER, 250, 20, 400, 30, hwnd, (HMENU)STATIC_TEXT, NULL, NULL);
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
    hOut = CreateWindowEx(WS_EX_CLIENTEDGE,"LISTBOX",NULL,WS_CHILD | WS_VISIBLE,300,300,250,150,hwnd,(HMENU)LIST_BOX,NULL,NULL);



}
