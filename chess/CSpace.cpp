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
		m_isValid = true;
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
		m_isValid = true;
		y == 50 ? m_team = Team::White : m_team = Team::Black;
		m_unit = Unit::Pawn;
	}
	else {
		m_isValid = false;
		m_team = Team::None;
		m_unit = Unit::None;
	}
}

void CSpace::unitClear() {
	m_isValid = false;
	m_team = Team::None;
	m_unit = Unit::None;
}

void CSpace::getSpaceIndex(int& x, int& y) {
	changeCoorToNum(x);
	changeCoorToNum(y);
}

void CSpace::changeCoorToNum(int& coor) {
	int start = 10;
	for (int i = 0; i < 8; i++) {
		if (coor >= start && coor < start+40) {
			coor = i;
			return;
		}
		start += 40;
	}
}

bool CSpace::isValidClick(const Team turn, bool firstClick) {
	bool retVal = false;
	if (firstClick && m_isValid) {	// 첫번째 클릭 칸에 기물이 있을 때
		if (turn == m_team) {		// 우리팀 기물이어야 클릭 가능
			retVal = true;
		}
	}
	else if (!firstClick && canMove()) {		// 두번째 클릭인 경우 기물이 움직일 수 있는 칸일 때

		
		retVal = true;
	}

	return retVal;
}

bool CSpace::canMove() {
	bool retVal = false;

	switch (m_unit) {
		case Unit::Pawn:

			break;
		case Unit::Rook:

			break;
		case Unit::Knight:

			break;
		case Unit::Bishop:

			break;
		case Unit::Queen:

			break;
		case Unit::King:

			break;
		default:
			retVal = false;
			break;
	}

	return retVal;
}