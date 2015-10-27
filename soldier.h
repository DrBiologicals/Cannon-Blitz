#pragma once

#if !defined(__SOLDIER_H__)
#define __SOLDIER_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CSoldier : public CEntity
{
    // Member Functions
public:
	CSoldier();
	virtual ~CSoldier();

	virtual bool InitialiseAlive(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY, int _iLevel);
	virtual bool InitialiseDead();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;

	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float _fX);
	void SetVelocityY(float _fY);

protected:

private:
	CSoldier(const CSoldier& _kr);
	CSoldier& operator= (const CSoldier& _kr);

    // Member Variables
public:

protected:
	int m_iFrame;
	int m_iLevel;
	bool m_bHit;
	float m_fVelocityX;
	float m_fVelocityY;

private:

};

#endif // __SOLDIER_H__
