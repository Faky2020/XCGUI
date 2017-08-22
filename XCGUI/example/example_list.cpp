/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



#if 0


HELE hEdit;//�༭����Դ���
//�б���ѡ���¼�
BOOL CALLBACK MyEventListSelect(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle) return FALSE;

	//hEle:�б�Ԫ�ؾ��
	//id:��ǰѡ��������
	//��ȡѡ��������
	int count=XList_GetSelectCount(hEventEle);
	//�����ѡ�����
	if(count>0)
	{
		//�����������ѡ��������
		int *pArr=new int[count];
		//��ȡѡ��������
		XList_GetSelectAllItem(hEventEle,pArr,count);
		//�����ַ�����Դ
		HSTRING hStr=XStr_Create();
		XStr_SetString(hStr,L"��ǰѡ�����:\n");
		for(int i=0;i<count;i++)
		{
			//��ȡ������
			wchar_t *pText=XList_GetItemText(hEventEle,pArr[i],0);
			if(pText)
			{
				wchar_t buf[20]={0};
				wsprintf(buf,L"index=%d, ",pArr[i]);
				//��ӵ��ַ�����Դ��
				XStr_AddString(hStr,buf);
				XStr_AddString(hStr,pText);
				XStr_AddString(hStr,L"\n");
			}
			//���ñ༭������
			XEdit_SetText(hEdit,XStr_GetBuffer(hStr));
		}
		//�����ַ�����Դ���
		XStr_Destroy(hStr);
		delete []pArr;
	}else
		XEdit_SetText(hEdit,NULL);
	//�ػ�༭����ͼ
	XEle_RedrawEle(hEdit);
	return TRUE;
}

//�б�ͷ�����¼�
BOOL CALLBACK MyEventListHeaderClick(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle) return FALSE;
	//hEle:�б�Ԫ�ؾ��
	//id:�б�ͷ������
	wchar_t buf[50]={0};
	wsprintf(buf,L"����б�ͷ:\nid=%d\n%s",id,XList_GetHeaderItemText(hEventEle,id));
	//���ñ༭������,��ʾ�б�ͷ�����¼�
	XEdit_SetText(hEdit,buf);
	//�ػ�༭����ͼ
	XEle_RedrawEle(hEdit);
	return TRUE;
}

//�б�Ԫ��-�б�ͷ���ȸı��¼�
BOOL CALLBACK MyEventListHeaderChange(HELE hEle,HELE hEventEle,int id,int width)
{
	if(hEle!=hEventEle) return FALSE;
	//hEle:�б�Ԫ�ؾ��
	//id:�б�ͷ������
	//width:��ǰ����
	wchar_t buf[50]={0};
	wsprintf(buf,L"�б�ͷ���ȸı�:\nid=%d\nwidth=%d\n%s",id,width,XList_GetHeaderItemText(hEventEle,id));
	//���ñ༭������,��ʾ�б�ͷ���ȸı��¼�
	XEdit_SetText(hEdit,buf);
	//�ػ�༭����ͼ
	XEle_RedrawEle(hEdit);
	return TRUE;
}

//�����˵���ѡ���¼�
BOOL CALLBACK MyEventMenuSelect(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle) return FALSE;
	//hEle:�б�Ԫ�ؾ��
	//id:�˵���id
	switch(id)
	{
	case 1: //ȡ��ѡ��
		{
			//ȡ���б�Ԫ������ѡ����
			XList_CancelSelectAll(hEle);
			//�ػ�����б�Ԫ����ͼ
			XEle_RedrawEle(hEle);
		}break;
	case 2: //ɾ����
		{
			//��ȡ�б�Ԫ�ص�ǰѡ�����
			int hItem=XList_GetSelectItem(hEle);
			//���ѡ���Ϊ��
			if(-1!=hItem)
			{
				//ɾ��ѡ�����
				XList_DeleteItem(hEle,hItem);
				//�ػ�����б�Ԫ����ͼ
				XEle_RedrawEle(hEle);
			}
		}break;
	case 3: //ȫѡ
		{
			//ѡ��������
			XList_SetSelectItemAll(hEle);
			//�ػ�����б�Ԫ����ͼ
			XEle_RedrawEle(hEle);
		}break;
	case 4: //���
		{
			//ɾ��������
			XList_DeleteAllItems(hEle);
			//�ػ�����б�Ԫ����ͼ
			XEle_RedrawEle(hEle);
		}break;
	}
	//����㲻֪���������ô��,�ͷ���FALSE
	return TRUE;
}

