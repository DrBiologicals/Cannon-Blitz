#pragma once

#if !defined(__BACKGROUND_H__)
#define __BACKGROUND_H__

// Library Includes

// Local Includes
#include "entity.h"
// Types

// Constants

// Prototypes

class CBackground : public CEntity
{
    // Member Functions
public:
	CBackground();
	virtual ~CBackground();

	virtual bool Initialise(float _fPosX, float _fPosY, int _iLevel);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:

private:
	CBackground (const CBackground & _kr);
	CBackground & operator= (const CBackground & _kr);

    // Member Variables
public:
	int m_iLevel;

protected:

private:

};

#endif // __BACKGROUND_H__