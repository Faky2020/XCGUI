/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//������

struct progressBar_
{
	ele_  ele; //�̳�
	//---------------------
	BOOL bHorizon; //TRUE:ˮƽ, FALSE:��ֱ
	BOOL bPercent;//��ʾ�ٷֱ�

	int  range;   //��Χ
	int  curPos;  //��ǰ���ȵ�

	HIMAGE hImage_bk;  //����ͼƬ
	HIMAGE hImage;     //��ǰ����ͼƬ
};


//API:
XC_API HELE WINAPI XProgBar_Create(int x, int y, int cx, int cy,BOOL bHorizon,HXCGUI hParent=NULL);
XC_API void WINAPI XProgBar_SetRange(HELE hEle,int range);  //���÷�Χ
XC_API void WINAPI XProgBar_SetPos(HELE hEle,int pos);   //���õ�ǰλ��
XC_API int  WINAPI XProgBar_GetRange(HELE hEle);
XC_API int  WINAPI XProgBar_GetPos(HELE hEle);

XC_API void WINAPI XProgBar_SetHorizon(HELE hEle,BOOL bHorizon); //ˮƽ��ʾ��ֱ
XC_API void WINAPI XProgBar_EnablePercent(HELE hEle,BOOL bPercent); //��ʾ�ٷֱ�

//���ý�����ɫ

//��ͼ:
XC_API void WINAPI XProgBar_SetImage(HELE hEle,HIMAGE hImage); //����
XC_API void WINAPI XProgBar_SetImage2(HELE hEle,HIMAGE hImage); //��ʾ��ǰ����ͼƬ



//˽�з���:
void ProgBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);

//�ص�����:
BOOL CALLBACK ProgBar_OnDraw(HELE hEle,HDRAW hDraw);
void ProgBar_OnDrawHorizon(HELE hEle,HDRAW hDraw,RECT &rect);
void ProgBar_OnDrawVertical(HELE hEle,HDRAW hDraw,RECT &rect);
