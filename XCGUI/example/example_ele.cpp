/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

/*
#define BUTTON_LEFT    10
#define BUTTON_TOP     10 
#define BUTTON_WIDTH   100
#define BUTTON_HEIGHT  25
#define VIEW_LEFT      120;
#define VIEW_TOP       10;

HWINDOW hWindows;
HELE hButton1;
HELE hButton2;
HELE hButton3;
HELE hButton4;
HELE hButton5;
HELE hButton6;
HELE hButton7;
HELE hButton8;
HELE hButton9;
HELE hButton10;
HELE hButton11,hButton12,hButton13,hButton14,hButton15,hButton16,hButton17,hButton18;
HELE hView1,hView2,hView3,hView4,hView5,hView6,hView7,hView8,hView9,hView10,
	 hView11,hView12,hView13,hView14,hView15,hView16,hView17,hView18;

HELE hButtonSelect=NULL; //��ǰѡ��ı�ǩ


BOOL CALLBACK Window_OnSize(HWINDOW hWindow,UINT type,int cx,int cy)
{
	RECT rect;
	XWnd_GetClientRect(hWindow,&rect);
	
	rect.left=VIEW_LEFT;
	rect.top=VIEW_TOP;
	rect.right-=10;
	rect.bottom-=10;
	XEle_SetRect(hView1,&rect);
	XEle_SetRect(hView2,&rect);
	XEle_SetRect(hView3,&rect);
	XEle_SetRect(hView4,&rect);
	XEle_SetRect(hView5,&rect);
	XEle_SetRect(hView6,&rect);
	XEle_SetRect(hView7,&rect);
	XEle_SetRect(hView8,&rect);
	XEle_SetRect(hView9,&rect);
	XEle_SetRect(hView10,&rect);
	XEle_SetRect(hView11,&rect);
	XEle_SetRect(hView12,&rect);
	XEle_SetRect(hView13,&rect);
	XEle_SetRect(hView14,&rect);
	XEle_SetRect(hView15,&rect);
	XEle_SetRect(hView16,&rect);
	XEle_SetRect(hView17,&rect);
	XEle_SetRect(hView18,&rect);
	return FALSE;
}

void View_Hide() //��ʾѡ���view
{
	if(hButton1==hButtonSelect) //�ҵ���Ӧ�ı�ǩ
	{
		XEle_ShowEle(hView1,FALSE);
	}else if(hButton2==hButtonSelect)
	{
		XEle_ShowEle(hView2,FALSE);
	}else if(hButton3==hButtonSelect)
	{
		XEle_ShowEle(hView3,FALSE);
	}else if(hButton4==hButtonSelect)
	{	
		XEle_ShowEle(hView4,FALSE);	
	}else if(hButton5==hButtonSelect)
	{
		XEle_ShowEle(hView5,FALSE);
	}else if(hButton6==hButtonSelect)
	{	
		XEle_ShowEle(hView6,FALSE);		
	}else if(hButton7==hButtonSelect)
	{	
		XEle_ShowEle(hView7,FALSE);
	}else if(hButton8==hButtonSelect)
	{
		XEle_ShowEle(hView8,FALSE);
	}else if(hButton9==hButtonSelect)
	{
		XEle_ShowEle(hView9,FALSE);
	}else if(hButton10==hButtonSelect)
	{
		XEle_ShowEle(hView10,FALSE);
	}else if(hButton11==hButtonSelect)
	{
		XEle_ShowEle(hView11,FALSE);
	}
	else if(hButton12==hButtonSelect)
	{
		XEle_ShowEle(hView12,FALSE);
	}else if(hButton13==hButtonSelect)
	{
		XEle_ShowEle(hView13,FALSE);
	}else if(hButton14==hButtonSelect)
	{
		XEle_ShowEle(hView14,FALSE);
	}else if(hButton15==hButtonSelect)
	{
		XEle_ShowEle(hView15,FALSE);
	}else if(hButton16==hButtonSelect)
	{
		XEle_ShowEle(hView16,FALSE);
	}else if(hButton17==hButtonSelect)
	{
		XEle_ShowEle(hView17,FALSE);
	}else if(hButton18==hButtonSelect)
	{
		XEle_ShowEle(hView18,FALSE);
	}
}

BOOL CALLBACK Button_OnEventBtnClick(HELE hEle,HELE hEventEle)
{
	XTRACEW(L"btn %s \n",XBtn_GetText(hEventEle));
	if(hButtonSelect!=hEventEle)
	{
		if(hButtonSelect) //���ص�ǰ��ʾ��view
		{
			View_Hide();
		}
		if(hButton1==hEventEle)//��ʾѡ���view
		{
			XEle_ShowEle(hView1,TRUE);
			hButtonSelect=hButton1;
		}else if(hButton2==hEventEle)
		{
			XEle_ShowEle(hView2,TRUE);
			hButtonSelect=hButton2;
		}else if(hButton3==hEventEle)
		{
			XEle_ShowEle(hView3,TRUE);
			hButtonSelect=hButton3;
		}else if(hButton4==hEventEle)
		{
			XEle_ShowEle(hView4,TRUE);
			hButtonSelect=hButton4;
		}else if(hButton5==hEventEle)
		{
			XEle_ShowEle(hView5,TRUE);
			hButtonSelect=hButton5;
		}else if(hButton6==hEventEle)
		{
			XEle_ShowEle(hView6,TRUE);
			hButtonSelect=hButton6;
		}else if(hButton7==hEventEle)
		{
			XEle_ShowEle(hView7,TRUE);
			hButtonSelect=hButton7;
		}else if(hButton8==hEventEle)
		{
			XEle_ShowEle(hView8,TRUE);
			hButtonSelect=hButton8;
		}else if(hButton9==hEventEle)
		{
			XEle_ShowEle(hView9,TRUE);
			hButtonSelect=hButton9;
		}else if(hButton10==hEventEle)
		{
			XEle_ShowEle(hView10,TRUE);
			hButtonSelect=hButton10;
		}else if(hButton11==hEventEle)
		{
			XEle_ShowEle(hView11,TRUE);
			hButtonSelect=hButton11;
		}else if(hButton12==hEventEle)
		{
			XEle_ShowEle(hView12,TRUE);
			hButtonSelect=hButton12;
		}else if(hButton13==hEventEle)
		{
			XEle_ShowEle(hView13,TRUE);
			hButtonSelect=hButton13;
		}else if(hButton14==hEventEle)
		{
			XEle_ShowEle(hView14,TRUE);
			hButtonSelect=hButton14;
		}else if(hButton15==hEventEle)
		{
			XEle_ShowEle(hView15,TRUE);
			hButtonSelect=hButton15;
		}else if(hButton16==hEventEle)
		{
			XEle_ShowEle(hView16,TRUE);
			hButtonSelect=hButton16;
		}else if(hButton17==hEventEle)
		{
			XEle_ShowEle(hView17,TRUE);
			hButtonSelect=hButton17;
		}else if(hButton18==hEventEle)
		{
			XEle_ShowEle(hView18,TRUE);
			hButtonSelect=hButton18;
		}

		XWnd_RedrawWnd(hWindows);
	}
	return FALSE;
}

void View1_Create() //button
{
	HELE hViewButton=XBtn_Create(10,10,100,25,L"button");
	XEle_AddEle(hView1,hViewButton);
}

void View2_Create() //check
{
	HELE hViewCheck1=XCheck_Create(10,10,100,20,L"check1");
	HELE hViewCheck2=XCheck_Create(10,30,100,20,L"check2");
	HELE hViewCheck3=XCheck_Create(10,50,100,20,L"check3");
	HELE hViewCheck4=XCheck_Create(10,70,100,20,L"check4");
	HELE hViewCheck5=XCheck_Create(10,90,100,20,L"check5");
	XEle_AddEle(hView2,hViewCheck1);
	XEle_AddEle(hView2,hViewCheck2);
	XEle_AddEle(hView2,hViewCheck3);
	XEle_AddEle(hView2,hViewCheck4);
	XEle_AddEle(hView2,hViewCheck5);
}

void View3_Create() //radio
{
	HELE hRadio1=XRadio_Create(10,10,100,20,L"radio1");
	HELE hRadio2=XRadio_Create(10,30,100,20,L"radio2");
	HELE hRadio3=XRadio_Create(10,50,100,20,L"radio3");
	HELE hRadio4=XRadio_Create(10,70,100,20,L"radio4");
	HELE hRadio5=XRadio_Create(10,90,100,20,L"radio5");
	XEle_AddEle(hView3,hRadio1);
	XEle_AddEle(hView3,hRadio2);
	XEle_AddEle(hView3,hRadio3);
	XEle_AddEle(hView3,hRadio4);
	XEle_AddEle(hView3,hRadio5);
	XEle_SetId(hRadio1,1);
	XEle_SetId(hRadio2,2);
	XEle_SetId(hRadio3,3);
	XEle_SetId(hRadio4,4);
	XEle_SetId(hRadio5,5);
}
//////////////////////////////////////////////////////
HELE hEdit;
//��ȡѡ������
BOOL CALLBACK View4_OnEventBtnClick(HELE hEle,HELE hEventEle)
{
	HSTRING hString=XEdit_GetSelectText(hEdit);
	if(hString)
	{
		MessageBox(XEle_GetHWnd(hEdit),XStr_GetBuffer(hString),L"��ȡѡ������",0);
		XStr_Destroy(hString);
	}
	return FALSE;
}
void View4_Create() //edit
{
	hEdit=XEdit_Create(10,10,300,300);
	XEle_AddEle(hView4,hEdit);
	XEdit_EnableMultiLine(hEdit,TRUE);

	HELE hGetSelectText=XBtn_Create(320,10,80,20,L"��ȡѡ���ı�");
	XEle_AddEle(hView4,hGetSelectText);
	XEle_RegisterEvent(hGetSelectText,XE_BNCLICK,View4_OnEventBtnClick);
}

void View5_Create() //pass
{	
	HELE hEdit=XEdit_Create(10,10,100,20);
	XEle_AddEle(hView5,hEdit);
}

void View6_Create() //list
{
	HELE hList=XList_Create(10,10,300,200);
	XEle_AddEle(hView6,hList);
	XList_AddColumn(hList,100,L"111");
	XList_AddColumn(hList,100,L"222");
	XList_AddColumn(hList,100,L"333");
	XList_AddItem(hList,L"item0");
	XList_AddItem(hList,L"item1");
	XList_AddItem(hList,L"item2");
	XList_SetItemText(hList,0,1,L"child1");
	XList_SetItemText(hList,0,2,L"child2");
}

void View7_Create() //tree
{
	HELE hTree=XTree_Create(10,10,200,300);
	XEle_AddEle(hView7,hTree);
	int root=XTree_InsertItem(hTree,L"root");
	XTree_InsertItem(hTree,L"item1",root);
	XTree_InsertItem(hTree,L"item2",root);
	XTree_InsertItem(hTree,L"item3",root);
}

void View8_Create() //listBox
{
	HELE hListBox=XListBox_Create(10,10,300,200);
	XEle_AddEle(hView8,hListBox);
	XListBox_AddString(hListBox,L"1111111");
	XListBox_AddString(hListBox,L"2222222");
	XListBox_AddString(hListBox,L"3333333");
}

void View9_Create()
{
	//���
}

void View10_Create()
{
	HELE hComboBox=XComboBox_Create(10,10,200,20);
	XEle_AddEle(hView10,hComboBox);
	XComboBox_AddString(hComboBox,L"111");
	XComboBox_AddString(hComboBox,L"222");
	XComboBox_AddString(hComboBox,L"333");
	XComboBox_SetText(hComboBox,1);
}
void View11_Create()
{
}
void View12_Create()
{
}
void View13_Create()
{
}
void View14_Create()
{
}
void View15_Create()
{
}
void View16_Create()
{
}
void View17_Create()
{
}
void View18_Create()
{
}
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	hWindows=XWnd_CreateWindow(400,200,600,520,L"���Դ���",XC_SY_MINIMIZE| XC_SY_MAXIMIZE | XC_SY_CLOSE);
	XWnd_ShowWindow(hWindows,SW_SHOW);
	XWnd_RegisterMessage(hWindows,WM_SIZE,Window_OnSize);

	int top=BUTTON_TOP;
	//����ѡ���ǩ
	hButton1=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"��ť"); top+=BUTTON_HEIGHT; top++;
	hButton2=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"��ѡ��ť"); top+=BUTTON_HEIGHT; top++;
	hButton3=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"��ѡ��ť"); top+=BUTTON_HEIGHT; top++;
	hButton4=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�༭��"); top+=BUTTON_HEIGHT; top++;
	hButton5=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�����"); top+=BUTTON_HEIGHT; top++;
	hButton6=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�б��"); top+=BUTTON_HEIGHT; top++;
	hButton7=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�б���"); top+=BUTTON_HEIGHT; top++;
	hButton8=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�ַ����б��"); top+=BUTTON_HEIGHT; top++;
	hButton9=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"���"); top+=BUTTON_HEIGHT; top++;
	hButton10=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"��Ͽ�"); top+=BUTTON_HEIGHT; top++;
	hButton11=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"TABԪ��"); top+=BUTTON_HEIGHT; top++;
	hButton12=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"������"); top+=BUTTON_HEIGHT; top++;
	hButton13=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"������"); top+=BUTTON_HEIGHT; top++;
	hButton14=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"������"); top+=BUTTON_HEIGHT; top++;
	hButton15=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"��̬�ı�"); top+=BUTTON_HEIGHT; top++;
	hButton16=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�����˵�"); top+=BUTTON_HEIGHT; top++;
	hButton17=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"�˵���"); top+=BUTTON_HEIGHT; top++;
	hButton18=XBtn_Create(BUTTON_LEFT,top,BUTTON_WIDTH,BUTTON_HEIGHT,L"������"); top+=BUTTON_HEIGHT; top++;

	XWnd_AddEle(hWindows,hButton1);
	XWnd_AddEle(hWindows,hButton2);
	XWnd_AddEle(hWindows,hButton3);
	XWnd_AddEle(hWindows,hButton4);
	XWnd_AddEle(hWindows,hButton5);
	XWnd_AddEle(hWindows,hButton6);
	XWnd_AddEle(hWindows,hButton7);
	XWnd_AddEle(hWindows,hButton8);
	XWnd_AddEle(hWindows,hButton9);
	XWnd_AddEle(hWindows,hButton10);
	XWnd_AddEle(hWindows,hButton11);
	XWnd_AddEle(hWindows,hButton12);
	XWnd_AddEle(hWindows,hButton13);
	XWnd_AddEle(hWindows,hButton14);
	XWnd_AddEle(hWindows,hButton15);
	XWnd_AddEle(hWindows,hButton16);
	XWnd_AddEle(hWindows,hButton17);
	XWnd_AddEle(hWindows,hButton18);

	//�¼�ӳ��
	XEle_RegisterEvent(hButton1,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton3,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton4,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton5,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton6,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton7,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton8,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton9,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton10,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton11,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton12,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton13,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton14,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton15,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton16,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton17,XE_BNCLICK,Button_OnEventBtnClick);
	XEle_RegisterEvent(hButton18,XE_BNCLICK,Button_OnEventBtnClick);

	//������ͼ
	hView1=XEle_Create(0,0,10,10);
	hView2=XEle_Create(0,0,10,10);
	hView3=XEle_Create(0,0,10,10);
	hView4=XEle_Create(0,0,10,10);
	hView5=XEle_Create(0,0,10,10);
	hView6=XEle_Create(0,0,10,10);
	hView7=XEle_Create(0,0,10,10);
	hView8=XEle_Create(0,0,10,10);
	hView9=XEle_Create(0,0,10,10);
	hView10=XEle_Create(0,0,10,10);
	hView11=XEle_Create(0,0,10,10);
	hView12=XEle_Create(0,0,10,10);
	hView13=XEle_Create(0,0,10,10);
	hView14=XEle_Create(0,0,10,10);
	hView15=XEle_Create(0,0,10,10);
	hView16=XEle_Create(0,0,10,10);
	hView17=XEle_Create(0,0,10,10);
	hView18=XEle_Create(0,0,10,10);

	XWnd_AddEle(hWindows,hView1);
	XWnd_AddEle(hWindows,hView2);
	XWnd_AddEle(hWindows,hView3);
	XWnd_AddEle(hWindows,hView4);
	XWnd_AddEle(hWindows,hView5);
	XWnd_AddEle(hWindows,hView6);
	XWnd_AddEle(hWindows,hView7);
	XWnd_AddEle(hWindows,hView8);
	XWnd_AddEle(hWindows,hView9);
	XWnd_AddEle(hWindows,hView10);
	XWnd_AddEle(hWindows,hView11);
	XWnd_AddEle(hWindows,hView12);
	XWnd_AddEle(hWindows,hView13);
	XWnd_AddEle(hWindows,hView14);
	XWnd_AddEle(hWindows,hView15);
	XWnd_AddEle(hWindows,hView16);
	XWnd_AddEle(hWindows,hView17);
	XWnd_AddEle(hWindows,hView18);

	//XEle_ShowEle(hView1,FALSE);
	XEle_ShowEle(hView2,FALSE);
	XEle_ShowEle(hView3,FALSE);
	XEle_ShowEle(hView4,FALSE);
	XEle_ShowEle(hView5,FALSE);
	XEle_ShowEle(hView6,FALSE);
	XEle_ShowEle(hView7,FALSE);
	XEle_ShowEle(hView8,FALSE);
	XEle_ShowEle(hView9,FALSE);
	XEle_ShowEle(hView10,FALSE);
	XEle_ShowEle(hView11,FALSE);
	XEle_ShowEle(hView12,FALSE);
	XEle_ShowEle(hView13,FALSE);
	XEle_ShowEle(hView14,FALSE);
	XEle_ShowEle(hView15,FALSE);
	XEle_ShowEle(hView16,FALSE);
	XEle_ShowEle(hView17,FALSE);
	XEle_ShowEle(hView18,FALSE);

	hButtonSelect=hButton1;

	View1_Create();
	View2_Create();
	View3_Create();
	View4_Create();
	View5_Create();
	View6_Create();
	View7_Create();
	View8_Create();
	View9_Create();
	View10_Create();
	View11_Create();
	View12_Create();
	View13_Create();
	View14_Create();
	View15_Create();
	View16_Create();
	View17_Create();
	View18_Create();

	Window_OnSize(hWindows,0,0,0);
	XRunXCGUI();

	return 0;
}
*/