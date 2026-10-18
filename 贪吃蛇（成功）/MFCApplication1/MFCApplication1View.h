#include "pch.h"
#pragma once
#include "Snake.h"
#include "Food.h"
#include "Config.h"

class CMFCApplication1View : public CView
{
protected: 
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;
protected:
	Snake* m_pSnake;
	Food* m_pFood;
	Config m_config;
	int    m_score;
	bool   m_isGameOver;
	int m_nSpeed;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void GameInit();
	void GameUpdate();
	void GameOver();
	afx_msg void OnDiffEasy();
	afx_msg void OnDiffMid();
	afx_msg void OnDiffSup();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGameStart();
};

#ifndef _DEBUG  
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

