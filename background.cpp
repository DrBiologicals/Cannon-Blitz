#include "resource.h"
#include "igutils.h"

#include "background.h"

CBackground::CBackground()
: m_iLevel(0)
{

}
CBackground::~CBackground()
{

}
bool
CBackground::Initialise(float _fPosX, float _fPosY, int _iLevel)
{
	m_iLevel = _iLevel;

	VALIDATE(CEntity::Initialise(IDB_BACKGROUND, IDB_BACKGROUNDMASK));

	m_fX = _fPosX;
	m_fY = _fPosY;

	return(true);
}
void
CBackground::Draw()
{
	CEntity::Draw();
}
void
CBackground::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
	
}