
// CS204_THE6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCS204_THE6Dlg dialog
class CCS204_THE6Dlg : public CDialogEx
{
// Construction
public:
	CCS204_THE6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CS204_THE6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit OperandBox1;
	CEdit OperandBox2;
	CListBox list;
	int RadioButtonAnd;
	int RadioButtonOr;
	int RadioButtonXOR;
	CButton CheckBoxShift;
	CComboBox combo1;
	CEdit editBoxShift;
	CButton ComputeButton;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton1();
	int AndBox;
	int OrBox;
	int XorBox;
	int RadioButtonGroup;
//	afx_msg void OnBnClickedRadio2();
//	afx_msg void OnBnClickedRadio3();
//	afx_msg void OnBnClickedRadio4();
	int RadioButtons;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio4();
	int comboGroup;
};
