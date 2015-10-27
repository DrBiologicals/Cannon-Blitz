#pragma once

#if !defined(__LIFE_H__)
#define __LIFE_H__

// Library Includes

// Local Includes
#include "entity.h"
// Types

// Constants

// Prototypes

class CLife : public CEntity
{
    // Member Functions
public:
	CLife();
	virtual ~CLife();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetLife(bool _b);
	bool LifeLost() const;


protected:

private:
	CLife(const CLife& _kr);
	CLife& operator= (const CLife& _kr);

    // Member Variables
public:

protected:
	bool m_bLifeLost;

private:

};

#endif // __LIFE_H__