// MFCLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCLogin.h"
#include "MFCLoginDlg.h"
#include "afxdialogex.h"
#include <afx.h>
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxdlgs.h>
#include <stdio.h>
#include <afxdisp.h>
#include <fstream>
#include <sstream>
#include <map>
#include<type_traits>


std::map<std::string, std::string> readCSV(const std::string& filename) {
    std::map<std::string, std::string> credentials;

    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, password;
        if (std::getline(iss, name, ',') && std::getline(iss, password)) {
            credentials[name] = password;
        }
    }

    return credentials;
}
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#undef ASSERT
#define ASSERT(x) ((void)0)

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
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


// CMFCLoginDlg 对话框

CMFCLoginDlg::CMFCLoginDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCLOGIN_DIALOG, pParent)
    , m_csName(_T(""))
    , m_PSW(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME, m_csName);
    DDX_Text(pDX, IDC_PSW, m_PSW);
}

BEGIN_MESSAGE_MAP(CMFCLoginDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDOK, &CMFCLoginDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CMFCLoginDlg::OnBnClickedCancel)
    ON_WM_NCHITTEST()
    ON_WM_CTLCOLOR()
    ON_EN_CHANGE(IDC_PSW, &CMFCLoginDlg::OnEnChangePsw)
END_MESSAGE_MAP()


BOOL CMFCLoginDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
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

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // TODO: 在此添加额外的初始化代码
    m_csName = "";
    m_PSW= "";
    UpdateData(FALSE);

    GetDlgItem(IDC_PSW)->SetFocus(); //限制一下，如果用户无密码输入，即 确定键 点击不了
    GetDlgItem(IDOK)->EnableWindow(FALSE);
    return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}




void CMFCLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

HCURSOR CMFCLoginDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMFCLoginDlg::OnBnClickedOk()
{
    CString sun;
    CString spwd; // 创造两个字符串变量来接受用户输入的信息（用户名和密码等）
    GetDlgItemText(IDC_NAME, sun); // 返回用户名
    GetDlgItemText(IDC_PSW, spwd); // 返回密码


    if (sun.IsEmpty())
    {
        MessageBox(_T("用户名不能为空！"));
        return;
    }
    if (spwd.IsEmpty())
    {
        MessageBox(_T("密码不能为空！"));
        return; 
    }

    /* 判断输入的用户名与密码是否正确
    使用用户名（可以是学号，也可以是名字）和密码（唯一）相匹配实现登陆
    如果其中一项为空或者错误都不可加入系统主页面，并且返回提示信息
    */
    std::map<std::string, std::string> credentials = readCSV("res//数据库.CSV");

    std::string usernameStr = CT2A(sun);
    std::string passwordStr = CT2A(spwd);

    if (credentials.count(usernameStr) > 0 && credentials[usernameStr] == passwordStr) {
        MessageBox(_T("用户登录成功"));
    }
    else {
        MessageBox(_T("用户名或密码错误"), _T("登录失败"));
    }

}



void CMFCLoginDlg::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    CDialogEx::OnCancel();
}


void CMFCLoginDlg::OnEnChangePsw()
{
    UpdateData(TRUE);
    GetDlgItem(IDOK)->EnableWindow(!m_PSW.IsEmpty());
}


void CMFCLoginDlg::OnPaint()
{
    CPaintDC dc(this);
    CFile m_file(_T("res//bgimg.jpg"), CFile::modeRead);
    //获取文件长度
    DWORD m_filelen = m_file.GetLength();
    //在堆上分配空间
    HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE, m_filelen);

    LPVOID pvdata = NULL;
    //锁定堆空间,获取指向堆空间的指针
    pvdata = GlobalLock(m_hglobal);

    //将文件数据读取到堆中
    m_file.Read(pvdata, m_filelen);

    IStream* m_stream;

    GlobalUnlock(m_hglobal);

    //在堆中创建流对象
    CreateStreamOnHGlobal(m_hglobal, TRUE, &m_stream);

    //利用流加载图像
    OleLoadPicture(m_stream, m_filelen, TRUE, IID_IPicture, (LPVOID*)&m_picture);
    m_stream->Release();

    m_picture->get_Width(&m_width);// 宽高，MM_HIMETRIC 模式，单位是0.01毫米
    m_picture->get_Height(&m_height);
    m_IsShow = TRUE;
    m_file.Close();

    if (m_IsShow == TRUE) {
        CRect rect;
        GetClientRect(rect);
        int nW, nH;
        nW = (int)(rect.Width());
        nH = (int)(rect.Height());
        m_picture->Render(dc, 0, 0, nW, nH, 0, m_height, m_width, -m_height, &rect);
    }
    CDialog::OnPaint();
}

LRESULT CMFCLoginDlg::OnNcHitTest(CPoint point)
{
    LRESULT ret = CDialogEx::OnNcHitTest(point);
    return (ret == HTCLIENT) ? HTCAPTION : ret;
}