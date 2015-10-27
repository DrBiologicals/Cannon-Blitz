#include "resource.h"
#include "igutils.h"

#include "cannon.h"

CCannon::CCannon()
{

}

CCannon::~CCannon()
{

}

bool
CCannon::Initialise(int _iCannon)
{
	if(_iCannon == 300)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON90, IDB_CANNON90MASK));
	}
	else if(_iCannon == 315)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON105, IDB_CANNON105MASK));
	}
	else if(_iCannon == 330)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON120, IDB_CANNON120MASK));
	}
	else if(_iCannon == 345)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON135, IDB_CANNON135MASK));
	}
	else if(_iCannon == 360)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON150, IDB_CANNON150MASK));
	}
	else if(_iCannon == 285)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON75, IDB_CANNON75MASK));
	}
	else if(_iCannon == 270)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON60, IDB_CANNON60MASK));
	}
	else if(_iCannon == 255)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON45, IDB_CANNON45MASK));
	}
	else if(_iCannon == 240)
	{
		VALIDATE(CEntity::Initialise(IDB_CANNON30, IDB_CANNON30MASK));
	}

	return (true);
}

void
CCannon::Draw()
{
	CEntity::Draw();
}

void
CCannon::Process(float _fDeltaTick)
{

	CEntity::Process(_fDeltaTick);
}