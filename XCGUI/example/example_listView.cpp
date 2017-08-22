/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

#if 0

class CMyDraw : public CXEventMsg
{
public:
	HXCGUI   m_hImageList;
	void Init(HELE hListView)
	{
		m_hImageList=XListView_GetImageList(hListView);
		XCGUI_ListView_SetUserDrawItem(hListView,&CMyDraw::OnListView_DrawItem);
		//XCGUI_ListView_SetUserDrawGroup(hListView,&CMyDraw::OnListView_DrawGroup);
	}
	void OnListView_DrawItem(HELE hEle,listView_drawItem_ *pDrawItem)
	{
		listView_drawItem_ *pItem=pDrawItem;
		if(STATE_SELECT==pItem->state)
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(pItem->hDraw,pItem->rect.left,pItem->rect.top,pItem->rect.right+1,pItem->rect.bottom+1,3,3);
			XDraw_GradientFill2_(pItem->hDraw,RGB(255,255,255),RGB(210,210,210),&pItem->rect,GRADIENT_FILL_RECT_V);
			HBRUSH hBrush=XDraw_CreateSolidBrush_(pItem->hDraw,RGB(180,180,180));
			XDraw_FrameRgn_(pItem->hDraw,hRgn,hBrush,1,1);
			XDraw_DeleteObject_(pItem->hDraw,hBrush);
			XDraw_DeleteObject_(pItem->hDraw,hRgn);
		}
		XImageList_DrawImage2(m_hImageList,pItem->hDraw,pItem->imageID,&pItem->rcIconDraw);

		if(pItem->pText)
			XDraw_DrawText_(pItem->hDraw,pItem->pText,wcslen(pItem->pText),&pItem->rcText,DT_CENTER);
	}

	void OnListView_DrawGroup(HELE hEle,listView_drawGroup_ *pDrawGroup)
	{
		//	if(pDrawGroup->bExpand)
		{
			HBRUSH hBrush=CreateSolidBrush(RGB(128,128,128));
			XDraw_GradientFill2_(pDrawGroup->hDraw,RGB(255,255,255),RGB(200,200,200),&pDrawGroup->rcButton,1);
			XDraw_FrameRect_(pDrawGroup->hDraw,&pDrawGroup->rcButton,hBrush);

			XDraw_MoveToEx_(pDrawGroup->hDraw,pDrawGroup->rcButton.left+2,pDrawGroup->rcButton.top+(pDrawGroup->rcButton.bottom-pDrawGroup->rcButton.top)/2,NULL);
			XDraw_LineTo_(pDrawGroup->hDraw,pDrawGroup->rcButton.right-2,pDrawGroup->rcButton.top+(pDrawGroup->rcButton.bottom-pDrawGroup->rcButton.top)/2);
			if(!pDrawGroup->bExpand)  //����
			{
				XDraw_MoveToEx_(pDrawGroup->hDraw,pDrawGroup->rcButton.left+(pDrawGroup->rcButton.right-pDrawGroup->rcButton.left)/2,pDrawGroup->rcButton.top+2,NULL);
				XDraw_LineTo_(pDrawGroup->hDraw,pDrawGroup->rcButton.left+(pDrawGroup->rcButton.right-pDrawGroup->rcButton.left)/2,pDrawGroup->rcButton.bottom-2);
			}
		}

		//����
		if(pDrawGroup->pText)
			XDraw_DrawText_(pDrawGroup->hDraw,pDrawGroup->pText,wcslen(pDrawGroup->pText),&pDrawGroup->rcText,0);
	}

};

/*
//�б���ͼ���Ի�
void CALLBACK OnListView_DrawItem(HELE hEle,listView_drawItem_ *pDrawItem)
{
	listView_drawItem_ *pItem=pDrawItem;
	if(pItem->bSelect)
	{
		HRGN hRgn=CreateRoundRectRgn(pItem->rect.left,pItem->rect.top,pItem->rect.right+1,pItem->rect.bottom+1,3,3);

		XDraw_GradientFill2(pItem->hdc,255,255,255,210,210,210,&pItem->rect,GRADIENT_FILL_RECT_V);
		HBRUSH hBrush=CreateSolidBrush(RGB(180,180,180));
		::FrameRgn(pItem->hdc,hRgn,hBrush,1,1);
		DeleteObject(hBrush);

		DeleteObject(hRgn);
	}

	int iconWidth=((listView_*)hEle)->iconSize.cx;
	int iconHeight=((listView_*)hEle)->iconSize.cy;
	int left=pItem->rcIcon.left+(pItem->rcIcon.right-pItem->rcIcon.left-iconWidth)/2;
	int top=pItem->rcIcon.bottom-iconHeight;

	XImageList_DrawImage(((listView_*)hEle)->hImageList,pItem->hdc,pItem->imageID,left,top);

	if(pItem->pText)
		DrawText(pItem->hdc,pItem->pText,wcslen(pItem->pText),&pItem->rcText,DT_CENTER);
}*/

