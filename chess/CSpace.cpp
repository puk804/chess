#include "pch.h"
#include "CSpace.h"
#include "CPrevClickData.h"
#include <iostream>

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
	if (firstClick && m_isValid) {	// ù��° Ŭ�� ĭ�� �⹰�� ���� ��
		if (turn == m_team) {		// �츮�� �⹰�̾�� Ŭ�� ����
			prevData.setPrevTeam(turn);
			prevData.setPrevUnit(m_unit);
			prevData.setPrevRowIndex(m_rowIndex);
			prevData.setPrevColIndex(m_colIndex);
			retVal = true;
		}
	}
	else if (!firstClick && canMove()) {		// �ι�° Ŭ���� ��� �⹰�� ������ �� �ִ� ĭ�� ��
		prevData.getPrevRowIndex(prevRowIndex);
		prevData.getPrevColIndex(prevColIndex);
		prevData.setisExist(prevRowIndex, prevColIndex, false);
		prevData.setisExist(m_rowIndex, m_colIndex, true);
		retVal = true;
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

	if (prevTeam != m_team) {			// ���� �� �⹰�� �ִ°����� ������ �� ����
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
	int canMove = 1;
	int clickMove = 0;
	int prevRow = 0;

	CPrevClickData& prevData = CPrevClickData::getInstance();
	prevData.getPrevTeam(prevTeam);
	prevData.getPrevRowIndex(prevRow);

	if (prevRow == 1 || prevRow == 6) {
		canMove = 2;
	}
	
	if (prevTeam == Team::White) {
		if (prevRow < m_rowIndex) {
			retVal = straightMove(canMove);
		}
	}
	else {
		if (prevRow > m_rowIndex) {
			retVal = straightMove(canMove);
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

	CPrevClickData& prevData = CPrevClickData::getInstance();

	prevData.getPrevRowIndex(prevRow);
	prevData.getPrevColIndex(prevCol);

	if (prevCol != m_colIndex) {	// ���� �������� �ƴ� ��
		return retVal;
	}

	if (std::abs(prevRow - m_rowIndex) > canMove) {		// �������� ������ ĭ���� ���� �������� ��
		return retVal;
	}

	// �Ʒ��κ� �Լ� ������ ��� �����ҵ�..
	if (prevRow > m_rowIndex) {		// ���� �̵��ϴ� ���
		prevRow -= 1;
		for (prevRow; prevRow >= m_rowIndex; --prevRow) {
			prevData.getisExist(prevRow, prevCol, isExist);
			if (isExist == true) {
				return retVal;
			}
			retVal = true;
		}
	}
	else {							// �Ʒ��� �̵��ϴ� ���
		prevRow += 1;
		for (prevRow; prevRow <= m_rowIndex; ++prevRow) {
			prevData.getisExist(prevRow, prevCol, isExist);
			if (isExist == true) {
				return retVal;
			}
			retVal = true;
		}
	}


	return retVal;
}

bool CSpace::diagonalMove() {
	bool retVal = false;

	

	return retVal;
}