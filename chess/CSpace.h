#pragma once
#include "ChessTypeDef.h"

class CSpace
{
public:
	CSpace();
	CSpace(int i, int j, int x, int y, int spaceNum);
	void unitClear();


public:
	void getSpaceIndex(int& x, int& y);
	void changeCoorToNum(int& coor);
	bool isValidClick(const Team turn, bool firstClick);
	bool canMove();
	
	bool pawnMove();
	bool rookMove();
	bool knightMove();
	bool bishopMove();
	bool queenMove();
	bool kingMove();

	bool straightMove(int canMove);
	bool diagonalMove();


public:
	int m_xStart;
	int m_yStart;
	int m_xEnd;
	int m_yEnd;
	int m_spaceNum;
	int m_rowIndex;
	int m_colIndex;

	bool m_isValid;	// 해당 공간에 기물이 있는지
	Team m_team;
	Unit m_unit;
};

