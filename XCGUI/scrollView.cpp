/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup scrollView ������ͼ(ScrollView)
/// @ingroup groupElements
/// @{

/// @brief ����������ͼԪ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XSView_Create(int x, int y, int cx, int cy,HXCGUI hParent)
{
	scrollView_ *pScrollView=(scrollView_*)malloc(sizeof(scrollView_));
	if (pScrollView)
	{
		memset(pScrollView,0,sizeof(scrollView_));
		SView_Init((HELE)pScrollView,x,y,cx,cy,XC_SCROLLVIEW,hParent);
	}
	return (HELE)pScrollView;
}

void SView_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_SCROLLVIEW);
	/////////////////////////////////////////////////////////////
	scrollView_ *pScrollView=SCROLLVIEW(hEle);
	pScrollView->bHScroll=TRUE;
	pScrollView->bVScroll=TRUE;
	pScrollView->left=2;
	pScrollView->top=2;
	pScrollView->right=2;
	pScrollView->bottom=2;

	pScrollView->barWidth=16;
	pScrollView->sizeLine.cx=20;
	pScrollView->sizeLine.cy=20;

	pScrollView->sizeTotal.cx=0;
	pScrollView->sizeTotal.cy=0;

	int width=cx-pScrollView->left-pScrollView->right;//-pScrollView->barWidth;
	int height=cy-pScrollView->top-pScrollView->bottom;//-pScrollView->barWidth;

	//��ͼ
	ele_  *pEleView=(ele_*)malloc(sizeof(ele_));
	if(NULL==pEleView) return;
	memset(pEleView,0,sizeof(ele_));
	Ele_Init((HELE)pEleView,pScrollView->left,pScrollView->top,width,height,XC_SCROLLVIEW_VIEW,hEle);
	pScrollView->hView=(HELE)pEleView;
	
	XEle_EnableFocus(pScrollView->hView,FALSE);
	XEle_EnableBorder(pScrollView->hView,FALSE);

	//����ˮƽ������
	pScrollView->pScrollBarH=(ele_*)XSBar_Create(pScrollView->left,cy-pScrollView->bottom-pScrollView->barWidth,pScrollView->sizeView.cx,pScrollView->barWidth,SY_HSCROLL);
	XEle_AddEle(hEle,(HELE)pScrollView->pScrollBarH);

	//������ֱ������
	pScrollView->pScrollBarV=(ele_*)XSBar_Create(cx-pScrollView->right-pScrollView->barWidth,pScrollView->top,pScrollView->barWidth,pScrollView->sizeView.cy,SY_VSCROLL);
	XEle_AddEle(hEle,(HELE)pScrollView->pScrollBarV);

	XEle_EnableFocus(hEle,TRUE);

	XEle_RegisterMessage(hEle,XM_PAINT,SView_OnDraw);
	XEle_RegisterMessage(hEle,XM_LBUTTONDOWN,SView_OnLButtonDown);
	XEle_RegisterMessage(hEle,XM_RBUTTONDOWN,SView_OnRButtonDown);

	XEle_RegisterEvent(hEle,XE_HSCROLL,SView_OnEventHScroll);
	XEle_RegisterEvent(hEle,XE_VSCROLL,SView_OnEventVScroll);
	XEle_RegisterEvent(hEle,XE_MOUSEWHEEL,SView_OnEventMouseWheel);

	XEle_RegisterEvent(hEle,XE_DESTROY,SView_OnDestroy);
	XEle_RegisterEvent(hEle,XE_SIZE,SView_OnEventSize);

	XEle_RegisterMessage(pScrollView->hView,XM_LBUTTONDOWN,SView_OnLButtonDown_View);

	XSView_Adjust(hEle);
}

