/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//������ڵ����� , һ���ڵ������ڵ�
struct PGridItem_
{
	int     id;       //��ID
	wchar_t *pName;   //����,��Ҫ�ͷ� malloc
	wchar_t *pValue;  //ֵ,��Ҫ�ͷ�,������ΪPGRID_STRINGʱʹ�� malloc
	HELE    hEle;     //ֵ��ӦԪ�ؾ��
	int     type;     //���� ,�ַ�������,Ԫ������,�����Ԫ������
	int     posy;     //Y����


	PGridItem_ *pNext; //����Ƕ����ڵ�ʹ��
};


//��������ڵ����� , һ���ڵ�
struct  PGridGroup_
{
	int      id;      //��ID
	wchar_t  *pName;  //����,��Ҫ�ͷ�
	BOOL     bExpand; //չ������
	int      posy;    //Y����

	PGridItem_  *pItemList; //������ڵ��б�
	PGridItem_  *pItemLast; //ָ��pItenĩβ�ڵ�
};


//��ڵ�, һ���ڵ�
struct PGridNode_
{
	int   type;    //�������, 1�� ,2��
	void  *pItem;  //������ָ�� PGridGroup_* �� PGridItem_*
	PGridNode_ *pNext;
};


//��һ���ڵ��������,�ڶ����ڵ�ֻ��������,�������ڵ�;


//��������
struct propertyGrid_
{
	scrollView_ scrollView; //�̳�
	//------------------------
	PGridNode_  *pItemList;	//���б�
	PGridNode_  *pItemLast; //ָ��1��ĩβ�ڵ�

	int   itemHeight;     //���
	int   spacePoint;     //�м�ָ���
	int   indent;         //����
	int   indentBtn;      //չ����ť����ֵ
	int   bottom;         //��Ͳ���λ��
	int   uid;            //����ID,  ��ʾ����1��ʼ,��Ϊ0����һ�����ڵ�
	int   selId;          //��ǰѡ����id, -1û��ѡ����
	BOOL  bAdjust;        //��������

	BOOL  bDown;      //��갴��
	wchar_t *pTemp;   //��ʱ��������,�Ա�ֵ�Ƿ��޸� malloc
};


//API:
XC_API HELE WINAPI XPGrid_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);


//  ����     :  ��ӷ���
//  pName    :  ������
//  bExpand  :  �Ƿ�չ��
XC_API int WINAPI XPGrid_AddGroup(HELE hEle,wchar_t *pName,BOOL bExpand=TRUE); //��ӷ���


//  ����   :  ����ָ���ķ���
//  pName  :  ������
//  type   :  ����
//  group  :  ���������ID,�����-1,�������κ���
//  return :  ������ı�ʾ��
XC_API int WINAPI XPGrid_AddItem(HELE hEle,wchar_t *pName,int type,int groupID=-1); //�����


//  ����    :  ����ָ���ķ���,ֵΪ�ַ���
//  pName   :  ������
//  pValue  :  ��ֵ
//  group   :  ���������ID,�����-1,�������κ���
//  return  :  ������ı�ʾ��
XC_API int WINAPI XPGrid_AddItemString(HELE hEle,wchar_t *pName,wchar_t *pValue,int groupID=-1); //�����


//  ����   :  ��ȡָ����Ԫ�ؾ��,ͨ�����صľ��,�޸�ֵ����
//  id     :  ��ID
XC_API HELE WINAPI XPGrid_GetItemHEle(HELE hEle,int itemID);


//  ����  :  �����ַ���������,������PGRID_STRING,PGRID_EDIT,PGRID_COMBOBOX���͵���
//  id    :  ��ID
XC_API BOOL WINAPI XPGrid_SetItemString(HELE hEle,int itemID,wchar_t *pText);

//  ����  :  �����ַ���������,������PGRID_CHOOSECOLOR���͵���
//  id    :  ��ID
XC_API BOOL WINAPI XPGrid_SetItemColor(HELE hEle,int itemID,COLORREF color);

//  ����  :  ��ȡָ�����ֵ
//  pOut  :  �ַ���������,�洢���ص��ַ���
//  len   :  pOut�ɽ����ַ�����
XC_API void WINAPI XPGrid_GetItemValue(HELE hEle,int itemID,wchar_t *pOut,int len);


XC_API void WINAPI XPGrid_DeleteItem(HELE hEle,int itemID);   //ɾ����

XC_API void WINAPI XPGrid_DeleteGroup(HELE hEle,int groupID);  //ɾ����

XC_API void WINAPI XPGrid_DeleteAll(HELE hEle);  //ɾ������

XC_API void WINAPI XPGrid_SetSpacePoint(HELE hEle,int point);//���÷ָ��߻���X����λ��

XC_API int WINAPI XPGrid_GetSelectItem(HELE hEle); //��ȡ��ǰѡ����

XC_API void WINAPI XPGrid_Adjust(HELE hEle); //��������

//�¼�����
//TODO: ���ý���ʧȥ�����¼�, ͨ����ľ��,ע��ص��¼�,���ֵ���޸�

//˽�з���:
void PGrid_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
int  PGrid_AddID(HELE hEle); //������ID
BOOL PGrid_AddIDTest(PGridNode_ *pNodeList, int id); //���ID�Ƿ�ʹ��

void PGrid_Adjust(HELE hEle); //����һ����
void PGrid_AdjustChildItem(HELE hEle,PGridGroup_ *pGroup,int &posy,int right,int posyPort); //����������

void PGrid_DrawGroup(HELE hEle,PGridGroup_ *pGroup,int left,int right,HDRAW hDraw,HBRUSH hBrush); //������
void PGrid_DrawItem(HELE hEle,PGridItem_ *pItem,int left,int right,HDRAW hDraw); //������
void PGrid_HideEle(HELE hEle); //����ָ��Ԫ��
void PGrid_ShowEle(HELE hEle,PGridItem_ *pItem);//��ʾָ����

//�������ֵ�ı�
void PGrid_CheckValueChange(HELE hEle,PGridItem_ *pItem);

// ����  : ��ȡָ����ڵ�
PGridGroup_ *PGrid_GetGroup(HELE hEle,int groupID);

PGridItem_  *PGrid_GetItem(HELE hEle,int itemID);  //��ȡָ����ڵ�

BOOL PGrid_LButtonDownItem(HELE hEle,PGridItem_ *pItem,POINT *pPt);

//�ص�����:
BOOL CALLBACK PGrid_OnEleDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK PGrid_OnDrawScrollView(HELE hEle,HDRAW hDraw);


BOOL CALLBACK PGrid_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK PGrid_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK PGrid_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);

BOOL CALLBACK PGrid_OnEventKillFocus(HELE hEle,HELE hEventEle); //ʧȥ����
BOOL CALLBACK PGrid_OnEventSize(HELE hEle,HELE hEventEle);

void CALLBACK PGrid_OnDestroy(HELE hEle);  //Ԫ������ - �ͷ���Դ
