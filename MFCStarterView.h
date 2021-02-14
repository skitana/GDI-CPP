
// MFCStarterView.h : interface of the CMFCStarterView class
//

#pragma once


class CMFCStarterView : public CView
{
public:
	CButton grid_OnAndOff_Button;//kreiranje dugmeta za mrezu
protected: // create from serialization only
	CMFCStarterView() noexcept;
	DECLARE_DYNCREATE(CMFCStarterView)

// Attributes
public:
	CMFCStarterDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	bool btnInvalidateGridLines = true; //marker za mrezu
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawPolygon(CDC* pDC);//dodata funkcija radi preglednosti onDraw
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCStarterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBtnClicked();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

};

#ifndef _DEBUG  // debug version in MFCStarterView.cpp
inline CMFCStarterDoc* CMFCStarterView::GetDocument() const
   { return reinterpret_cast<CMFCStarterDoc*>(m_pDocument); }
#endif

