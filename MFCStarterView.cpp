
// MFCStarterView.cpp : implementation of the CMFCStarterView class
//

#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCStarter.h"
#endif

#include "MFCStarterDoc.h"
#include "MFCStarterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCStarterView
constexpr UINT ID_BUTTON1{ 101 };
IMPLEMENT_DYNCREATE(CMFCStarterView, CView)

BEGIN_MESSAGE_MAP(CMFCStarterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_BN_CLICKED(ID_BUTTON1, OnBtnClicked) //def. funckcije dugmeta
END_MESSAGE_MAP()

// CMFCStarterView construction/destruction

CMFCStarterView::CMFCStarterView() noexcept
{

}

CMFCStarterView::~CMFCStarterView()
{
}

BOOL CMFCStarterView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
// CMFCStarterView drawing
void CMFCStarterView::OnDraw(CDC* pDC)
{
	CMFCStarterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;
	
	//povrsina na kojoj cu crtati, pozadinska boja siva, na njoj se iscrtava i grid 
	CRect rect(10, 50, 510, 550);

	CBrush brush;
	//siva cetka za background rekt
	brush.CreateSolidBrush(RGB(208, 208, 208));
	//crtanje default olovkom i datom cetkom
	//pDC->FillRect(&rect, &brush);
	int nPoints = 4;
	double pi = 3.145926535;
	double alpha = pi / 2;
	int radius = 100;
	CPoint ptCenter(100,100);
	double dAlpha = 2 * pi / nPoints;
	CPoint arPoints[4];
	for (int iPoint = 0; iPoint < nPoints; iPoint++) {

		arPoints[iPoint].x = ptCenter.x + radius * cos(alpha);

		arPoints[iPoint].y = ptCenter.y + radius * sin(alpha);

		alpha += dAlpha;

	}

	pDC->Polygon(arPoints, nPoints);

	//pDC->Polygon(arPoints, nPoints);
	CRect rk = new CRect(10,10,100,100);
	CPen pen(PS_DASH, 5, RGB(0,0,0));
	pDC->SelectObject(pen);
	//pDC->Rectangle(10,10,100,100);
	//da bi ondraw bio pregledniji napravio sam posebnu funkciju za crtanje objekta u tangramu
	//DrawPolygon(pDC);

	//crtanje mreze
	//if (btnInvalidateGridLines) { //default je true, tada crta, 
	//	//klik dugmeta menja na false i tada ne crta mrezu
	//	CPen pen;
	//	//pen.CreateStockObject(PS_COSMETIC);
	//	pen.CreatePen(PS_COSMETIC,0, RGB(245, 245, 245));
	//	pDC->SelectObject(&pen);

	//	//crtanje linije po linije uz dati pomeraj, grid overlay
	//	for (int i = 0; i < 475; i += 25) {
	//		//y
	//		pDC->MoveTo(i, -25);
	//		pDC->LineTo(i, 475);
	//		//x
	//		pDC->MoveTo(-25, i);
	//		pDC->LineTo(475, i);
	//	}
	//	pen.DeleteObject();
	//}
}
//pomocna funkcija za crtanje svih mnogouglova
void crtanjeMnogouglova(CDC* pDC,int brojUglova, CPoint *c, int dim) {
	double step = 0;
	for (int i = 0; i < brojUglova; i++) {
		c[i].x = dim * cos(step * M_PI / 180);
		c[i].y = dim * sin(step * M_PI / 180);
		step += 360/brojUglova;
	}
	pDC->Polygon(c, brojUglova);
}
void CMFCStarterView::DrawPolygon(CDC* pDC)
{
	//olovka, okrugli spoj i deblja, boja nijansa plave
	CPen penFirst(PS_USERSTYLE | PS_JOIN_ROUND, 7, RGB(0, 255, 204));
	CPen* pOldPen = pDC->SelectObject(&penFirst);

	//cetka, pink, za prvi trougao koji crtam
	CBrush brushFirst(RGB(255, 153, 255));
	CBrush* pOldBrush = pDC->SelectObject(&brushFirst);

	//stavljam pocetak za crtanje, zbog dugmeta, i pregledniojeg prikaza, da nije uz ivicu
	pDC->SetViewportOrg(35,75);
	
	//niz tacaka za sve sto se crta
	CPoint pts[8];
	
	//----------- pink trougao -----------------
	pts[0].x = 0;
	pts[0].y = 0;

	pts[1].x = 0;
	pts[1].y = 425;

	pts[2].x = 213;
	pts[2].y = 213;

	//centar za trougao, gde ce biti centar mnogougla u njemu
	double centerCounterX = (pts[0].x + pts[1].x + pts[2].x) / 3;
	double centerCounterY = (pts[0].y + pts[1].y + pts[2].y) / 3;
	CPoint pinkCentar(centerCounterX+25, centerCounterY);
	
	pDC->Polygon(pts, 3);

	brushFirst.DeleteObject();

	//------ crveni trougao -----------
	pts[1].x = 300;
	pts[1].y = 0;

	pts[2].x = 150;
	pts[2].y = 150;

	centerCounterX = (pts[0].x + pts[1].x + pts[2].x) / 3;
	centerCounterY = (pts[0].y + pts[1].y + pts[2].y) / 3;
	CPoint crveniCentar(centerCounterX, centerCounterY+10);
	
	CBrush brushSecond(RGB(255, 0, 0));
	pDC->SelectObject(&brushSecond);

	pDC->Polygon(pts, 3);
	brushSecond.DeleteObject();

	//--------- zuti trougao -----------
	CBrush brushThird(RGB(255, 255, 0));
	pDC->SelectObject(&brushThird);

	pts[0].x = 300;
	pts[0].y = 150;

	////centar za monougao
	centerCounterX = (pts[0].x + pts[1].x + pts[2].x) / 3;
	centerCounterY = (pts[0].y + pts[1].y + pts[2].y) / 3;

	CPoint zutiCentar(centerCounterX+5, centerCounterY+5);

	pDC->Polygon(pts, 3);
	brushThird.DeleteObject();

	//---- zeleni kvadrat ------
	CBrush brushForth(RGB(0,204, 0));
	pDC->SelectObject(&brushForth);

	pDC->Rectangle(300, 0, 450, 150);
	brushForth.DeleteObject();

	//-----narandzasti trougao------
	pts[1].x = 450;
	pts[1].y = 150;

	pts[2].x = 450;
	pts[2].y = 300;

	//centar za mnogougao
	centerCounterX = (pts[0].x + pts[1].x + pts[2].x) / 3;
	centerCounterY = (pts[0].y + pts[1].y + pts[2].y) / 3;
	CPoint narandzastiCentar(centerCounterX+5, centerCounterY-5);

	CBrush BrushFifth(RGB(255, 102, 0));
	pDC->SelectObject(&BrushFifth);

	pDC->Polygon(pts, 3);
	BrushFifth.DeleteObject();

	// ---------- paralelogram, ljubicasta --------
	CBrush BrushSixth(RGB(153, 0, 153));
	pDC->SelectObject(&BrushSixth);

	pts[1].x = pts[2].x;
	pts[1].y = pts[2].y;

	pts[2].x = 450;
	pts[2].y = 450;

	pts[3].x = 300;
	pts[3].y = pts[1].y;
	
	pDC->Polygon(pts, 4);

	BrushSixth.DeleteObject();

	//-------- trougao, srafura linije, bela boja ------
	pts[0].x = 237;
	pts[0].y = 237;

	pts[1].x = 27;
	pts[1].y = 450;

	//tacke centara trougla
	centerCounterX = (pts[1].x + pts[2].x) / 2;
	centerCounterY = (pts[1].y + pts[0].y) / 2;
	CPoint beliSrafuraCentar(centerCounterX, centerCounterY+25);

	CBrush BrushSeventh(HS_HORIZONTAL, RGB(51, 204, 255));
	pDC->SelectObject(&BrushSeventh);

	pDC->Polygon(pts, 3);

	BrushSeventh.DeleteObject();
	penFirst.DeleteObject();

	//za ostrije uglove jer je olovka tanja, za mnogougle
	CPen penSecond(PS_SOLID | PS_JOIN_MITER, 3, RGB(0, 255, 204));
	pDC->SelectObject(&penSecond);


	//transparentna cetka za crtanje mnogouglova
	CBrush BrushEighth;
	BrushEighth.CreateStockObject(NULL_BRUSH);
	pDC->SelectObject(&BrushEighth);

	//cetvorougao  u roze trouglu	
	pDC->SetWindowOrg(-pinkCentar.x, -pinkCentar.y);
	crtanjeMnogouglova(pDC, 4, pts, 50);
	
	//sestougao u crvenon trouglu
	pDC->SetWindowOrg(-crveniCentar.x, -crveniCentar.y);
	crtanjeMnogouglova(pDC, 6, pts, 30);

	// sedmougao u zutom trouglu
	pDC->SetWindowOrg(-zutiCentar.x, -zutiCentar.y);
	crtanjeMnogouglova(pDC, 7, pts, 30);

	//petougao u narandzastom trouglu
	pDC->SetWindowOrg(-narandzastiCentar.x, -narandzastiCentar.y);
	crtanjeMnogouglova(pDC, 5, pts, 30);

	// osmougao u srafiranom, belom trouglu
	pDC->SetWindowOrg(-beliSrafuraCentar.x, -beliSrafuraCentar.y);
	crtanjeMnogouglova(pDC, 8, pts, 50);

	BrushEighth.DeleteObject();
	penSecond.DeleteObject();
	
	//vracam na pocetnu poziciju, bez ovoga dugme se crta van prozora
	pDC->SetWindowOrg(0, 0);

	//vracamo default cetku i olovku
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

BOOL CMFCStarterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCStarterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CMFCStarterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{ 

}


// CMFCStarterView diagnostics

#ifdef _DEBUG
void CMFCStarterView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCStarterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCStarterDoc* CMFCStarterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCStarterDoc)));
	return (CMFCStarterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCStarterView message handlers

//funkcija za klik dugmeta
void CMFCStarterView::OnBtnClicked()
{
	btnInvalidateGridLines = !btnInvalidateGridLines;
	Invalidate(); //brise i ponovo zove onDraw za crtanje
}

int CMFCStarterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	LVS_EX_GRIDLINES ;
	//dugme za mrezu
	grid_OnAndOff_Button.Create(_T("GRID OVERLAY"), BS_PUSHBUTTON, CRect(10,5,200,40), this, ID_BUTTON1);
	grid_OnAndOff_Button.ShowWindow(SW_SHOW);

	return 0;
}
