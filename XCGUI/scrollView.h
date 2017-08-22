/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//scrollView

struct drawScrollView_
{
	pFunDrawScrollView  pFun;
#ifdef	XCGUI_PLUS          //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
	drawScrollView_ *pNext;
};


struct scrollView_
{
	ele_  ele; //�̳�
	//---------------
	HELE  hView;  //��ͼԪ��
	ele_  *pScrollBarH;  //ˮƽ������
	ele_  *pScrollBarV;  //��ֱ������
	int  left, top, right, bottom; //�����߼��
	SIZE  sizeTotal;  //��ͼ�ܴ�С
	SIZE  sizeView;   //�ӿڴ�С
	SIZE  sizeLine;   //�д�С

	BOOL  bHScroll;  //��ʾˮƽ������
	BOOL  bVScroll;  //��ʾ��ֱ������

	int   barWidth;  //��������Ȼ�߶�

	int hPos;   //ˮƽ������
	int vPos;   //��ֱ������

	HIMAGE   hImage_bk;//����ͼƬ

	//------------------------------------------------------------
	drawScrollView_  *pDrawScrollViewList; //���ƹ�����ͼ����
};

#ifdef	XCGUI_PLUS          //C++��֧��,�����Ա����ע���֧��
XC_API void WINAPI XSView_SetDrawScrollViewEx(HELE hEle,pFunClassEventMsg pCallBackFun,void *pClass_Fun_Info);
#endif

//API:
XC_API HELE WINAPI XSView_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);
XC_API void WINAPI XSView_SetDrawScrollView(HELE hEle,pFunDrawScrollView pFun);

XC_API HELE WINAPI XSView_GetView(HELE hEle); //��ȡ��Ԫ��
XC_API BOOL WINAPI XSView_AddEle(HELE hEle,HELE hNewEle); //���Ԫ�ص�������ͼ

XC_API int WINAPI XSView_GetHViewPos(HELE hEle);   //��ȡ�ӿ�ԭ��X����
XC_API int WINAPI XSView_GetVViewPos(HELE hEle);   //��ȡ�ӿ�ԭ��Y����

XC_API int WINAPI XSView_GetSpacingLeft(HELE hEle);
XC_API int WINAPI XSView_GetSpacingTop(HELE hEle);
XC_API int WINAPI XSView_GetSpacingRight(HELE hEle);
XC_API int WINAPI XSView_GetSpacingBottom(HELE hEle);
XC_API int WINAPI XSView_GetScrollBarWidth(HELE hEle);  //��ȡ���������
XC_API int WINAPI XSView_GetViewWidth(HELE hEle);  //��ȡ�ӿڿ��(�����߿�����������)
XC_API int WINAPI XSView_GetViewHeight(HELE hEle); //��ȡ�ӿڸ߶�(�����߿�����������)
XC_API int WINAPI XSView_GetHSizeTotalAccurate(HELE hEle); //��ȡ�����ܿ��,��ȷ��(�����߿�����������),�����ݴ�СС���ӿڴ�Сʱ,���ص����ӿڴ�С
XC_API int WINAPI XSView_GetVSizeTotalAccurate(HELE hEle); //��ȡ�����ܸ߶�,��ȷ��(�����߿�����������),�����ݴ�СС���ӿڴ�Сʱ,���ص����ӿڴ�С
XC_API void WINAPI XSView_GetViewRect(HELE hEle,out_ RECT *pRect); //��ȡ�ӿ�����(�����߿���),leftΪ�ӿ�������С,topΪ�ӿ��ϼ����С,��(0,0).
XC_API void WINAPI XSView_GetSize(HELE hEle,SIZE *pSize);  //��ȡ���õ����ݴ�С

XC_API HELE WINAPI XSView_GetHScrollBar(HELE hEle); //��ȡˮƽ������
XC_API HELE WINAPI XSView_GetVScrollBar(HELE hEle); //��ȡ��ֱ������

XC_API void WINAPI XSView_SetSize(HELE hEle,int cx, int cy); //������ͼ�����ܴ�С(�������߿���)
XC_API void WINAPI XSView_SetSpacing(HELE hEle,int left, int top, int right, int bottom);  
XC_API void WINAPI XSView_SetScrollSize(HELE hEle,int line,int column);  //���ù����к��д�С

//��ͼ
XC_API void WINAPI XSView_SetImage(HELE hEle,HIMAGE hImage);//������ͼ


XC_API void WINAPI XSView_EnableHScroll(HELE hEle,BOOL bEnable); //����ˮƽ������
XC_API void WINAPI XSView_EnableVScroll(HELE hEle,BOOL bEnable); //���ô�ֱ������
XC_API BOOL WINAPI XSView_IsHScrollBarVisible(HELE hEle); //ˮƽ��������ǰ�Ƿ�ɼ�
XC_API BOOL WINAPI XSView_IsVScrollBarVisible(HELE hEle); //��ֱ��������ǰ�Ƿ�ɼ�

XC_API void WINAPI XSView_Adjust(HELE hEle);

//������ͼ
XC_API BOOL WINAPI XSView_ScrollHPos(HELE hEle,int pos); //������ָ����
XC_API BOOL WINAPI XSView_ScrollVPos(HELE hEle,int pos); //������ָ����

//������ָ������
XC_API BOOL WINAPI XSView_ScrollHPosX(HELE hEle,int posX); //������ָ������
XC_API BOOL WINAPI XSView_ScrollVPosY(HELE hEle,int posY); //������ָ������

XC_API BOOL WINAPI XSView_ScrollLeftLine(HELE hEle);    //�������
XC_API BOOL WINAPI XSView_ScrollRightLine(HELE hEle);   //���ҹ���
XC_API BOOL WINAPI XSView_ScrollTopLine(HELE hEle);     //���Ϲ���
XC_API BOOL WINAPI XSView_ScrollDownLine(HELE hEle);    //���¹���

XC_API BOOL WINAPI XSView_ScrollLeft(HELE hEle);    //ˮƽ���������
XC_API BOOL WINAPI XSView_ScrollRight(HELE hEle);   //ˮƽ�������Ҳ�
XC_API BOOL WINAPI XSView_ScrollTop(HELE hEle);     //����������
XC_API BOOL WINAPI XSView_ScrollBottom(HELE hEle);  //�������ײ�


//˽�з���:
void SView_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);

//�ص�����:
void CALLBACK SView_OnDestroy(HELE hEle);  //����
BOOL CALLBACK SView_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK SView_OnEventHScroll(HELE hEle,HELE hEventEle,int pos);
BOOL CALLBACK SView_OnEventVScroll(HELE hEle,HELE hEventEle,int pos);
BOOL CALLBACK SView_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SView_OnRButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SView_OnEventMouseWheel(HELE hEle,HELE hEventEle,UINT flags,POINT *pPt); //�����¼�
BOOL CALLBACK SView_OnEventSize(HELE hEle,HELE hEventEle);

BOOL CALLBACK SView_OnLButtonDown_View(HELE hEle,UINT flags,POINT *pPt);