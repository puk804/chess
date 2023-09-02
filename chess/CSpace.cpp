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
		prevData.setisExist(prevRowIndex, prevColIndex, false);
		prevData.setisExist(m_rowIndex, m_colIndex, true);
		prevData.setPrevRowIndex(MAX);			// �ʱ�ȭ
		prevData.setPrevColIndex(MAX);
		retVal = true;
	} 
	else if (prevRowIndex == m_rowIndex && prevColIndex == m_colIndex) {	// ������ ���� ĭ�� Ŭ������ ��
		retVal = true;
	}
	else {
		// no action
	}

	return retVal;
}

bool CSpace::canMove() {
	bool retVal = false;
	int canMove = 0;
	int prevRow = 0;
	int prevCol = 0;
	Unit prevUnit = Unit::None;
	Team prevTeam = Team::None;

	CPrevClickData& prevData = CPrevClickData::getInstance();
	prevData.getPrevRowIndex(prevRow);
	prevData.getPrevColIndex(prevCol);
	prevData.getPrevUnit(prevUnit);
	prevData.getPrevTeam(prevTeam);

	if (prevTeam == m_team) {			// ���� �� �⹰�� �ִ°����� ������ �� ����
		return false;
	}

	if (prevUnit == Unit::Pawn) {		// Pawn �� ó�� �������� 2ĭ ������ ����
		if ((prevRow == 1 || prevRow == 6) && prevCol == m_colIndex) {
			canMove = 2;
		}
		else {
			canMove = 1;
		}
	}
	else if (prevUnit == Unit::King) {
		canMove = 1;
	}
	else {								// Pawn, King�� ������ ������ ������ 7ĭ���� ������ ����. (Knight�� ���� �̻��)
		canMove = 7;
	}


	if (prevRow == m_rowIndex || prevCol == m_colIndex) {		// ���� �������� ��
		if (checkUnitMoveType(prevTeam, prevUnit, Move::STRAIGHT, prevRow)) {
			retVal = straightMove(canMove);
		}
	}
	else if (std::abs(prevRow - m_rowIndex) == std::abs(prevCol - m_colIndex)) {	// �밢�� �������� ��
		if (checkUnitMoveType(prevTeam, prevUnit, Move::DIAGONAL, prevRow)) {
			retVal = diagonalMove(canMove);
		}
	}
	else if((std::abs(prevRow - m_rowIndex) == 2 && std::abs(prevCol - m_colIndex) == 1) ||		// Knight ���� ������
			(std::abs(prevRow - m_rowIndex) == 1 && std::abs(prevCol - m_colIndex) == 2)) {
		if (prevUnit == Unit::Knight) {
			retVal = true;
		}		
	}
	else {
		// no action
	}

	return retVal;
}

bool CSpace::checkUnitMoveType(Team team, Unit unit, Move move, int row){
	bool retVal = false;

	if (unit == Unit::Pawn) {								// Pawn�� ���� �����θ� ������ ����
		if ((team == Team::White && row < m_rowIndex) ||
			(team == Team::Black && row > m_rowIndex)) {
			retVal = true;
		}
	}
	else{
		if (move == Move::STRAIGHT) {
			if (unit == Unit::Rook || unit == Unit::King || unit == Unit::Queen) {
				retVal = true;
			}
		}
		else {
			if (unit == Unit::Bishop || unit == Unit::King || unit == Unit::Queen) {
				retVal = true;
			}
		}
	}

	return retVal;
}

