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

// Local Includes
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"
#include "sprite.h"
#include "resource.h"


// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

const int CGame::s_kBoardOffsetX = 35;
const int CGame::s_kBoardOffsetY = 20;
const int CGame::s_kBoardDividerWidth = 10;
const int CGame::s_kBoardCellSize = 130;

// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
{
	for (size_t i = 0; i < m_board.size(); ++i)
	{
		for (size_t j = 0; j < m_board[i].size(); ++j)
		{
			m_board[i][j] = FREE;
		}
	}
}

bool CGame::CheckDiagWinCondition(bool offDiagonal)
{
	size_t r = 0;
	size_t c = 0;
	int deltac = 1;

	if (offDiagonal)
	{
		c = m_board.size() - 1;
		deltac = -1;
	}

	ECELL_STATE firstCell = m_board[r][c];
	for (; r < m_board.size() && c < m_board.size(); ++r, c += deltac)
	{
		if (m_board[r][c] == FREE || m_board[r][c] != firstCell)
		{
			return false;
		}
	}

	return true;
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
	//Load a new sprite.
	
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
				m_board[clickedCellRow][clickedCellCol] = NOUGHT;
			}
		}
	}
}

bool isValidBoardPos(int i, int j)
{
	return i >= 0 && i < 3 && j >= 0 && j < 3;
}

// Check if any element in a boolean array is set to true
template <size_t sz>
bool any(std::array<bool, sz> arr)
{
	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (arr[i])
		{
			return true;
		}
	}

	return false;
}

bool CGame::CheckWinCondition()
{
	// Check horizontal and vertical win condition
	std::array<bool, 3> vertWin{ true, true, true };
	for (int r = 0; r < 3; ++r)
	{
		ECELL_STATE firstCellH = m_board[r][0];

		bool horizWin = true;
		for (int c = 0; c < 3; ++c)
		{
			ECELL_STATE firstCellV = m_board[0][c];

			if (horizWin && (m_board[r][c] == FREE || m_board[r][c] != firstCellH))
			{
				horizWin = false;
			}
			if (vertWin[c] && (m_board[r][c] == FREE || m_board[r][c] != firstCellV))
			{
				vertWin[c] = false;
			}
		}

		if (horizWin)
		{
			return true;
		}
	}

	if (any(vertWin))
	{
		return true;
	}

	// Check diagonal win conditions
	if (CheckDiagWinCondition(false) || CheckDiagWinCondition(true))
	{
		return true;
	}

	return false;
}

//bool CGame::CheckWinCondition()
//{
//	for (int y = 0; y < m_board.size(); ++y)
//	{
//		for (int x = 0; x < m_board[0].size(); ++x)
//		{
//			// Get token type at location
//			ECELL_STATE cell_state = m_board[y][x];
//			if (cell_state != FREE)
//			{
//				// Iterate over 8 all directions
//				int xDir = 1;
//				int xDirDelta = -1;
//				int yDir = 0;
//				int yDirDelta = -1;
//				for (int k = 0; k < 8; ++k)
//				{
//					if (xDir + xDirDelta < -1 || xDir + xDirDelta > 1)
//					{
//						xDirDelta *= -1;
//					}
//					if (yDir + yDirDelta < -1 || yDir + yDirDelta > 1)
//					{
//						yDirDelta *= -1;
//					}
//
//					xDir += xDirDelta;
//					yDir += yDirDelta;
//
//					// Explore direction
//					int curX = x;
//					int curY = y;
//					size_t inARow = 0;
//					for (int l = 0; l < 3; ++l)
//					{
//						if (isValidBoardPos(curX, curY))
//						{
//							// Check if adjacent cell has same token type
//							if (m_board[curY][curX] == cell_state)
//							{
//								++inARow;
//							}
//							// Break loop when line of tokens is broken
//							else
//							{
//								break;
//							}
//						}
//						// Break at edges
//						else
//						{
//							break;
//						}
//
//						curX += xDir;
//						curY += yDir;
//					}
//
//					// If we found 3 in a row then someone won
//					if (inARow == 3)
//					{
//						return true;
//					}
//				}
//			}
//		}
//	}
//
//	return false;
//}

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
