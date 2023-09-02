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
	bool checkUnitMoveType(Team team, Unit unit, Move move, int row);

	bool UnitMove(Unit unit, Move moveType, int start, int end, int rowIndexPlus, int colIndexPlus, int otherCoor, bool isRowMove = true);
	bool straightMove(int canMove);
	bool diagonalMove(int canMove);


public:
	int m_xStart;
	int m_yStart;
	int m_xEnd;
	int m_yEnd;
	int m_spaceNum;
	int m_rowIndex;
	int m_colIndex;

	bool m_isValid;	// �ش� ������ �⹰�� �ִ���
	Team m_team;
	Unit m_unit;
};

