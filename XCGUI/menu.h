/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct menu_
{
	int        id;          //id
	int        parentId;    //����ID  
	int        len;         //�ı�����
	int        state;	    //״̬
	RECT       rcItem;      //����
	HIMAGE     hImage;      //ͼƬ
	HSTRING    hString;     //�ı�
};

//�����˵����ݶ���
struct popupMenu_
{
	object_ object;

	HXCGUI   hMTreeData;  //������ multiTree_;

	int      height;       //���
	int      leftWidth;    //��߻�ɫ������
	int      leftText;     //�˵����ı�����
	//Image    *pBkImage;    //�˵�����ͼƬ
	HIMAGE   hBkImage;     //�˵�����ͼƬ
	HFONT    hFont;        //����
	BOOL     bAutoDestroy; //�Ƿ��Զ�����,�ڲ˵��˳�ʱ
	HELE     hParentEle;   //��Ԫ��
	HWINDOW  hMenuWindow;  //��ǰ�����˵����ھ��
	HELE     hMenuBar;     //�˵������,��Ϊ�˵�����������

	//�Ի�
	//--------------------------------------
	pFunMenu_DrawItem  pDrawItem;
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif

	//���Ƶ����˵����ڱ���
	pFunMenu_DrawBG  pDrawBG;
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info_drawBG;//��Ϣ�¼��ص�������Ϣָ��
#endif

	//�˵������UI
	pFunMenu_UpdateUI   pUpdateUI;
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info_updateUI;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

//�˵���IDӦ�ô���0
//ɾ���ָ���,���ݷָ����ID

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
XC_API void WINAPI XMenu_SetUserDrawItemEx(HMENUX hMenu,pFunClassEventMsg pCallBackFun,void *pClass_Fun_Info); //�����û��Ի�˵���
XC_API void WINAPI XMenu_SetUserDrawBGEx(HMENUX hMenu,pFunClassEventMsg pCallBackFun,void *pClass_Fun_Info); //�����û��Ի�˱���
XC_API void WINAPI XMenu_SetUserUpdateUIEx(HMENUX hMenu,pFunClassEventMsg pCallBackFun,void *pClass_Fun_Info);
#endif

//API:
XC_API HMENUX WINAPI XMenu_Create();
XC_API void WINAPI XMenu_AddItem(HMENUX hMenu,int id,wchar_t *pText,int parentId=XMENU_ROOT,int uFlags=0); //��Ӳ˵���
XC_API void WINAPI XMenu_AddItemImage(HMENUX hMenu,int id,wchar_t *pText,int parentId,int uFlags,HIMAGE hImage);

//����˵��ָ����ǰ��
XC_API void WINAPI XMenu_InsertItem(HMENUX hMenu,int id,wchar_t *pText,int uFlags,int insertID);
XC_API void WINAPI XMenu_InsertItemImage(HMENUX hMenu,int id,wchar_t *pText,int uFlags,int insertID,HIMAGE hImage);

//ɾ����
XC_API void WINAPI XMenu_DeleteItem(HMENUX hMenu,int id);


XC_API void WINAPI XMenu_SetAutoDestroy(HMENUX hMenu,BOOL bAuto); //�Ƿ��Զ����ٶ���,Ĭ�ϵ����˵��رպ��Զ�����
XC_API void WINAPI XMenu_SetItemHeight(HMENUX hMenu,int height); //���ò˵���߶�
XC_API BOOL WINAPI XMenu_SetBGImage(HMENUX hMenu,HIMAGE hImage);//���ò˵�����ͼƬ
XC_API BOOL WINAPI XMenu_SetItemImage(HMENUX hMenu,int id,HIMAGE hImage); //������ͼ��
XC_API BOOL WINAPI XMenu_SetItemText(HMENUX hMenu,int id,wchar_t *pText); //�������ı�
XC_API void WINAPI XMenu_SetItemFlags(HMENUX hMenu,int id,int uFlags);   //����������
XC_API void WINAPI XMenu_SetItemCheck(HMENUX hMenu,int id,BOOL bCheck);

XC_API BOOL WINAPI XMenu_IsItemCheck(HMENUX hMenu,int id);

XC_API int  WINAPI XMenu_GetItemFlags(HMENUX hMenu,int id);   //��ȡ������
XC_API int  WINAPI XMenu_GetItemHeight(HMENUX hMenu);  //��ȡ�˵���߶�
XC_API int  WINAPI XMenu_GetItemCount(HMENUX hMenu); //��ȡ�˵�������,�����Ӳ˵���
XC_API wchar_t* WINAPI XMenu_GetItemText(HMENUX hMenu,int id); //��ȡ�˵����ı�

XC_API int  WINAPI XMenu_GetItemLeftWidth(HMENUX hMenu); //��ȡ�����
XC_API int  WINAPI XMenu_GetItemLeftText(HMENUX hMenu);  //��ȡ�˵����ı�����


//������Ϣ���ڻ�����¼�Ԫ��
//hParentEle:�����¼�Ԫ�ؾ��,���ΪNULL��������Ϣ��������
//���������Ϊ�������򴰿ڻ�����,ͨ�����ý�����Ϣ����
XC_API BOOL WINAPI XMenu_Popup(HMENUX hMenu,HWND hParentWnd,int x,int y,HELE hParentEle=NULL,int uFlags=NULL); //�����˵�
XC_API void WINAPI XMenu_Destroy(HMENUX hMenu);
XC_API void WINAPI XMenu_CloseMenu(HMENUX hMenu);

//���
XC_API void WINAPI XMenu_SetUserDrawItem(HMENUX hMenu,pFunMenu_DrawItem pFunDrawItem); //�����û��Ի���
XC_API void WINAPI XMenu_SetUserDrawBG(HMENUX hMenu,pFunMenu_DrawBG pFunDrawBG); //�����û��Ի�˵�����
XC_API void WINAPI XMenu_SetUserUpdateUI(HMENUX hMenu,pFunMenu_UpdateUI pUpdateUI);

void Menu_AddItemX(HMENUX hMenu,int id,wchar_t *pText, int parentId,int uFlags,HIMAGE hImage); //���Ӳ˵���

//��ȡ��ǰ�����Ĳ˵������ھ��
HWINDOW Menu_GetMenuHWindow(HMENUX hMenu);

//���㴰�ڵ����˵����ڴ�С
BOOL Menu_computeWndSize(HMENUX hMenu,int parentID,SIZE &size);
void Menu_AdjustPosition(int &x,int &y,int width,int height,int uFlags);


/////////////////////////////////////////////////////
//�����˵�����
struct popupMenuChildWindow_;
struct popupMenuWindow_
{
	window_ window; //�̳�
	//---------------------------
	popupMenu_       *pMenuData;   //�˵����ݶ��� HMENUX
	HXCGUI            hMTreeData;  //������ multiTree_;

