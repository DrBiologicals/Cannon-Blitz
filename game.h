#pragma once

#if !defined __GAME_H__
#define __GAME_H__

#include <windows.h>

#include "Clock.h"
#include "CINIParser.h"

class CLevel;
class CBackBuffer;

class CGame
{
public:
	
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);
	virtual bool InitialiseCannon(int _iCannonPos);
	virtual bool InitialiseBullet(int _iBulletStart);
	virtual bool InitialiseSoldier();

	virtual void Process(float _fDeltTick);
	virtual void Draw();
	virtual void Pause();

	void ExecuteOneFrame();

	void SoldierProcess();

	CBackBuffer* GetBackBuffer();
	CLevel* GetLevel();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	void GameOverWon();
	void GameOverLost();

	void SetSpawn(int _iSpawn);
	void SetCannonPos(int _iCannonPos);

	int GetCannonPos() const;

	void Instruction();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

private:
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

protected:
	//Singleton instance
	static CGame* s_pGame;

	int m_iFrame;
	int m_iNumBullets;
	int m_iHeight;
	int m_iWidth;
	int m_iLevel;
	int m_iSoldiers;
	int m_iSoldierIncrease;
	int m_iCannonPos;

	CClock* m_pClock;
	CLevel* m_pLevel;
	CINIParser* m_pIniParser;

	CBackBuffer* m_pBackBuffer;

	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

};
#endif // __GAME_H__
