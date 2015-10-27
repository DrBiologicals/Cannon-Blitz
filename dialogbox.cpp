#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

#include "resource.h"
#include "game.h"
#include "level.h"
#include "dialogbox.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

float fResult;
int iResult;
CLevel* m_pLevel;
CGame* m_pGame;
HINSTANCE _hInstance;
BOOL CALLBACK DialogProc(HWND _hDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{
	case WM_INITDIALOG:
		{
			return true;
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(_wparam))
			{
			case IDC_APPLY1:
				{
					
					iResult = GetDlgItemInt(_hDlg, IDC_SOLDIER_SPAWN, NULL, true);
					m_pGame->SetSpawn(iResult);

					DestroyWindow(_hDlg);
					return(0);
				}
				break;
			case IDC_APPLY2:
				{
					iResult = GetDlgItemInt(_hDlg, IDC_SOLDIER_SPEED, NULL, true);
					m_pLevel->SetSpeed(iResult);

					DestroyWindow(_hDlg);
					return(0);
				}
				break;
			case IDC_APPLY4:
				{
					iResult = GetDlgItemInt(_hDlg, IDC_BULLET_VELY, NULL, true);
					m_pLevel->BulletVelY(iResult);

					DestroyWindow(_hDlg);
					return(0);
				}
				break;
			case IDC_APPLY5:
				{
					iResult = GetDlgItemInt(_hDlg, IDC_NUM_LIVES, NULL, true);
					m_pLevel->NumLives(iResult);

					DestroyWindow(_hDlg);
					return(0);
				}
				break;
			case IDC_APPLY6:
				{
					iResult = GetDlgItemInt(_hDlg, IDC_NUM_SOLDIER, NULL, true);
					m_pLevel->NumSoldiers(iResult);

					DestroyWindow(_hDlg);
					return(0);
				}
				break;
			default:
				{
					return false;
				}
				break;
			}
		}
		break;
	default:
		{
			return false;
		}
	}

}
int
CDialog::Initialise()
{
	DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);

	return(0);
}




