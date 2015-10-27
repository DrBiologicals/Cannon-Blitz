#include "resource.h"
#include "igutils.h"

#include "soldier.h"

CSoldier::CSoldier()
: m_bHit(false)
, m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
, m_iFrame(1)
, m_iLevel(0)
{

}

CSoldier::~CSoldier()
{

}

bool
CSoldier::InitialiseAlive(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY, int _iLevel)
{
	m_iLevel = _iLevel;

	VALIDATE(CEntity::Initialise(IDB_SOLDIERALIVE, IDB_SOLDIERALIVEMASK));

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityX = _fVelocityX;
	m_fVelocityY = _fVelocityY;

	return (true);
}
bool
CSoldier::InitialiseDead()
{
	if(m_iFrame >= 1)
	{
		m_iFrame = 0;
	}

	VALIDATE(CEntity::Initialise(IDB_SOLDIERDEAD, IDB_SOLDIERDEADMASK));

	return (true);
}
void
CSoldier::Draw()
{
	if(m_iFrame < 50)
	{		
		CEntity::Draw();
		++m_iFrame;
	}
	else if (!m_bHit)
	{
		CEntity::Draw();
	}
}
void
CSoldier::Process(float _fDeltaTick)
{
	if (m_iFrame < 50)
	{
		m_fX += m_fVelocityX * _fDeltaTick;
		m_fY += m_fVelocityY * _fDeltaTick;
		CEntity::Process(_fDeltaTick);	
	}
	else if (!m_bHit)
	{
		m_fX += m_fVelocityX * _fDeltaTick;
		m_fY += m_fVelocityY * _fDeltaTick;
		CEntity::Process(_fDeltaTick);
	}
}

void
CSoldier::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CSoldier::IsHit() const
{


	return (m_bHit);
}
float
CSoldier::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CSoldier::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CSoldier::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}

void
CSoldier::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}
