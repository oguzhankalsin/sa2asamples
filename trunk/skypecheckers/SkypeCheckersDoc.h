// SkypeCheckersDoc.h : CSkypeCheckersDoc クラスのインターフェイス
//
#pragma once

// SkypeCheckers
#include "SkypeCheckers.h"

class CSkypeCheckersDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CSkypeCheckersDoc();
	DECLARE_DYNCREATE(CSkypeCheckersDoc)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 実装
public:
	virtual ~CSkypeCheckersDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};

extern SkypeCheckers* pSC;
