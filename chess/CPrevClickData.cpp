#include "pch.h"
#include "CPrevClickData.h"

CPrevClickData::CPrevClickData() {
	m_prevRowIndex = 0;
	m_prevColIndex = 0;
}

CPrevClickData::~CPrevClickData(){

}

CPrevClickData& CPrevClickData::getInstance(){
	static CPrevClickData instance;
	return instance;
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
