
// CreatImageWidthTableDlg.cpp : 實作檔
//

#include "stdafx.h"
#include <strsafe.h>
#include "CreatImageWidthTable.h"
#include "CreatImageWidthTableDlg.h"
#include "afxdialogex.h"
#include "CFolder\FolderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCreatImageWidthTableDlg 對話方塊



CCreatImageWidthTableDlg::CCreatImageWidthTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATIMAGEWIDTHTABLE_DIALOG, pParent)
	, m_nStart(0)
	, m_nEnd(0)
	, m_Folder(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreatImageWidthTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_START, m_nStart);
	DDV_MinMaxInt(pDX, m_nStart, 0, 255);
	DDX_Text(pDX, IDC_EDIT_END, m_nEnd);
	DDV_MinMaxInt(pDX, m_nEnd, 0, 255);
	DDX_Text(pDX, IDC_EDIT_FOLDER, m_Folder);
}

BEGIN_MESSAGE_MAP(CCreatImageWidthTableDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_SEL, &CCreatImageWidthTableDlg::OnBnClickedSelectFolder)
	ON_BN_CLICKED(IDC_BUT_RUN, &CCreatImageWidthTableDlg::OnBnClickedButRun)
	ON_EN_CHANGE(IDC_EDIT_START, &CCreatImageWidthTableDlg::OnEnChangeEditStart)
	ON_EN_CHANGE(IDC_EDIT_END, &CCreatImageWidthTableDlg::OnEnChangeEditEnd)
	ON_BN_CLICKED(IDC_BUT_COPY, &CCreatImageWidthTableDlg::OnBnClickedButCopytoClipboard)
	ON_BN_CLICKED(IDC_BUT_COPY_CHAR, &CCreatImageWidthTableDlg::OnBnClickedButCopyChar)
	ON_EN_CHANGE(IDC_EDIT_FOLDER, &CCreatImageWidthTableDlg::OnEnChangeEditFolder)
END_MESSAGE_MAP()


// CCreatImageWidthTableDlg 訊息處理常式

