#include "pch.h"
#include "CSpace.h"

CSpace::CSpace() {
	//no action
}

CSpace::CSpace(int x, int y, int spaceNum) {
	m_xStart = x;
	m_yStart = y;
	m_xEnd = x+40;
	m_yEnd = y+40;
	m_spaceNum = spaceNum;
}

