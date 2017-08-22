/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct slider_
{
	ele_  ele; //�̳�
	//---------------------
	BOOL bHorizon; //TRUE:ˮƽ, FALSE:��ֱ

	HELE hButton;   //����
	BOOL   bDown;     //����Ƿ���
	int    range;     //��Χ
	int    pos;       //��ǰλ��
	double minPos;    //ÿ�����С

	int    btnWidth; //��ť���

	HIMAGE hImage_bk;  //����ͼƬ
	HIMAGE hImage;     //��ǰ����ͼƬ
};

//API:
XC_API HELE WINAPI XSliderBar_Create(int x, int y, int cx, int cy,BOOL bHorizon,HXCGUI hParent=NULL);
XC_API void WINAPI XSliderBar_SetRange(HELE hEle,int range);  //���û�����Χ
XC_API void WINAPI XSliderBar_SetPos(HELE hEle,int pos);     //���û���λ��
XC_API int  WINAPI XSliderBar_GetPos(HELE hEle);            //��ȡ����λ��
XC_API HELE WINAPI XSliderBar_GetButton(HELE hEle);        //��ȡ����ָ��
XC_API int  WINAPI XSliderBar_GetButtonWidth(HELE hEle); //��ȡ������

XC_API void WINAPI XSliderBar_SetHorizon(HELE hEle,BOOL bHorizon);  //ˮƽ��ʾ��ֱ
XC_API void WINAPI XSliderBar_SetButtonWidth(HELE hEle,int width); //���û�����

//���ý�����ɫ1
//���ý�����ɫ2

//��ͼ:
XC_API void WINAPI XSliderBar_SetImage(HELE hEle,HIMAGE hImage); //����
XC_API void WINAPI XSliderBar_SetImage2(HELE hEle,HIMAGE hImage); //��ʾ��ǰ����ͼƬ


//˽�з���:
void SliderBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
void SliderBar_Adjust(HELE hEle);


//�ص�����:
void CALLBACK SliderBar_OnDestroy(HELE hEle);  //����
BOOL CALLBACK SliderBar_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK SliderBar_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SliderBar_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SliderBar_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SliderBar_OnEventMouseLeave(HELE hEle,HELE hEventEle);

BOOL CALLBACK SliderBar_OnDrawButton(HELE hEle,HDRAW hDraw);