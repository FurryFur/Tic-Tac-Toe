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

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <array>

// Local Includes
#include "clock.h"
#include "sprite.h"

// Types

// Constants

// Prototypes
class CBackBuffer;

class CGame
{
    // Member Functions
public:
    ~CGame();

    bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	enum ECELL_STATE {
		NOUGHT,
		CROSS,
		FREE
	};

    void Draw();
    void Process(float _fDeltaTick);

    void ExecuteOneFrame();

    CBackBuffer* GetBackBuffer();
    HINSTANCE GetAppInstance();
    HWND GetWindow();

    // Singleton Methods
    static CGame& GetInstance();
    static void DestroyInstance();

	void HandleClick();
	bool CheckWinCondition();

protected:

private:
    CGame();
    CGame(const CGame& _kr);
    CGame& operator= (const CGame& _kr);

	// Check for a win condition along the specified diagonal
	// offDiagonal: true or false, whether we are checking the off diagonal for the win condition
	bool CheckDiagWinCondition(bool offDiagonal = false);

    // Member Variables
public:

protected:
    CClock* m_pClock;

    CBackBuffer* m_pBackBuffer;

	std::array<std::array<ECELL_STATE, 3>, 3> m_board;
	CSprite m_boardSprite;
	CSprite m_noughtSprite;
	CSprite m_crossSprite;

	static const int s_kBoardOffsetX;
	static const int s_kBoardOffsetY;
	static const int s_kBoardDividerWidth;
	static const int s_kBoardCellSize;

    //Application data
    HINSTANCE m_hApplicationInstance;
    HWND m_hMainWindow;

    // Singleton Instance
    static CGame* s_pGame;

private:

};

#endif    // __GAME_H__
