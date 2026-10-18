#include "pch.h"
#include "Food.h"
#include "Snake.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_DIFF_EASY, &CMFCApplication1View::OnDiffEasy)
    ON_COMMAND(ID_DIFF_MID, &CMFCApplication1View::OnDiffMid)
    ON_COMMAND(ID_DIFF_SUP, &CMFCApplication1View::OnDiffSup)
    ON_WM_TIMER()
    ON_WM_KEYDOWN()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_Game_Start, &CMFCApplication1View::OnGameStart)
END_MESSAGE_MAP()

CMFCApplication1View::CMFCApplication1View() noexcept
{
    m_pSnake = new Snake();
    m_nSpeed = 300;

    m_pFood = new Food();

    m_score = 0;
    m_isGameOver = false;
}

CMFCApplication1View::~CMFCApplication1View()
{
    if (m_pSnake) {
        delete m_pSnake;
        m_pSnake = nullptr;
    }

    if (m_pFood) {
        delete m_pFood;
        m_pFood = nullptr;
    }
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
    return CView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnDraw(CDC* pDC)
{
    int size = 20;
    int mapW = m_config.GetWidth();
    int mapH = m_config.GetHeight();

    // Draw border (wall) using 4 lines
    CPen borderPen(PS_SOLID, 2, RGB(100, 100, 100));
    CPen* pOldPen = pDC->SelectObject(&borderPen);
    pDC->MoveTo(0, 0);
    pDC->LineTo(mapW * size, 0);
    pDC->LineTo(mapW * size, mapH * size);
    pDC->LineTo(0, mapH * size);
    pDC->LineTo(0, 0);
    pDC->SelectObject(pOldPen);

    // Draw food
    if (m_pFood) {
        Point fPos = m_pFood->GetPosition();
        CBrush redBrush(RGB(255, 0, 0));
        CBrush* pOldBr = pDC->SelectObject(&redBrush);
        pDC->Rectangle(fPos.x * size, fPos.y * size, (fPos.x + 1) * size, (fPos.y + 1) * size);
        pDC->SelectObject(pOldBr);
    }

    // Draw snake
    if (m_pSnake) {
        auto body = m_pSnake->GetBody();
        CBrush greenBrush(RGB(0, 255, 0));
        CBrush* pOldBr = pDC->SelectObject(&greenBrush);

        for (const auto& node : body) {
            pDC->Rectangle(node.x * size, node.y * size, (node.x + 1) * size, (node.y + 1) * size);
        }

        pDC->SelectObject(pOldBr);
    }

    // Draw score panel (to the right of the map)
    int panelX = mapW * size + 20;
    CFont scoreFont;
    scoreFont.CreatePointFont(160, _T("Arial"));
    CFont* pOldFont = pDC->SelectObject(&scoreFont);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);

    CString scoreText;
    scoreText.Format(_T("Score: %d"), m_score);
    pDC->TextOut(panelX, 20, scoreText);

    CString speedText;
    speedText.Format(_T("Speed: %d ms"), m_nSpeed);
    pDC->TextOut(panelX, 50, speedText);

    pDC->SelectObject(pOldFont);
}


BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
    return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
    CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
    return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


void CMFCApplication1View::GameInit()
{
    m_score = 0;
    m_isGameOver = false;
    m_nSpeed = 300;

    if (m_pSnake) { delete m_pSnake; }
    m_pSnake = new Snake();

    if (m_pFood) { delete m_pFood; }
    m_pFood = new Food();
    m_pFood->GenerateFood(m_config.GetWidth(), m_config.GetHeight(), m_pSnake->GetBody());

    SetFocus();

    Invalidate();
}

void CMFCApplication1View::GameUpdate()
{
    // Calculate next head position
    Point nextHead = m_pSnake->GetHead();
    switch (m_pSnake->GetDirection()) {
    case UP:    nextHead.y--; break;
    case DOWN:  nextHead.y++; break;
    case LEFT:  nextHead.x--; break;
    case RIGHT: nextHead.x++; break;
    }

    // Wall collision check
    if (nextHead.x < 0 || nextHead.x >= m_config.GetWidth() || nextHead.y < 0 || nextHead.y >= m_config.GetHeight()) {
        GameOver();
        return;
    }

    // Food check (using next position)
    Point foodPos = m_pFood->GetPosition();
    bool bEat = false;

    if (nextHead.x == foodPos.x && nextHead.y == foodPos.y)
    {
        bEat = true;
        m_pFood->GenerateFood(m_config.GetWidth(), m_config.GetHeight(), m_pSnake->GetBody());
        m_score += m_config.GetScoreReward();
    }

    // Move snake
    m_pSnake->Move(bEat);

    // Self-collision check (must be AFTER Move)
    if (m_pSnake->CheckCollision()) {
        GameOver();
        return;
    }

    Invalidate();
}

void CMFCApplication1View::GameOver()
{
    KillTimer(1);

    int nRet = AfxMessageBox(_T("Game Over! Restart?"), MB_YESNO | MB_ICONQUESTION);

    if (nRet == IDYES) {
        GameInit();
        SetTimer(1, m_nSpeed, NULL);
    }
}

void CMFCApplication1View::OnDiffEasy()
{
    m_nSpeed = 500;
    SetTimer(1, m_nSpeed, NULL);
}

void CMFCApplication1View::OnDiffMid()
{
    m_nSpeed = 300;
    SetTimer(1, m_nSpeed, NULL);
}

void CMFCApplication1View::OnDiffSup()
{
    m_nSpeed = 100;
    SetTimer(1, m_nSpeed, NULL);
}

void CMFCApplication1View::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        GameUpdate();
    }

    CView::OnTimer(nIDEvent);
}

void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
    case VK_UP:    m_pSnake->ChangeDirection(UP); break;
    case VK_DOWN:  m_pSnake->ChangeDirection(DOWN); break;
    case VK_LEFT:  m_pSnake->ChangeDirection(LEFT); break;
    case VK_RIGHT: m_pSnake->ChangeDirection(RIGHT); break;
    }

    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    CBrush whiteBrush(RGB(255, 255, 255));
    pDC->FillRect(&rect, &whiteBrush);
    return TRUE;
}

void CMFCApplication1View::OnGameStart()
{
    GameInit();

    SetFocus();

    SetTimer(1, m_nSpeed, NULL);
}