void CALLBACK OnListView_DrawGroup(HELE hEle,listView_drawGroup_ *pDrawGroup)
{
	//	if(pDrawGroup->bExpand)
	{
		//XDraw_FillSolidRect(hdc,&pGroup->rcButton,RGB(255,0,0));
		HBRUSH hBrush=CreateSolidBrush(RGB(128,128,128));
		XDraw_GradientFill2_(pDrawGroup->hDraw,RGB(255,255,255),RGB(200,200,200),&pDrawGroup->rcButton,1);
		XDraw_FrameRect_(pDrawGroup->hDraw,&pDrawGroup->rcButton,hBrush);

		XDraw_MoveToEx_(pDrawGroup->hDraw,pDrawGroup->rcButton.left+2,pDrawGroup->rcButton.top+(pDrawGroup->rcButton.bottom-pDrawGroup->rcButton.top)/2,NULL);
		XDraw_LineTo_(pDrawGroup->hDraw,pDrawGroup->rcButton.right-2,pDrawGroup->rcButton.top+(pDrawGroup->rcButton.bottom-pDrawGroup->rcButton.top)/2);
		if(!pDrawGroup->bExpand)  //����
		{
			XDraw_MoveToEx_(pDrawGroup->hDraw,pDrawGroup->rcButton.left+(pDrawGroup->rcButton.right-pDrawGroup->rcButton.left)/2,pDrawGroup->rcButton.top+2,NULL);
			XDraw_LineTo_(pDrawGroup->hDraw,pDrawGroup->rcButton.left+(pDrawGroup->rcButton.right-pDrawGroup->rcButton.left)/2,pDrawGroup->rcButton.bottom-2);
		}
	}

	//����
	if(pDrawGroup->pText)
		XDraw_DrawText_(pDrawGroup->hDraw,pDrawGroup->pText,wcslen(pDrawGroup->pText),&pDrawGroup->rcText,0);
}

// �б���Ԫ��,��ѡ���¼�.
BOOL CALLBACK OnEventListViewSelect(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex)
{
	XTRACE("OnEventListViewSelect() groupIndex=%d itemIndex=%d \n",groupIndex,itemIndex);
	//int count=XListView_GetSelectCount(hEle);
/*	int  ids[100]={0};	
	int count=XListView_GetSelectAllItem(hEle,ids,100);
	for(int i=0;i<count;i++)
	{
		XTRACE("%d,",ids[i]);
	}*/
	XTRACE("---------------\n");
	return FALSE;
}

// �б���Ԫ��,��չ�������¼�
BOOL CALLBACK OnEventListViewExpand(HELE hEle,HELE hEventEle,int groupIndex,BOOL bExpand)
{
	XTRACE("OnEventListViewExpand() groupIndex=%d bExpand=%d \n",groupIndex ,bExpand?1:0);
	return FALSE;
}

BOOL CALLBACK OnEleLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	int groupIndex=-1;
	int itemIndex=-1;
	if(XListView_HitTest(hEle,pPt,&groupIndex,&itemIndex))
	{
		XTRACE("OnEleLButtonDown() groupIndex=%d itemIndex=%d \n",groupIndex,itemIndex);
	}
	return FALSE;
}

//�б���ͼ,��ͼ��
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,640,580,L"�Ųʽ����-����");

	HELE hListView=XListView_Create(10,10,600,300,hWindow);

	HIMAGE hImage=XImage_LoadFile(L"image\\open.ico");

	int group1=XListView_AddGroup(hListView,L"��1group1");
	int group2=XListView_AddGroup(hListView,L"��2group2");
	int group3=XListView_AddGroup(hListView,L"��3group3");

	XListView_AddItem(hListView,L"111",0,group1);
	int  iddel=XListView_AddItem(hListView,L"222",0,group1);
	XListView_AddItem(hListView,L"333",0,group1);


	XListView_AddItem(hListView,L"444",0,group2);
	int id2=XListView_AddItem(hListView,L"555",0,group2);
	XListView_AddItem(hListView,L"666",0,group2);


	XListView_AddItem(hListView,L"333\n333",NULL,group3);
	XListView_AddItem(hListView,L"444\n444\n444",NULL,group3);
	XListView_AddItem(hListView,L"444",NULL,group3);

	XListView_AddItem(hListView,L"555",0);
	XListView_AddItem(hListView,L"666",0);
	XListView_AddItem(hListView,L"777",0);

