#include "pch.h"
#include "CSpace.h"
#include "CPrevClickData.h"
#include <iostream>

#define MAX 9999

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

	CPrevClickData& prevData = CPrevClickData::getInstance();
	prevData.getPrevRowIndex(prevRowIndex);
	prevData.getPrevColIndex(prevColIndex);

	if (firstClick && m_isValid) {	// 첫번째 클릭 칸에 기물이 있을 때
		if (turn == m_team) {		// 우리팀 기물이어야 클릭 가능
			prevData.setPrevTeam(turn);
			prevData.setPrevUnit(m_unit);
			prevData.setPrevRowIndex(m_rowIndex);
			prevData.setPrevColIndex(m_colIndex);
			retVal = true;
		}
	}
	else if (!firstClick && canMove()) {		// 두번째 클릭인 경우 기물이 움직일 수 있는 칸일 때
		prevData.setisExist(prevRowIndex, prevColIndex, false);
		prevData.setisExist(m_rowIndex, m_colIndex, true);
		prevData.setPrevRowIndex(MAX);			// 초기화
		prevData.setPrevColIndex(MAX);
		retVal = true;
	} 
	else if (prevRowIndex == m_rowIndex && prevColIndex == m_colIndex) {	// 이전과 같은 칸을 클릭했을 때
		retVal = true;
	}
	else {
		// no action
	}

	return retVal;
}

bool CSpace::canMove() {
	bool retVal = false;
	Unit prevUnit = Unit::None;
	Team prevTeam = Team::None;
	CPrevClickData& prevData = CPrevClickData::getInstance();
	prevData.getPrevUnit(prevUnit);
	prevData.getPrevTeam(prevTeam);

	if (prevTeam != m_team) {			// 같은 팀 기물이 있는곳으로 움직일 수 없음
		switch (prevUnit) {
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
	}
	return retVal;
}

bool CSpace::pawnMove() {
	Team prevTeam = Team::None;
	bool retVal = false;
	int canStrMove = 1;
	int canDiaMove = 1;
	int clickMove = 0;
	int prevRow = 0;
	int prevCol = 0;

	CPrevClickData& prevData = CPrevClickData::getInstance();
	prevData.getPrevTeam(prevTeam);
	prevData.getPrevRowIndex(prevRow);
	prevData.getPrevColIndex(prevCol);

	if (prevRow == 1 || prevRow == 6) {
		canStrMove = 2;
	}
	
	if ((prevTeam == Team::White && prevRow < m_rowIndex) ||
		(prevTeam == Team::Black && prevRow > m_rowIndex)) {
		if (prevCol != m_colIndex) {
			retVal = diagonalMove(canDiaMove);
		}
		else {
			retVal = straightMove(canStrMove);
		}
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
	bool isExist = false;
	int prevRow = 0;
	int prevCol = 0;
	Unit prevUnit = Unit::None;

	CPrevClickData& prevData = CPrevClickData::getInstance();

	prevData.getPrevRowIndex(prevRow);
	prevData.getPrevColIndex(prevCol);
	prevData.getPrevUnit(prevUnit);

	if (prevUnit == Unit::Pawn && prevCol != m_colIndex) {	// 폰은 옆으로 움직일 수 없음
		return retVal;
	}

	if (prevRow != m_rowIndex && prevCol != m_colIndex) {	// 직선 움직임이 아닐 때
		return retVal;
	}

	if ((std::abs(prevRow - m_rowIndex) > canMove) ||
		((std::abs(prevCol - m_colIndex) > canMove))){		// 움직임이 가능한 칸보다 많이 움직였을 때
		return retVal;
	}

	// todo: 아래부분 함수 포인터 사용 가능할듯..
	if (prevRow > m_rowIndex) {		// 위로 이동하는 경우
		--prevRow;					// 다음 칸부터 검사
		for (prevRow; prevRow >= m_rowIndex; --prevRow) {
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevRow == m_rowIndex) {		// 마지막 이동 지점이면 상대 기물이 있어도 이동 가능 (Pawn 제외)
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
					retVal = true;
				}
			}
			else {
				if (isExist == true) {
					retVal = false;
					break;
				}
			}
		}
	}
	else if (prevRow < m_rowIndex){	// 아래로 이동하는 경우
		++prevRow;					// 다음 칸부터 검사
		for (prevRow; prevRow <= m_rowIndex; ++prevRow) {
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevRow == m_rowIndex) {		// 마지막 이동 지점이면 상대 기물이 있어도 이동 가능 (Pawn 제외)
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
					retVal = true;
				}
			}
			else {
				if (isExist == true) {
					retVal = false;
					break;
				}
			}
		}
	}
	else if (prevCol > m_colIndex) {	// 왼쪽으로 이동하는 경우
		--prevCol;						// 다음 칸부터 검사
		for (prevCol; prevCol <= m_colIndex; --prevCol) {
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevCol == m_colIndex) {		// 마지막 이동 지점이면 상대 기물이 있어도 이동 가능 (Pawn 제외)
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
					retVal = true;
				}
			}
			else {
				if (isExist == true) {
					retVal = false;
					break;
				}
			}
		}
	}
	else if (prevCol < m_colIndex) {	// 오른쪽으로 이동하는 경우
		++prevCol;						// 다음 칸부터 검사
		for (prevCol; prevCol >= m_colIndex; ++prevCol) {
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevCol == m_colIndex) {		// 마지막 이동 지점이면 상대 기물이 있어도 이동 가능 (Pawn 제외)
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
					retVal = true;
				}
			}
			else {
				if (isExist == true) {
					retVal = false;
					break;
				}
			}
		}
	}
	else {
		// no action
	}


	return retVal;
}

bool CSpace::diagonalMove(int canMove) {
	bool retVal = false;
	bool isExist = false;
	int prevRow = 0;
	int prevCol = 0;
	Unit prevUnit = Unit::None;

	CPrevClickData& prevData = CPrevClickData::getInstance();

	prevData.getPrevRowIndex(prevRow);
	prevData.getPrevColIndex(prevCol);
	prevData.getPrevUnit(prevUnit);

	if (prevRow - m_rowIndex != prevCol - m_colIndex) {	// 대각선 움직임이 아닐 때
		return retVal;
	}

	if (std::abs(prevRow - m_rowIndex) > canMove) {		// 움직임이 가능한 칸보다 많이 움직였을 때
		return retVal;
	}

	return retVal;
}