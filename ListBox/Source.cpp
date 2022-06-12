#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include"resource.h"
#include <cstdio>

CONST CHAR* string[] = {"This","is","my","List","1024","00254"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc_ADD(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstanse, MAKEINTRESOURCE(IDD_DIALOG1),0,DlgProc,0);
	DialogBoxParam(hInstanse, MAKEINTRESOURCE(IDD_DIALOG_ADD),0,DlgProc_ADD,0);
		
	return 0;
}
BOOL CALLBACK DlgProc_ADD(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return false;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND  hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i< sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}
		SendMessage(hListBox, LB_SETCURSEL,4,0);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int i= SendMessage(hListBox,LB_GETCURSEL,0,0);
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_msg[SIZE] = {};
			sprintf(sz_msg,"Вы выбрали элемент %d со значением %s ",i,sz_buffer);
			MessageBox(hwnd, sz_msg, "info", MB_OK | MB_ICONINFORMATION);

		}
			break;
		case IDC_BUTTON_DELETE:  
		{
			HWND HListBox = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(HListBox, LB_GETCURSEL, 0, 0);
			SendMessage(HListBox, LB_DELETESTRING, i, 0); // Удаляем строку в ListBox
			SendMessage(HListBox, LB_SETCURSEL, 0, 0); // Устанавливаем курсор на нолувой
						
		}
		break;
		case IDC_BUTTON_ADD: 
		{
			/*HWND child = DlgProc_ADD();
			ShowWindow(child, SW_NORMAL);*/
		}
		break;

		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return false;
}