	int               selItemID;       //��ǰѡ�����ID, -1Ϊ��
	int               enterItemID;     //������ID   , -1Ϊ�� ,�Ա�ȷ�������Ӳ˵�ʱѡ������ȷ
	DWORD             enterTiemr;      //��������ʱ��

	popupMenuChildWindow_ *pChildWnd;  //�����Ӵ���ָ��
};



//�˵�������:
HWINDOW MenuWnd_CreateWindow(int x,int y,int width,int height,HWND hWndParent);


//˽�з���:
BOOL MenuWnd_Init(HWINDOW hWindow,int x,int y,int cx,int cy,wchar_t *pTitle,HWND hWndParent,int exType);
void MenuWnd_UpdateUI(HWINDOW hWindow,int parentID);
BOOL MenuWnd_computeSize(HWINDOW hWindow,int &width, int &height);  //���㵯���˵����ڴ�С
void MenuWnd_AdjustPosition(HWINDOW hWindow,int &x,int &y,int width,int height,int uFlags); //���������ʾλ�ã��Ա���Ӧ��ʾ��Χ
BOOL MenuWnd_CheckMouseMove(popupMenuWindow_ *pObj,POINT &pt);
void MenuWnd_DrawItem(HWINDOW hWindow,HDRAW hDraw, menu_drawItem_ *pItem);
void MenuWnd_DrawBackground(window_ *pWindow,HDRAW hDraw,HIMAGE hImage);//���Ʋ˵�����

void MenuWnd_OnDestroyWindow(HWND hWnd,popupMenu_ *pMenu);
void MenuWnd_OnExitMenu(HELE hParentEle,HWND hParentWnd);
BOOL MenuWnd_OnDestroyMenu(popupMenu_ *pMenu);

//�ص�����
BOOL CALLBACK MenuWnd_OnDrawWindow(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK MenuWnd_OnLButtonDown(HWINDOW hWindow,POINT *pPt);
BOOL CALLBACK MenuWnd_OnLButtonUp(HWINDOW hWindow,POINT *pPt);
BOOL CALLBACK MenuWnd_OnMouseMove(HWINDOW hWindow,UINT flags,POINT *pPt);
BOOL CALLBACK MenuWnd_OnNCMouseMove(HWINDOW hWindow,UINT flags,POINT *pPt);
BOOL CALLBACK MenuWnd_OnRButtonDown(HWINDOW hWindow,POINT *pPt);
BOOL CALLBACK MenuWnd_OnCaptureChanged(HWINDOW hWindow,HWND hWnd);
BOOL CALLBACK MenuWnd_OnWndSysKeyDown(HWINDOW hWindow,WPARAM wParam,LPARAM lParam);

VOID CALLBACK MenuWnd_TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);


/////////////////////////////////////////////////////////////////
struct popupMenuChildWindow_
{
	window_ window; //�̳�
	//---------------------------
	popupMenuWindow_      *pMainWnd;
	popupMenuChildWindow_ *pChildWnd;   //�����Ӵ���ָ��
	popupMenuChildWindow_ *pPreviouWnd; //��һ������

	DWORD             enterTiemr;       //��������ʱ�� , �Ա�ȷ�������Ӳ˵�ʱѡ������ȷ
	int               parentItemId;     //�Ӵ��ڶ�Ӧ�ĸ���˵�ID
	int               enterItemID;      //������ID ,  -1Ϊ��
	int               selItemID;        //��ǰѡ�����ID, , -1Ϊ��
};
//API:
popupMenuChildWindow_* MenuChildWnd_Popup(popupMenuWindow_  *pMainWnd,window_ *pParentWnd,int parentItemId, int x,int y);

//˽�з���:
BOOL MenuChildWnd_Init(HWINDOW hWindow,int x,int y,int cx,int cy,HWND hWndParent,int exType);
BOOL MenuChildWnd_computeSize(popupMenuChildWindow_ *pObj,int &width, int &height);  //���㵯���˵����ڴ�С
void MenuChildWnd_AdjustPosition(popupMenuChildWindow_ *pObj,int &x,int &y,int width,int height); //���������ʾλ�ã��Ա���Ӧ��ʾ��Χ

void MenuChildWnd_OnLButtonUp(popupMenuChildWindow_ *pObj,POINT *pPt);
void MenuChildWnd_OnMouseMove(popupMenuChildWindow_ *pObj,POINT *pPt);

//�ص�����:
BOOL CALLBACK MenuChildWnd_OnDrawWindow(HWINDOW hWindow,HDRAW hDraw);

VOID CALLBACK MenuChildWnd_TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);

