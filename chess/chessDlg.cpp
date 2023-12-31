﻿
// chessDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "chess.h"
#include "chessDlg.h"
#include "afxdialogex.h"

#include "defValue.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchessDlg 대화 상자



CchessDlg::CchessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CchessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CchessDlg::OnBnClickedMfcbutton3)
END_MESSAGE_MAP()


// CchessDlg 메시지 처리기

BOOL CchessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_isFirstClick = true;
	m_isFirstPaint = true;
	m_prevSpace = CSpace();
	m_turn = Team::White;
	m_gameEnd = false;

	m_unitToString = {
		{Unit::Pawn, "pawn"},
		{Unit::Rook, "rook"},
		{Unit::Knight, "knight"},
		{Unit::Bishop, "bishop"},
		{Unit::Queen, "queen"},
		{Unit::King, "king"},
	};
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CchessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CchessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		if (m_isFirstPaint) {
			int x = 10;
			int y = 10;
			int count = 1;
			bool drawBlack = true;

			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					m_spaceNum[i][j] = CSpace(i, j, x, y, count);
					if (drawBlack) {
						dc.FillSolidRect(CRect(x, y, x + SPACE_BOARD_SIZE, y + SPACE_BOARD_SIZE), RGB_BLACK_SPACE);	// 어두운 공간
						m_isWhiteSpace[i][j] = false;
					}
					else {
						dc.FillSolidRect(CRect(x, y, x + SPACE_BOARD_SIZE, y + SPACE_BOARD_SIZE), RGB_WHITE_SPACE);	// 밝은 공간
						m_isWhiteSpace[i][j] = true;
					}
					firstUnitSetting(&dc, x, y, i, j);
					drawSquareLine(&dc, x, y, SPACE_BOARD_SIZE);

					x += 40;
					count++;
					drawBlack = !drawBlack;
				}
				y += 40;
				x = 10;
				drawBlack = !drawBlack;
			}
			// 클릭한 유닛 나오는 공간 그리기
			dc.FillSolidRect(CRect(COOR_SIDE_START_X, COOR_SIDE_START_Y, COOR_SIDE_START_X + SPACE_SIDE_SIZE, COOR_SIDE_START_Y + SPACE_SIDE_SIZE), RGB_WHITE);
			drawSquareLine(&dc, COOR_SIDE_START_X, COOR_SIDE_START_Y, SPACE_SIDE_SIZE);		

			// 텍스트 출력
			CString strTurn = _T(STR_WHITE_TURN); // 출력할 문자열
			dc.TextOut(COOR_TURN_X, COOR_TURN_Y, strTurn);

			m_isFirstPaint = false;
			CDialogEx::OnPaint();
		}

		else {
			
			if (!m_isFirstClick) {		// 첫번째 클릭 (아래에서 업데이트 후 paint 하는거라 반대임)

				m_prevX = m_prevSpace.m_xStart;
				m_prevY = m_prevSpace.m_yStart;
				m_preSpaceNum = m_prevSpace.m_spaceNum;

				dc.FillSolidRect(CRect(m_prevX, m_prevY, m_prevX + SPACE_BOARD_SIZE, m_prevY + SPACE_BOARD_SIZE), RGB_RED);

				drawUnit(&dc, m_nowSpace.m_xStart, m_nowSpace.m_yStart, m_prevSpace.m_team, m_prevSpace.m_unit, SPACE_BOARD_SIZE);

				drawSquareLine(&dc, m_prevX, m_prevY, SPACE_BOARD_SIZE);

				dc.FillSolidRect(CRect(COOR_SIDE_START_X, COOR_SIDE_START_Y, COOR_SIDE_START_X + SPACE_SIDE_SIZE, COOR_SIDE_START_Y + SPACE_SIDE_SIZE), RGB_WHITE);
				drawSquareLine(&dc, COOR_SIDE_START_X, COOR_SIDE_START_Y, SPACE_SIDE_SIZE);
				drawUnit(&dc, COOR_SIDE_START_X, COOR_SIDE_START_Y, m_prevSpace.m_team, m_prevSpace.m_unit, SPACE_SIDE_SIZE);

				CDialogEx::OnPaint();
			}
			else {						// 두번째 클릭
				if (m_isWhiteSpace[m_prevSpace.m_rowIndex][m_prevSpace.m_colIndex]) {	// 이전 클릭 공간이 밝은색
					dc.FillSolidRect(CRect(m_prevX, m_prevY, m_prevX + SPACE_BOARD_SIZE, m_prevY + SPACE_BOARD_SIZE), RGB_WHITE_SPACE);
				}
				else {																	// 이전 클릭 공간이 어두운색
					dc.FillSolidRect(CRect(m_prevX, m_prevY, m_prevX + SPACE_BOARD_SIZE, m_prevY + SPACE_BOARD_SIZE), RGB_BLACK_SPACE);
				}

				if (m_isWhiteSpace[m_nowSpace.m_rowIndex][m_nowSpace.m_colIndex]) {		// 현재 클릭 공간이 밝은색
					dc.FillSolidRect(CRect(m_nowSpace.m_xStart, m_nowSpace.m_yStart, m_nowSpace.m_xStart + SPACE_BOARD_SIZE, m_nowSpace.m_yStart + SPACE_BOARD_SIZE), RGB_WHITE_SPACE);
				}
				else {																	// 현재 클릭 공간이 어두운색
					dc.FillSolidRect(CRect(m_nowSpace.m_xStart, m_nowSpace.m_yStart, m_nowSpace.m_xStart + SPACE_BOARD_SIZE, m_nowSpace.m_yStart + SPACE_BOARD_SIZE), RGB_BLACK_SPACE);
				}

				drawUnit(&dc, m_nowSpace.m_xStart, m_nowSpace.m_yStart, m_prevSpace.m_team, m_prevSpace.m_unit, SPACE_BOARD_SIZE);

				drawSquareLine(&dc, m_prevX, m_prevY, SPACE_BOARD_SIZE);
				drawSquareLine(&dc, m_nowSpace.m_xStart, m_nowSpace.m_yStart, SPACE_BOARD_SIZE);

				if (!m_gameEnd) {
					dc.FillSolidRect(CRect(COOR_SIDE_START_X, COOR_SIDE_START_Y, COOR_SIDE_START_X + SPACE_SIDE_SIZE, COOR_SIDE_START_Y + SPACE_SIDE_SIZE), RGB_WHITE);
					drawSquareLine(&dc, COOR_SIDE_START_X, COOR_SIDE_START_Y, SPACE_SIDE_SIZE);

					// 텍스트 출력
					CString strTurn = _T(""); // 출력할 문자열
					if (m_turn == Team::White) {
						strTurn = _T(STR_WHITE_TURN);
					}
					else {
						strTurn = _T(STR_BLACK_TURN);
					}
					dc.TextOut(COOR_TURN_X, COOR_TURN_Y, strTurn);
				}
				else {
					// 오른쪽 유닛 크게보기 공간 덮기 (테두리 덮기 위해 +1 추가)
					dc.FillSolidRect(CRect(COOR_SIDE_START_X, COOR_TURN_Y, COOR_SIDE_START_X + SPACE_SIDE_SIZE + 1, COOR_SIDE_START_Y + SPACE_SIDE_SIZE + 1), RGB_BASE);

					// 텍스트 출력
					CString strTurn = _T(""); // 출력할 문자열
					if (m_turn == Team::White) {
						strTurn = _T(STR_BLACK_WIN);
					}
					else {
						strTurn = _T(STR_WHITE_WIN);
					}
					dc.TextOut(COOR_END_X, COOR_END_Y, strTurn);
				}

				

				CDialogEx::OnPaint();
			}
			
		}
	}
}

