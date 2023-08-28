#pragma once
#include "ChessTypeDef.h"

class CSpace
{
public:
	CSpace();
	CSpace(int x, int y, int spaceNum);
	void unitClear(CSpace& space);


public:
	void getSpaceIndex(int& x, int& y);
	void changeCoorToNum(int& coor);
	bool isValidClick(CSpace space, bool firstClick);
	bool canMove(CSpace space);


public:
	int m_xStart;
	int m_yStart;
	int m_xEnd;
	int m_yEnd;
	int m_spaceNum;

	bool m_isValid;	// 해당 공간에 기물이 있는지
	Team m_team;
	Unit m_unit;
};

