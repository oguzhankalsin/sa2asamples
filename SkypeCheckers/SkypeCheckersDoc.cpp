// SkypeCheckersDoc.cpp : CSkypeCheckersDoc �N���X�̎���
//
#include "stdafx.h"
#include "SkypeCheckersDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSkypeCheckersDoc

IMPLEMENT_DYNCREATE(CSkypeCheckersDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkypeCheckersDoc, CDocument)
END_MESSAGE_MAP()


// CSkypeCheckersDoc �R���X�g���N�V����/�f�X�g���N�V����

CSkypeCheckersDoc::CSkypeCheckersDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CSkypeCheckersDoc::~CSkypeCheckersDoc()
{
}

BOOL CSkypeCheckersDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CSkypeCheckersDoc �V���A����

void CSkypeCheckersDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
	}
}


// CSkypeCheckersDoc �f�f

#ifdef _DEBUG
void CSkypeCheckersDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkypeCheckersDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSkypeCheckersDoc �R�}���h



//  SkypeCheckers

SkypeCheckers* pSC = 0;
