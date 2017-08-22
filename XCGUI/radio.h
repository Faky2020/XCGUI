/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct radio_
{
	button_  button; //�̳�
	//-------------
	int   groupID;  //��ID
    BOOL  bButtonStyle;

	HELE  hBindEle;  //��ҳԪ��

	HIMAGE  hImage_leave_check;   //��ѡ ����뿪
	HIMAGE  hImage_stay_check;    //��ѡ ���ͣ��
	HIMAGE  hImage_down_check;    //��ѡ ��갴��
	HIMAGE  hImage_disable_check; //��ѡ ����
};

//API:
XC_API HELE WINAPI XRadio_Create(int x, int y, int cx, int cy,wchar_t *pTitle=NULL,HXCGUI hParent=NULL);  //������ť


//��ͼ:
XC_API void WINAPI XRadio_SetImageLeave_UnCheck(HELE hEle,HIMAGE hImage=NULL);  //����뿪ʱͼƬ  δѡ��
XC_API void WINAPI XRadio_SetImageStay_UnCheck(HELE hEle,HIMAGE hImage=NULL);   //���ͣ��ʱͼƬ  δѡ��
XC_API void WINAPI XRadio_SetImageDown_UnCheck(HELE hEle,HIMAGE hImage=NULL);   //��갴��ʱͼƬ  δѡ��
XC_API void WINAPI XRadio_SetImageDisable_UnCheck(HELE hEle,HIMAGE hImage=NULL); //��ť����״̬ͼƬ  δѡ��

XC_API void WINAPI XRadio_SetImageLeave_Check(HELE hEle,HIMAGE hImage=NULL);  //����뿪ʱͼƬ  ѡ��
XC_API void WINAPI XRadio_SetImageStay_Check(HELE hEle,HIMAGE hImage=NULL);   //���ͣ��ʱͼƬ  ѡ��
XC_API void WINAPI XRadio_SetImageDown_Check(HELE hEle,HIMAGE hImage=NULL);   //��갴��ʱͼƬ  ѡ��
XC_API void WINAPI XRadio_SetImageDisable_Check(HELE hEle,HIMAGE hImage=NULL); //��ť����״̬ͼƬ  ѡ��

XC_API void WINAPI XRadio_SetGroupID(HELE hEle,int groupID);  //������ID
XC_API int  WINAPI XRadio_GetGroupID(HELE hEle);  //��ȡ��ID
XC_API void WINAPI XRadio_EnableButtonStyle(HELE hEle,BOOL bStyle); //���ð�ť��ʽ

XC_API void WINAPI XRadio_SetBindEle(HELE hEle,HELE bindEle);


//˽�з���:
void Radio_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);
void Radio_DrawCheck(HELE hEle,HDRAW hDraw,RECT &rect); //���ƹ�ѡ״̬
void Radio_DrawUnCheck(HELE hEle,HDRAW hDraw,RECT &rect); //����δ��ѡ״̬

void Radio_Draw_Check2(HDRAW hDraw,int x,int y,COLORREF color_dot,COLORREF color_border);
void Radio_Draw_UnCheck2(HDRAW hDraw,int x,int y,COLORREF color_dot1,COLORREF color_dot2,COLORREF color_border);


//�ص�����
void CALLBACK Radio_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Radio_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK Radio_OnEventBtnClick(HELE hEle,HELE hEventEle);
