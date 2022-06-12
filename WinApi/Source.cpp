#include<Windows.h>
#include "resource.h"

CONST CHAR g_szLoginDefaultMessage[] = "Введите логин";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst,
	LPSTR lpCmdline, int nCmdShow)
{
	/*MessageBox(FindWindow(NULL,"WinApi - Microsoft Visual Studio"), "Привет", 
		"INFO",	MB_YESNOCANCEL | MB_ICONINFORMATION | MB_HELP | MB_SYSTEMMODAL);*/

	DialogBoxParam(hInstanse, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_INITDIALOG: // Создаются элементы интерфейса, производится настройка окна. 
		//Отрабатывается только при ПЕРВОМ запуске
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd,WM_SETICON,0,(LPARAM)hIcon);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT1),WM_SETTEXT,0,LPARAM(g_szLoginDefaultMessage));
	}
		break;
	case WM_COMMAND: // Обрабатывает нажатие кнопок и  любые обращения к элементам окна
		switch (LOWORD(wParam)) 
		{
		case IDOK: MessageBox(hwnd, "Была нажата OK", "", MB_OK | MB_ICONERROR); break;
		case IDCANCEL: EndDialog(hwnd, 0);

		}
		break;
	case WM_CLOSE: // Обрабатывает нажатие на крестик.
		EndDialog(hwnd,0);
	case IDC_EDIT1:
			
	
		if (HIWORD(wParam) == EN_SETFOCUS) 
		{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND Hlogin = GetDlgItem(hwnd, IDC_EDIT1);
				SendMessage(Hlogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strcmp(sz_buffer, g_szLoginDefaultMessage) == 0)
					SendMessage(Hlogin, WM_SETTEXT, 0, (LPARAM)"");
		}

		if (HIWORD(wParam) == EN_KILLFOCUS)
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT1);
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (strlen(sz_buffer) == 0)
				SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)g_szLoginDefaultMessage);
		}

		break;
	
	}
	return FALSE;
}