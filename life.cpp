#include "resource.h"
#include "igutils.h"

#include "life.h"

CLife::CLife()
: m_bLifeLost(false)
{

}
CLife::~CLife()
{

}
bool
CLife::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_LIFE, IDB_LIFEMASK));

	return(true);
}
void
CLife::Draw()
{
	if (!m_bLifeLost)
	{
		CEntity::Draw();
	}
}
void
CLife::Process(float _fDeltaTick)
{
	if (!m_bLifeLost)
	{
		CEntity::Process(_fDeltaTick);
	}
}
void
CLife::SetLife(bool _b)
{
	m_bLifeLost = _b;
}
bool
CLife::LifeLost() const
{
	return(m_bLifeLost);
}