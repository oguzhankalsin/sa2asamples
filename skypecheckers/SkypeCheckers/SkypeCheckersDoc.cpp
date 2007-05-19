// SkypeCheckersDoc.cpp : CSkypeCheckersDoc クラスの実装
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


// CSkypeCheckersDoc コンストラクション/デストラクション

CSkypeCheckersDoc::CSkypeCheckersDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CSkypeCheckersDoc::~CSkypeCheckersDoc()
{
}

BOOL CSkypeCheckersDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CSkypeCheckersDoc シリアル化

void CSkypeCheckersDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}


// CSkypeCheckersDoc 診断

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


// CSkypeCheckersDoc コマンド



//  SkypeCheckers

SkypeCheckers* pSC = 0;
