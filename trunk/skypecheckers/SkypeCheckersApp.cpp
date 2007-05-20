// SkypeCheckersApp.cpp : アプリケーションのクラス動作を定義します。
//
#include "stdafx.h"
#include "SkypeCheckersApp.h"
#include "SkypeCheckersDoc.h"
#include "SkypeCheckersView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSkypeCheckersApp

BEGIN_MESSAGE_MAP(CSkypeCheckersApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSkypeCheckersApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CSkypeCheckersApp コンストラクション

CSkypeCheckersApp::CSkypeCheckersApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

CSkypeCheckersApp::~CSkypeCheckersApp()
{
	delete pSC;
	pSC = 0;
}


// 唯一の CSkypeCheckersApp オブジェクトです。

CSkypeCheckersApp theApp;


// CSkypeCheckersApp 初期化

BOOL CSkypeCheckersApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(0);  // 標準の INI ファイルのオプションをロードします (MRU を含む)
	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME, 
		RUNTIME_CLASS(CSkypeCheckersDoc), 
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CSkypeCheckersView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出してください。
	//  SDI アプリケーションでは、ProcessShellCommand の直後にこの呼び出しが発生しなければなりません。
	return TRUE;
}



// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CSkypeCheckersApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CSkypeCheckersApp メッセージ ハンドラ


//////////////////
// SkypeCheckers.cpp : 実装ファイル
//

// CGetSkypeIDDialog ダイアログ

IMPLEMENT_DYNAMIC(CGetSkypeIDDialog, CDialog)

CGetSkypeIDDialog::CGetSkypeIDDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGetSkypeIDDialog::IDD, pParent)
	, m_csSkypeId(_T(""))
{

}

CGetSkypeIDDialog::~CGetSkypeIDDialog()
{
}

void CGetSkypeIDDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GET_DEST_SKYPE_ID, m_skypeId);
	DDX_Text(pDX, IDC_GET_DEST_SKYPE_ID, m_csSkypeId);
}


BEGIN_MESSAGE_MAP(CGetSkypeIDDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CGetSkypeIDDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetSkypeIDDialog メッセージ ハンドラ

void CGetSkypeIDDialog::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	OnOK();
}