void CALLBACK SView_OnDestroy(HELE hEle) //����
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	drawScrollView_ *pObj=SCROLLVIEW(hEle)->pDrawScrollViewList;
	drawScrollView_ *pDel=NULL;
	while(pObj)
	{
		pDel=pObj;
		pObj=pObj->pNext;
#ifdef	XCGUI_PLUS          //C++��֧��,�����Ա����ע���֧��
		if(pDel->pClass_Fun_Info)
			free(pDel->pClass_Fun_Info);
#endif
		free(pDel);
	}

	if(SCROLLVIEW(hEle)->hImage_bk) XImage_Destroy(SCROLLVIEW(hEle)->hImage_bk);
}

/// @brief ע�������ͼ���ƺ���,����ע��������.
/// @param hEle Ԫ�ؾ��.
/// @param pFun ������ͼ���ƺ�����.������������:
/// @code  BOOL CALLBACK DrawScrollView(HELE hEle,HDRAW hDraw);  @endcode
void WINAPI XSView_SetDrawScrollView(HELE hEle,pFunDrawScrollView pFun)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	drawScrollView_ *pNew=(drawScrollView_*)malloc(sizeof(drawScrollView_));//new drawScrollView_;
	pNew->pFun=pFun;
	pNew->pNext=NULL;
#ifdef	XCGUI_PLUS  //C++��֧��,�����Ա����ע���֧��
	pNew->pClass_Fun_Info=NULL;
#endif

	if(NULL==SCROLLVIEW(hEle)->pDrawScrollViewList)
	{
		SCROLLVIEW(hEle)->pDrawScrollViewList=pNew;
	}else
	{
		pNew->pNext=SCROLLVIEW(hEle)->pDrawScrollViewList;
		SCROLLVIEW(hEle)->pDrawScrollViewList=pNew;
	}

}
/// @brief ��ȡ������ͼ��Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @return ������Ԫ��.
HELE WINAPI XSView_GetView(HELE hEle) //��ȡ��Ԫ��
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return ((scrollView_*)hEle)->hView;
}

/// @brief ���Ԫ�ص�������ͼ,
/// @param hEle Ԫ�ؾ��.
/// @param hNewEle  Ҫ��ӵ���Ԫ����Դ���.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_AddEle(HELE hEle,HELE hNewEle) //���Ԫ�ص�������ͼ
{
	return XEle_AddEle(((scrollView_*)hEle)->hView,hNewEle);
}

#ifdef	XCGUI_PLUS          //C++��֧��,�����Ա����ע���֧��
void WINAPI XSView_SetDrawScrollViewEx(HELE hEle,pFunClassEventMsg pCallBackFun,void *pClass_Fun_Info)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	drawScrollView_ *pNew=(drawScrollView_*)malloc(sizeof(drawScrollView_));
	pNew->pFun=(pFunDrawScrollView)pCallBackFun;
	pNew->pNext=NULL;
	pNew->pClass_Fun_Info=pClass_Fun_Info;

	if(NULL==SCROLLVIEW(hEle)->pDrawScrollViewList)
	{
		SCROLLVIEW(hEle)->pDrawScrollViewList=pNew;
	}else
	{
		pNew->pNext=SCROLLVIEW(hEle)->pDrawScrollViewList;
		SCROLLVIEW(hEle)->pDrawScrollViewList=pNew;
	}
}
#endif

/// @brief ������ͼ�����ܴ�С(�������߿���).
/// @param hEle Ԫ�ؾ��.
/// @param cx  ��ͼ���ݿ��.
/// @param cy  ��ͼ���ݸ߶�.
void WINAPI XSView_SetSize(HELE hEle,int cx, int cy)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	SCROLLVIEW(hEle)->sizeTotal.cx=cx;
	SCROLLVIEW(hEle)->sizeTotal.cy=cy;
	XSView_Adjust(hEle);
}

/// @brief ��ȡ�ӿ�ԭ��X����.
/// @param hEle Ԫ�ؾ��.
/// @return �ӿ�ԭ��X����,ֵΪС�ڻ����0,����ֵ.
int WINAPI XSView_GetHViewPos(HELE hEle)   //��ȡ�ӿ�ԭ��X����
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return -(SCROLLVIEW(hEle)->hPos*SCROLLVIEW(hEle)->sizeLine.cx);
}

