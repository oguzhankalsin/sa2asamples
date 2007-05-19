// SkypeCheckersView.h : CSkypeCheckersView クラスのインターフェイス
//
#pragma once
#include "SkypeCheckersDoc.h"

class CSkypeCheckersView : public CView
{
protected: // シリアル化からのみ作成します。
	CSkypeCheckersView();
	DECLARE_DYNCREATE(CSkypeCheckersView)

// 属性
public:
	CSkypeCheckersDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CSkypeCheckersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawBoard(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SkypeCheckersView.cpp のデバッグ バージョン
inline CSkypeCheckersDoc* CSkypeCheckersView::GetDocument() const
   { return reinterpret_cast<CSkypeCheckersDoc*>(m_pDocument); }
#endif

