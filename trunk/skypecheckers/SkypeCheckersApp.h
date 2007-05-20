// SkypeCheckersApp.h : SkypeCheckers アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "afxwin.h"

// CSkypeCheckersApp:
// このクラスの実装については、SkypeCheckers.cpp を参照してください。
//

class CSkypeCheckersApp : public CWinApp
{
public:
	CSkypeCheckersApp();
	~CSkypeCheckersApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};


// CGetSkypeIDDialog ダイアログ

class CGetSkypeIDDialog : public CDialog
{
	DECLARE_DYNAMIC(CGetSkypeIDDialog)

public:
	CGetSkypeIDDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CGetSkypeIDDialog();

// ダイアログ データ
	enum { IDD = IDD_GET_DEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_skypeId;
	CString m_csSkypeId;
};
