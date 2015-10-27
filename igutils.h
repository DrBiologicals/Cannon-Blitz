#ifndef __IGUTILS_H__
#define __IGUTILS_H__

#include <strstream>
#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

#endif // __IGUTILS_H__