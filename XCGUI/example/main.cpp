/**************************************************************************\
*
* Copyright 
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"



/*
BOOL CALLBACK OnEventListViewDragInsert(HELE hEle,HELE hEventEle,listView_dragInsert_ *pInfo) //�б���ͼԪ��,�û��϶�������¼�
{

	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	int size=sizeof(UINT_PTR);
	XInitXCGUI();
	
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,400,L"�Ųʽ����-����");//��������
	if(hWindow)
	{
	//	HELE hButton=XBtn_Create(10,10,80,25,L"��ť",hWindow);//������ť
	//	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);//ע�ᰴť����¼�

		HIMAGE hImage1 = XImage_LoadFile(L"image3//���� 1.png",0); //XImage_LoadFile(L"image3//1.png",0);
		HIMAGE hImage2 = XImage_LoadFile(L"image3//bg_Mian1.png",0); //XImage_LoadFile(L"image3//2.png",0);
		HIMAGE hImage3 = XImage_LoadFile(L"image3//3.png",0);
		HIMAGE hImage4 = XImage_LoadFile(L"image3//4.png",0);
		HIMAGE hImage5 = XImage_LoadFile(L"image3//5.png",0);
		HIMAGE hImage6 = XImage_LoadFile(L"image3//6.png",0);
		HIMAGE hImage7 = XImage_LoadFile(L"image3//bntimg//Add_But.png",0);

		HXCGUI hImageList=XImageList_Create(48,48);
		XImageList_EnableFixedSize(hImageList,false);

		XImageList_AddImage(hImageList,hImage1);
		XImageList_AddImage(hImageList,hImage2);
		XImageList_AddImage(hImageList,hImage3);
		XImageList_AddImage(hImageList,hImage4);
		XImageList_AddImage(hImageList,hImage5);
		XImageList_AddImage(hImageList,hImage6);
		XImageList_AddImage(hImageList,hImage7);

		HELE hListView=XListView_Create(10,10,300,300,hWindow);

		//XEle_SetBkColor(hListView,RGB(255,0,0));	
		XListView_SetImageList(hListView,hImageList);
		XListView_AddItem(hListView,L"����",0);
		XListView_AddItem(hListView,L"�Ա�",1);
		XListView_AddItem(hListView,L"�Ѻ�",2);
		XListView_AddItem(hListView,L"�Ų�",3);
		XListView_AddItem(hListView,L"�ٶ�",4);
	//	XListView_AddItem(hListView,L"�ȸ�",5);
	//	XListView_AddItem(hListView,L"���Ӧ��",6);
		XListView_EnableMultiSelect(hListView,false);

		//XImage_LoadFileAdaptive(L"image3\\bk_select.png",12,72,12,72);
		HIMAGE hImage_Select=XImage_LoadFileAdaptive(L"image3\\bk_select.png",12,72,12,72);
		HIMAGE hImage_stay=XImage_LoadFileAdaptive(L"image3\\bk_stay.png",12,72,12,72);

		XListView_SetItemImageSelect(hListView,-1,0,hImage_Select);
		XListView_SetItemImageStay(hListView,-1,0,hImage_stay);

		XListView_SetItemImageSelect(hListView,-1,1,hImage_Select);
		XListView_SetItemImageStay(hListView,-1,1,hImage_stay);

		XListView_SetItemImageSelect(hListView,-1,2,hImage_Select);
		XListView_SetItemImageStay(hListView,-1,2,hImage_stay);


		XEle_RegisterEvent(hListView,XE_LISTVIEW_DRAG_INSERT,OnEventListViewDragInsert);

		XWnd_ShowWindow(hWindow,SW_SHOW);//��ʾ����

		XRunXCGUI();
	}
	return 0;
}
*/