void CchessDlg::drawSquareLine(CPaintDC* dc, int x, int y, int size)
{
	dc->MoveTo(x, y);
	dc->LineTo(x + size, y);
	dc->LineTo(x + size, y + size);
	dc->LineTo(x, y + size);
	dc->LineTo(x, y);
}

void CchessDlg::drawUnit(CPaintDC* dc, int x, int y, Team team, Unit unit, int size)
{
	CImage pngImage;
	CString fname;

	std::string imgPath = "res/unit/";
	std::string teamName = "";
	std::string unitName = "";

	for (auto iter : m_unitToString) {
		if (iter.first == unit) {
			unitName = iter.second;
			break;
		}
	}

	team == Team::White ? teamName = "white/" : teamName = "black/";

	imgPath += teamName + unitName + ".png";
	fname = imgPath.c_str();

	if (SUCCEEDED(pngImage.Load(fname))) // SUCCEEDED 매크로로 로드 성공 여부 확인
	{
		pngImage.Draw(dc->GetSafeHdc(), x, y, size, size);
	}
}

void CchessDlg::firstUnitSetting(CPaintDC* dc, int x, int y, int row, int col)
{
	Team team = Team::None;
	Unit unit = Unit::None;

	if (row < 2) {
		team = Team::White;
	}
	else if (row > 5) {
		team = Team::Black;
	}
	else {
		team = Team::None;
	}

	if (team != Team::None) {
		if (row == 0 || row == 7) {
			const Unit units[] = { Unit::Rook, Unit::Knight, Unit::Bishop, Unit::Queen, Unit::King, Unit::Bishop, Unit::Knight, Unit::Rook };
			unit = units[col];
		}
		else if (row == 1 || row == 6) {
			unit = Unit::Pawn;
		}
	}

	if (unit != Unit::None) {
		drawUnit(dc, x, y, team, unit, SPACE_BOARD_SIZE);
	}
}

