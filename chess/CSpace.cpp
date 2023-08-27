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

	if (y == 10) {
		m_team = Team::White;
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
	else if (y == 50) {
		m_team = Team::White;
		m_unit = Unit::Pawn;
	}
	else if (y == 250) {
		m_team = Team::Black;
		m_unit = Unit::Pawn;
	}
	else if (y == 290) {
		m_team = Team::Black;
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
			m_unit = Unit::King;
		}
		else {
			m_unit = Unit::Queen;
		}
	}
	else {
		m_team = Team::None;
		m_unit = Unit::None;
	}
}

