/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//ģ̬����
struct modalWindow_
{
	window_ window; //�̳�
	//------------------------

	HARRAY  hArrayWnd;//��¼���õĴ����б�
};
extern int  g_modal_returnValue;  //����ֵ

//����API:
XC_API HWINDOW WINAPI XModalWnd_CreateWindow(int width,int height,wchar_t *pTitle,HWND hWndParent,int XCStyle=XC_SY_MODAL_WINDOW);//���ڸ���������
XC_API int WINAPI XModalWnd_DoModal(HWINDOW hWindow);     //����ģ̬����
XC_API void WINAPI XModalWnd_DoOk(HWINDOW hWindow);       //ȷ��
XC_API void WINAPI XModalWnd_DoCancel(HWINDOW hWindow);   //ȡ��

//˽�з���:
BOOL ModalWnd_Init(HWINDOW hWindow,DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName,DWORD dwStyle,int cx,int cy,HWND hWndParent,int XCStyle,int exType);

//�ص�����
BOOL CALLBACK ModalWnd_OnClose(HWINDOW hWindow); 
BOOL CALLBACK ModalWnd_OnDestroy(HWINDOW hWindow);


//////�ڲ�ʹ��//////////////////////////////////////////
struct messageBoxWnd_
{
	modalWindow_ modalWindow; //�̳�
	//----------------------------------
	HSTRING hString;  //��Ϣ������
	SIZE    sizeText; //�ı������С
	int     type;
	HELE    hBtnOk;
	HELE    hBtnCancel;
};

//API:
int MsgBox_DoModal(HWND hWndParent,wchar_t *pText,wchar_t *pCaption,int type);     //����ģ̬����

//˽�з���:
void MsgBox_CreateButton(HWINDOW hWindow); //������ť

//�ص�����:
BOOL CALLBACK MsgBox_OnDestroy(HWINDOW hWindow);
BOOL CALLBACK MsgBox_OnDrawWindow(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK MsgBox_OnEventBtnClickOk(HELE hEle,HELE hEventEle);
BOOL CALLBACK MsgBox_OnEventBtnClickCancel(HELE hEle,HELE hEventEle);


//hXCGUI:������Ԫ�ؾ���򴰿���Դ���,ʧ�ܷ���-1,������������ϵĹرհ�ť����0
XC_API int WINAPI XMessageBox(HXCGUI hXCGUI, wchar_t *pText, wchar_t *pCaption=L"�Ųʽ����-��ʾ��",int type=XMB_OK);