BOOL CCreatImageWidthTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	SetDlgItemInt(IDC_EDIT_START, 0x21);
	SetDlgItemInt(IDC_EDIT_END, 0x7E);
	DWORD currentPahtlength = 0;
	DWORD dwError = 0;
	currentPahtlength = GetCurrentDirectory(0, NULL);
	currentPahtlength += 1;
	LPWSTR pBuf = new TCHAR[currentPahtlength];
	dwError = GetCurrentDirectory(currentPahtlength, pBuf);
	if (dwError == 0)
	{
		dwError = GetLastError();
		if (pBuf) delete[] pBuf;
		return dwError;
	}
	m_strCurFolder.Format(_T("%s"), pBuf);
	if (pBuf) delete[] pBuf;
	//SetDlgItemText(IDC_EDIT_FOLDER, pBuf);
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CCreatImageWidthTableDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CCreatImageWidthTableDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CCreatImageWidthTableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCreatImageWidthTableDlg::OnBnClickedSelectFolder()
{
	CString strFilter, strTemp;
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

#if 0
	strFilter.Format(_T("預設格式檔案|*.bin|"));
	strTemp.Format(_T("%s|*.*||", allFilter);
	strFilter += strTemp;
#else
	strFilter.Format(_T("%s|*.*||"), allFilter);
#endif
	CString m_strFolderPath;
	CString m_strDisplayName;
#ifdef _DEBUG
	m_Folder = _T("E:\\LCD\\[20180426]EngTest3\\FONT");
#else
	GetDlgItemText(IDC_EDIT_FOLDER, m_Folder);
	if (m_Folder == _T(""))
		m_Folder = m_strCurFolder;
#endif
	CFolderDialog dlg(_T("Select Folder"), m_strFolderPath, this);//E:\LCD\[20180426]EngTest3\FONT
	dlg.SetSelectedFolder(m_Folder);
	if (dlg.DoModal() == IDOK)
	{
		m_strFolderPath = dlg.GetFolderPath();
		m_strDisplayName = dlg.GetFolderName();
	}
	m_Folder = m_strFolderPath;
	SetDlgItemText(IDC_EDIT_FOLDER, m_Folder);
	/*
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, strFilter);

	if (dlgFile.DoModal() != IDOK) return;

	// set output device to resulting path name
	m_strDownload = dlgFile.GetPathName();
	CString name;
	name = m_strDownload;
	GetFileTitle(m_strDownload, name.GetBuffer(_MAX_PATH), _MAX_PATH);
	name.ReleaseBuffer();
	SetDlgItemText(IDC_EDIT_FOLDER, name);
	*/
	/*
	//===== Open File
	CFile fDownload;
	CFileException ex;

	if (!fDownload.Open(m_strDownload, CFile::modeRead, &ex))
	{
		// complain if an error happened
		// no need to delete the ex object

		CString strMessage;
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);
		strMessage.Format(_T("Couldn't open source file: %s"), szError);
		AfxMessageBox(strMessage);
		return;
	}

	int m_nDownloadSize = (int)fDownload.GetLength();
	fDownload.Close();

	strTemp.Format(IDS_FORM_MESS8, m_nDownloadSize); // "%d Byte"
	SetDlgItemText(IDC_EDIT6, strTemp);

	GetDlgItem(IDC_BUTTON12)->EnableWindow(TRUE);
	*/
}


void DisplayErrorBox(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and clean up

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40)*sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

int get_filename_extT_(_TCHAR* filename) {
	_TCHAR *dot = _tcsrchr(filename, _T('.'));
	if (!dot || dot == filename) return NULL;
	return (dot - filename);
}
int h2d(_TCHAR* str)
{
	int n = 0;
	char tN;
	while (tN = (char)*str++)
	{
		if (tN >= '0' && tN <= '9')
		{
			n = (n * 16) + (tN - '0');
		}
		else if (tN >= 'A' && tN <= 'F')
		{
			n = n * 16 + (tN - 'A') + 10;
		}
		else if (tN >= 'a' && tN <= 'f')
		{
			n = n * 16 + (tN - 'a') + 10;
		}
		else
			break;
	}
	return n;
}
void CCreatImageWidthTableDlg::OnBnClickedButRun()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strFolder;
	CString csTable;
	CString csWTable;
	CString csCTable;
	CString csFname_R;
	CString csFname_L;
	CString csFname;
	CString csASCII;
	LPTSTR tASCII;
	CFile file;
	CxImage *pCxImage = NULL;
	char nASCII = 0;
	int imageW = 0;
	//int nPahtlength = 0;
	//strFolder = m_Folder;
	//nPahtlength = strFolder.GetLength();
	//LPTSTR pBuf;// = new TCHAR[nPahtlength];

	//pBuf = strFolder.GetBuffer();
	//StringCchCat(pBuf, MAX_PATH, TEXT("\\*"));
	//strFolder.ReleaseBuffer();
	//hFind = FindFirstFile(pBuf, &ffd);

	SetDlgItemText(IDC_EDIT_LIST, _T(""));
	SetDlgItemText(IDC_EDIT_TABLE, _T(""));
	if (m_Folder == _T(""))
	{
		m_strList = _T("No JPG Image!");
		SetDlgItemText(IDC_EDIT_LIST, m_strList);
		return;
	}
	strFolder.Format(_T("%s\\*"), m_Folder);
	hFind = FindFirstFile(strFolder, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
	}
	csTable = _T("");
	csWTable = _T("{\r\n\t");
	csCTable = _T("{\r\n\t");
	char arr[256];
	memset(arr, 0, 256);
	int maxchar = 0;
	int minchar = 255;
	CStringArray strArrChar;
	CString pa;

	for (int i = 0; i <= 255; i++)
	{
		strArrChar.Add(_T("    0"));
	}
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			if (_tcsstr(ffd.cFileName, _T(".jpg")))
			{
				csFname_R.Format(_T("%s\\%s"), m_Folder, ffd.cFileName);
				csFname_L.Format(_T("%s"), ffd.cFileName);
				csFname_L.Delete(get_filename_extT_(ffd.cFileName), 4);
				csFname = csFname_L;
				csFname_L.Delete(0, csFname_L.GetLength() - 2);
				tASCII = csFname_L.GetBuffer(0);
				csFname_L.ReleaseBuffer();
				nASCII = (char)h2d(tASCII);
				
				//csFname_L = csFname_R.GetBuffer(csFname_R.GetLength() - 2);
				csTable += csFname_R;
				csTable += _T("\r\n");
				/* Check range */
				if (minchar > nASCII)
					minchar = nASCII;
				if (maxchar < nASCII)
					maxchar = nASCII;
				if (maxchar > m_nEnd || minchar < m_nStart)
				{
					csTable += _T("Over Range! Check Image, Start and End.\r\n");
					SetDlgItemText(IDC_EDIT_LIST, csTable);
					return;
				}
				/* Get image width and save into the arr table */
				//if (!file.Open(csFname_R, CFile::modeRead))
				//	continue;
				//pCxImage = new CxImage(csFname_R, CxImage::GetTypeIdFromName(csFname_R));
				pCxImage = new CxImage(csFname_R, CXIMAGE_FORMAT_UNKNOWN);
				if (pCxImage->GetWidth())
				{
					imageW = pCxImage->GetWidth();
					arr[nASCII] = imageW;
				}
				//if ((pa = strArrChar.GetAt(nASCII)) != NULL)
				{
					strArrChar.SetAt(nASCII, csFname);  // Replace element nASCII.
					//delete pa; // Delete the original element at nASCII.
				}
				//strArrChar.SetAt(nASCII, csFname);
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	if (csTable == _T(""))
	{
		m_strList = _T("No JPG Image!");
		SetDlgItemText(IDC_EDIT_LIST, m_strList);
		return;
	}
	for (int i = m_nStart; i <= m_nEnd; i++)
	{
		if (i % 16 == 0)
			csWTable += _T("\r\n\t");
		csFname_L.Format(_T("0x%02x,"), arr[i]);
		csWTable += csFname_L;
	}
	csWTable += _T("\r\n};");

	for (int i = m_nStart; i <= m_nEnd; i++)
	{
		if (i % 16 == 0)
			csCTable += _T("\r\n\t");
		csFname_L.Format(_T("%s,"), strArrChar.GetAt(i));
		csCTable += csFname_L;
	}
	csCTable += _T("\r\n};");

	m_strList = csTable;
	SetDlgItemText(IDC_EDIT_LIST, m_strList);
	SetDlgItemText(IDC_EDIT_TABLE, csWTable);
	SetDlgItemText(IDC_EDIT_TABLE_CHAR, csCTable);

}



void CCreatImageWidthTableDlg::OnEnChangeEditStart()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	m_nStart = GetDlgItemInt(IDC_EDIT_START);
	if (m_nStart > 255)
	{
		m_nStart = 255;
		SetDlgItemInt(IDC_EDIT_START, 255);
	}
}


