/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"



///////////////////////////////////////////
//������������////////////////////////////////

/*
//����������ѡ��ı��¼�
BOOL CALLBACK OnEventPGridSelChange(HELE hEle,HELE hEventEle,int prevID,int id)
{
	XTRACE("����������ѡ��ı�=%d \n",id);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,260,260,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//������������Ԫ��
	HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
	//�����
	int group1=XPGrid_AddGroup(hPGrid,L"һ�� ��1");
	//�����
	int item1=XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	int item2=XPGrid_AddItem(hPGrid,L"���� color",PGRID_CHOOSECOLOR,group1);

	int group2=XPGrid_AddGroup(hPGrid,L"һ�� ��2");
	//���ֵΪ��̬�ַ���������
	XPGrid_AddItemString(hPGrid,L"���� �ַ���1",L"ֵ",group2);
	XPGrid_AddItemString(hPGrid,L"���� �ַ���2",L"ֵ",group2);


	int id=XPGrid_AddItem(hPGrid,L"��Ͽ�",PGRID_COMBOBOX);//,group2);
	HELE hCom=XPGrid_GetItemHEle(hPGrid,id);

	XComboBox_AddString(hCom,L"FALSE");
	XComboBox_AddString(hCom,L"TRUE");

	PGrid_Adjust(hPGrid);

	XEle_RegisterEvent(hPGrid,XE_PGRID_SELCHANGE,OnEventPGridSelChange);

	XRunXCGUI();
	return 0;
}

*/


//1608
#if 0
//�������� �����
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"�Ųʽ����-����");


	//������������Ԫ��
	HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
	//�����
	int group1=XPGrid_AddGroup(hPGrid,L"һ�� ��1");
	//�����
	int item1=XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	int item2=XPGrid_AddItem(hPGrid,L"���� color",PGRID_CHOOSECOLOR,group1);

	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);

	int group2=XPGrid_AddGroup(hPGrid,L"һ�� ��2");
	//���ֵΪ��̬�ַ���������
	XPGrid_AddItemString(hPGrid,L"���� �ַ���1",L"ֵ",group2);
	XPGrid_AddItemString(hPGrid,L"���� �ַ���2",L"ֵ",group2);


	int id=XPGrid_AddItem(hPGrid,L"��Ͽ�",PGRID_COMBOBOX);//,group2);
	HELE hCom=XPGrid_GetItemHEle(hPGrid,id);

	XComboBox_AddString(hCom,L"FALSE");
	XComboBox_AddString(hCom,L"TRUE");

	PGrid_Adjust(hPGrid);

	Resource_Test();
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
#endif


/*
//���������� ֵ�ı��¼�
BOOL CALLBACK EventPGridValueChange(HELE hEle,HELE hEventEle,int id)
{
	XTRACE("����������ֵ�ı�=%d \n",id);
	return TRUE;
}


//�������� �����
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XWnd_SetBorderSize(hWindow,1,1,1,1);

//	HELE hEditFile=XEditFile_Create(10,10,100,20,hWindow);
//	XEditFile_SetDefaultFile(hEditFile,L"F:\\��Ŀ\\XCGUI(2012_03_31)(v1.4.2+)\\*");
//	XEditFile_SetRelativeDir(hEditFile,L"F:\\��Ŀ");
	//XComboBox_Create(10,10,100,20,hWindow);


	//������������Ԫ��
	HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
	//�����
	int group1=XPGrid_AddGroup(hPGrid,L"һ�� ��1");
	//�����
	int item1=XPGrid_AddItem(hPGrid,L"���� editFile",PGRID_EDIT_FILE,group1);
	int item2=XPGrid_AddItem(hPGrid,L"���� color",PGRID_CHOOSECOLOR,group1);

	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);

	int group2=XPGrid_AddGroup(hPGrid,L"һ�� ��2");
	//���ֵΪ��̬�ַ���������
	XPGrid_AddItemString(hPGrid,L"���� �ַ���1",L"ֵ",group2);
	XPGrid_AddItemString(hPGrid,L"���� �ַ���2",L"ֵ",group2);


	int id=XPGrid_AddItem(hPGrid,L"��Ͽ�",PGRID_COMBOBOX);//,group2);
	HELE hCom=XPGrid_GetItemHEle(hPGrid,id);

	XComboBox_AddString(hCom,L"FALSE");
	XComboBox_AddString(hCom,L"TRUE");

	PGrid_Adjust(hPGrid);
	XEle_RegisterEvent(hPGrid,XE_PGRID_VALUECHANGE,EventPGridValueChange);

	XRunXCGUI();
	return 0;
}
*/



