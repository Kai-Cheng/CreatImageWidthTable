
// CreatImageWidthTableDlg.h : 標頭檔
//

#pragma once

#include "ximage.h"

// CCreatImageWidthTableDlg 對話方塊
class CCreatImageWidthTableDlg : public CDialogEx
{
// 建構
public:
	CCreatImageWidthTableDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATIMAGEWIDTHTABLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