/// @brief ��ȡ�ӿ�ԭ��Y����.
/// @param hEle Ԫ�ؾ��.
/// @return �ӿ�ԭ��Y����.
int WINAPI XSView_GetVViewPos(HELE hEle)   //��ȡ�ӿ�ԭ��Y����
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return -(SCROLLVIEW(hEle)->vPos*SCROLLVIEW(hEle)->sizeLine.cy);
}

/// @brief ��ȡ�ӿ�����(�����߿���),leftΪ�ӿ�������С,topΪ�ӿ��ϼ����С,��(0,0).
/// @param hEle Ԫ�ؾ��.
/// @param pRect �����ӿ�����.
void WINAPI XSView_GetViewRect(HELE hEle,RECT *pRect) //��ȡ��ͼ����
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	pRect->left=SCROLLVIEW(hEle)->left;
	pRect->top=SCROLLVIEW(hEle)->top;
	pRect->right=pRect->left+SCROLLVIEW(hEle)->sizeView.cx;
	pRect->bottom=pRect->top+SCROLLVIEW(hEle)->sizeView.cy;
}

/// @brief ��ȡ���õ����ݴ�С,���ص���XSView_SetSize()���õ�ֵ.
/// @param hEle Ԫ�ؾ��.
/// @param pSize ���մ�С.
void WINAPI XSView_GetSize(HELE hEle,SIZE *pSize)  //��ȡ���õ����ݴ�С
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	*pSize=SCROLLVIEW(hEle)->sizeTotal;
}

/// @brief ��ȡ������ͼԪ���ϵ�ˮƽ������.��������ΪScrollBarԪ�ؾ��.
/// @param hEle Ԫ�ؾ��.
/// @return ������Ԫ�ؾ��.
HELE WINAPI XSView_GetHScrollBar(HELE hEle) //��ȡˮƽ������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return (HELE)SCROLLVIEW(hEle)->pScrollBarH;
}

/// @brief ��ȡ������ͼԪ���ϵĴ�ֱ������.��������ΪScrollBarԪ�ؾ��.
/// @param hEle Ԫ�ؾ��.
/// @return ������Ԫ�ؾ��.
HELE WINAPI XSView_GetVScrollBar(HELE hEle) //��ȡ��ֱ������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return (HELE)SCROLLVIEW(hEle)->pScrollBarV;
}

/// @brief ˮƽ������,������ָ����.
/// @param hEle Ԫ�ؾ��.
/// @param pos ����λ��
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollHPos(HELE hEle,int pos) //������ָ����
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollPos((HELE)SCROLLVIEW(hEle)->pScrollBarH,pos);
}

/// @brief ��ֱ������,������ָ��λ��.
/// @param hEle Ԫ�ؾ��.
/// @param pos ����λ��
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollVPos(HELE hEle,int pos) //������ָ����
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollPos((HELE)SCROLLVIEW(hEle)->pScrollBarV,pos);
}

BOOL WINAPI XSView_ScrollHPosX(HELE hEle,int posX) //������ָ������
{
	IsScrollViewDebug(hEle,__FUNCTION__);

	scrollView_ *pSView=(scrollView_*)hEle;

	int pos=posX/pSView->sizeLine.cx;
	return XSView_ScrollHPos(hEle,pos+1);
}

