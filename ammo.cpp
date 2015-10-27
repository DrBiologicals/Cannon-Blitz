#include "resource.h"
#include "igutils.h"

#include "ammo.h"

CAmmo::CAmmo()
: m_bAmmoLost(false)
{

}
CAmmo::~CAmmo()
{

}
bool
CAmmo::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_AMMO, IDB_AMMOMASK));

	return(true);
}
void
CAmmo::Draw()
{
	if (!m_bAmmoLost)
	{
		CEntity::Draw();
	}
}
void
CAmmo::Process(float _fDeltaTick)
{
	if (!m_bAmmoLost)
	{
		CEntity::Process(_fDeltaTick);
	}
}
void
CAmmo::SetAmmo(bool _b)
{
	m_bAmmoLost = _b;
}
bool
CAmmo::AmmoLost() const
{
	return(m_bAmmoLost);
}