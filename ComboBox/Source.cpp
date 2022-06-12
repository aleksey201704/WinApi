#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include "resource.h"
#include <cstdio>

CONST CHAR* string[] = {"This","is","Make","First","Combo"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam);

INT WINAPI WinMain
	(
		HINSTANCE hInstanse, HINSTANCE hPrevInvest,
		LPSTR lpCmdLine,
		int nCmdShow
	)
{
	DialogBoxParam(hInstanse, MAKEINTRESOURCE(IDD_DIALOG1),
		0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: 
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)string[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			int i = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
			SendMessage(hComboBox,CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_msg[SIZE] = {};
			sprintf(sz_msg, " %d со значением %s", i, sz_buffer);
			MessageBox(hwnd, sz_msg, "info", MB_OK | MB_ICONINFORMATION);
		}
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}