/*
//���������� ֵ�ı��¼�
BOOL CALLBACK EventPGridValueChange(HELE hEle,HELE hEventEle,int id)
{
	XTRACE("����������ֵ�ı�=%d \n",id);
	return TRUE;
}

BOOL CALLBACK EventPGridValueChange2(HELE hEle,HELE hEventEle,int id)
{
	XTRACE("����������ֵ�ı�2=%d \n",id);
	return TRUE;
}

//�����������
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,600,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	{
		//������������Ԫ��
		HELE hPGrid=XPGrid_Create(10,10,200,200,hWindow);
		//�����
		int group1=XPGrid_AddGroup(hPGrid,L"һ�� ��1");
		//�����
		int item1=XPGrid_AddItem(hPGrid,L"���� editFile",PGRID_EDIT_FILE,group1);
		int item2=XPGrid_AddItem(hPGrid,L"���� color",PGRID_CHOOSECOLOR,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);

		XEle_RegisterEvent(hPGrid,XE_PGRID_VALUECHANGE,EventPGridValueChange);
	}
	/////////////////////////////////////////////////
	{
		//������������Ԫ��
		HELE hPGrid2=XPGrid_Create(220,10,200,200,hWindow);
		//�����
		int group1=XPGrid_AddGroup(hPGrid2,L"һ�� ��1");
		//�����
		XPGrid_AddItem(hPGrid2,L"���� editFile",PGRID_EDIT_FILE,group1);
		XPGrid_AddItem(hPGrid2,L"���� color",PGRID_CHOOSECOLOR,group1);
		XPGrid_AddItem(hPGrid2,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid2,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid2,L"���� edit",PGRID_EDIT,group1);

		XEle_RegisterEvent(hPGrid2,XE_PGRID_VALUECHANGE,EventPGridValueChange2);
	}

	XRunXCGUI();
	return 0;
}
*/


/*
HELE hPGrid=NULL;
BOOL CALLBACK OnBtnClick(HELE hEle,HELE hEventEle)
{
	XPGrid_DeleteAll(hPGrid);
	int group1=XPGrid_AddGroup(hPGrid,L"һ�� ��1");
	//�����
	int item1=XPGrid_AddItem(hPGrid,L"���� editFile",PGRID_EDIT_FILE,group1);
	int item2=XPGrid_AddItem(hPGrid,L"���� color",PGRID_CHOOSECOLOR,group1);
	XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);

	XEle_RedrawEle(hPGrid);
	return TRUE;
}

//�����������
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,600,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	{
		//������������Ԫ��
		hPGrid=XPGrid_Create(10,10,200,200,hWindow);
		//�����
		int group1=XPGrid_AddGroup(hPGrid,L"һ�� ��1");
		//�����
		int item1=XPGrid_AddItem(hPGrid,L"���� editFile",PGRID_EDIT_FILE,group1);
		int item2=XPGrid_AddItem(hPGrid,L"���� color",PGRID_CHOOSECOLOR,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
		XPGrid_AddItem(hPGrid,L"���� edit",PGRID_EDIT,group1);
	}

	HELE hButton=XBtn_Create(220,10,60,20,L"button",hWindow);
	XEle_RegisterEvent(hButton,XE_BNCLICK,OnBtnClick);

	//XEle_EnableFocus(hPGrid,TRUE);
	/////////////////////////////////////////////////

	XRunXCGUI();
	return 0;
}
*/