BOOL WINAPI XSView_ScrollVPosY(HELE hEle,int posY) //������ָ������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	scrollView_ *pSView=(scrollView_*)hEle;
	int pos=posY/pSView->sizeLine.cy;
	return XSView_ScrollVPos(hEle,pos+1);

}
/// @brief �������.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollLeftLine(HELE hEle)    //�������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollUp((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief ���ҹ���.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollRightLine(HELE hEle)   //���ҹ���
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollDown((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief ���Ϲ���.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollTopLine(HELE hEle)      //���Ϲ���
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollUp((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief ���¹���.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollDownLine(HELE hEle)    //���¹���
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollDown((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief ˮƽ���������.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollLeft(HELE hEle)    //ˮƽ���������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollTop((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief ˮƽ�������Ҳ�.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollRight(HELE hEle)   //ˮƽ�������Ҳ�
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollBottom((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief ��ֱ����������.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollTop(HELE hEle)     //����������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollTop((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief ��ֱ�������ײ�.
/// @param hEle Ԫ�ؾ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XSView_ScrollBottom(HELE hEle)  //�������ײ�
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XSBar_ScrollBottom((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief ����������ͼ����.
/// @param hEle Ԫ�ؾ��.
void WINAPI XSView_Adjust(HELE hEle)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	scrollView_ *pSView=SCROLLVIEW(hEle);

	int cx=rect.right-rect.left;
	int cy=rect.bottom-rect.top;
	BOOL bShowH=FALSE, bShowV=FALSE;
	pSView->sizeView.cx=cx-pSView->left-pSView->right;
	pSView->sizeView.cy=cy-pSView->top-pSView->bottom;

	if(pSView->sizeTotal.cx>(pSView->sizeView.cx) && pSView->bHScroll) //��ʾˮƽ������
	{
		bShowH=TRUE;
		pSView->sizeView.cy-=pSView->barWidth;
	}
	if(pSView->sizeTotal.cy>(pSView->sizeView.cy) && pSView->bVScroll)  //��ʾ��ֱ������
	{
		bShowV=TRUE;
		pSView->sizeView.cx-=pSView->barWidth;
	}
	if(bShowV && FALSE==bShowH)
	{
		if((pSView->sizeTotal.cx>pSView->sizeView.cx) && pSView->bHScroll) //��ʾˮƽ������
		{
			bShowH=TRUE;
			pSView->sizeView.cy-=pSView->barWidth;
		}
	}
	if(bShowH && FALSE==bShowV)
	{
		if((pSView->sizeTotal.cy>pSView->sizeView.cy) && pSView->bVScroll)  //��ʾ��ֱ������
		{
			bShowV=TRUE;
			pSView->sizeView.cx-=pSView->barWidth;
		}
	}

	//ˮƽ������-------------------
	//�޸Ĺ�������

	double posd=0;
	int size=pSView->sizeTotal.cx-pSView->sizeView.cx;
	int pos=0;

	if(0!=size && 0!=pSView->sizeLine.cx)
	{
		posd=((double)(size))/pSView->sizeLine.cx;
		if(posd>0)
		{
			pos=(int)posd;
			if(posd>pos)
				pos++;
		}
	}

	pSView->pScrollBarH->rect.left=pSView->left;
	pSView->pScrollBarH->rect.top=cy-pSView->bottom-pSView->barWidth;
	pSView->pScrollBarH->rect.right=pSView->pScrollBarH->rect.left+pSView->sizeView.cx;
	pSView->pScrollBarH->rect.bottom=cy-pSView->bottom;

	XSBar_SetScrollRange((HELE)pSView->pScrollBarH,pos);

	//�޸Ĺ��������鳤��
	int btnLength=XSBar_GetButtonLength((HELE)pSView->pScrollBarH);

	int len=0;
	if(0!=pSView->sizeTotal.cx)
		len=(int)(((double)pSView->sizeView.cx/pSView->sizeTotal.cx)*(pSView->sizeView.cx-btnLength-btnLength-2));
	
	XSBar_SetSliderLength((HELE)pSView->pScrollBarH,len);

	XSBar_Adjust((HELE)pSView->pScrollBarH);
	if(bShowH)  //��ʾ
		XEle_ShowEle((HELE)pSView->pScrollBarH,TRUE);
	else
		XEle_ShowEle((HELE)pSView->pScrollBarH,FALSE);

	//��ֱ������---------------------------
	//�޸Ĺ�������

	int size2=pSView->sizeTotal.cy-pSView->sizeView.cy;
	pos=0;
	if( 0!=size2 && 0!=pSView->sizeLine.cy)
	{
		posd=((double)(size2))/pSView->sizeLine.cy;
		if(posd>0)
		{
			pos=(int)posd;
			if(posd>pos)
				pos++;
		}
	}

	//�޸Ĺ���������
	pSView->pScrollBarV->rect.left=cx-pSView->right-pSView->barWidth;
	if ( XC_LIST==((ele_*)hEle)->eleType )
	{
		pSView->pScrollBarV->rect.top=2;
	}else
		pSView->pScrollBarV->rect.top=pSView->top;
	pSView->pScrollBarV->rect.right=cx-pSView->right;
	pSView->pScrollBarV->rect.bottom=pSView->top+pSView->sizeView.cy;

	XSBar_SetScrollRange((HELE)pSView->pScrollBarV,pos);

	//�޸Ĺ��������鳤��
	btnLength=XSBar_GetButtonLength((HELE)pSView->pScrollBarV);

	int len2=0;
	if(0!=pSView->sizeTotal.cy)
		len2=(int)(((double)pSView->sizeView.cy/pSView->sizeTotal.cy)*(pSView->sizeView.cy-btnLength-btnLength-2));

	XSBar_SetSliderLength((HELE)pSView->pScrollBarV,len2);

	XSBar_Adjust((HELE)pSView->pScrollBarV);

	if(bShowV) //��ʾ
		XEle_ShowEle((HELE)pSView->pScrollBarV,TRUE);
	else
		XEle_ShowEle((HELE)pSView->pScrollBarV,FALSE);

	RECT rcView;
	rcView.left=pSView->left;
	rcView.top=pSView->top;
	rcView.right=rcView.left+pSView->sizeView.cx;
	rcView.bottom=rcView.top+pSView->sizeView.cy;
	XEle_SetRect(pSView->hView,&rcView);

}

/// @brief ������ͼԪ��,��ȡ�������Ŀ��,�����ˮƽ������,��ô��ȡ���Ǹ߶�.
/// @param hEle Ԫ�ؾ��.
/// @return ��ֱ�������Ŀ�Ȼ�ˮƽ�������ĸ߶�.
int WINAPI XSView_GetScrollBarWidth(HELE hEle)  //��ȡ���������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->barWidth;
}

/// @brief ˮƽ��������ǰ�Ƿ�ɼ�.
/// @param hEle Ԫ�ؾ��.
/// @return ���ˮƽ��������ǰ�ɼ�,����TRUE,�����෴.
BOOL WINAPI XSView_IsHScrollBarVisible(HELE hEle) //ˮƽ��������ǰ�Ƿ�ɼ�
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XEle_IsShowEle((HELE)SCROLLVIEW(hEle)->pScrollBarH);
}

/// @brief ������ͼԪ��,��ֱ��������ǰ�Ƿ�ɼ�.
/// @param hEle Ԫ�ؾ��.
/// @return �����ֱ��������ǰ�ɼ�,����TRUE,�����෴.
BOOL WINAPI XSView_IsVScrollBarVisible(HELE hEle) //��ֱ��������ǰ�Ƿ�ɼ�
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return XEle_IsShowEle((HELE)SCROLLVIEW(hEle)->pScrollBarV);
}

/// @brief ������ͼԪ��,���û����ˮƽ������.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable TRUE����,FALSE����.
void WINAPI XSView_EnableHScroll(HELE hEle,BOOL bEnable) //����ˮƽ������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	SCROLLVIEW(hEle)->bHScroll=bEnable;
}

/// @brief ������ͼԪ��,���û���ô�ֱ������.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable TRUE����,FALSE����.
void WINAPI XSView_EnableVScroll(HELE hEle,BOOL bEnable) //���ô�ֱ������
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	SCROLLVIEW(hEle)->bVScroll=bEnable;
}

/// @brief ��ȡ�ӿڿ��(�����߿�����������).
/// @param hEle Ԫ�ؾ��.
/// @return �ӿڿ��.
int  WINAPI XSView_GetViewWidth(HELE hEle)  //��ȡ�ӿڿ��
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->sizeView.cx;
}

/// @brief ������ͼԪ��,��ȡ������ͼ�߶�(�����߿�����������).
/// @param hEle Ԫ�ؾ��.
/// @return �ӿڸ߶�.
int  WINAPI XSView_GetViewHeight(HELE hEle) //��ȡ�ӿڸ߶�
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->sizeView.cy;
}

/// @brief ��ȡ�����ܿ��,��ȷ��(�����߿�����������),�����ݴ�СС���ӿڴ�Сʱ,���ص����ӿڴ�С.
/// @param hEle Ԫ�ؾ��.
/// @return �����ܿ��.
int  WINAPI XSView_GetHSizeTotalAccurate(HELE hEle) //��ȡ�����ܿ��,��ȷ��,,�����ݴ�СС���ӿڴ�Сʱ,���ص����ӿڴ�С
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	scrollView_ *pScrollView=SCROLLVIEW(hEle);
	int range=(SCROLLBAR(pScrollView->pScrollBarH))->range;
	return range*pScrollView->sizeLine.cx+pScrollView->sizeView.cx;
}

/// @brief ��ȡ�����ܸ߶�,��ȷ��(�����߿�����������),�����ݴ�СС���ӿڴ�Сʱ,���ص����ӿڴ�С.
/// @param hEle Ԫ�ؾ��.
/// @return �����ܸ߶�.
int  WINAPI XSView_GetVSizeTotalAccurate(HELE hEle) //��ȡ�����ܸ߶�,��ȷ��,,�����ݴ�СС���ӿڴ�Сʱ,���ص����ӿڴ�С
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	scrollView_ *pScrollView=SCROLLVIEW(hEle);
	int range=SCROLLBAR(pScrollView->pScrollBarV)->range;
	return range*pScrollView->sizeLine.cy+pScrollView->sizeView.cy;
}

