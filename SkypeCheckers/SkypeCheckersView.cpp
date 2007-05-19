// SkypeCheckersView.cpp : CSkypeCheckersView �N���X�̎���
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

// CSkypeCheckersView �R���X�g���N�V����/�f�X�g���N�V����

CSkypeCheckersView::CSkypeCheckersView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CSkypeCheckersView::~CSkypeCheckersView()
{
}

BOOL CSkypeCheckersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CSkypeCheckersView �`��

void CSkypeCheckersView::OnDraw(CDC* pDC)
{
	CSkypeCheckersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	DrawBoard(pDC);
}


// CSkypeCheckersView �f�f

#ifdef _DEBUG
void CSkypeCheckersView::AssertValid() const
{
	CView::AssertValid();
}

void CSkypeCheckersView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSkypeCheckersDoc* CSkypeCheckersView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkypeCheckersDoc)));
	return (CSkypeCheckersDoc*)m_pDocument;
}
#endif //_DEBUG


// CSkypeCheckersView ���b�Z�[�W �n���h��

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

	// �`�F�X�Ղ̕`��
	for(int i=1;i<pSC->pGame->board.getSize()-1;i++)for(int j=1;j<pSC->pGame->board.getSize()-1;j++)
	{
		if(pSC->pGame->board.getAt(i, j)->available)
			pDC->SelectObject(&yerrow_brush);
		else
			pDC->SelectObject(&black_brush);
		pDC->Rectangle((i-1)*cellSize-1, (j-1)*cellSize-1, i*cellSize, j*cellSize);
	}

	// �R�}�̕`��
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
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	lastLBDownPoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void CSkypeCheckersView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	
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
