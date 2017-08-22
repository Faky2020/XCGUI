/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



//////////////////////////////////////////////////
//�б���//////////////////////////////////////////
/*
HELE hTree; //����Դ���
HELE hEdit; //�༭����Դ���
//���ذ�ť-��ť����¼�
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	//hEle:��ť��Դ���
	//�ж����Ƿ���ʾ��ť
	if(XTree_IsButton(hTree))
		//�����ذ�ť
		XTree_EnableButton(hTree,FALSE);
	else
		//����ʾ��ť
		XTree_EnableButton(hTree,TRUE);
	//�ػ��������ͼ
	XEle_RedrawEle(hTree);
	return TRUE;
}

//���������߰�ť-����¼�
BOOL CALLBACK MyEventBtnClick2(HELE hEle,HELE hEventEle)
{
	//hEle:��ť��Դ���
	//�ж��Ƿ���ʾ������
	if(XTree_IsLine(hTree))
		//����������
		XTree_EnableLine(hTree,FALSE);
	else
		//��ʾ������
		XTree_EnableLine(hTree,TRUE);
	//�ػ��������ͼ
	XEle_RedrawEle(hTree);
	return TRUE;
}

//ȡ�������߰�ť-����¼�
BOOL CALLBACK MyEventBtnClick3(HELE hEle,HELE hEventEle)
{
	//hEle:��ť��Դ���
	//�ж����Ƿ���ʾ����������
	if(XTree_IsRootLine(hTree))
		//���ظ���������
		XTree_EnableRootLine(hTree,FALSE);
	else
		//��ʾ����������
		XTree_EnableRootLine(hTree,TRUE);
	//�ػ��������ͼ
	XEle_RedrawEle(hTree);
	return TRUE;
}

//���б�ѡ���¼�
BOOL CALLBACK MyEventTreeSelect(HELE hEle,HELE hEventEle,int id)
{
	//hEle:����Դ���
	//id:ѡ����id
	//ȷ����ѡ�����
	if(id>0)
	{
		wchar_t buf[50]={0};
		//��ȡѡ��������
		wchar_t *pText=XTree_GetItemText(hEle,id);
		wsprintf(buf,L"ѡ����:\n%s",pText);
		//���ñ༭������
		XEdit_SetText(hEdit,buf);
	}else
	{
		XEdit_SetText(hEdit,L"û��ѡ����");
	}

	return TRUE;
}

//����չ���������¼�
BOOL CALLBACK MyEventTreeExpand(HELE hEle,HELE hEventEle,int id,BOOL bExpand)
{
	//hEle:����Դ���
	//id:ѡ����id
	wchar_t buf[50]={0};
	//��ȡѡ��������
	wchar_t *pText=XTree_GetItemText(hEle,id);
	if(bExpand)
		wsprintf(buf,L"չ����:\n%s",pText);
	else
		wsprintf(buf,L"������:\n%s",pText);
	//���ñ༭������
	XEdit_SetText(hEdit,buf);

	return TRUE;
}

//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(500,200,400,260,L"���Դ���");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//����ͼ���б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ��Դ
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2063.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2057.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2062.ico"));
	//������
	hTree=XTree_Create(10,10,200,200,hWindow);
	//XTree_SetSpacingLeft(hTree,10);   //��������
	//XTree_SetSpacingTop(hTree,10);    //�����ϼ��
	//������ͼƬ�б�
	XTree_SetImageList(hTree,hImageList);
	//��������
	//XTree_InsertItem(����Դ���,����,����id,ͼƬ,ͼƬ,��ʶ��id,�Ƿ�չ��)
	int root1=XTree_InsertItem(hTree,L"���ڵ���1",0,0,1);
	int root2=XTree_InsertItem(hTree,L"���ڵ���2",0,0,1);
	int root3=XTree_InsertItem(hTree,L"���ڵ���3",0,0,1);
	int root4=XTree_InsertItem(hTree,L"���ڵ���4",0,0,1);
	int root5=XTree_InsertItem(hTree,L"���ڵ���5",0,0,1);
	XTree_InsertItem(hTree,L"���ڵ���6",0,0,1);
	int child1=XTree_InsertItem(hTree,L"Ҷ����1",root1,2,3);
	XTree_InsertItem(hTree,L"Ҷ����2",root1,2,3);
	XTree_InsertItem(hTree,L"Ҷ����3",root1,2,3);
	XTree_InsertItem(hTree,L"Ҷ����4",child1,2,3);
	XTree_InsertItem(hTree,L"Ҷ����5",child1,2,3);
	XTree_InsertItem(hTree,L"Ҷ����6",root2,2,3);
	XTree_InsertItem(hTree,L"Ҷ����7",root2,2,3);
	XTree_InsertItem(hTree,L"Ҷ����8",root2,2,3);
	//������ť
	HELE hButton=XBtn_Create(220,10,80,20,L"���ذ�ť",hWindow);
	HELE hButton2=XBtn_Create(220,40,80,20,L"����������",hWindow);
	HELE hButton3=XBtn_Create(220,70,80,20,L"ȡ��������",hWindow);
	//�����༭��
	hEdit=XEdit_Create(220,100,150,110,hWindow);
	XEdit_EnableMultiLine(hEdit,TRUE);
	//ע�ᰴť����¼�
	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,MyEventBtnClick2);
	XEle_RegisterEvent(hButton3,XE_BNCLICK,MyEventBtnClick3);
	//ע������ѡ���¼�
	XEle_RegisterEvent(hTree,XE_TREE_SELECT,MyEventTreeSelect);
	//ע������չ�������¼�
	XEle_RegisterEvent(hTree,XE_TREE_EXPAND,MyEventTreeExpand);
	//���г���
	XRunXCGUI();

	return 0;
}
*/