/// @brief ��ȡ������ͼ������С.
/// @param hEle Ԫ�ؾ��.
/// @return ������ͼ������С.
int WINAPI XSView_GetSpacingLeft(HELE hEle)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->left;
}

/// @brief ��ȡ������ͼ�ϼ����С.
/// @param hEle Ԫ�ؾ��.
/// @return ������ͼ�ϼ����С.
int WINAPI XSView_GetSpacingTop(HELE hEle)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->top;
}

/// @brief ��ȡ������ͼ�Ҽ����С.
/// @param hEle Ԫ�ؾ��.
/// @return ������ͼ�Ҽ����С.
int WINAPI XSView_GetSpacingRight(HELE hEle)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->right;
}

/// @brief ��ȡ������ͼ�¼����С.
/// @param hEle Ԫ�ؾ��.
/// @return ������ͼ�¼����С.
int WINAPI XSView_GetSpacingBottom(HELE hEle)
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	return SCROLLVIEW(hEle)->bottom;
}

/// @brief �����ӿ���߿���.
/// @param hEle Ԫ�ؾ��.
/// @param left  ����.
/// @param top   �ϼ��.
/// @param right �Ҽ��.
/// @param bottom �¼��.
void WINAPI XSView_SetSpacing(HELE hEle,int left, int top, int right, int bottom) 
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	scrollView_ *pScrollView=SCROLLVIEW(hEle);
	pScrollView->left=left;
	pScrollView->top=top;
	pScrollView->right=right;
	pScrollView->bottom=bottom;

	XSView_Adjust(hEle);
}

