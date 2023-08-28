#pragma once
#include "ChessTypeDef.h"

class CSpace
{
public:
	CSpace();
	CSpace(int x, int y, int spaceNum);
	void unitClear();


public:
	void getSpaceIndex(int& x, int& y);
	void changeCoorToNum(int& coor);
	bool isValidClick(const Team turn, bool firstClick);
	bool canMove();


public:
	int m_xStart;
	int m_yStart;
	int m_xEnd;
	int m_yEnd;
	int m_spaceNum;

	bool m_isValid;	// �ش� ������ �⹰�� �ִ���
	Team m_team;
	Unit m_unit;
};

