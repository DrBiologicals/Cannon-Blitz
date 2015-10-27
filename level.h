#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>


// Local Includes
// Types

// Constants

// Prototypes
class CBullet;
class CCannon;
class CSoldier;
class CLife;
class CAmmo;
class CBackground;

class CLevel
{
    // Member Functions
public:
	CLevel();
	virtual ~CLevel();

	virtual bool Initialise(int _iWidth, int _iHeight, int _iLevel);
	virtual bool InitialiseCannon(int _iCannon);
	virtual bool InitialiseBullet(int _iBulletStart, float _fBulletVelX);
	virtual bool InitialiseSoldier();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void NumSoldiers(int _iSoldiers);
	void NumLives(int _iLives);
	void SetSpeed(float _fSoldier);
	void BulletVelY(float _fVelY);

	void AmmoRemaining(int _iAmmo, bool _bAmmoFired);

protected:
	void ProcessBulletWallCollision();
	void ProcessBulletSoldierCollision();
	void ProcessSoldierGroundCollision();
	
	void CheckForWin();

	void UpdateScoreText();
	void DrawScore();

private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	std::vector<CBullet*> m_vecBullet;
	CCannon* m_pCannon;
	CBackground* m_pBackground;
	std::vector<CAmmo*> m_vecAmmo;
	std::vector<CSoldier*> m_vecSoldier;
	std::vector<CLife*> m_vecLife;

	int m_iWidth;
	int m_iHeight;
	int m_iLevel;
	int m_iBulletPos;

	float m_fBulletVelX;

	bool bBullet;
	bool bLifeDebug;
	bool bPause;

	std::string m_strScore;

private:

};

#endif // __LEVEL_H__
