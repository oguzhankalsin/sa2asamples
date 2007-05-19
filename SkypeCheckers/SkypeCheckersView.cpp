// SkypeCheckersView.cpp : CSkypeCheckersView クラスの実装
//
#include "stdafx.h"
#include "SkypeCheckersView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSkypeCheckersView

IMPLEMENT_DYNCREATE(CSkypeCheckersView, CView)

BEGIN_MESSAGE_MAP(CSkypeCheckersView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CSkypeCheckersView コンストラクション/デストラクション

CSkypeCheckersView::CSkypeCheckersView()
{
	// TODO: 構築コードをここに追加します。

}

CSkypeCheckersView::~CSkypeCheckersView()
{
}

BOOL CSkypeCheckersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CSkypeCheckersView 描画

void CSkypeCheckersView::OnDraw(CDC* pDC)
{
	CSkypeCheckersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	DrawBoard(pDC);
}


// CSkypeCheckersView 診断

#ifdef _DEBUG
void CSkypeCheckersView::AssertValid() const
{
	CView::AssertValid();
}

void CSkypeCheckersView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSkypeCheckersDoc* CSkypeCheckersView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkypeCheckersDoc)));
	return (CSkypeCheckersDoc*)m_pDocument;
}
#endif //_DEBUG


// CSkypeCheckersView メッセージ ハンドラ

void CSkypeCheckersView::DrawBoard(CDC* pDC)
{
	extern SkypeCheckers* pGame;
	if(pSC == 0)return;

	int x, y;
	CBrush red_brush, white_brush, yerrow_brush, black_brush;
	red_brush.CreateSolidBrush(RGB(0xff, 0x00, 0x00));
	white_brush.CreateStockObject(WHITE_BRUSH);
	yerrow_brush.CreateSolidBrush(RGB(0xff, 0xff, 0xcc));
	black_brush.CreateSolidBrush(BLACK_BRUSH);

	// チェス盤の描画
	for(int i=1;i<pSC->pGame->board.getSize()-1;i++)for(int j=1;j<pSC->pGame->board.getSize()-1;j++)
	{
		if(pSC->pGame->board.getAt(i, j)->available)
			pDC->SelectObject(&yerrow_brush);
		else
			pDC->SelectObject(&black_brush);
		pDC->Rectangle((i-1)*cellSize-1, (j-1)*cellSize-1, i*cellSize, j*cellSize);
	}

	// コマの描画
	for(int i=1;i<pSC->pGame->board.getSize()-1;i++)for(int j=1;j<pSC->pGame->board.getSize()-1;j++)
	{
		if(pSC->pGame->board.getAt(i, j)->piece)
		{
			if(pSC->pGame->board.getAt(i, j)->piece->getSide() == pSC->pGame->ally)
			{
				pDC->SelectObject(&white_brush);
				pDC->Ellipse((i-1)*cellSize-1, (j-1)*cellSize-1, i*cellSize, j*cellSize);
			}
			else if(pSC->pGame->board.getAt(i, j)->piece->getSide() == pSC->pGame->enemy)
			{
				pDC->SelectObject(&red_brush);
				pDC->Ellipse((i-1)*cellSize-1, (j-1)*cellSize-1, i*cellSize, j*cellSize);
			}
		}
	}
}

static CPoint lastLBDownPoint;

void CSkypeCheckersView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	lastLBDownPoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void CSkypeCheckersView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	
	if(pSC->pGame != 0 && lastLBDownPoint.x > 0 && lastLBDownPoint.y > 0)
	{
		int xf = -1, yf = -1, xt = -1, yt = -1;
		for(int i=1;i<pSC->pGame->board.getSize()-1;i++)for(int j=1;j<pSC->pGame->board.getSize()-1;j++)
		{
			if((i-1)*cellSize-1 <= lastLBDownPoint.x && lastLBDownPoint.x <= i*cellSize &&
			   (j-1)*cellSize-1 <= lastLBDownPoint.y && lastLBDownPoint.y <= j*cellSize)
			{
				xf = i, yf = j;
				break;
			}
		}
		for(int i=1;i<pSC->pGame->board.getSize()-1;i++)for(int j=1;j<pSC->pGame->board.getSize()-1;j++)
		{
			if((i-1)*cellSize-1 <= point.x && point.x <= i*cellSize &&
			   (j-1)*cellSize-1 <= point.y && point.y <= j*cellSize)
			{
				xt = i, yt = j;
				break;
			}
		}
		if(xf > 0 && yf > 0 && xt > 0 && yt > 0)
		{
			bool ret;
			ret = pSC->pGame->getAlly()->Move(xf, yf, xt, yt);
			if(ret)
			{
				pSC->SendMove(xf, yf, xt, yt, pSC->pGame->getTurn() != pSC->pGame->ally);
			}
		}
		lastLBDownPoint.SetPoint(-1, -1);
	}
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}
