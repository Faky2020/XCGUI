/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


//ͼ����ʾ���������
//ͼ����ʾ�������ұ�
//ͼ����ʾ�������ϱ�
//ͼ����ʾ���ļ��±�
//����ʾͼ��
//����ʾ����
/*
////////////������//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"���Դ���");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hToolBtn1=XToolBarBtn_Create(2,2,L"����1");
	HELE hToolBtn2=XToolBarBtn_Create(2,2,L"����2");
	HELE hToolBtn3=XToolBarBtn_Create(2,2,L"����3");
	HELE hToolBtn4=XToolBarBtn_Create(2,2,L"����4");
	HELE hToolBtn5=XToolBarBtn_Create(2,2,L"�ı�5");

	XToolBarBtn_SetImage(hToolBtn1,L"image/1073.ico");
	XToolBarBtn_SetImage(hToolBtn2,L"image/save.ico");
	XToolBarBtn_SetImage(hToolBtn3,L"image/open.ico");
	XToolBarBtn_SetImage(hToolBtn4,L"image/open.ico");

	HELE hEdit=XEdit_Create(0,0,60,20);
	HELE hCheck=XCheck_Create(0,0,60,20,L"check");

	HXCGUI hToolBar=XToolBar_Create(0,30,200,28,hWindow);

	XToolBar_InsertEle(hToolBar,hToolBtn1);
	XToolBar_InsertEle(hToolBar,hToolBtn2);
	XToolBar_InsertEle(hToolBar,hEdit);
	XToolBar_InsertEle(hToolBar,hToolBtn3);
	XToolBar_InsertEle(hToolBar,hToolBtn4);
	XToolBar_InsertEle(hToolBar,hToolBtn5);
	XToolBar_InsertEle(hToolBar,hCheck);
	XToolBar_InsertSeparator(hToolBar,1);

	XEle_EnableEle(hToolBtn3,FALSE);

	XToolBarBtn_Adjust(hToolBtn1);
	XToolBarBtn_Adjust(hToolBtn2);
	XToolBarBtn_Adjust(hToolBtn3);
	XToolBarBtn_Adjust(hToolBtn4);
	XToolBarBtn_Adjust(hToolBtn5);


	XBtn_Create(10,50,100,25,L"button",hWindow);

	HELE hMenuBar=XMenuBar_Create(10,10,300,26);
	
	XMenuBar_AddButton(hMenuBar,L"�ļ�");
	XMenuBar_AddButton(hMenuBar,L"�༭");
	XMenuBar_AddButton(hMenuBar,L"��ͼ");

	XMenuBar_AddMenuItem(hMenuBar,0,1,L"111");
	XMenuBar_AddMenuItem(hMenuBar,0,2,L"222");
	XMenuBar_AddMenuItem(hMenuBar,0,3,L"333");

	XMenuBar_AddMenuItem(hMenuBar,1,4,L"444");
	XMenuBar_AddMenuItem(hMenuBar,1,5,L"555");
	XMenuBar_AddMenuItem(hMenuBar,1,6,L"666");

	XMenuBar_AddMenuItem(hMenuBar,2,7,L"777");
	XMenuBar_AddMenuItem(hMenuBar,2,8,L"888");

	XWnd_AddMenuBar(hWindow,hMenuBar);

	XRunXCGUI();
	return 0;
}
*/

///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    XInitXCGUI();

    //��������:
    HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"�Ųʽ����-����");
    XWnd_ShowWindow(hWindow,SW_SHOW);

    //������������ť
    HELE hToolBtn1=XToolBarBtn_Create(2,2,L"����1");
    HELE hToolBtn2=XToolBarBtn_Create(2,2,L"����2");
    HELE hToolBtn3=XToolBarBtn_Create(2,2,L"����3");
    HELE hToolBtn4=XToolBarBtn_Create(2,2,L"����4");
    HELE hToolBtn5=XToolBarBtn_Create(2,2,L"�ı�5");
    //����ͼ��
	XBtn_SetIcon(hToolBtn1,XImage_LoadFile(L"image/1073.ico"));
	XBtn_SetIcon(hToolBtn2,XImage_LoadFile(L"image/save.ico"));
	XBtn_SetIcon(hToolBtn3,XImage_LoadFile(L"image/open.ico"));
	XBtn_SetIcon(hToolBtn4,XImage_LoadFile(L"image/open.ico"));

    HELE hEdit=XEdit_Create(0,0,60,20);
    HELE hCheck=XCheck_Create(0,0,60,20,L"check");
    XEle_SetBkTransparent(hCheck,TRUE);
    //����������
    HELE hToolBar=XToolBar_Create(0,30,200,28,hWindow);
    //��Ԫ����ӵ���������
    XToolBar_InsertEle(hToolBar,hToolBtn1);
    XToolBar_InsertEle(hToolBar,hToolBtn2);
    XToolBar_InsertEle(hToolBar,hEdit);
    XToolBar_InsertEle(hToolBar,hToolBtn3);
    XToolBar_InsertEle(hToolBar,hToolBtn4);
    XToolBar_InsertEle(hToolBar,hToolBtn5);
    XToolBar_InsertEle(hToolBar,hCheck);
    XToolBar_InsertSeparator(hToolBar,1);
    //����ָ��Ԫ��
    XEle_EnableEle(hToolBtn3,FALSE);
    //�Զ�������������ť��С
    XToolBarBtn_Adjust(hToolBtn1);
    XToolBarBtn_Adjust(hToolBtn2);
    XToolBarBtn_Adjust(hToolBtn3);
    XToolBarBtn_Adjust(hToolBtn4);
    XToolBarBtn_Adjust(hToolBtn5);

    XRunXCGUI();
    return 0;
}*/