bool CSpace::UnitMove(Unit unit, int start, int end, int rowIndexPlus, int colIndexPlus, bool isRowMove) {
	bool retVal = false;
	bool isExist = false;
	int beforeEndIndex = end;

	CPrevClickData& prevData = CPrevClickData::getInstance();

	isRowMove ? beforeEndIndex += rowIndexPlus : beforeEndIndex += colIndexPlus;

	for (start; start != beforeEndIndex;) {
		if (isRowMove) {
			start += rowIndexPlus;
			end += colIndexPlus;
			prevData.getisExist(start, end, isExist);
		}
		else {
			start += colIndexPlus;
			end += rowIndexPlus;
			prevData.getisExist(end, start, isExist);
		}

		if (start == end) {		// ������ �̵� �����̸� ��� �⹰�� �־ �̵� ���� (Pawn ����)
			if (unit != Unit::Pawn || (unit == Unit::Pawn && isExist == false)) {
				retVal = true;
			}
		}
		else {
			if (isExist == true) {
				retVal = false;
				break;
			}
		}

		// ������
		if (isRowMove) {
			start += rowIndexPlus;
			end += colIndexPlus;
			prevData.getisExist(start, end, isExist);
		}
		else {
			start += colIndexPlus;
			end += rowIndexPlus;
			prevData.getisExist(end, start, isExist);
		}
	}
	
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

	if (prevUnit == Unit::Pawn && prevCol != m_colIndex) {	// ���� ������ ������ �� ����
		return retVal;
	}

	if ((std::abs(prevRow - m_rowIndex) > canMove) ||
		((std::abs(prevCol - m_colIndex) > canMove))){		// �������� ������ ĭ���� ���� �������� ��
		return retVal;
	}

	// todo: �Ʒ��κ� �Լ� ������ ��� �����ҵ�..
	if (prevRow > m_rowIndex) {		// ���� �̵��ϴ� ���
		--prevRow;					// ���� ĭ���� �˻�
		retVal = UnitMove(m_unit, prevRow, m_rowIndex, -1, 0, true);
		//for (prevRow; prevRow != m_rowIndex-1; --prevRow) {
		//	prevData.getisExist(prevRow, prevCol, isExist);
		//	if (prevRow == m_rowIndex) {		// ������ �̵� �����̸� ��� �⹰�� �־ �̵� ���� (Pawn ����)
		//		if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
		//			retVal = true;
		//		}
		//	}
		//	else {
		//		if (isExist == true) {
		//			retVal = false;
		//			break;
		//		}
		//	}
		//}
	}
	else if (prevRow < m_rowIndex){	// �Ʒ��� �̵��ϴ� ���
		++prevRow;					// ���� ĭ���� �˻�
		retVal = UnitMove(m_unit, prevRow, m_rowIndex, 1, 0, true);
		//for (prevRow; prevRow != m_rowIndex+1; ++prevRow) {
		//	prevData.getisExist(prevRow, prevCol, isExist);
		//	if (prevRow == m_rowIndex) {		// ������ �̵� �����̸� ��� �⹰�� �־ �̵� ���� (Pawn ����)
		//		if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
		//			retVal = true;
		//		}
		//	}
		//	else {
		//		if (isExist == true) {
		//			retVal = false;
		//			break;
		//		}
		//	}
		//}
	}
	else if (prevCol > m_colIndex) {	// �������� �̵��ϴ� ���
		--prevCol;						// ���� ĭ���� �˻�
		retVal = UnitMove(m_unit, prevCol, m_colIndex, 0, -1, false);

		//for (prevCol; prevCol != m_colIndex-1; --prevCol) {
		//	prevData.getisExist(prevRow, prevCol, isExist);
		//	if (prevCol == m_colIndex) {		// ������ �̵� �����̸� ��� �⹰�� �־ �̵� ���� (Pawn ����)
		//		if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
		//			retVal = true;
		//		}
		//	}
		//	else {
		//		if (isExist == true) {
		//			retVal = false;
		//			break;
		//		}
		//	}
		//}
	}
	else if (prevCol < m_colIndex) {	// ���������� �̵��ϴ� ���
		++prevCol;						// ���� ĭ���� �˻�
		retVal = UnitMove(m_unit, prevCol, m_colIndex, 0, 1, false);

		//for (prevCol; prevCol != m_colIndex+1; ++prevCol) {
		//	prevData.getisExist(prevRow, prevCol, isExist);
		//	if (prevCol == m_colIndex) {		// ������ �̵� �����̸� ��� �⹰�� �־ �̵� ���� (Pawn ����)
		//		if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == false)) {
		//			retVal = true;
		//		}
		//	}
		//	else {
		//		if (isExist == true) {
		//			retVal = false;
		//			break;
		//		}
		//	}
		//}
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

	if (std::abs(prevRow - m_rowIndex) > canMove) {		// �������� ������ ĭ���� ���� �������� ��
		return retVal;
	}

	if (prevRow > m_rowIndex && prevCol > m_colIndex) {		// ���� ���� �̵��ϴ� ���
		--prevRow;								// ���� ĭ���� �˻�
		for (prevRow; prevRow != m_rowIndex-1; --prevRow) {		// ������ �밢�� �������̶� ��/�� �ϳ��� ������ �Ǵ� ����
			--prevCol;
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevRow == m_rowIndex) {		// Pawn �� ������ �̵� ������ ��� �⹰�� �־�� �̵� ���� 
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == true)) {
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
	else if (prevRow > m_rowIndex && prevCol < m_colIndex) {		// ������ ���� �̵��ϴ� ���
		--prevRow;								// ���� ĭ���� �˻�
		for (prevRow; prevRow != m_rowIndex-1; --prevRow) {		// ������ �밢�� �������̶� ��/�� �ϳ��� ������ �Ǵ� ����
			++prevCol;
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevRow == m_rowIndex) {		// Pawn �� ������ �̵� ������ ��� �⹰�� �־�� �̵� ���� 
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == true)) {
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
	else if (prevRow < m_rowIndex && prevCol > m_colIndex) {		// ���� �Ʒ��� �̵��ϴ� ���
		++prevRow;								// ���� ĭ���� �˻�
		for (prevRow; prevRow != m_rowIndex+1; ++prevRow) {		// ������ �밢�� �������̶� ��/�� �ϳ��� ������ �Ǵ� ����
			--prevCol;
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevRow == m_rowIndex) {		// Pawn �� ������ �̵� ������ ��� �⹰�� �־�� �̵� ���� 
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == true)) {
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
	else if (prevRow < m_rowIndex && prevCol < m_colIndex) {		// ������ �Ʒ��� �̵��ϴ� ���
		++prevRow;								// ���� ĭ���� �˻�
		for (prevRow; prevRow != m_rowIndex+1; ++prevRow) {		// ������ �밢�� �������̶� ��/�� �ϳ��� ������ �Ǵ� ����
			++prevCol;
			prevData.getisExist(prevRow, prevCol, isExist);
			if (prevRow == m_rowIndex) {		// Pawn �� ������ �̵� ������ ��� �⹰�� �־�� �̵� ���� 
				if (prevUnit != Unit::Pawn || (prevUnit == Unit::Pawn && isExist == true)) {
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

	return retVal;
}
