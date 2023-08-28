#pragma once
class CPrevClickData
{
private:
	CPrevClickData();
	CPrevClickData(const CPrevClickData& ref);
	~CPrevClickData();

public:
	static CPrevClickData& getInstance();

	void setPrevRowIndex(int row);
	void getPrevRowIndex(int &row);

	void setPrevColIndex(int col);
	void getPrevColIndex(int &col);

private:
	int m_prevRowIndex;
	int m_prevColIndex;
};
