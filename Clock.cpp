//Local Includes

//This Includes
#include "clock.h"

CClock::CClock()
: m_fDeltaTick(0.0f)
, m_fTimeElapsed(0.0f)
{

}

CClock::~CClock()
{
}

float
CClock::GetDeltaTick()
{
	return (m_fDeltaTick);
}

float
CClock::GetTimeElapsed()
{
	return (m_fTimeElapsed);
}