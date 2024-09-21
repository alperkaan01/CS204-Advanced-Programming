
// CS204_THE6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS204_THE6.h"
#include "CS204_THE6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCS204_THE6Dlg dialog



CCS204_THE6Dlg::CCS204_THE6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCS204_THE6Dlg::IDD, pParent)
	, RadioButtons(0)
	, comboGroup(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCS204_THE6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, OperandBox1);
	DDX_Control(pDX, IDC_EDIT2, OperandBox2);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_CHECK2, CheckBoxShift);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_EDIT3, editBoxShift);
	DDX_Control(pDX, IDC_BUTTON1, ComputeButton);
	DDX_Radio(pDX, IDC_RADIO2, RadioButtons);
	DDX_CBIndex(pDX, IDC_COMBO1, comboGroup);
}

BEGIN_MESSAGE_MAP(CCS204_THE6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK2, &CCS204_THE6Dlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON1, &CCS204_THE6Dlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_RADIO2, &CCS204_THE6Dlg::OnBnClickedRadio2)
//	ON_BN_CLICKED(IDC_RADIO3, &CCS204_THE6Dlg::OnBnClickedRadio3)
//	ON_BN_CLICKED(IDC_RADIO4, &CCS204_THE6Dlg::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO3, &CCS204_THE6Dlg::OnBnClickedRadio3)
ON_BN_CLICKED(IDC_RADIO2, &CCS204_THE6Dlg::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_RADIO4, &CCS204_THE6Dlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CCS204_THE6Dlg message handlers

BOOL CCS204_THE6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCS204_THE6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCS204_THE6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCS204_THE6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//-------------------------------------CLICK-----------------------------------

int maxSize = 0;
int globInt= 0;

void CCS204_THE6Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	unsigned int uOperand1, uOperand2;
	CString operand1, operand2, SelectedRadio, shiftDirection, shiftAmount, result;

	CDC * pDC = GetDC();
	CSize cz;

	OperandBox1.GetWindowTextW(operand1);
	OperandBox2.GetWindowTextW(operand2);

	uOperand1 =  _tcstoul(operand1,nullptr,10);
	uOperand2 = _tcstoul(operand2,nullptr,10);


	if(CheckBoxShift.GetCheck())
	{
		editBoxShift.GetWindowTextW(shiftAmount);
	}


	if(operand1.GetLength() <= 0 || operand2.GetLength() <= 0 )
	{
		result = _T("At least one operand was not entered.");
		list.AddString(result);
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize)
			maxSize = cz.cx;
	}else if(CheckBoxShift.GetCheck() && shiftAmount.GetLength() <= 0)
	{
		result = _T("Specify how many bits you want to shift");
		list.AddString(result);
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize)
			maxSize = cz.cx;
	}else
	{
		//Operations
		
		if(globInt == 0) //Instead of radio button indexes I used global variable which changes with radio button press operation
		{
			unsigned int uMyResult = uOperand1 & uOperand2;
			CString sMyResult;
			if(!CheckBoxShift.GetCheck())
			{
				sMyResult.Format(_T("%u"), uMyResult);
				result = operand1 + _T(" AND ") + operand2 + _T(" = ") + sMyResult;
				list.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
			}else
			{
				int indx = combo1.GetCurSel();
				combo1.GetLBText(indx, shiftDirection);
				int iShiftAmount = _ttoi(shiftAmount);
				if(shiftDirection == _T("Left"))
				{
					uOperand1 = uOperand1 << iShiftAmount;
					uOperand2 = uOperand2 << iShiftAmount;
				}else{
					uOperand1 = uOperand1 >> iShiftAmount;
					uOperand2 = uOperand2 >> iShiftAmount;
				}
				uMyResult = uOperand1 & uOperand2;
				sMyResult.Format(_T("%u"), uMyResult);
				operand1.Format(_T("%u"), uOperand1);
				operand2.Format(_T("%u"), uOperand2);
				result = operand1 + _T(" AND ") + operand2 + _T(" = ") + sMyResult;
				list.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
			}
		}
		else if(globInt == 1)
		{
			unsigned int uMyResult = uOperand1 | uOperand2;
			CString sMyResult;
			if(!CheckBoxShift.GetCheck())
			{
				sMyResult.Format(_T("%u"), uMyResult);
				result = operand1 + _T(" OR ") + operand2 + _T(" = ") + sMyResult;
				list.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
				
			}else
			{
				int indx = combo1.GetCurSel();
				combo1.GetLBText(indx, shiftDirection);
				int iShiftAmount = _ttoi(shiftAmount);
				if(shiftDirection == _T("Left"))
				{
					uOperand1 = uOperand1 << iShiftAmount;
					uOperand2 = uOperand2 << iShiftAmount;
				}else{
					uOperand1 = uOperand1 >> iShiftAmount;
					uOperand2 = uOperand2 >> iShiftAmount;
				}
				uMyResult = uOperand1 | uOperand2;
				sMyResult.Format(_T("%u"), uMyResult);
				operand1.Format(_T("%u"), uOperand1);
				operand2.Format(_T("%u"), uOperand2);
				result = operand1 + _T(" OR ") + operand2 + _T(" = ") + sMyResult;
				list.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
			}
		}
		else if(globInt == 2)
		{
			unsigned int uMyResult = uOperand1 ^ uOperand2;
			CString sMyResult;
			if(!CheckBoxShift.GetCheck())
			{
				sMyResult.Format(_T("%u"), uMyResult);
				result = operand1 + _T(" XOR ") + operand2 + _T(" = ") + sMyResult;
				list.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
			}else
			{
				int indx = combo1.GetCurSel();
				combo1.GetLBText(indx, shiftDirection);
				int iShiftAmount = _ttoi(shiftAmount);
				if(shiftDirection == _T("Left"))
				{
					uOperand1 = uOperand1 << iShiftAmount;
					uOperand2 = uOperand2 << iShiftAmount;
				}else{
					uOperand1 = uOperand1 >> iShiftAmount;
					uOperand2 = uOperand2 >> iShiftAmount;
				}
				uMyResult = uOperand1 ^ uOperand2;
				sMyResult.Format(_T("%u"), uMyResult);
				operand1.Format(_T("%u"), uOperand1);
				operand2.Format(_T("%u"), uOperand2);
				result = operand1 + _T(" XOR ") + operand2 + _T(" = ") + sMyResult;
				list.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
			}
		}else
		{/*Do nothing*/
		}
	}
	list.SetHorizontalExtent(maxSize);
}

void CCS204_THE6Dlg::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
	if(CheckBoxShift.GetCheck())
	{
		combo1.EnableWindow(TRUE);
		editBoxShift.EnableWindow(TRUE);
	}else
	{
		combo1.EnableWindow(FALSE);
		editBoxShift.EnableWindow(FALSE);
	}
}



void CCS204_THE6Dlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	globInt = 0;
	
}


void CCS204_THE6Dlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	globInt = 1;
}


void CCS204_THE6Dlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	globInt = 2;
}