//�б�Ԫ������Ҽ�������Ϣ
BOOL CALLBACK MyRButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
	//hEle:�б�Ԫ����Դ���
	//��ȡ�������������
	int pos=XList_HitTest(hEle,pPt); 
	//ȷ�������ڿհ���
	if(pos>=0) 
	{
		//ȡ������ѡ����
		XList_CancelSelectAll(hEle);
		//ѡ�����������
		XList_SetSelectItem(hEle,pos);
		//�ػ��Ա���½���
		XEle_RedrawEle(hEle);
		//���������˵�
		HMENUX hMenu=XMenu_Create();
		//��Ӳ˵���
		XMenu_AddItem(hMenu,1,L"ȡ��ѡ��");
		XMenu_AddItem(hMenu,2,L"ɾ����");
		XMenu_AddItem(hMenu,3,L"ȫѡ");
		XMenu_AddItem(hMenu,4,L"���");
		//�������ת������Ļ����
		POINT pt=*pPt;
		XEle_PointToNCWnd(hEle,&pt);
		ClientToScreen(XEle_GetHWnd(hEle),&pt);
		//�����˵�
		XMenu_Popup(hMenu,XEle_GetHWnd(hEle),pt.x,pt.y,hEle);
		//ע��˵���ѡ���¼�
		XEle_RegisterEvent(hEle,XE_MENUSELECT,MyEventMenuSelect);
	}
	//Ĭ�Ϸ���FALSE
	return FALSE;
}

//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,640,350,L"�Ųʽ����-����");

	//���ô��ڱ���ͼƬ
	//XWnd_SetImage(hWindow,L"image\\11.jpg");
	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//�����б�Ԫ��
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//����ͼƬ�б�
	XList_SetImageList(hList,hImageList);
	//����б�ͷ
	XList_AddColumn(hList,160,L"�б�ͷ��-1",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-2",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-3",2);
	//����б���
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<12;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//�����
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//������������
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}
	//�����ұ߱༭��,��ʾ�б�Ԫ���¼�
	hEdit=XEdit_Create(465,10,150,300,hWindow);
	//����֧�ֶ���
	XEdit_EnableMultiLine(hEdit,TRUE);
	//ע���б�Ԫ����ѡ���¼�
	XEle_RegisterEvent(hList,XE_LIST_SELECT,MyEventListSelect);
	//ע���б�Ԫ��-�б�ͷ�����¼�
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CLICK,MyEventListHeaderClick);
	//ע���б�Ԫ��-�б�ͷ���ȸı��¼�
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CHANGE,MyEventListHeaderChange);
	//ע���б�Ԫ��-����Ҽ�������Ϣ
	XEle_RegisterMessage(hList,XM_RBUTTONUP,MyRButtonUp);

	XEle_SetBkColor(XSView_GetView(hList),RGB(200,200,200));

	itemBindEle_ info;
	info.hEle=XBtn_Create(0,0,10,10,L"1111");
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XList_SetItemBindEle(hList,3,0,&info);

	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����

	//���г���
	XRunXCGUI();
	//����ͼƬ�б�
	//XImageList_Destroy(hImageList);
	return 0;
}

