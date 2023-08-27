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

	if (y == 10 || y == 290) {
		y == 10 ? m_team = Team::White : m_team = Team::Black;
		if (x == 10 || x == 290) {
			m_unit = Unit::Rook;
		}
		else if (x == 50 || x == 250) {
			m_unit = Unit::Knight;
		}
		else if (x == 90 || x == 210) {
			m_unit = Unit::Bishop;
		}
		else if (x == 130) {
			m_unit = Unit::Queen;
		}
		else {
			m_unit = Unit::King;
		}
	}
	else if (y == 50 || y == 250) {
		y == 50 ? m_team = Team::White : m_team = Team::Black;
		m_unit = Unit::Pawn;
	}
	else {
		m_team = Team::None;
		m_unit = Unit::None;
	}
}

int CSpace::getSpaceIndex(int x, int y) {
	int xNum = changeCoorToNum(x, true);
	int yNum = changeCoorToNum(y, false);

	return xNum + yNum;

}

int CSpace::changeCoorToNum(int coor, bool isX) {
	int retVal = -1;
	if (coor >= 10 && coor < 50) {
		retVal = 0;
	}
	else if (coor >= 50 && coor < 90) {
		retVal = 1;
	}
	else if (coor >= 90 && coor < 130) {
		retVal = 2;
	}
	else if (coor >= 130 && coor < 170) {
		retVal = 3;
	}
	else if (coor >= 170 && coor < 210) {
		retVal = 4;
	}
	else if (coor >= 210 && coor < 250) {
		retVal = 5;
	}
	else if (coor >= 250 && coor < 290) {
		retVal = 6;
	}
	else if (coor >= 290 && coor < 330) {
		retVal = 7;
	}

	if (!isX) {
		retVal *= 8;
	}
	
	return retVal;
}