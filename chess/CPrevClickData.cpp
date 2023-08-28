#include "pch.h"
#include "CPrevClickData.h"

CPrevClickData::CPrevClickData() {
	m_prevTeam = Team::None;
	m_prevUnit = Unit::None;
	m_prevRowIndex = 0;
	m_prevColIndex = 0;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (i < 2 || i > 5) {
				m_isExist[i][j] = true;
			}
			else {
				m_isExist[i][j] = false;
			}
		}
	}
}

CPrevClickData::~CPrevClickData(){

}

CPrevClickData& CPrevClickData::getInstance(){
	static CPrevClickData instance;
	return instance;
}

void CPrevClickData::setPrevTeam(Team team){
	m_prevTeam = team;
}

void CPrevClickData::getPrevTeam(Team & team){
	team = m_prevTeam;
}

void CPrevClickData::setPrevUnit(Unit unit){
	m_prevUnit = unit;
}

void CPrevClickData::getPrevUnit(Unit & unit){
	unit = m_prevUnit;
}

void CPrevClickData::setPrevRowIndex(int row){
	m_prevRowIndex = row;
}

void CPrevClickData::getPrevRowIndex(int &row){
	row = m_prevRowIndex;
}

void CPrevClickData::setPrevColIndex(int col){
	m_prevColIndex = col;
}

void CPrevClickData::getPrevColIndex(int &col){
	col = m_prevColIndex;
}

void CPrevClickData::setisExist(int row, int col, bool exist){
	m_isExist[row][col] = exist;
}

void CPrevClickData::getisExist(int row, int col, bool & exist){
	exist = m_isExist[row][col];
}