void CchessDlg::reGame()
{
	m_isFirstClick = true;
	m_isFirstPaint = true;
	m_prevSpace = CSpace();
	m_turn = Team::White;
	m_gameEnd = false;

	m_unitToString = {
		{Unit::Pawn, "pawn"},
		{Unit::Rook, "rook"},
		{Unit::Knight, "knight"},
		{Unit::Bishop, "bishop"},
		{Unit::Queen, "queen"},
		{Unit::King, "king"},
	};
	CSpace().reGame();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CchessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CchessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_gameEnd) {
		return;
	}

	if ((point.x < 330 && point.x >= 10) && (point.y < 330 && point.x >= 10)) {		// 체스판 범위를 클릭했을 때
		int x = point.y;
		int y = point.x;
		CSpace().getSpaceIndex(x, y);		// todo: 함수 정의위치 바꾸기

		if (m_spaceNum[x][y].isValidClick(m_turn, m_isFirstClick)) {	// 유효한 클릭인지 체크
			if (m_isFirstClick) {
				m_prevSpace = m_spaceNum[x][y];
			}
			else {
				if (m_spaceNum[x][y].m_team != m_prevSpace.m_team) {	// 똑같은곳 2번 클릭이면 무효
					if (m_spaceNum[x][y].m_unit == Unit::King) {
						m_gameEnd = true;
					}

					int prevX = m_prevSpace.m_rowIndex;
					int prevY = m_prevSpace.m_colIndex;

					m_spaceNum[x][y].m_isValid = m_spaceNum[prevX][prevY].m_isValid;
					m_spaceNum[x][y].m_team = m_spaceNum[prevX][prevY].m_team;
					m_spaceNum[x][y].m_unit = m_spaceNum[prevX][prevY].m_unit;
					m_spaceNum[prevX][prevY].unitClear();

					m_turn == Team::White ? m_turn = Team::Black : m_turn = Team::White;
				}
			}
			m_isFirstClick = !m_isFirstClick;
			m_nowSpace = m_spaceNum[x][y];			// 현재 클릭한 곳의 정보를 담아서 그림을 그리기 위함
			Invalidate(false);		// 수정된 부분만 그리기 예약
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

// 다시하기 버튼 클릭
void CchessDlg::OnBnClickedMfcbutton3()
{
	reGame();
	Invalidate();
}
