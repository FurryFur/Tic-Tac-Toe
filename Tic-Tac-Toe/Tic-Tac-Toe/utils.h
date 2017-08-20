//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>

// Local Includes

// Types

// Constants

// Prototypes

#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
    std::strstream theStream;
    theStream << _value << std::ends;
    return (theStream.str());
}

enum ETOKEN_TYPE {
	NOUGHT,
	CROSS,
	FREE
};

enum EPLAYER_TYPE
{
	HUMAN,
	COMPUTER
};

enum EWIN_STATE
{
	NOUGHT_WIN,
	CROSS_WIN,
	NO_WIN,
	DRAW
};

#endif    // __UTILS_H__

