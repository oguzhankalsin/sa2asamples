// SkypeCheckersDoc.h : CSkypeCheckersDoc �N���X�̃C���^�[�t�F�C�X
//
#pragma once

// SkypeCheckers
#include "SkypeCheckers.h"

class CSkypeCheckersDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CSkypeCheckersDoc();
	DECLARE_DYNCREATE(CSkypeCheckersDoc)

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CSkypeCheckersDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};

extern SkypeCheckers* pSC;