/// @brief ���ù�����ͼ,ˮƽ�����ʹ�ֱ����ÿ����������ͼ��������.
/// @param hEle Ԫ�ؾ��.
/// @param line  ˮƽ����ÿ����������ͼ��������.
/// @param column ��ֱ����ÿ����������ͼ��������.
void WINAPI XSView_SetScrollSize(HELE hEle,int line,int column)  //���ù����к��д�С
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	SCROLLVIEW(hEle)->sizeLine.cx=line;
	SCROLLVIEW(hEle)->sizeLine.cy=column;
	XSView_Adjust(hEle);
}

/// @brief ���ù�����ͼԪ�ر�����ͼ.
/// @param hEle Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XSView_SetImage(HELE hEle,HIMAGE hImage)  //������ͼ
{
	IsScrollViewDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(SCROLLVIEW(hEle)->hImage_bk,hImage);
}

BOOL CALLBACK SView_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(SCROLLVIEW(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw,SCROLLVIEW(hEle)->hImage_bk,&rect);
	}

	if(((ele_*)hEle)->bBorder)
	{
		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,((ele_*)hEle)->borderColor);
		HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
		if(SCROLLVIEW(hEle)->left>0)
		{
			XDraw_MoveToEx_(hDraw,0,0,NULL);
			XDraw_LineTo_(hDraw,0,rect.bottom);
		}
		if(SCROLLVIEW(hEle)->top>0)
		{
			XDraw_MoveToEx_(hDraw,0,0,NULL);
			XDraw_LineTo_(hDraw,rect.right,0);
		}
		if(SCROLLVIEW(hEle)->right>0)
		{
			XDraw_MoveToEx_(hDraw,rect.right-1,0,NULL);
			XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
		}
		if(SCROLLVIEW(hEle)->bottom>0)
		{
			XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
		}
	}
	return TRUE;
}

