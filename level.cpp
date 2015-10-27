#include "game.h"
#include "cannon.h"
#include "soldier.h"
#include "bullet.h"
#include "life.h"
#include "ammo.h"
#include "background.h"
#include "igutils.h"
#include "BackBuffer.h"

#include "level.h"

#include <cmath>

int m_iLivesRemaining = 0;
int m_iSoldiersRemaining = 0;
float m_fBulletVelY = 0.0f;
float m_fSoldierVelY = 0.0f;
CLevel::CLevel()
: m_pCannon(0)
, m_iWidth(0)
, m_iHeight(0)
, m_iBulletPos(0)
, m_iLevel(0)
, m_fBulletVelX(0)
, m_pBackground(0)
, bPause(false)
, bBullet(false)
, bLifeDebug(false)
{

}

CLevel::~CLevel()
{
	while (m_vecSoldier.size() > 0)
	{
		CSoldier* pSoldier = m_vecSoldier[m_vecSoldier.size() - 1];

		m_vecSoldier.pop_back();

		delete pSoldier;
	}

	delete m_pCannon;
	m_pCannon = 0;

	while (m_vecBullet.size() > 0)
	{
		CBullet* pBullet = m_vecBullet[m_vecBullet.size() - 1];

		m_vecBullet.pop_back();

		delete pBullet;
	}
	while (m_vecLife.size() > 0)
	{
		CLife* pLife = m_vecLife[m_vecLife.size() - 1];

		m_vecLife.pop_back();

		delete pLife;
	}
	while (m_vecAmmo.size() > 0)
	{
		CAmmo* pAmmo = m_vecAmmo[m_vecAmmo.size() - 1];

		m_vecAmmo.pop_back();

		delete pAmmo;
	}
}
bool
CLevel::Initialise(int _iWidth, int _iHeight, int _iLevel)
{
	m_iLevel = _iLevel;

	m_fSoldierVelY = 50.0f;
	m_fBulletVelY = 200.0f;

	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	//Initialises the background sprite.
	m_pBackground = new CBackground();
	VALIDATE(m_pBackground->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, m_iLevel));

	m_iLivesRemaining = 3;
	m_iSoldiersRemaining = 100;

	const int kiStartY = 500;
	const int kiStartX = 20;
	const int kiGap = 1;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartY;

	//Initialises the Lives.
	for (int i = 0; i < m_iLivesRemaining; ++i)
	{
		CLife* pLife = new CLife();
		VALIDATE(pLife->Initialise());

		pLife->SetX(static_cast<float>(iCurrentX));
		pLife->SetY(static_cast<float>(iCurrentY));

		iCurrentX += static_cast<int>(pLife->GetWidth()) + kiGap;

		m_vecLife.push_back(pLife);
	}

	const int m_iAmmoRemaining = 14;
	const int kiAmmoY = 540;
	const int kiAmmoX = 500;
	
	int iAmmoX = kiAmmoY;
	int iAmmoY = kiAmmoX;

	//Initialises the Ammo.
	for (int i = 1; i <= m_iAmmoRemaining; ++i)
	{
		CAmmo* pAmmo = new CAmmo();
		VALIDATE(pAmmo->Initialise());

		pAmmo->SetX(static_cast<float>(iAmmoX));
		pAmmo->SetY(static_cast<float>(iAmmoY));

		iAmmoX += static_cast<int>(pAmmo->GetWidth()) + kiGap;

		if (iAmmoX > (_iWidth - 5))
		{
			iAmmoX = 540;
			iAmmoY += 20;
		}

		m_vecAmmo.push_back(pAmmo);
	}
	return(true);
}
bool
CLevel::InitialiseCannon(int _iCannon)
{
	//Initialises the cannon, cannon sprite varies depending on the value in _iCannon.
	m_pCannon = new CCannon();
	VALIDATE(m_pCannon->Initialise(_iCannon));

	m_pCannon->SetX(m_iHeight / 2.0f);
	m_pCannon->SetY(m_iHeight - ( 2 * m_pCannon->GetHeight()));

	return (true);
}
bool 
CLevel::InitialiseBullet(int _iBulletStart, float _fBulletVelX)
{
	bBullet = true;

	m_iBulletPos = _iBulletStart;
	m_fBulletVelX = _fBulletVelX;
	
	CBullet* m_pBullet = new CBullet();
	VALIDATE(m_pBullet->Initialise(m_iBulletPos, m_iHeight / 1.4f, m_fBulletVelX, m_fBulletVelY));

	m_vecBullet.push_back(m_pBullet);

	return(true);
}
bool
CLevel::InitialiseSoldier()
{
	int m_fSoldierWidth = rand() % 590;
	const float m_fSoldierVelX = 0.0f;
	const float m_fSoldierHeight = 0.0f;

	CSoldier* pSoldier = new CSoldier();
	VALIDATE(pSoldier->InitialiseAlive(m_fSoldierWidth, m_fSoldierHeight, m_fSoldierVelX, m_fSoldierVelY, m_iLevel));

	m_vecSoldier.push_back(pSoldier);
	
	
	return (true);
}
void
CLevel::Draw()
{

		m_pBackground->Draw();
		m_pCannon->Draw();
		for (unsigned int i = 0; i < m_vecLife.size(); ++i)
		{
			m_vecLife[i]->Draw();
		}	
		for (unsigned int i = 0; i < m_vecSoldier.size(); ++i)
		{
			m_vecSoldier[i]->Draw();
		}
		for (unsigned int i = 0; i < m_vecAmmo.size(); ++i)
		{
			m_vecAmmo[i]->Draw();
		}
		if(bBullet == true)
		{
			for (unsigned int i = 0; i < m_vecBullet.size(); ++i)
			{
 				m_vecBullet[i]->Draw();
			}
		}
		DrawScore();

}

