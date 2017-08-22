/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

struct check_
{
	button_  button; //�̳�
	//---------------

	HIMAGE  hImage_leave_check;   //��ѡ ����뿪
	HIMAGE  hImage_stay_check;    //��ѡ ���ͣ��
	HIMAGE  hImage_down_check;    //��ѡ ��갴��
	HIMAGE  hImage_disable_check; //��ѡ ����
};

//API:

XC_API HELE WINAPI XCheck_Create(int x, int y, int cx, int cy,wchar_t *pTitle=NULL,HXCGUI hParent=NULL);

//��ͼ:
XC_API void WINAPI XCheck_SetImageLeave_UnCheck(HELE hEle,HIMAGE hImage);   //����뿪ʱͼƬ  δѡ��
XC_API void WINAPI XCheck_SetImageStay_UnCheck(HELE hEle,HIMAGE hImage);    //���ͣ��ʱͼƬ  δѡ��
XC_API void WINAPI XCheck_SetImageDown_UnCheck(HELE hEle,HIMAGE hImage);    //��갴��ʱͼƬ  δѡ��
XC_API void WINAPI XCheck_SetImageDisable_UnCheck(HELE hEle,HIMAGE hImage); //��ť����״̬ͼƬ  δѡ��

XC_API void WINAPI XCheck_SetImageLeave_Check(HELE hEle,HIMAGE hImage);   //����뿪ʱͼƬ   ѡ��
XC_API void WINAPI XCheck_SetImageStay_Check(HELE hEle,HIMAGE hImage);    //���ͣ��ʱͼƬ   ѡ��
XC_API void WINAPI XCheck_SetImageDown_Check(HELE hEle,HIMAGE hImage);    //��갴��ʱͼƬ   ѡ��
XC_API void WINAPI XCheck_SetImageDisable_Check(HELE hEle,HIMAGE hImage); //��ť����״̬ͼƬ  ѡ��


//˽�з���:
void Check_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);
void Check_DrawCheck(HELE hEle,HDRAW hDraw,RECT &rect); //���ƹ�ѡ״̬
void Check_DrawUnCheck(HELE hEle,HDRAW hDraw,RECT &rect); //����δ��ѡ״̬


//�ص�����:
void CALLBACK Check_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Check_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK Check_OnEventBtnClick(HELE hEle,HELE hEventEle);
