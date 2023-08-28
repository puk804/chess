#include "pch.h"
#include "CSpace.h"
#include "CPrevClickData.h"


CSpace::CSpace() {
	//no action
}

CSpace::CSpace(int i, int j, int x, int y, int spaceNum) {
	m_xStart = x;
	m_yStart = y;
	m_xEnd = x+40;
	m_yEnd = y+40;
	m_spaceNum = spaceNum;
	m_rowIndex = i;
	m_colIndex = j;

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
	int prevRowIndex = 0;
	int prevColIndex = 0;
	CPrevClickData& instance = CPrevClickData::getInstance();
	if (firstClick && m_isValid) {	// 첫번째 클릭 칸에 기물이 있을 때
		if (turn == m_team) {		// 우리팀 기물이어야 클릭 가능
			instance.setPrevRowIndex(m_rowIndex);
			instance.setPrevRowIndex(m_colIndex);
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
			retVal = pawnMove();
			break;
		case Unit::Rook:
			retVal = rookMove();
			break;
		case Unit::Knight:
			retVal = knightMove();
			break;
		case Unit::Bishop:
			retVal = bishopMove();
			break;
		case Unit::Queen:
			retVal = queenMove();
			break;
		case Unit::King:
			retVal = kingMove();
			break;
		default:
			retVal = false;
			break;
	}

	return retVal;
}

bool CSpace::pawnMove() {
	bool retVal = false;
	int canMove = 1;
	int clickMove = 0;

	if (m_rowIndex == 1 || m_rowIndex == 6) {
		canMove = 2;
	}
	
	if (m_team == Team::White) {
	}
	else {

	}

	return retVal;
}

bool CSpace::rookMove() {
	bool retVal = false;

	return retVal;
}

bool CSpace::knightMove() {
	bool retVal = false;

	return retVal;
}

bool CSpace::bishopMove() {
	bool retVal = false;

	return retVal;
}

bool CSpace::queenMove() {
	bool retVal = false;

	return retVal;
}

bool CSpace::kingMove() {
	bool retVal = false;

	return retVal;
}

bool CSpace::straightMove(int canMove) {
	bool retVal = false;

	return retVal;
}

bool CSpace::diagonalMove() {
	bool retVal = false;

	

	return retVal;
}