/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


/*
BOOL CALLBACK MyEventComboBoxPopupList(HELE hEle,HELE hEventEle,HWINDOW hWindow,HELE hListBox)  //XE_COMBOBOX_POPUP_LIST
{
	XTRACE("pop ���� \n");
	return TRUE;
}

BOOL CALLBACK MyEventComboBoxCloseList(HELE hEle,HELE hEventEle) //XE_COMBOBOX_EXIT_LIST
{
	XTRACE("pop �ر� \n");
	return TRUE;
}

HELE hEdit;
BOOL CALLBACK OnEventComboBoxSelecting(HELE hEle,HELE hEventEle,int index,BOOL *pBOOL)
{
	XTRACE("ѡ�������ڸı�...\n");
//	*pBOOL=TRUE;
	return TRUE;
}

BOOL CALLBACK MyEventComboBoxSelect(HELE hEle,HELE hEventEle,int id) //������Ͽ�ѡ���¼�
{
	if(id>-1)
	{
		wchar_t buf[100]={0};
		wchar_t *pText=XComboBox_GetItemText(hEle,id);
		wsprintf(buf,L"ѡ����:\n%s",pText);
		XEdit_SetText(hEdit,buf);
		XEle_RedrawEle(hEdit);
		XTRACEW(L"ѡ����:%s \n",pText);
	}
	return TRUE;
}


//��Ͽ�
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����������Ͽ�Ԫ��
	HELE hComboBox=XComboBox_Create(10,120,100,20,hWindow);
	XComboBox_EnableEdit(hComboBox,FALSE); //��ֹ�༭����
	XComboBox_SetListHeight(hComboBox,100); //���������б�߶�
	XComboBox_AddString(hComboBox,L"1111");
	XComboBox_AddString(hComboBox,L"2222");
	XComboBox_AddString(hComboBox,L"3333");
	XComboBox_AddString(hComboBox,L"4444");
	XComboBox_AddString(hComboBox,L"5555");
	XComboBox_AddString(hComboBox,L"666");
	XComboBox_AddString(hComboBox,L"7777");
	XComboBox_AddString(hComboBox,L"8888");
	XComboBox_SetText(hComboBox,0); //���õ�ǰѡ����

	//�����༭������ʾ׷���¼�
	hEdit=XEdit_Create(120,10,100,50,hWindow);
	XEdit_EnableMultiLine(hEdit,TRUE);
	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_SELECT,MyEventComboBoxSelect);
	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_SELECT_ING,OnEventComboBoxSelecting);

	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_POPUP_LIST,MyEventComboBoxPopupList);
	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_EXIT_LIST,MyEventComboBoxCloseList);
	
	XEle_SetBkColor(XSView_GetView(hEdit),RGB(255,0,0));
	//XSView_SetImage(hComboBox,L"image/123.jpg");
//XComboBox_SetBtnImageStay(hComboBox,L"image/btn_stay.bmp");

	XRunXCGUI();
	return 0;
}
*/

/*
//��Ͽ�
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

//	HELE hEdit=XEdit_Create(10,10,200,200,hWindow);
//	XEdit_SetTextSpacingLeft(hEdit,10);


	//����������Ͽ�Ԫ��
	HELE hComboBox=XComboBox_Create(10,10,100,20,hWindow);
//	XComboBox_EnableEdit(hComboBox,FALSE); //��ֹ�༭����
	XComboBox_SetListHeight(hComboBox,100); //���������б�߶�
	XComboBox_AddString(hComboBox,L"1111");
	XComboBox_AddString(hComboBox,L"2222");
	XComboBox_AddString(hComboBox,L"3333");
	XComboBox_AddString(hComboBox,L"4444");
	XComboBox_AddString(hComboBox,L"5555");
	XComboBox_AddString(hComboBox,L"666");
	XComboBox_AddString(hComboBox,L"7777");
	XComboBox_AddString(hComboBox,L"8888");
	XComboBox_SetText(hComboBox,0); //���õ�ǰѡ����

	HELE hStatic=XStatic_Create(10,50,100,20,L"12345678901234567890",hWindow);
	XStatic_AdjustSize(hStatic);
	XEle_SetBkColor(hStatic,RGB(255,0,0));

	XRunXCGUI();
	return 0;
}
*/



/*
//�����б����¼�
BOOL CALLBACK MyEventComboBoxPopupList(HELE hEle,HELE hEventEle,HWINDOW hWindow,HELE hListBox)
{
	XEle_SetBorderColor(hListBox,RGB(86,165,213)); //���������б�߿���ɫ
	return TRUE;
}

//��Ͽ���ͼ
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,150,L"�Ųʽ����-����");

	//����������Ͽ�Ԫ��
	HELE hComboBox=XComboBox_Create(10,10,100,22,hWindow);
	XComboBox_EnableEdit(hComboBox,FALSE); //��ֹ�༭����
	XComboBox_SetListHeight(hComboBox,100); //���������б�߶�
	XComboBox_AddString(hComboBox,L"1111"); //������
	XComboBox_AddString(hComboBox,L"2222");
	XComboBox_AddString(hComboBox,L"3333");
	XComboBox_AddString(hComboBox,L"4444");
	XComboBox_AddString(hComboBox,L"5555");
	XComboBox_AddString(hComboBox,L"666");
	XComboBox_AddString(hComboBox,L"7777");
	XComboBox_AddString(hComboBox,L"8888");
	XComboBox_SetSelectItem(hComboBox,0); //���õ�ǰѡ����

	XEle_EnableBorder(hComboBox,FALSE); //�����Ʊ߿�
	//������ͼ
	XComboBox_SetImageLeave(hComboBox,XImage_LoadFile(L"image//combo_leave.png"));
	XComboBox_SetImageStay(hComboBox,XImage_LoadFile(L"image//combo_stay.png"));
	XComboBox_SetImageDown(hComboBox,XImage_LoadFile(L"image//combo_down.png"));
//	XSView_EnableImageStretch(hComboBox,TRUE);

	//�༭����ͼ
	HELE hEdit=XEdit_Create(150,10,100,22,hWindow);
	XEle_EnableBorder(hEdit,FALSE); //�����Ʊ߿�
	XEdit_SetImageLeave(hEdit,XImage_LoadFile(L"image//edit_leave.jpg"));
	XEdit_SetImageStay(hEdit,XImage_LoadFile(L"image//edit_stay.jpg"));

	XEle_RegisterEvent(hComboBox,XE_COMBOBOX_POPUP_LIST,MyEventComboBoxPopupList); //ע���¼�

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
*/