#endif 

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/*
BOOL CALLBACK MyEventListSelect(HELE hEle,HELE hEventEle,int id)
{	
	//hEle:�б�Ԫ�ؾ��
	//id:��ǰѡ��������
	return FALSE;
}

//�б�ͷ�����¼�
BOOL CALLBACK MyEventListHeaderClick(HELE hEle,HELE hEventEle,int id)
{
	//hEle:�б�Ԫ�ؾ��
	//id:�б�ͷ������
	return FALSE;
}

//�б�Ԫ��-�б�ͷ���ȸı��¼�
BOOL CALLBACK MyEventListHeaderChange(HELE hEle,HELE hEventEle,int id,int width)
{
	//hEle:�б�Ԫ�ؾ��
	//id:�б�ͷ������
	//width:��ǰ����
	return FALSE;
}
//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,350,L"�Ųʽ����-����");
	//��ʾ����
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//�����б�Ԫ��
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//����ͼƬ�б�
	XList_SetImageList(hList,hImageList);
	//����б�ͷ
	XList_AddColumn(hList,160,L"�б�ͷ��-1",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-2",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-3",2);
	//����б���
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<100;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//�����
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//������������
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}

	//ע���б�Ԫ����ѡ���¼�
	XEle_RegisterEvent(hList,XE_LIST_SELECT,MyEventListSelect);
	//ע���б�Ԫ��-�б�ͷ�����¼�
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CLICK,MyEventListHeaderClick);
	//ע���б�Ԫ��-�б�ͷ���ȸı��¼�
	XEle_RegisterEvent(hList,XE_LIST_HEADER_CHANGE,MyEventListHeaderChange);
	//���г���
	XRunXCGUI();
	//����ͼƬ�б�
	//XImageList_Destroy(hImageList);
	return 0;
}
*/


////////////////////////////////////////////////////////////////////////////////////
/*
//�б�ͷ�Ի�
void CALLBACK MyListHeader_DrawItem(HELE hEle,listHeader_drawItem_ *pDrawItem)
{
	XTRACE("���Ʊ��� \n");
	RECT rect=pDrawItem->rect;
	//�����б�ͷ����
	if(-1==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(0,210,0));

		HPEN hPen=XDraw_CreatePen_(pDrawItem->hDraw,PS_SOLID,2,RGB(255,0,0));
		HGDIOBJ hOldPen=XDraw_SelectObject_(pDrawItem->hDraw,hPen);
		XDraw_MoveToEx_(pDrawItem->hDraw,0,rect.bottom-1,0);
		XDraw_LineTo_(pDrawItem->hDraw,rect.right,rect.bottom-1);
		XDraw_SelectObject_(pDrawItem->hDraw,hOldPen);
		XDraw_DeleteObject_(pDrawItem->hDraw,hPen);
		return ;
	}
	rect.bottom-=2;
	//�����б�ͷ��
	if(STATE_LEAVE==pDrawItem->state)
	{
		rect.right--;
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(0,255,0));
	}else if(STATE_STAY==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(255,147,147));
	}else if(STATE_DOWN==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(255,202,202));
	}
	//����ͼ��
	HXCGUI hImageList=XList_GetImageList(hEle);
	if(hImageList)
	{
		XImageList_DrawImage(hImageList,pDrawItem->hDraw,pDrawItem->imageId,rect.left+3,rect.top+5);
		rect.left+=22;
	}else
		rect.left+=3;
	rect.top+=3;
	//�����ı�
	XDraw_DrawText_(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&rect,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

}

//�б��Ի�
void CALLBACK MyList_OnDrawItem(HELE hEle,list_drawItem_ *pDrawItem)
{
	//���Ʊ���
	if(STATE_SELECT==pDrawItem->state)
	{
		XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(0,255,0));
	}else
	{
		if(0==pDrawItem->index%2)
			XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(197,255,197));
		else
			XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(255,202,202));
	}
	//����ͼ��
	HXCGUI hImageList=XList_GetImageList(hEle);
	RECT rect=pDrawItem->rect;
	if(hImageList)
	{
		rect.left+=3;
		XImageList_DrawImage(hImageList,pDrawItem->hDraw,pDrawItem->imageId,rect.left,pDrawItem->rect.top+3);
		rect.left+=19;
	}else
		rect.left+=3;
	//�����ı�
	XDraw_DrawText_(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&rect,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}

//���ڶ������Ķ����---����
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,500,380,L"�Ųʽ����-����");

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,true);
	//���ͼƬ

	HIMAGE hImage1=XImage_LoadFile(L"image\\2055.ico");
	HIMAGE hImage2=XImage_LoadFile(L"image\\2050.ico");
	HIMAGE hImage3=XImage_LoadFile(L"image/2063.ico");
	XImageList_AddImage(hImageList,hImage1);
	XImageList_AddImage(hImageList,hImage2);
	XImageList_AddImage(hImageList,hImage3);

	//�����б�Ԫ��
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//����ͼƬ�б�
	XList_SetImageList(hList,hImageList);
	//����б�ͷ
	XList_AddColumn(hList,160,L"�б�ͷ��-1",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-2",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-3",2);
	//����б���
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//�����
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//������������
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}

	XList_SetUserDrawItem(hList,MyList_OnDrawItem);
	XList_SetUserDrawItemHeader(hList,MyListHeader_DrawItem);
	//��ʾ����
	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();    //���г���
	return 0;
}
*/



