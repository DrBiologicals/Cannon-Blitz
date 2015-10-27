#pragma once

#if !defined(__CANNON_H__)
#define __CANNON_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"
// Types

// Constants

// Prototypes


class CCannon : public CEntity
{
    // Member Functions
public:
	CCannon();
	virtual ~CCannon();

	virtual bool Initialise(int _iCannon);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:

private:
	CCannon(const CCannon& _kr);
	CCannon& operator= (const CCannon& _kr);
    // Member Variables
public:

protected:

private:

};

#endif // __CANNON_H__
