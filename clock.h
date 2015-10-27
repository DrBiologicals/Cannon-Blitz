#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

class CClock
{
public:
	//Construct and Destruct
	CClock();
	virtual ~CClock();

	//Initialises input
	virtual bool Initialise() = 0;

	//Starts the clock processing
	virtual void Process() = 0;

	//Gets the delta tick
	float GetDeltaTick();
	float GetTimeElapsed();

private:
	CClock(const CClock& _kr);
	CClock& operator=(const CClock& _kr);
public:
		//************************************ MEMBER VARIABLES *******************************
	float m_fDeltaTick;
	float m_fTimeElapsed;
protected:

};

#endif //__CLOCK_H__