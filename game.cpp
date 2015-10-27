#include "Clock.h"
#include "BackBuffer.h"
#include "igutils.h"
#include "level.h"
#include "CINIParser.h"

#include "game.h"

CGame* CGame::s_pGame = 0;

bool bPauseGame = false;

int m_iSpawnTime = 0;

CGame::CGame()
: m_pClock(0)
, m_pLevel(0)
, m_pIniParser(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_iHeight(0)
, m_iWidth(0)
, m_pBackBuffer(0)
, m_iLevel(0)
, m_iSoldiers(0)
, m_iSoldierIncrease(0)
, m_iFrame(0)
, m_iCannonPos(0)
, m_iNumBullets(14)
{

}
CGame::~CGame()
{
	delete m_pIniParser;
	m_pIniParser = 0;

	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
}
bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	bPauseGame = false;
	m_iSpawnTime = 200;
	m_iNumBullets = 14;

	SetCannonPos(300);
	m_iFrame = 0;

	//Loads different levels and sets the spawn time of soldiers.
	m_pIniParser = new CINIParser();
	if(m_iLevel == 0)
	{
		m_pIniParser->LoadIniFile("Level1");
		m_pIniParser->GetIntValue("Data", "SpawnTime", m_iSpawnTime);
	}
	else if(m_iLevel == 1)
	{
		m_pIniParser->LoadIniFile("Level2");
		m_pIniParser->GetIntValue("Data", "SpawnTime", m_iSpawnTime);
	}
	else if(m_iLevel == 2)
	{
		m_pIniParser->LoadIniFile("Level3");
		m_pIniParser->GetIntValue("Data", "SpawnTime", m_iSpawnTime);
	}

	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, m_iWidth, m_iHeight));

	//Initialises Lives, Cannon and ammo.
	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(m_iWidth, m_iHeight, m_iLevel));
	VALIDATE(m_pLevel->InitialiseCannon(m_iWidth / 2.0f));

	return (true);
}
bool
CGame::InitialiseCannon(int _iCannonPos)
{
	VALIDATE(m_pLevel->InitialiseCannon(GetCannonPos()));
	return (true);
}
bool
CGame::InitialiseBullet(int _iBulletStart)
{ 
	float m_fBulletVelX = 0;
	//Changes the angel of which the bullet is fired at.
		if(_iBulletStart == 315)
		{
			m_fBulletVelX = 100.0f;
		}
		else if(_iBulletStart == 285)
		{
			m_fBulletVelX = -100.0f;
		}
		else if(_iBulletStart == 330)
		{
			m_fBulletVelX = 150.0f;
		}
		else if(_iBulletStart == 270)
		{
			m_fBulletVelX = -150.0f;
		}
		else if(_iBulletStart == 345)
		{
			m_fBulletVelX = 200.0f;
		}
		else if(_iBulletStart == 255)
		{
			m_fBulletVelX = -200.0f;
		}
		else if(_iBulletStart == 360)
		{
			m_fBulletVelX = 300.0f;
		}
		else if(_iBulletStart == 240)
		{
			m_fBulletVelX = -300.0f;
			
		}

		//Initialises a bullet if the player has more than 0 bullets avaliable
		if(m_iNumBullets > 0)
		{
			--m_iNumBullets;
			m_pLevel->AmmoRemaining(m_iNumBullets, true);
			VALIDATE(m_pLevel->InitialiseBullet(_iBulletStart, m_fBulletVelX));		
		}
	return (true);
}
bool
CGame::InitialiseSoldier()
{
	VALIDATE(m_pLevel->InitialiseSoldier());
	return (true);
}
void 
CGame::Process(float _fDeltaTick)
{

	m_pLevel->Process(_fDeltaTick);
	
}
void 
CGame::Draw()
{

		m_pBackBuffer->Clear();

		m_pLevel->Draw();

		m_pBackBuffer->Present();

}
void 
CGame::ExecuteOneFrame()
{
	//Pauses game by skipping the excution.
	if(bPauseGame == false)
	{
		//iFrame is the amount which have been excuted.
		++m_iFrame;

		double fDT = m_pClock->GetDeltaTick();
			
		Process(fDT);
		Draw();

		SoldierProcess();

		m_pClock->Process();

		Sleep(1);
	}
}
void
CGame::SoldierProcess()
{
	
	//Initialises a Soldier.
  	if(m_iFrame == (m_iSpawnTime - m_iSoldierIncrease))
	{
		InitialiseSoldier();
	}	
	else if(m_iFrame == ((m_iSpawnTime + 1) - m_iSoldierIncrease))
	{
		//Adds another bullet which the player can fire.
		if(m_iNumBullets < 14)
		{
			m_pLevel->AmmoRemaining(m_iNumBullets, false);
			++m_iNumBullets;
			
		}

		//Increases the amount of soldiers which are parachuting down.
		++m_iSoldiers;
		if(m_iSoldiers == 5)
		{
			++m_iSoldierIncrease;
		}
		else if(m_iSoldiers == 6)		
		{
			m_iSoldiers = 0;
		}
		m_iFrame = 0;
	} 
}
CGame&
CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}

	return (*s_pGame);
}
void
CGame::GameOverWon()
{
	SetCannonPos(300);
	
	if(m_iLevel == 0)
	{
		MessageBox(m_hMainWindow, L"LEVEL 1 COMPLETE! \nAdvancing to level 2", L"LEVEL 1", MB_OK);
		m_iLevel = 1;
		Initialise(m_hApplicationInstance, m_hMainWindow, m_iWidth, m_iHeight);
	}
	else if(m_iLevel == 1)
	{

		MessageBox(m_hMainWindow, L"LEVEL 2 COMPLETE! \nAdvancing to level 3", L"LEVEL 2", MB_OK);
		m_iLevel = 2;
		Initialise(m_hApplicationInstance, m_hMainWindow, m_iWidth, m_iHeight);
	}
	else
	{
		m_iLevel = 0;
		Pause();
		MessageBox(m_hMainWindow, L"***WINNER***", L"Game Over", MB_OK);	
	}
}

void
CGame::GameOverLost()
{
	MessageBox(m_hMainWindow, L"***GAME OVER***", L"Game Over", MB_OK);
	Pause();
}
void
CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}
CBackBuffer*
CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

CLevel*
CGame::GetLevel()
{
	return (m_pLevel);
}

HINSTANCE
CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND
CGame::GetWindow()
{
	return (m_hMainWindow);
}
void 
CGame::SetSpawn(int _iSpawn)
{
	m_iSpawnTime = _iSpawn;
}
void 
CGame::SetCannonPos(int _iCannonPos)
{
	m_iCannonPos = _iCannonPos;
}
int
CGame::GetCannonPos() const
{
	return(m_iCannonPos);
}
void
CGame::Pause()
{
	if(bPauseGame == false)
	{
		bPauseGame = true;
	}
	else
	{
		bPauseGame = false;
	}

}
void
CGame::Instruction()
{
	MessageBox(m_hMainWindow, L"***INSTRUCTIONS***\n\nGoal of Cannon Blitz is too shoot"
		L" Parachuting Soldiers coming down the screen.\nIf a Soldier Reaches the bottom"
		L" the player loses a life.\nRotate the cannon in order to adjust the angel in which"
		L" you fire bullets at\n\n ***CONTROLS***\n SpaceBar == Shoot"
		L"\n Left Arrow == Cannon Rotates Left\n Right Arrow == Cannon Rotates Right"
		L"\n Pause == Pauses the game", L"Instructions", MB_OK);

}

