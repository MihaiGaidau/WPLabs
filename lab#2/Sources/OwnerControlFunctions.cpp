#include <windows.h>
#include "resources.h"
void ShowMenu(HWND hwnd)
{
    HMENU hmenu = CreateMenu();
    HMENU FileMenu = CreateMenu();
    HMENU EditMenu = CreateMenu();
    HMENU ViewMenu = CreateMenu();
    HMENU SettingsMenu = CreateMenu();
    HMENU HelpMenu = CreateMenu();


    AppendMenu(hmenu, MF_POPUP,(UINT_PTR)FileMenu,"File");
    AppendMenu(hmenu, MF_POPUP,(UINT_PTR)EditMenu,"Edit");
    AppendMenu(hmenu, MF_POPUP,(UINT_PTR)ViewMenu,"View");
    AppendMenu(hmenu, MF_POPUP,(UINT_PTR)SettingsMenu,"Settings");
    AppendMenu(hmenu, MF_POPUP,(UINT_PTR)HelpMenu,"Help");


    //Sub-options of menu
    AppendMenu(FileMenu, MF_STRING,NEW_OPTION,"New");
    AppendMenu(FileMenu, MF_STRING,OPEN_OPTION,"Open");
    AppendMenu(FileMenu, MF_STRING,SAVE_OPTION,"Save");
    AppendMenu(FileMenu, MF_STRING,QUIT_OPTION,"Quit    F1");
    AppendMenu(HelpMenu, MF_STRING,IDD_INFO, "Info      F2");
    AppendMenu(EditMenu, MF_STRING,IDD_CHANGEFONT,"Change Font      F3");
    AppendMenu(ViewMenu, MF_STRING,IDD_PERSPECTIVE,"Perspective");
    AppendMenu(SettingsMenu, MF_STRING,IDD_ENVIRONMENT,"Environment");

    SetMenu(hwnd, hmenu);

}

void ChangeFont(HWND hwnd)
{

    static HFONT hFont5 = CreateFont(30, 0, 0, 0, FW_BOLD, 0, TRUE, 0, 0, 0, 0, 0, 0, "Underline");
    SendMessage(GetDlgItem(hwnd, STATIC_TEXT), WM_SETFONT, (WPARAM)hFont5, TRUE);
}
