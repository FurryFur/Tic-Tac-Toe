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

// Library Includes
#include <algorithm>
#include <random>

// Local Includes
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"
#include "sprite.h"
#include "resource.h"
#include "AIUtil.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

const int CGame::s_kBoardOffsetX = 35;
const int CGame::s_kBoardOffsetY = 20;
const int CGame::s_kBoardDividerWidth = 10;
const int CGame::s_kBoardCellSize = 130;
const std::array<ETOKEN_TYPE, 2> s_kPlayerTokens = { CROSS, NOUGHT };

// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_state{ m_board }
, m_turnOrder{ COMPUTER, HUMAN }
, m_playMode{ VS_AI_HARD }
{
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		for (size_t j = 0; j < m_board[i].size(); ++j)
		{
			m_board[i][j] = FREE;
		}
	}
}

CGame::~CGame()
{
    delete m_pBackBuffer;
    m_pBackBuffer = 0;

    delete m_pClock;
    m_pClock = 0;
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hApplicationInstance = _hInstance;
    m_hMainWindow = _hWnd;

    m_pClock = new CClock();
    VALIDATE(m_pClock ->Initialise());
    m_pClock->Process();

    m_pBackBuffer = new CBackBuffer();
    VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_boardSprite.Initialise(IDB_BOARD, IDB_BOARD_MASK);
	m_noughtSprite.Initialise(IDB_NOUGHT, IDB_NOUGHT_MASK);
	m_crossSprite.Initialise(IDB_CROSS, IDB_CROSS_MASK);

	m_boardSprite.SetX(s_kBoardOffsetX);
	m_boardSprite.SetY(s_kBoardOffsetY);

	//m_board[1][1] = CROSS;

    return (true);
}

void
CGame::Draw()
{
    m_pBackBuffer->Clear();

// Do all the game’s drawing here...
	m_boardSprite.Draw();

	int yOffset = s_kBoardOffsetY;
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		int xOffset = s_kBoardOffsetX;
		for (size_t j = 0; j < m_board[i].size(); ++j)
		{
			// Select token to draw
			CSprite* pCurSprite = nullptr;
			if (m_board[i][j] == NOUGHT)
			{
				pCurSprite = &m_noughtSprite;
			}
			else if (m_board[i][j] == CROSS)
			{
				pCurSprite = &m_crossSprite;
			}

			// Draw player token
			if (pCurSprite != nullptr)
			{
				pCurSprite->SetX(xOffset);
				pCurSprite->SetY(yOffset);
				pCurSprite->Draw();
			}

			xOffset += s_kBoardCellSize + s_kBoardDividerWidth;
		}
		yOffset += s_kBoardCellSize + s_kBoardDividerWidth;
	}

    m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
    // Process all the game’s logic here.
	
	static std::random_device s_rd;
	static std::mt19937 s_rng{ s_rd() };

	if (m_turnOrder[m_state.Turn()] == COMPUTER && !m_state.IsTerminal())
	{
		size_t actionId;

		if (m_playMode == VS_AI_HARD)
		{
			AIUtil::Minimax(m_state, &actionId);
		}
		else
		{
			std::uniform_int_distribution<size_t> uni(0, m_state.NumActionsAvailable());
			actionId = uni(s_rng);
		}

		m_state.PerformAction(actionId);
	}
}

void 
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

    Process(fDT);
    Draw();

    m_pClock->Process();

    Sleep(1);
}

CGame&
CGame::GetInstance()
{
    if (s_pGame == 0)
    {
        s_pGame = new CGame();
    }

    return (*s_pGame);
}

void 
CGame::DestroyInstance()
{
    delete s_pGame;
    s_pGame = 0;
}

