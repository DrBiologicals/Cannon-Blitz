#pragma once

#if !defined(__AMMO_H__)
#define __AMMO_H__

// Library Includes

// Local Includes
#include "entity.h"
// Types

// Constants

// Prototypes

class CAmmo : public CEntity
{
    // Member Functions
public:
	CAmmo();
	virtual ~CAmmo();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetAmmo(bool _b);
	bool AmmoLost() const;


protected:

private:
	CAmmo(const CAmmo& _kr);
	CAmmo& operator= (const CAmmo& _kr);

    // Member Variables
public:

protected:
	bool m_bAmmoLost;

private:

};

#endif // __AMMO_H__