void
CLevel::Process(float _fDeltaTick)
{

		CheckForWin();
 		ProcessSoldierGroundCollision();
		if(bBullet == true)
		{
			ProcessBulletWallCollision();
			ProcessBulletSoldierCollision();
			for (unsigned int i = 0; i < m_vecBullet.size(); ++i)
			{
				 m_vecBullet[i]->Process(_fDeltaTick);
			}
	 		
		}
		for (unsigned int i = 0; i < m_vecSoldier.size(); ++i)
		{
			m_vecSoldier[i]->Process(_fDeltaTick);
		}
		for (unsigned int i = 0; i < m_vecLife.size(); ++i)
		{
			m_vecLife[i]->Process(_fDeltaTick);
		}
		for (unsigned int i = 0; i < m_vecAmmo.size(); ++i)
		{
			m_vecAmmo[i]->Process(_fDeltaTick);
		}
		m_pCannon->Process(_fDeltaTick);
		m_pBackground->Process(_fDeltaTick);

		UpdateScoreText();

 }

void
CLevel::ProcessBulletWallCollision()
{
	float fBulletX = 0.0f;
	float fBulletY = 0.0f;
	float fBulletW = 0.0f;
	float fBulletH = 0.0f;

	float fHalfBulletW = 0.0f;

	for (unsigned int i = 0; i < m_vecBullet.size(); ++i)
	{
		fBulletX = m_vecBullet[i]->GetX();
		fBulletY = m_vecBullet[i]->GetY();
		fBulletW = m_vecBullet[i]->GetWidth();
		fBulletH = m_vecBullet[i]->GetHeight();

		fHalfBulletW = fBulletW / 2;

		if(fBulletX < fHalfBulletW)
		{
			m_vecBullet[i]->SetCollision(true);
		}
		else if (fBulletX > m_iWidth - fHalfBulletW)
		{
			m_vecBullet[i]->SetCollision(true);
		}

		if (fBulletY < 0)
		{
			m_vecBullet[i]->SetCollision(true);
		}
	}
}

void
CLevel::ProcessBulletSoldierCollision()
{  

	for (unsigned int i = 0; i < m_vecSoldier.size(); ++i)
	{	
		for (unsigned int j = 0; j < m_vecBullet.size(); ++j)
		{
			if (!m_vecSoldier[i]->IsHit())
			{ 
				float fBulletR = m_vecBullet[j]->GetRadius();

				float fBulletX = m_vecBullet[j]->GetX();
				float fBulletY = m_vecBullet[j]->GetY();

				float fSoldierX = m_vecSoldier[i]->GetX();
				float fSoldierY = m_vecSoldier[i]->GetY();

				float fSoldierH = m_vecSoldier[i]->GetHeight();
				float fSoldierW = m_vecSoldier[i]->GetWidth();

				if ((fBulletX + fBulletR > fSoldierX - fSoldierW / 2) &&
					(fBulletX - fBulletR < fSoldierX + fSoldierW / 2) &&
					(fBulletY + fBulletR > fSoldierY - fSoldierH / 2) &&
					(fBulletY - fBulletR < fSoldierY + fSoldierH / 2))
				{
					//Hit the Soldier...
					if(!m_vecBullet[j]->GetCollision() == true)
					{
						m_vecBullet[j]->SetCollision(true);
					
						m_vecSoldier[i]->InitialiseDead();
						m_vecSoldier[i]->SetHit(true);

						--m_iSoldiersRemaining;
					}
						
				}
			}
		}
		
	}
}

void
CLevel::ProcessSoldierGroundCollision()
{

	for (unsigned int i = 0; i < m_vecSoldier.size(); ++i)
	{
		if(m_vecSoldier[i]->GetY() > 450)
		{
			if(m_vecSoldier[i]->IsHit() == false)
			{
				m_iLivesRemaining -= 1;
				if(bLifeDebug == false)
				{
					m_vecLife[m_iLivesRemaining]->SetLife(true);
				}
				m_vecSoldier[i]->SetHit(true);

				--m_iSoldiersRemaining;
			}
		}
	}
	if(m_iLivesRemaining == 0)
	{ 
		CGame::GetInstance().GameOverLost();
	}
}
void
CLevel::CheckForWin()
{
	if(m_iSoldiersRemaining == 0)
	{
		CGame::GetInstance().GameOverWon();
	}
}
void
CLevel::AmmoRemaining(int _iAmmo, bool _bAmmoFired)
{
	m_vecAmmo[_iAmmo]->SetAmmo(_bAmmoFired);
}
void
CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBackDC();

	const int kiX = 0;
	const int kiY = 0;

	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void
CLevel::UpdateScoreText()
{
	m_strScore = "Soldiers Remaining : ";
	m_strScore += ToString(m_iSoldiersRemaining);
}
void
CLevel::SetSpeed(float _fSoldier)
{
	m_fSoldierVelY = _fSoldier;

}
void
CLevel::BulletVelY(float _fVelY)
{
	m_fBulletVelY = _fVelY;
}
void
CLevel::NumLives(int _iLives)
{
	m_iLivesRemaining = _iLives;
	bLifeDebug = true;
}
void
CLevel::NumSoldiers(int _iSoldiers)
{
	m_iSoldiersRemaining = _iSoldiers;
}