/*
///����ѡ��ť///////////////////////////////////////////////////////////////////////////////////
//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,350,L"�Ųʽ����-����");
	//��ʾ����
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ
	XImageList_AddImage(hImageList,XImage_LoadFile( L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//�����б�Ԫ��
	HELE hList=XList_Create(10,10,450,300,hWindow);
	//����ͼƬ�б�
	XList_SetImageList(hList,hImageList);
	//����б�ͷ
	XList_AddColumn(hList,160,L"�б�ͷ��-1",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-2",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-3",2);
	//����б���
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//�����
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//������������
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}
//	XList_ShowHeader(hList,FALSE);
	XList_EnableGrid(hList,FALSE);
	XList_EnableCheckBox(hList,TRUE);

//	XList_SetHeaderHeight(hList,50);
	//���г���
	XRunXCGUI();

	return 0;
}*/



/*
//����:�����
HELE hList=NULL;
BOOL CALLBACK EleLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	//�������
	int item,sub;
	BOOL res=XList_HitTestEx(hList,pPt,&item,&sub);
	if(res)
		XTRACE("hit line=%d, column=%d \n", item,sub);

	return FALSE;
}

//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,500,350,L"�Ųʽ����-����");
	//��ʾ����
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ
	XImageList_AddImage(hImageList,XImage_LoadFile( L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//�����б�Ԫ��
	hList=XList_Create(10,10,450,300,hWindow);
	//����ͼƬ�б�
	XList_SetImageList(hList,hImageList);
	//����б�ͷ
	XList_AddColumn(hList,160,L"�б�ͷ��-1",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-2",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-3",2);
	//����б���
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//�����
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//������������
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}
	XList_EnableGrid(hList,FALSE);
	XList_EnableCheckBox(hList,TRUE);

	XEle_RegisterMessage(hList,XM_LBUTTONDOWN,EleLButtonDown);

	//���г���
	XRunXCGUI();

	return 0;
}*/

/*

BOOL CALLBACK OnEventSetFocus(HELE hEle,HELE hEventEle)
{
	if( hEle== hEventEle)
		XTRACE("list ��ý��� \n");
	return FALSE;
}

//������ں���,�������Ԫ��
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,600,380,L"�Ųʽ����-����");
	//��ʾ����
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ
	XImageList_AddImage(hImageList,XImage_LoadFile( L"image\\2055.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image\\2063.ico"));
	//�����б�Ԫ��
	HELE  hList=XList_Create(10,10,450,300,hWindow);
	XList_EnableCheckBox(hList,TRUE);

	//����ͼƬ�б�
	XList_SetImageList(hList,hImageList);
	//����б�ͷ
	XList_AddColumn(hList,160,L"�б�ͷ��-1",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-2",2);
	XList_AddColumn(hList,160,L"�б�ͷ��-3",2);
	//����б���
	wchar_t item[20]={0};
	wchar_t child[20]={0};
	for(int i=0;i<20;i++)
	{
		wsprintf(item,L"item-(%d)",i);
		//�����
		XList_AddItem(hList,item,0);
		for(int j=0;j<2;j++)
		{
			wsprintf(child,L"item-(%d)-child-(%d)",i,j+1);
			//������������
			XList_SetItemText(hList,i,j+1,child,1);
		}
	}

	itemBindEle_ info;
	info.hEle=XBtn_Create(10,10,100,20,L"aaa",hList);
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XList_SetItemBindEle(hList,1,1,&info);

	XList_SetColumnMinWidth(hList,1,100);

	XBtn_Create(480,10,100,20,L"btn",hWindow);

	XEdit_Create(480,50,100,20,hWindow);

	XEle_SetId(hList,101);
	XEle_SetId(info.hEle,102);

	XEle_RegisterEvent(hList,XE_SETFOCUS,OnEventSetFocus);
	//���г���
	XRunXCGUI();

	return 0;
}*/