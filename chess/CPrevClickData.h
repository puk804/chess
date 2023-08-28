#pragma once
#include "ChessTypeDef.h"
class CPrevClickData
{
private:
	CPrevClickData();
	CPrevClickData(const CPrevClickData& ref);
	~CPrevClickData();

public:
	static CPrevClickData& getInstance();

	void setPrevTeam(Team team);
	void getPrevTeam(Team &team);
	
	void setPrevUnit(Unit unit);
	void getPrevUnit(Unit &unit);

	void setPrevRowIndex(int row);
	void getPrevRowIndex(int &row);

	void setPrevColIndex(int col);
	void getPrevColIndex(int &col);
	
	void setisExist(int col, int row, bool exist);
	void getisExist(int col, int row, bool &exist);
	
	

private:
	Team m_prevTeam;
	Unit m_prevUnit;
	int m_prevRowIndex;
	int m_prevColIndex;
	bool m_isExist[8][8];
};