/*
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//�Ի�����
void CALLBACK MyTree_DrawItem(HELE hEle,tree_drewItem_ *pDrawItem)
{
	//����ѡ�����
	if(STATE_SELECT==pDrawItem->state)
	{
		XDraw_FillSolidRect(pDrawItem->hdc,&pDrawItem->rcText,RGB(197,255,197));
	}

	//����չ����ť
	if(pDrawItem->bExpand)
		XDraw_FillSolidRect(pDrawItem->hdc,&pDrawItem->rcButton,RGB(255,0,0));
	else
		XDraw_FillSolidRect(pDrawItem->hdc,&pDrawItem->rcButton,RGB(0,255,0));

	//����ͼ��
	HXCGUI hImageList=XTree_GetImageList(hEle);
	if(hImageList)
	{
		XImageList_DrawImage(hImageList,pDrawItem->hdc,pDrawItem->imageId,pDrawItem->rcImage.left,pDrawItem->rcImage.top);
	}

	//�����ı�
	DrawText(pDrawItem->hdc,pDrawItem->pText,wcslen(pDrawItem->pText),&pDrawItem->rcText,DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}
//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(500,200,400,260,L"�Ųʽ����-����");

	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ��Դ
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2063.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico"));

	//������
	HELE hTree=XTree_Create(10,10,200,200,hWindow);

	//������ͼƬ�б�
	XTree_SetImageList(hTree,hImageList);
	//��������
	//XTree_InsertItem(�����,����,����id,ͼƬ,ͼƬ,��ʶ��id,�Ƿ�չ��)
	int root1=XTree_InsertItem(hTree,L"���ڵ���1",0,0,1);
	int root2=XTree_InsertItem(hTree,L"���ڵ���2",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root3=XTree_InsertItem(hTree,L"���ڵ���3",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root4=XTree_InsertItem(hTree,L"���ڵ���4",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root5=XTree_InsertItem(hTree,L"���ڵ���5",0,0,1,XTREE_INSERT_LAST,FALSE);

	XTree_InsertItem(hTree,L"Ҷ����1",root1,0,1);
	XTree_InsertItem(hTree,L"Ҷ����2",root1,0,1);
	XTree_InsertItem(hTree,L"Ҷ����3",root2,0,1);
	XTree_InsertItem(hTree,L"Ҷ����4",root3,0,1);
	XTree_InsertItem(hTree,L"Ҷ����5",root4,0,1);

	//�������Ի���
	XTree_SetUserDrawItem(hTree,MyTree_DrawItem);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();

	return 0;
}
*/