//	int res=XListView_InsertItem(hListView,id2,L"insert",0,group2);
//	res=XListView_InsertGroup(hListView,group2,L"insertGroup");

	HXCGUI hImageList=XImageList_Create(60,60);
	XImageList_AddImage(hImageList,hImage);

	XListView_EnableMultiSelect(hListView,FALSE);
	XListView_SetImageList(hListView,hImageList);
	//XListView_EnableExpandButton(hListView,FALSE);
	//XListView_SetUserDrawItem(hListView,OnListView_DrawItem);
	
	//XListView_SetUserDrawGroup(hListView,OnListView_DrawGroup);

	//XListView_DeleteItem(hListView,iddel);

//	XEle_RegisterEvent(hListView,XE_LISTVIEW_SELECT,OnEventListViewSelect);
//	XEle_RegisterEvent(hListView,XE_LISTVIEW_EXPAND,OnEventListViewExpand);
//	XEle_RegisterMessage(hListView,XM_LBUTTONDOWN,OnEleLButtonDown);

	CMyDraw  draw;
	draw.Init(hListView);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}


#endif


#if 0
// �б���Ԫ��,��ѡ���¼�.
BOOL CALLBACK OnEventListViewSelect(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex)
{
	XTRACE("��ѡ�� groupIndex=%d itemIndex=%d \n",groupIndex,itemIndex);

	return FALSE;
}

// �б���Ԫ��,��չ�������¼�
BOOL CALLBACK OnEventListViewExpand(HELE hEle,HELE hEventEle,int groupIndex,BOOL bExpand)
{
	//XTRACE("��չ������ groupIndex=%d bExpand=%d \n",groupIndex ,bExpand?1:0);
	return FALSE;
}

BOOL CALLBACK OnEleLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	int groupIndex=-1; //��
	int itemIndex=-1; //��
	if(XListView_HitTest(hEle,pPt,&groupIndex,&itemIndex))
	{
		//XTRACE("�����λ�� groupIndex=%d itemIndex=%d \n",groupIndex,itemIndex);
	}
	return FALSE;
}
HELE hListView=NULL;
BOOL CALLBACK OnClick(HELE hEle,HELE hEvent)
{
	XListView_SetSelectItem(hListView,0,1,TRUE);
	XEle_RedrawEle(hListView);
	return TRUE;
}

//�б���ͼ,��ͼ��
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,380,L"�Ųʽ����-����");

	hListView=XListView_Create(10,10,300,300,hWindow);

	HIMAGE hImage=XImage_LoadFile(L"image\\open.ico");
	HXCGUI hImageList=XImageList_Create(60,60);
	XImageList_AddImage(hImageList,hImage);
	XListView_SetImageList(hListView,hImageList);

	int group1=XListView_AddGroup(hListView,L"��1group1");
	int group2=XListView_AddGroup(hListView,L"��2group2");
	int group3=XListView_AddGroup(hListView,L"��3group3");

	XListView_AddItem(hListView,L"111",0,group1);
	int  iddel=XListView_AddItem(hListView,L"222",0,group1);
	XListView_AddItem(hListView,L"333",0,group1);

	XListView_AddItem(hListView,L"444",0,group2);
	int id2=XListView_AddItem(hListView,L"555",0,group2);
	XListView_AddItem(hListView,L"666",0,group2);

	XListView_AddItem(hListView,L"777\n777",NULL,group3);
	XListView_AddItem(hListView,L"888\n888\n88",NULL,group3);
	XListView_AddItem(hListView,L"999",NULL,group3);

	XListView_AddItem(hListView,L"11-11",0);
	XListView_AddItem(hListView,L"12-12",0);
	XListView_AddItem(hListView,L"13-13",0);

	XListView_SetIconSize(hListView,60,60);

	XEle_RegisterEvent(hListView,XE_LISTVIEW_SELECT,OnEventListViewSelect);
	XEle_RegisterEvent(hListView,XE_LISTVIEW_EXPAND,OnEventListViewExpand);
	XEle_RegisterMessage(hListView,XM_LBUTTONDOWN,OnEleLButtonDown);

	HELE hButton=XBtn_Create(320,10,60,20,L"Button",hWindow);
	XEle_RegisterEvent(hButton,XE_BNCLICK,OnClick);

	XListView_EnableMultiSelect(hListView,FALSE);
	//XSView_SetSpacing(hListView,20,20,20,20);
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}

#endif