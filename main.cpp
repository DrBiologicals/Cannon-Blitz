#define WIN32_LEAN_AND_MEAN

#include <windows.h>	//Include all the windows headers.
#include <windowsx.h>	//Include useful macros.

#include "resource.h"
#include "game.h"
#include "Clock.h"
#include "igutils.h"
#include "dialogbox.h"
#include "CINIParser.h"

#define WINDOW_CLASS_NAME "Cannon Blitz"

int iCannonPos = 0;
bool bNewGame = false;
HWND hwnd;
CGame& rGame = CGame::GetInstance();
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	//What is the message?
	switch (_uiMsg)
	{
		case WM_KEYDOWN:
		{
			if (_wParam == VK_SPACE)
			{
				iCannonPos = rGame.GetCannonPos();
				rGame.InitialiseBullet(iCannonPos);
				
				return(0);
			}
			
			if (_wParam == VK_LEFT)
			{
				iCannonPos = rGame.GetCannonPos();

				iCannonPos -= 15;
				if(iCannonPos < 240)
				{
					iCannonPos = 240;
				}
				
				rGame.SetCannonPos(iCannonPos);
				rGame.InitialiseCannon(iCannonPos);

				return(iCannonPos);
			}
			
  			if (_wParam == VK_RIGHT)
			{
				iCannonPos = rGame.GetCannonPos();

				iCannonPos += 15;
				if(iCannonPos > 360)
				{
					iCannonPos = 360;
				}

				rGame.SetCannonPos(iCannonPos);
				rGame.InitialiseCannon(iCannonPos);

				return(iCannonPos);
			}

			if (_wParam == VK_PAUSE)
			{
				rGame.Pause();

				return(0);
			}
			
		}
		break;

		case WM_COMMAND:
			{
				switch(LOWORD(_wParam))
				{
				case ID_FILE_RESTART:
					{
						bNewGame = true;
						iCannonPos = 300;
						return(0);
	
					}
					break;
				case ID_FILE_DEBUG:
					{
						rGame.Pause();
						CDialog* m_pDialog = new CDialog;
						m_pDialog->Initialise();
						rGame.Pause();

					}
					break;
				case ID_FILE_QUIT:
					{
						CGame::DestroyInstance();
						PostQuitMessage(0);
						return (0);
					}
					break;
				case ID_HELP_ABOUT:
					{
						rGame.Instruction();
						bNewGame = true;
					}
					break;
				}
			}
			break;

		case WM_DESTROY:
		{
			//Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);

			//Return success
			return (0);
		}
		break;
		default:break;
	} // End switch.

	//Process any messages that we didn't take care of...

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
	WNDCLASSEX winclass;
	
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_SOLDIERICON));
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName = L"Cannon Blitz";
	winclass.hIconSm = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_SOLDIERICON));

	if (!RegisterClassEx(&winclass))
	{
		//Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL, 
		L"Cannon Blitz", 
		_pcTitle, 
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!hwnd)
	{
		//Failed to create
		return (0);
	}

	return (hwnd);
}
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _iCmdShow)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	
	const int kiWidth = 600;
	const int kiHeight = 600;

	hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Cannon Blitz");
	
	if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	{
		//Failed
		return (0);
	}
	//Enter main event loop
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
 			DispatchMessage(&msg);
		}
		else if(bNewGame == true)
		{	
			rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight);
			bNewGame = false;
		}
		else
		{

			rGame.ExecuteOneFrame();
		}

	}

	// Return to Windows like this...
	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}