/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

/*
 BOOL CALLBACK OnEleDraw(HELE hEle,HDC hdc)
 {
//	 RECT rc={10,10,30,30};
//	 XDraw_FillSolidRect(hdc,&rc,RGB(100,100,100));
	return TRUE;
 }

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XWnd_SetBkColor(hWindow,RGB(255,0,0));

//	HELE hBtn=XBtn_Create(10,10,100,100,L"123",hWindow);
//	XEle_SetId(hBtn,111);
	//XEle_RegisterMessage(hBtn,XM_PAINT,OnEleDraw);
//	XEle_SetBkTransparent(hBtn,TRUE);


	XCHColor_Create(10,10,100,20,hWindow);

	XWnd_SetImageBorderBottom(hWindow,XImage_LoadFile(L"image\\111.jpg"));
	XWnd_SetBorderSize(hWindow,8,8,8,110);

//	XWnd_SetImage(hWindow,XImage_LoadFile(L"image\\frame.jpg"));

	XRunXCGUI();

	return 0;
}
*/

/*

#define IDB_BUTTON1  L"IDB_BUTTON1"  //����Դ�ļ��а�ťID����

//����XML�ļ��������� - ��ʾ2
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //��ʼ�������

	HXMLRES  hRes=XXmlRes_Load(L"xml\\resource.res");	//������Դ
	if(NULL==hRes)
	{
		MessageBox(NULL,L"������Դʧ��",L"����",0);
		return 0;
	}

	HWINDOW hWindow=XC_LoadXML_Window(L"xml\\layout.xml",hRes); //��������
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"����XMLʧ��",L"����",0);
		return 0;
	}

	if(FALSE==XC_LoadXML_Style(hWindow,L"xml\\style.css",hRes))	//������ʽ�ļ�
	{
		MessageBox(NULL,L"������ʽʧ��",L"����",0);
		return 0;
	}

	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����

	//����������ǵ�UI�ļ�
	int idButton1=XXmlRes_FindId(hRes,IDB_BUTTON1); //ͨ����ť��Դ��,���ҵ�ID
	HELE hbutton1=XWnd_GetEle(hWindow,idButton1);   //ͨ��ID��ȡ��ť���
	if(XC_BUTTON==XC_GetObjectType(hbutton1))       //�ж��Ƿ�Ϊ��ť
	{
		wchar_t *pBtnText=XBtn_GetText(hbutton1);  //��ȡ��ť�ı�����

		wchar_t buf[MAX_PATH]={0};
		swprintf_s(buf,MAX_PATH,L"���԰�ť[%s]�ı���:[%s]",IDB_BUTTON1,pBtnText);

		XMessageBox(hWindow,buf,L"�Ųʽ����-����"); //��ʾ�����Ϣ
	}else
	{
		XTRACE("������Դ�д���\n");
	}
	XXmlRes_Destroy(hRes); //��ʹ����������Դ�ļ�

	XRunXCGUI(); //����

	return 0;
}
*/

/*
//����XML�����ļ�
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//SSLWnd_Init("3BAJ-G934-A6H1-8AVB-A14C-9009-FAAC-908F");
	XInitXCGUI(); //��ʼ�������

	XC_LoadXML_WindowRes(1,L"123");
	HXMLRES  hRes=XXmlRes_Load(L"360\\mainFrame.res");	//������Դ
	if(NULL==hRes)
	{
		MessageBox(NULL,L"������Դʧ��",L"����",0);
		return 0;
	}

	HWINDOW hWindow=XC_LoadXML_Window(L"360\\mainFrame.xml",hRes); //��������
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"����XMLʧ��",L"����",0);
		return 0;
	}

	if(FALSE==XC_LoadXML_Style(hWindow,L"360\\mainFrame.css",hRes))	//������ʽ�ļ�
	{
		MessageBox(NULL,L"������ʽʧ��",L"����",0);
		return 0;
	}

	//XWnd_EnableBorderStrokeOuter(hWindow,FALSE);
	XWnd_SetBorderStrokeOuterColor(hWindow,RGB(30,30,30),RGB(0,0,0));
	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����

	XXmlRes_Destroy(hRes); //��ʹ����������Դ�ļ�

	XRunXCGUI(); //����

	return 0;
}
*/


/*
//����XML����ҳ�ļ�
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//XInitXCGUI("3BAJ-G934-A6H1-8AVB-A14C-9009-FAAC-908F"); //��ʼ�������
	XInitXCGUI(); //��ʼ�������

	HXMLRES  hRes=XXmlRes_Load(L"360v2\\resources.res");	//������Դ
	if(NULL==hRes)
	{
		MessageBox(NULL,L"������Դʧ��",L"����",0);
		return 0;
	}

	HWINDOW hWindow=XC_LoadXML_Window(L"360v2\\layout.xml",hRes); //��������
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"����XMLʧ��",L"����",0);
		return 0;
	}

	//XC_LoadXML_Page(hWindow,L"360\\mainPage2.xml",hRes);

	if(FALSE==XC_LoadXML_Style(hWindow,L"360v2\\style.css",hRes))	//������ʽ�ļ�
	{
		MessageBox(NULL,L"������ʽʧ��",L"����",0);
		return 0;
	}

//	HELE hBtn=XWnd_GetEle(hWindow,188);
//	XBtn_SetImageLeave(hBtn,XImage_LoadFile(L"360v2\\image\\frame.jpg"));

	//HELE hParentEle=XWnd_GetEle(hWindow,501);

	//XWnd_EnableBorderStrokeOuter(hWindow,FALSE);
	//XWnd_SetBorderStrokeOuterColor(hWindow,RGB(30,30,30),RGB(0,0,0));
	//XWnd_SetBorderStrokeOuterColor(hWindow,RGB(255,0,0),RGB(0,255,0));
	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����

	XXmlRes_Destroy(hRes); //��ʹ����������Դ�ļ�

	XRunXCGUI(); //����

	return 0;
}
*/


/*
//����XML����ҳ�ļ� �����Բ����ļ�
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //��ʼ�������

	//HWINDOW hWindow=XC_LoadXML_Window(L"F:\\��Ŀ\\UI�����\\GuiDesigner(2012_03_10)\\Debug\\MyProject\\layout.xml"); //��������
	HWINDOW hWindow=XC_LoadXML_Window(L"360\\mainFrame.xml"); //��������
	if(NULL==hWindow)
	{
		MessageBox(NULL,L"����XMLʧ��",L"����",0);
		return 0;
	}
	//XWnd_SetBkColor(hWindow,RGB(255,0,0));
	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����
	XRunXCGUI(); //����

	return 0;
}
*/