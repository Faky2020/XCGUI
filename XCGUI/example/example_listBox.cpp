/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


/*
/////////////////////////////////////////////
BOOL CALLBACK OnEleRButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
    POINT pt=*pPt;

  //  pt.x+=XWnd_GetClientLeft(hWindow);
 //   pt.y+=XWnd_GetClientTop(hWindow);
    
	RECT rc;
	XListBox_GetItemRect(hEle,1,&rc);

	int index=XListBox_HitTest(hEle,&pt);
	XTRACE("index=%d \n",index);
	if(index>=0)
	{
		//���������˵�
		HMENUX hMenu=XMenu_Create();
		XMenu_AddItem(hMenu,201,L"���");
		XMenu_AddItem(hMenu,202,L"������");
		XMenu_AddItem(hMenu,203,L"ɾ��");

		XEle_PointToNCWnd(hEle,&pt);

		HWINDOW hWindow=XEle_GetHWindow(hEle);
		ClientToScreen(XWnd_GetHWnd(hWindow),&pt);
		XMenu_Popup(hMenu,XWnd_GetHWnd(hWindow),pt.x,pt.y);
	}
	return FALSE;
}

//�б��
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//�����б��
	HELE hListBox=XListBox_Create(10,10,300,200,hWindow);
	XListBox_AddString(hListBox,L"111111111111",0);
	XListBox_AddString(hListBox,L"22222",0);
	XListBox_AddString(hListBox,L"333333333",0);
	XListBox_AddString(hListBox,L"4444444",1);
	XListBox_AddString(hListBox,L"5555555",1);
	XListBox_AddString(hListBox,L"66666666666",1);
	XListBox_AddString(hListBox,L"777777777",1);
	XListBox_AddString(hListBox,L"8888888888888888888888888888888888888888888888123",1);
	XListBox_AddString(hListBox,L"999999999",0);
	XListBox_AddString(hListBox,L"10101010",0);
	XListBox_AddString(hListBox,L"11111111",0);
	XListBox_AddString(hListBox,L"12121212",0);

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico")); //���ͼ��
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2055.ico"));

	//�����б��
	XListBox_SetImageList(hListBox,hImageList);

	XListBox_EnableCheckBox(hListBox,TRUE);


	itemBindEle_ info;
	info.hEle=XBtn_Create(10,10,100,20,L"aaa",hListBox);
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XListBox_SetItemBindEle(hListBox,2,&info);
	
	//XListBox_SetItemMouseStayColor(hListBox,RGB(255,0,0));

	XEle_RegisterMessage(hListBox,XM_RBUTTONUP,OnEleRButtonUp);

	XRunXCGUI();

	return 0;
}
*/

////////////////////////////////////////////////////////////////////////
/*
//�Ի��б����
void CALLBACK MyListBox_DrawItem(HELE hEle,listBox_drawItem_ *pDrawItem)
{
	//���Ʊ���
	if(STATE_SELECT==pDrawItem->state)
	{
		XDraw_FillSolidRect(pDrawItem->hdc,&pDrawItem->rcItem,RGB(0,255,0));
	}else
	{
		if(0==pDrawItem->index%2)
			XDraw_FillSolidRect(pDrawItem->hdc,&pDrawItem->rcItem,RGB(197,255,197));
		else
			XDraw_FillSolidRect(pDrawItem->hdc,&pDrawItem->rcItem,RGB(255,202,202));
	}
	//����ͼ��
	HXCGUI hImageList=XListBox_GetImageList(hEle);
	RECT rect=pDrawItem->rcItem;
	rect.left+=15;
	XImageList_DrawImage(hImageList,pDrawItem->hdc,pDrawItem->imageId,rect.left+3,rect.top+2);
	rect.left+=22;

	//�����ı�
	DrawText(pDrawItem->hdc,pDrawItem->pText,wcslen(pDrawItem->pText),&rect,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

	//���Ƹ�ѡ��
	int top=pDrawItem->rcCheck.top+(pDrawItem->rcCheck.bottom-pDrawItem->rcCheck.top)/2-6;
	int left=pDrawItem->rcCheck.left;
	if( XListBox_IsItemCheck(hEle,pDrawItem->index))
	{
		XDraw_Check(pDrawItem->hdc,left,top,TRUE);
	}else
	{
		XDraw_Check(pDrawItem->hdc,left,top,FALSE);
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,400,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//�����б��
	HELE hListBox=XListBox_Create(10,10,300,200,hWindow);
	XListBox_AddString(hListBox,L"111111111111",0);
	XListBox_AddString(hListBox,L"22222",0);
	XListBox_AddString(hListBox,L"333333333",0);
	XListBox_AddString(hListBox,L"4444444",1);
	XListBox_AddString(hListBox,L"5555555",1);
	XListBox_AddString(hListBox,L"66666666666",1);
	XListBox_AddString(hListBox,L"777777777",1);
	XListBox_AddString(hListBox,L"8888888888",1);
	XListBox_AddString(hListBox,L"999999999",0);
	XListBox_AddString(hListBox,L"10101010",0);
	XListBox_AddString(hListBox,L"11111111",0);
	XListBox_AddString(hListBox,L"12121212",0);

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);

	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico")); //���ͼ��
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2055.ico"));

	//ͼƬ�б�����б��
	XListBox_SetImageList(hListBox,hImageList);

	//�����Ի��б����
	XListBox_SetUserDrawItem(hListBox,MyListBox_DrawItem);

	XListBox_EnableCheckBox(hListBox,TRUE);

	XRunXCGUI();

	return 0;
}*/