void CCreatImageWidthTableDlg::OnEnChangeEditEnd()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	m_nEnd = GetDlgItemInt(IDC_EDIT_END);
	if (m_nEnd > 255)
	{
		m_nEnd = 255;
		SetDlgItemInt(IDC_EDIT_END, 255);
	}
}


void CCreatImageWidthTableDlg::OnBnClickedButCopytoClipboard()
{
	CString mTable;
	int mLen = 0;
	GetDlgItemText(IDC_EDIT_TABLE, mTable);
	if (mTable == _T(""))
	{
		return;
	}
	mLen = (mTable.GetLength() + 1) * 2;
	char *nstringw = new char[mLen];

	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, mLen, mTable, _TRUNCATE);

	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	// Remove the current Clipboard contents
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}
	// Get the currently selected data
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, mLen);
	//strcpy_s((char*)hGlob, 64, "Current selection\r\n");
	strcpy_s((char*)hGlob, mLen, nstringw);

	// For the appropriate data formats...
	if (::SetClipboardData(CF_TEXT, hGlob) == NULL)
	{
		CString msg;
		msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
		AfxMessageBox(msg);
		CloseClipboard();
		GlobalFree(hGlob);
		return;
	}
	CloseClipboard();
}


void CCreatImageWidthTableDlg::OnBnClickedButCopyChar()
{
	CString mTable;
	int mLen = 0;
	GetDlgItemText(IDC_EDIT_TABLE_CHAR, mTable);
	if (mTable == _T(""))
	{
		return;
	}
	mLen = (mTable.GetLength() + 1) * 2;
	char *nstringw = new char[mLen];

	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, mLen, mTable, _TRUNCATE);

	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	// Remove the current Clipboard contents
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}
	// Get the currently selected data
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, mLen);
	//strcpy_s((char*)hGlob, 64, "Current selection\r\n");
	strcpy_s((char*)hGlob, mLen, nstringw);

	// For the appropriate data formats...
	if (::SetClipboardData(CF_TEXT, hGlob) == NULL)
	{
		CString msg;
		msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
		AfxMessageBox(msg);
		CloseClipboard();
		GlobalFree(hGlob);
		return;
	}
	CloseClipboard();
}


void CCreatImageWidthTableDlg::OnEnChangeEditFolder()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	GetDlgItemText(IDC_EDIT_FOLDER, m_Folder);
}
