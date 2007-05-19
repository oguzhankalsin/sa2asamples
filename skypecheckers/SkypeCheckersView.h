// SkypeCheckersView.h : CSkypeCheckersView �N���X�̃C���^�[�t�F�C�X
//
#pragma once
#include "SkypeCheckersDoc.h"

class CSkypeCheckersView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CSkypeCheckersView();
	DECLARE_DYNCREATE(CSkypeCheckersView)

// ����
public:
	CSkypeCheckersDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~CSkypeCheckersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawBoard(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SkypeCheckersView.cpp �̃f�o�b�O �o�[�W����
inline CSkypeCheckersDoc* CSkypeCheckersView::GetDocument() const
   { return reinterpret_cast<CSkypeCheckersDoc*>(m_pDocument); }
#endif