/*

//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,450,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//������
	HELE hScrollView=XSView_Create(10,10,300,350,hWindow);
	XSView_SetSize(hScrollView,500,800);

	HELE hView=XSView_GetView(hScrollView);
	XEle_SetBkColor(hView,RGB(255,0,0));

	HELE hTree=XTree_Create(10,10,200,300,hView);
	HELE hTreeView=XSView_GetView(hTree);
	XEle_SetBkColor(hTreeView,RGB(0,255,0));

	XEle_SetId(hScrollView,101);
	XEle_SetId(hView,102);
	XEle_SetId(hTree,103);
	XEle_SetId(hTreeView,104);


//////////////////////////////////////////////
	HELE hTree2=XTree_Create(10,10,200,300,hTreeView);
	HELE hTreeView2=XSView_GetView(hTree2);
	XEle_SetBkColor(hTreeView2,RGB(0,0,255));

	XRunXCGUI();

	return 0;
}
*/


/*

class CMyTree : public CXEventMsg
{
public:
	HELE m_hTree;
	void Init(HELE hTree)
	{
		m_hTree=hTree;
		XCGUI_Tree_SetUserDrawItem(m_hTree,&CMyTree::OnTree_DrawItem);
	}
	void OnTree_DrawItem(HELE hEle,tree_drewItem_ *pDrawItem)
	{

	}
};

BOOL CALLBACK OnEleMouseDBClick(HELE hEle,POINT *pPt)
{
	return FALSE;
}

//������ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(469);

	//��ʼ�������
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(500,200,400,260,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//����ͼƬ�б�
	HXCGUI hImageList=XImageList_Create(16,16);
	XImageList_EnableFixedSize(hImageList,TRUE);
	//���ͼƬ��Դ
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2063.ico"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"image/2050.ico"));

	//������
	HELE hTree=XTree_Create(10,10,200,200,hWindow);

	//������ͼƬ�б�
	XTree_SetImageList(hTree,hImageList);
	//��������
	//XTree_InsertItem(�����,����,����id,ͼƬ,ͼƬ,��ʶ��id,�Ƿ�չ��)
	int root1=XTree_InsertItem(hTree,L"���ڵ���1",0,0,1);
	int root2=XTree_InsertItem(hTree,L"���ڵ���2",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root3=XTree_InsertItem(hTree,L"���ڵ���3",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root4=XTree_InsertItem(hTree,L"���ڵ���4",0,0,1,XTREE_INSERT_LAST,FALSE);
	int root5=XTree_InsertItem(hTree,L"���ڵ���5",0,0,1,XTREE_INSERT_LAST,FALSE);

	int id2=	XTree_InsertItem(hTree,L"Ҷ����1",root1,0,1);
	int id=	XTree_InsertItem(hTree,L"Ҷ����2",root1,0,1);
	XTree_InsertItem(hTree,L"Ҷ����3",root2,0,1);
	XTree_InsertItem(hTree,L"Ҷ����4",root3,0,1);
	XTree_InsertItem(hTree,L"Ҷ����5",root4,0,1);

	//	XTree_SetItemCheck(hTree,root2,TRUE);

	//XTree_EnableCheckBox(hTree,TRUE);
	XTree_EnableButton(hTree,FALSE);
	XTree_EnableLine(hTree,FALSE);
	XTree_SetSpacingLeft(hTree,10);

	XEle_RegisterMessage(hTree,XM_MOUSEDBCLICK,OnEleMouseDBClick);

	//	XTree_SetItemText(hTree,root1,L"1111111111111111111111122222");


	itemBindEle_ info;
	info.hEle=XBtn_Create(10,10,100,20,L"aaa",hTree);
	info.left=0;
	info.top=0;
	info.width=60;
	info.height=20;
	XTree_SetItemBindEle(hTree,id,&info);

	CMyTree MyTree;
	MyTree.Init(hTree);

	XRunXCGUI();

	return 0;
}
*/