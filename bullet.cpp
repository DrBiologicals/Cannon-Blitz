#include "resource.h"
#include "igutils.h"

#include "bullet.h"

CBullet::CBullet()
: m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
, m_bCollision(false)
{

}

CBullet::~CBullet()
{
	
}

bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
	VALIDATE(CEntity::Initialise(IDB_BULLET, IDB_BULLETMASK));

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityX = _fVelocityX;
	m_fVelocityY = _fVelocityY;

	return (true);
}

void
CBullet::Draw()
{
	if(!m_bCollision)
	{
		CEntity::Draw();
	}
}

void
CBullet::Process(float _fDeltaTick)
{

	m_fX += m_fVelocityX * _fDeltaTick;
	m_fY -= m_fVelocityY * _fDeltaTick;

	CEntity::Process(_fDeltaTick);
	
}
void
CBullet::SetCollision(bool _b)
{
	m_bCollision = _b;
}

bool
CBullet::GetCollision() const
{
	return (m_bCollision);
}
float
CBullet::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CBullet::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CBullet::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}

void
CBullet::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

float
CBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}