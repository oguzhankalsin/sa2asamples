// SkypeCheckersApp.h : SkypeCheckers �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "afxwin.h"

// CSkypeCheckersApp:
// ���̃N���X�̎����ɂ��ẮASkypeCheckers.cpp ���Q�Ƃ��Ă��������B
//

class CSkypeCheckersApp : public CWinApp
{
public:
	CSkypeCheckersApp();
	~CSkypeCheckersApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};


// CGetSkypeIDDialog �_�C�A���O

class CGetSkypeIDDialog : public CDialog
{
	DECLARE_DYNAMIC(CGetSkypeIDDialog)

public:
	CGetSkypeIDDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CGetSkypeIDDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_GET_DEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_skypeId;
	CString m_csSkypeId;
};
