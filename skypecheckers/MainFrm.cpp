// MainFrm.cpp : CMainFrame クラスの実装
//
#include "stdafx.h"
#include "MainFrm.h"
#include "SkypeCheckersApp.h"
#include "SkypeCheckersDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(IDM_ATTACH_SKYPE, &CMainFrame::OnAttachSkype)
	ON_COMMAND(IDM_NEW_GAME, &CMainFrame::OnNewGame)
END_MESSAGE_MAP()


// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバ初期化コードをここに追加してください。
}

CMainFrame::~CMainFrame()
{
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_SYSMENU;
	cs.cx = cellSize*8 + GetSystemMetrics(SM_CXEDGE)*2
					   + GetSystemMetrics(SM_CXFIXEDFRAME)*2;
	cs.cy = cellSize*8 + GetSystemMetrics(SM_CYEDGE)*2
					   + GetSystemMetrics(SM_CYFIXEDFRAME)*2
					   + GetSystemMetrics(SM_CYMENU)*2;

	return TRUE;
}


// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


void CMainFrame::OnAttachSkype()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	if(pSC)
//		if(pSC->Attached())
			return;
	pSC = new SkypeCheckers;
	pSC->Attach();
}

void CMainFrame::OnNewGame()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	if(pSC == 0)
		return;
	else if(pSC->pGame->Started())
		return;
	CGetSkypeIDDialog idDlg;
	idDlg.DoModal();
	pSC->Connect(idDlg.m_csSkypeId);
	pSC->StartGame();
	Invalidate();
}
