#pragma once
class CSpace
{
public:
	CSpace();
	CSpace(int x, int y, int spaceNum);

public:
	int m_xStart = 0;
	int m_yStart = 0;
	int m_xEnd = 0;
	int m_yEnd = 0;
	int m_spaceNum = 0;
};

