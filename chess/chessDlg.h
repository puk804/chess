
// chessDlg.h: 헤더 파일
//

#pragma once
#include "CSpace.h"
#include <map>

// CchessDlg 대화 상자
class CchessDlg : public CDialogEx
{
// 생성입니다.
public:
	CchessDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void drawSquareLine(CPaintDC* dc, int x, int y, int size);
	void drawUnit(CPaintDC* dc, int x, int y, Team team, Unit unit, int size);
	void firstUnitSetting(CPaintDC* dc, int x, int y, int row, int col);


public:
	CSpace m_spaceNum[8][8];
	CSpace m_prevSpace;
	CSpace m_nowSpace;
	bool m_isFirstClick;
	bool m_isFirstPaint;
	bool m_isWhiteSpace[8][8];
	Team m_turn;

	int m_prevX;
	int m_prevY;
	int m_preSpaceNum;

	int m_gameEnd;

	std::map<Unit, std::string> m_unitToString;
};