void CGame::HandleClick()
{
	if (m_turnOrder[m_state.Turn()] == COMPUTER)
		return;

	POINT p;
	if (GetCursorPos(&p))
	{
		if (ScreenToClient(m_hMainWindow, &p))
		{
			int clickedCellCol = (p.x - (s_kBoardOffsetX - s_kBoardDividerWidth / 2)) / (s_kBoardCellSize + s_kBoardDividerWidth);
			int clickedCellRow = (p.y - (s_kBoardOffsetY - s_kBoardDividerWidth / 2)) / (s_kBoardCellSize + s_kBoardDividerWidth);

			// Clamp
			clickedCellCol = clickedCellCol < 0 ? 0 : clickedCellCol;
			clickedCellCol = clickedCellCol > 2 ? 2 : clickedCellCol;
			clickedCellRow = clickedCellRow < 0 ? 0 : clickedCellRow;
			clickedCellRow = clickedCellRow > 2 ? 2 : clickedCellRow;

			if (m_board[clickedCellRow][clickedCellCol] == FREE)
			{
				m_state.PerformAction({ static_cast<size_t>(clickedCellRow), static_cast<size_t>(clickedCellCol) });
			}
		}
	}
}

EWIN_STATE CGame::CheckDiagWinCondition(bool offDiagonal)
{
	size_t r = 0;
	size_t c = 0;
	int deltac = 1;

	if (offDiagonal)
	{
		c = m_board.size() - 1;
		deltac = -1;
	}

	ETOKEN_TYPE firstCell = m_board[r][c];
	for (; r < m_board.size() && c < m_board.size(); ++r, c += deltac)
	{
		if (m_board[r][c] == FREE || m_board[r][c] != firstCell)
		{
			return NO_WIN;
		}
	}

	return static_cast<EWIN_STATE>(firstCell);
}

EWIN_STATE CGame::CheckWinCondition()
{
	// Check horizontal and vertical win condition
	bool draw = true;
	std::array<bool, 3> vertWin{ true, true, true };
	for (int r = 0; r < 3; ++r)
	{
		ETOKEN_TYPE firstCellH = m_board[r][0];

		bool horizWin = true;
		for (int c = 0; c < 3; ++c)
		{
			ETOKEN_TYPE firstCellV = m_board[0][c];

			if (m_board[r][c] == FREE)
			{
				horizWin = false;
				vertWin[c] = false;
				draw = false;
			}
			else
			{
				if (m_board[r][c] != firstCellH)
				{
					horizWin = false;
				}
				if (m_board[r][c] != firstCellV)
				{
					vertWin[c] = false;
				}
			}
		}

		if (horizWin)
		{
			return static_cast<EWIN_STATE>(firstCellH);
		}
	}
	
	for (size_t c = 0; c < 3; ++c)
	{
		if (vertWin[c])
		{
			return static_cast<EWIN_STATE>(m_board[0][c]);
		}
	}

	if (CheckDiagWinCondition(false) != NO_WIN || CheckDiagWinCondition(true) != NO_WIN)
	{
		return static_cast<EWIN_STATE>(m_board[1][1]);
	}

	if (draw)
	{
		return DRAW;
	}

	return NO_WIN;
}

void CGame::SetPlayMode(EPLAY_MODE playMode)
{
	m_playMode = playMode;

	switch (playMode)
	{
	case PVP:
		m_turnOrder = { HUMAN, HUMAN };
		break;
	case VS_AI_EASY:
		m_turnOrder = { COMPUTER, HUMAN };
		break;
	case VS_AI_HARD:
		m_turnOrder = { COMPUTER, HUMAN };
		break;
	default:
		break;
	}
}

ETOKEN_TYPE CGame::GetPlayerToken(size_t playerId)
{
	return s_kPlayerTokens.at(playerId);
}

CBackBuffer* 
CGame::GetBackBuffer()
{
    return (m_pBackBuffer);
}

HINSTANCE 
CGame::GetAppInstance()
{
    return (m_hApplicationInstance);
}

HWND 
CGame::GetWindow()
{
    return (m_hMainWindow);
}
