/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//ͼ��Ԫ��
struct picture_
{
	ele_ ele; //�̳�
	//---------------------
	HIMAGE hImage_bk; //ͼƬ
};


//API:
XC_API HELE WINAPI XPic_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);

//��ͼ
XC_API void WINAPI XPic_SetImage(HELE hEle,HIMAGE hImage);  //����ͼƬ


//˽�з���:
void Pic_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);


//�ص�����:
BOOL CALLBACK Pic_OnDraw(HELE hEle,HDRAW hDraw);
void CALLBACK Pic_OnDestroy(HELE hEle);  //����