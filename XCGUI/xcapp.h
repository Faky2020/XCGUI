/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once



struct eventList_  //�¼��ṹ
{
	HELE     hEle;	 //�����¼���Ԫ�ؾ��
	int      type;	 //�¼�����
	WPARAM   wParam;
	LPARAM   lParam;
	BOOL     bEvent;  //TRUE:���¼�, FALSE:û���¼�
};


#define            EVENT_LIST_SIZE          10         //�¼����д�С
extern int         g_event_write_pos;                  //�¼���ǰλ���α�,д��
extern eventList_  g_eventList[EVENT_LIST_SIZE];       //�¼�����
extern ULONG_PTR   gdiplusToken;

extern HMODULE    g_resourcesModule;  //��Դģ����

//�������ʽ
extern int  g_clipbroad_RichEditFormat;
extern int  g_clipborad_HTMLFormat;

//Ӧ�ó���API:
XC_API BOOL WINAPI XC_RegisterWndClass(wchar_t *pClassName,HICON hIcon=NULL); //ע�ᴰ����


XC_API BOOL WINAPI XInitXCGUI(wchar_t *pText=NULL);
XC_API void WINAPI XRunXCGUI();
XC_API void WINAPI XExitProcess(); //�˳�����(�൱��������)

LRESULT CALLBACK XCGUI_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


XC_API void WINAPI xtrace(char *pszFormat, ...);
XC_API void WINAPI xtracew(wchar_t *pszFormat, ...);



