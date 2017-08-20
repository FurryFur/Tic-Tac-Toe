//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: game.h
// Description	: Header file for CGame class
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#define NOMINMAX
#include <windows.h>
#include <array>

// Local Includes
#include "clock.h"
#include "sprite.h"
#include "GameState.h"
#include "utils.h"

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

    void Draw();
    void Process(float _fDeltaTick);

    void ExecuteOneFrame();

    CBackBuffer* GetBackBuffer();
    HINSTANCE GetAppInstance();
    HWND GetWindow();

    // Singleton Methods
    static CGame& GetInstance();
    static void DestroyInstance();

	/// <summary>
	/// Handles the click.
	/// </summary>
	void HandleClick();

	/// <summary>
	/// Gets the state of the win.
	/// </summary>
	/// <returns>A win state (can be NO_WIN to represent the case where noone has won yet)</returns>
	EWIN_STATE GetWinState();

	/// <summary>
	/// Sets the play mode.
	/// </summary>
	/// <param name="playMode">The play mode.</param>
	void SetPlayMode(EPLAY_MODE playMode);

	/// <summary>
	/// Restarts this instance.
	/// </summary>
	void Restart();
	
	/// <summary>
	/// Gets the player token for <paramref name="playerId"/>.
	/// </summary>
	/// <param name="playerId">The player identifier.</param>
	/// <returns>The player token for <paramref name="playerId"/>.</returns>
	static ETOKEN_TYPE GetPlayerToken(size_t playerId);

protected:

private:
    CGame();
    CGame(const CGame& _kr);
    CGame& operator= (const CGame& _kr);

	/// <summary>
	/// Checks the diagonal for a win condition.
	/// </summary>
	/// <param name="offDiagonal">if set to <c>true</c> checks the off diagonal for a win condition.</param>
	/// <returns>A win state (can be NO_WIN to represent the case where noone has won yet)</returns>
	EWIN_STATE CheckDiagWinCondition(bool offDiagonal = false);

    // Member Variables
public:

protected:
    CClock* m_pClock;

    CBackBuffer* m_pBackBuffer;

	CGameState m_state;
	CSprite m_boardSprite;
	CSprite m_noughtSprite;
	CSprite m_crossSprite;

	std::array<EPLAYER_TYPE, 2> m_turnOrder;
	EPLAY_MODE m_playMode;

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
