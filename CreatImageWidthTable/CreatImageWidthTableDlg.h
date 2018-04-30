
// CreatImageWidthTableDlg.h : ���Y��
//

#pragma once

#include "ximage.h"

// CCreatImageWidthTableDlg ��ܤ��
class CCreatImageWidthTableDlg : public CDialogEx
{
// �غc
public:
	CCreatImageWidthTableDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATIMAGEWIDTHTABLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelectFolder();
	afx_msg void OnBnClickedButRun();

	CString m_strCurFolder;
	CString m_strList;
	CString m_Folder;
	int m_nStart;
	afx_msg void OnEnChangeEditStart();
	int m_nEnd;
	afx_msg void OnEnChangeEditEnd();
	afx_msg void OnBnClickedButCopytoClipboard();
	afx_msg void OnBnClickedButCopyChar();
	afx_msg void OnEnChangeEditFolder();
};
