#pragma once
#include "ChessTypeDef.h"

class CSpace
{
public:
	CSpace();
	CSpace(int x, int y, int spaceNum);

public:
	int m_xStart;
	int m_yStart;
	int m_xEnd;
	int m_yEnd;
	int m_spaceNum;

	bool isValid;
	Team m_team;
	Unit m_unit;
};