BOOL CALLBACK SView_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
//	HELE hFocus=XWnd_GetFocusEle(XEle_GetHWindow(hEle));
//	if(hFocus)
//	{
	//	if(XEle_IsChildEle(hEle,hFocus))
	//	{
	//		return FALSE;
	//	}else
	//	{
	//		XEle_SetFocus(hEle,TRUE);
	//		return FALSE;
	//	}
//	}
//	XEle_SetFocus(hEle,TRUE);
	return FALSE;
}

BOOL CALLBACK SView_OnRButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
//	HELE hFocus=XWnd_GetFocusEle(XEle_GetHWindow(hEle));
//	if(hFocus)
//	{
//		if(XEle_IsChildEle(hEle,hFocus))
//		{
//			return FALSE;
//		}else
//		{
//			XEle_SetFocus(hEle,TRUE);
//			return FALSE;
//		}
//	}
//	XEle_SetFocus(hEle,TRUE);
	return FALSE;
}

BOOL CALLBACK SView_OnEventHScroll(HELE hEle,HELE hEventEle,int pos)
{
	if(hEventEle==(HELE)SCROLLVIEW(hEle)->pScrollBarH)
	{
		SCROLLVIEW(hEle)->hPos=pos;
		XEle_RedrawEle(hEle);
		Ele_SendEvent(hEle,XE_HSCROLLVIEW,pos,0);

		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK SView_OnEventVScroll(HELE hEle,HELE hEventEle,int pos)
{
	//XTRACE("SView_OnEventVScroll \n");
	if(hEventEle==(HELE)SCROLLVIEW(hEle)->pScrollBarV)
	{
		SCROLLVIEW(hEle)->vPos=pos;
		XEle_RedrawEle(hEle);
		Ele_SendEvent(hEle,XE_VSCROLLVIEW,pos,0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK SView_OnEventMouseWheel(HELE hEle,HELE hEventEle,UINT flags,POINT *pPt) //�����¼�
{
	int zDelta = GET_WHEEL_DELTA_WPARAM(flags);
	if(zDelta>0) //�Ϲ��� //WHEEL_DELTA
	{
		XSView_ScrollVPos(hEle,SCROLLVIEW(hEle)->vPos-(zDelta/WHEEL_DELTA)*3);
	}else //�¹���
	{
		XSView_ScrollVPos(hEle,SCROLLVIEW(hEle)->vPos+((-zDelta)/WHEEL_DELTA)*3);
	}

	return TRUE;
}

BOOL CALLBACK SView_OnEventSize(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
	{
		XSView_Adjust(hEle);
	}
	return FALSE;
}

BOOL CALLBACK SView_OnLButtonDown_View(HELE hEle,UINT flags,POINT *pPt)
{
	XEle_SetFocus( (HELE)((ele_*)hEle)->pParentEle,TRUE);

	return FALSE;
}


///@}