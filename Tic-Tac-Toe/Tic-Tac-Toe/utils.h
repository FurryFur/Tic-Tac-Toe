//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: utils.h
// Description	: Collection of header only functions and enum definitions
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
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

enum EPLAY_MODE
{
	PVP,
	VS_AI_EASY,
	VS_AI_HARD
};

#endif    // __UTILS_H__

