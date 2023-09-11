
// MFCLoginDlg.h: 头文件
//

#pragma once


// CMFCLoginDlg 对话框
class CMFCLoginDlg : public CDialogEx
{
// 构造
public:
	CMFCLoginDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnBnClickedOk();
	void OnBnClickedCancel();

	void OnEnChangePsw();
	
	LRESULT OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	// username
	// username
	CString m_csName;
	CString m_PSW;
	IPicture* m_picture;
	OLE_XSIZE_HIMETRIC m_width;
	OLE_YSIZE_HIMETRIC m_height;
	BOOL m_IsShow;
};
