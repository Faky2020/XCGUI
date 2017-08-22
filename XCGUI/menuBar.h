/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct menuBarItem_
{
	int        id;          //id
	HSTRING    hText;       //����
	int        parentId;    //����ID
	int        uFlags;
	HSTRING    hImageName;  //ͼƬ�ļ���
	int        resID;       //��ԴID
	HSTRING    hResType;    //��Դ����

	HARRAY     hArrayItem;   //�˵����б� menuBarItem_* //������
};

//�˵�����ť
struct menuBarButon_
{
	button_ button; //�̳�
	//-------------------------

	HMENUX   hMenu;  //�����˵�
};

//Ĭ�ϸ��ڵ�IDΪXMENU_ROOT

//API: �ڲ���
HELE MenuBarBtn_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent=NULL);
void MenuBarBtn_AddMenuItem(HELE hEle,int id,wchar_t *pText,int parentId=XMENU_ROOT,int uFlags=0);
void MenuBarBtn_AddMenuItemImage(HELE hEle,int id,wchar_t *pText,int parentId,int uFlags,HIMAGE hImage); //���Ӳ˵���

//����˵���
void MenuBarBtn_InsertMenuItem(HELE hEle,int id,wchar_t *pText,int uFlags,int insertID);
void MenuBarBtn_InsertMenuItemImage(HELE hEle,int id,wchar_t *pText,int uFlags,int insertID,HIMAGE hImage); //���Ӳ˵���

//ɾ���˵���
void MenuBarBtn_DeleteMenuItem(HELE hEle,int id);

//˽�з���:
void MenuBarBtn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);

//ע��˵����Ի�
//ע��˵������Ի�

//���з���:
void MenuBarBtn_PopupMenu(HELE hEle);
void MenuBarBtn_CloseMenu(HELE hEle);

//�ص�����
void CALLBACK MenuBarBtn_OnDestroy(HELE hEle);  //����
BOOL CALLBACK MenuBarBtn_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK MenuBarBtn_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK MenuBarBtn_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK MenuBarBtn_OnEventMouseSay(HELE hEle,HELE hEventEle); //���ͣ��
BOOL CALLBACK MenuBarBtn_OnEventMouseLeave(HELE hEle,HELE hEventEle); //����뿪


///////////////////////////////////////////////////////////////////////////

//�˵���
struct menuBar_
{
	ele_  ele; //�̳�
	//----------------

	menuBarButon_   *pBtnTop;  //���ͣ�����ĸ���ť�� //��ǰ�����˵���ť
	BOOL   bDown;          //�˵������� TRUE �Զ����� 
	int    buttonHeight;   //�˵���ť�߶�

	HIMAGE  hImage; 
	BOOL    bAdjust;  //��������
};


//API:
XC_API HELE WINAPI XMenuBar_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);  //������ť
XC_API int WINAPI XMenuBar_AddButton(HELE hEle,wchar_t *pText);     //���ӵ����˵���ť

XC_API int WINAPI XMenuBar_InsertButton(HELE hEle,wchar_t *pText,int index);     //���뵯���˵���ť

XC_API void WINAPI XMenuBar_AddMenuItem(HELE hEle,int index,int id,wchar_t *pText,int parentId=XMENU_ROOT,int uFlags=0);
XC_API void WINAPI XMenuBar_AddMenuItemImage(HELE hEle,int index,int id,wchar_t *pText,int parentId,int uFlags,HIMAGE hImage); //���Ӳ˵���


XC_API void WINAPI XMenuBar_InsertMenuItem(HELE hEle,int index,int id,wchar_t *pText,int uFlags,int insertID); //����˵���,���뵽IDΪinsertID�˵���ǰ��λ��
XC_API void WINAPI XMenuBar_InsertMenuItemImage(HELE hEle,int index,int id,wchar_t *pText,int uFlags,int insertID,HIMAGE hImage); //���Ӳ˵���

//ɾ���ڵ�
XC_API void WINAPI XMenuBar_DeleteMenuItem(HELE hEle,int index,int id); //ɾ���˵���

XC_API void WINAPI XMenuBar_SetButtonHeight(HELE hEle,int height); //���õ����˵���ť�߶�

XC_API HELE WINAPI XMenuBar_GetButton(HELE hEle,int index);  //��ȡ�����˵���ť���
XC_API HMENUX WINAPI XMenuBar_GetMenu(HELE hEle,int index); //��ȡ�˵����

XC_API void WINAPI XMenuBar_DeleteButton(HELE hEle,int index); //ɾ���˵��������,ͬʱ�ð�ť�µĵ����˵�Ҳ������
//�Ƴ������˵���ť

//��ͼ:
XC_API void WINAPI XMenuBar_SetImage(HELE hEle,HIMAGE hImage=NULL);


//˽�з���:
void MenuBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);

void MenuBar_Adjust(HELE hEle); //��������

//�����˵�����ƶ�,hEle:�˵������
void MenuBar_OnMenuMouseMove(HELE hEle,POINT *pPt);

//�ص�����:
void CALLBACK MenuBar_OnDestroy(HELE hEle);  //����
BOOL CALLBACK MenuBar_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK MenuBar_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);


//����˵���
//�޸Ĳ˵���