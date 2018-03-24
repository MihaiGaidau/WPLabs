
#include <windows.h>
#include "colors.h"

BOOL CALLBACK ColorScrDlg (HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam)
{
        static int iColor[3] ;
        HWND hwndParent, hCtrl ;
        int iCtrlID, iIndex ;
        switch (message)
        {
            case WM_INITDIALOG :
                for (iCtrlID = 10 ; iCtrlID < 13 ; iCtrlID++)
                    {
                        hCtrl = GetDlgItem (hDlg, iCtrlID) ;
                        SetScrollRange (hCtrl, SB_CTL, 0, 255, FALSE) ;
                        SetScrollPos (hCtrl, SB_CTL, 0, FALSE) ;
                    }
                return TRUE ;
            case WM_VSCROLL :
                    hCtrl = (HWND)lParam ;
                    iCtrlID=GetWindowLong(hCtrl,GWL_ID);
                    iIndex=(iCtrlID - 10);
                    hwndParent = GetParent (hDlg) ;
                    switch (LOWORD (wParam))
                        {
                            case SB_PAGEDOWN :
                                iColor[iIndex] += 15 ; // fall through
                                case SB_LINEDOWN :
                                iColor[iIndex] = min (255, iColor[iIndex] + 1) ;
                            break ;
                            case SB_PAGEUP :
                                iColor[iIndex] -= 15 ; // fall through
                            case SB_LINEUP :
                                iColor[iIndex] = max (0, iColor[iIndex] - 1) ;
                            break ;
                            case SB_TOP :
                                iColor[iIndex] = 0 ;

                            break ;
                            case SB_BOTTOM :
                                iColor[iIndex] = 255 ;
                            break ;
                            case SB_THUMBPOSITION :
                            case SB_THUMBTRACK :
                                iColor[iIndex] = HIWORD (wParam) ;
                            break ;
                            default :
                                return FALSE ;
                        }
                        SetScrollPos (hCtrl, SB_CTL, iColor[iIndex], TRUE) ;
                        SetDlgItemInt (hDlg, iCtrlID + 3, iColor[iIndex], FALSE) ;
                        DeleteObject ((HGDIOBJ) SetClassLong (hwndParent, GCL_HBRBACKGROUND,(LONG) CreateSolidBrush (RGB (iColor[0], iColor[1], iColor[2])))) ;
                        InvalidateRect (hwndParent, NULL, TRUE) ;
                        return TRUE ;
                        }
                    return FALSE ;
}

