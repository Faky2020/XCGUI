/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup propertyGrid ��������Ԫ��(PropertyGrid)
/// @ingroup groupElements
/// @{

/// @brief ������������Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XPGrid_Create(int x, int y, int cx, int cy,HXCGUI hParent)
{
	propertyGrid_ *pObj=(propertyGrid_*)malloc(sizeof(propertyGrid_));
	memset(pObj,0,sizeof(propertyGrid_));
	PGrid_Init((HELE)pObj,x,y,cx,cy,XC_PROPERTYGRID,hParent);
	return (HELE)pObj;
}

void PGrid_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	SView_Init(hEle,x,y,cx,cy,eleType,hParent);

	AddTypeDebug(hEle,XC_PROPERTYGRID);

	((propertyGrid_*)hEle)->itemHeight=22;
	((propertyGrid_*)hEle)->spacePoint=cx/2;
	((propertyGrid_*)hEle)->indent=12;
	((propertyGrid_*)hEle)->indentBtn=2;
	((propertyGrid_*)hEle)->selId=-1;
	((propertyGrid_*)hEle)->bAdjust=FALSE;
	((propertyGrid_*)hEle)->uid=0; //��ʾ����1��ʼ,��Ϊ0����һ�����ڵ�
	((propertyGrid_*)hEle)->pItemList=NULL;
	((propertyGrid_*)hEle)->pItemLast=NULL;
	((ele_*)hEle)->bEnableFocus=TRUE;

	XEle_RegisterEvent(hEle,XE_DESTROY,PGrid_OnDestroy);
	XSView_SetDrawScrollView(hEle,PGrid_OnDrawScrollView);
	XEle_RegisterMessage(hEle,XM_LBUTTONDOWN,PGrid_OnLButtonDown);
	XEle_RegisterMessage(hEle,XM_LBUTTONUP,PGrid_OnLButtonUp);
	XEle_RegisterMessage(hEle,XM_MOUSEMOVE,PGrid_OnMouseMove);
	XEle_RegisterMessage(hEle,XM_PAINT,PGrid_OnEleDraw);

	XEle_RegisterEvent(hEle,XE_KILLFOCUS,PGrid_OnEventKillFocus);
	XEle_RegisterEvent(hEle,XE_SIZE,PGrid_OnEventSize);
}

int PGrid_AddID(HELE hEle)
{
	propertyGrid_ *pGrid=(propertyGrid_*)hEle;

	int id=pGrid->uid+1;
	if(id>2100000000) //2100000000
		id=1;

	while(pGrid->uid!=id)
	{
		if(FALSE==PGrid_AddIDTest(pGrid->pItemList,id))
		{
			pGrid->uid=id;
			return id;
		}
		id++;
		if(id>2100000000)
			id=1;
	}

	MessageBox(NULL,L"Tree_ ��Ԫ�ط���ID���ִ���!",L"�Ųʽ������ʾ",0);
	exit(0);
	return -1;
}

BOOL PGrid_AddIDTest(PGridNode_ *pNodeList, int id) //���ID�Ƿ�ʹ��
{
	PGridNode_ *pNode=pNodeList;
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			PGridItem_ *pItem=((PGridGroup_*)pNode->pItem)->pItemList;
			while(pItem)
			{
				if(id==pItem->id)
					return TRUE;
				pItem=pItem->pNext;
			}
		}else if(2==pNode->type) //��
		{
			if(id==((PGridItem_*)pNode->pItem)->id)
				return TRUE;
		}
		pNode=pNode->pNext;
	}
	return FALSE;
}

void PGrid_Adjust(HELE hEle)
{
	propertyGrid_  *pObj=(propertyGrid_*)hEle;
	pObj->bAdjust=FALSE;

	int left=XSView_GetSpacingLeft(hEle)-XSView_GetHViewPos(hEle);
	PGridNode_  *pNode=pObj->pItemList;
	int posy=0;

	//������ͼ��Ҫ�߶�
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			posy+=pObj->itemHeight;
			//����
			if(((PGridGroup_*)pNode->pItem)->bExpand)
			{
				PGridItem_ *pItem=((PGridGroup_*)pNode->pItem)->pItemList;
				while(pItem)
				{
					posy+=pObj->itemHeight;
					pItem=pItem->pNext;
				}
			}
		}else //��
		{
			PGridItem_ *pItem=(PGridItem_*)pNode->pItem;
			posy+=pObj->itemHeight;
		}
		pNode=pNode->pNext;
	}
	pObj->bottom=posy;

	XSView_SetSize(hEle,1,posy);

	int viewWidth=XSView_GetViewWidth(hEle)-XSView_GetHViewPos(hEle);

	int right=left+viewWidth;
	pNode=pObj->pItemList;

	int posyPort=XSView_GetVViewPos(hEle);

	posy=0;
	//��������
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			((PGridGroup_*)pNode->pItem)->posy=posy;
			posy+=pObj->itemHeight;
			//����
			if(((PGridGroup_*)pNode->pItem)->bExpand)
				PGrid_AdjustChildItem(hEle,(PGridGroup_*)pNode->pItem,posy,right,posyPort);
		}else //��
		{
			PGridItem_ *pItem=(PGridItem_*)pNode->pItem;
			pItem->posy=posy;
			if(pItem->hEle)
			{
				RECT rc={pObj->spacePoint,posy,right,posy+pObj->itemHeight-1};
				XEle_SetRect(pItem->hEle,&rc);
			}
			posy+=pObj->itemHeight;
		}
		pNode=pNode->pNext;
	}
	pObj->bottom=posy;
}

void PGrid_AdjustChildItem(HELE hEle,PGridGroup_ *pGroup,int &posy,int right,int posyPort)
{
	propertyGrid_  *pObj=(propertyGrid_*)hEle;
	PGridItem_ *pItem=pGroup->pItemList;

	while(pItem)
	{
		pItem->posy=posy;
		if(pItem->hEle)
		{
			RECT rc={pObj->spacePoint,posy,right,posy+pObj->itemHeight-1};
			XEle_SetRect(pItem->hEle,&rc);
		}
		posy+=pObj->itemHeight;
		pItem=pItem->pNext;
	}
}

/// @brief ��ӷ���.
/// @param hEle  Ԫ�ؾ��.
/// @param pName   ����.
/// @param bExpand TRUEչ��,FALSE��չ��.
/// @return ��ID��ʾ��,ʧ�ܷ���-1.
int WINAPI XPGrid_AddGroup(HELE hEle,wchar_t *pName,BOOL bExpand) //��ӷ���
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_  *pObj=(propertyGrid_*)hEle;

	//�½��ڵ�
	PGridNode_  *pNode=(PGridNode_*)malloc(sizeof(PGridNode_));
	pNode->type=1;
	pNode->pNext=NULL;

	//�ڵ�����
	PGridGroup_  *pData=(PGridGroup_*)malloc(sizeof(PGridGroup_));
	pData->id=PGrid_AddID(hEle);
	pData->bExpand=bExpand;
	pData->pItemList=NULL;
	pData->pItemLast=NULL;
	if(pName)
	{
		int size=wcslen(pName)+1;
		pData->pName=(wchar_t*)malloc(size*sizeof(wchar_t));
		wcscpy_s(pData->pName,size,pName);
	}else
		pData->pName=NULL;

	pNode->pItem=pData;

	//�����б�,һ���ڵ�
	if(NULL==pObj->pItemList)
	{
		pObj->pItemList=pNode;
		pObj->pItemLast=pNode;
	}else
	{
		pObj->pItemLast->pNext=pNode;
		pObj->pItemLast=pNode;
	}
	pObj->bAdjust=TRUE;
	return pData->id;
}

/// @brief ��������Ԫ��,�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pName   ������.
/// @param type    ������.
/// @param groupID  ������ID,���-1û�з���
/// @return ����ӵ���ID��ʾ��,���ʧ�ܷ���-1.
int WINAPI XPGrid_AddItem(HELE hEle,wchar_t *pName,int type,int groupID) //�����
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_  *pObj=(propertyGrid_*)hEle;

	PGridItem_ *pItem=(PGridItem_*)malloc(sizeof(PGridItem_));
	pItem->id=PGrid_AddID(hEle);
	pItem->posy=NULL;
	pItem->hEle=NULL;
	pItem->type=type;
	pItem->pName=NULL;
	pItem->pValue=NULL;
	pItem->pNext=NULL;
	if(pName)
	{
		int size=wcslen(pName)+1;
		pItem->pName=(wchar_t*)malloc(size*sizeof(wchar_t));
		wcscpy_s(pItem->pName,size,pName);
	}

	switch(type)
	{
	case PGRID_EDIT:
		{
			HELE hEdit=XEdit_Create(0,0,20,20,hEle);
			XEle_ShowEle(hEdit,FALSE);
			pItem->hEle=hEdit;
		}break;
	case PGRID_COMBOBOX:
		{
			HELE hCom=XComboBox_Create(0,0,20,20,hEle);
			XEle_ShowEle(hCom,FALSE);
			pItem->hEle=hCom;
		}break;
	case PGRID_CHOOSECOLOR:
		{
			HELE hColor= XCHColor_Create(0,0,20,20,hEle);
			XEle_ShowEle(hColor,FALSE);
			pItem->hEle=hColor;
		}break;
	case PGRID_EDIT_FILE:
		{
			HELE hEditFile= XEditFile_Create(0,0,20,20,hEle);
			XEle_ShowEle(hEditFile,FALSE);
			pItem->hEle=hEditFile;
		}
#ifdef _DEBUG
	case PGRID_STRING: break;
	default:
		{
			XMessageBox(hEle,L"XPGrid_AddItem() API,����type����",L"�Ųʽ����-������ʾ",XMB_OK);
		}
#endif
	}

	if(-1==groupID) //һ����
	{
		PGridNode_ *pNode=(PGridNode_*)malloc(sizeof(PGridNode_));
		pNode->pItem=pItem;
		pNode->type=2;
		pNode->pNext=NULL;

		if(NULL==pObj->pItemList)
		{
			pObj->pItemList=pNode;
			pObj->pItemLast=pNode;
		}else
		{
			pObj->pItemLast->pNext=pNode;
			pObj->pItemLast=pNode;
		}
	}else //������
	{
		PGridGroup_  *pGroup=PGrid_GetGroup(hEle,groupID);
		if(pGroup)
		{
			if(NULL==pGroup->pItemList)
			{
				pGroup->pItemList=pItem;
				pGroup->pItemLast=pItem;
			}else
			{
				pGroup->pItemLast->pNext=pItem;
				pGroup->pItemLast=pItem;
			}
		}
	}

	pObj->bAdjust=TRUE;

	return pItem->id;
}

/// @brief ��������Ԫ��,�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pName   ������.
/// @param pValue   ��ֵ.
/// @param groupID  ��������ID,���û�з���-1.
/// @return ��������ID��ʾ��.
int WINAPI XPGrid_AddItemString(HELE hEle,wchar_t *pName,wchar_t *pValue,int groupID) //�����
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_  *pObj=(propertyGrid_*)hEle;

	PGridItem_ *pData=(PGridItem_*)malloc(sizeof(PGridItem_));
	pData->id=PGrid_AddID(hEle);
	pData->hEle=NULL;
	pData->type=PGRID_STRING;
	pData->pNext=NULL;
	//	pData->pTemp=NULL;
	if(pName)
	{
		int size=wcslen(pName)+1;
		pData->pName=(wchar_t*)malloc(size*sizeof(wchar_t));
		wcscpy_s(pData->pName,size,pName);
	}else
		pName=NULL;

	if(pValue)
	{
		int size=wcslen(pValue)+1;
		pData->pValue=(wchar_t*)malloc(size*sizeof(wchar_t));
		wcscpy_s(pData->pValue,size,pValue);
	}else
		pData->pValue=NULL;

	if(-1==groupID) //һ���ڵ�
	{

		PGridNode_ *pNode=(PGridNode_*)malloc(sizeof(PGridNode_));
		pNode->type=2;
		pNode->pItem=pData;
		pNode->pNext=NULL;

		if(NULL==pObj->pItemList)
		{
			pObj->pItemList=pNode;
			pObj->pItemLast=pNode;
		}else
		{
			pObj->pItemLast->pNext=pNode;
			pObj->pItemLast=pNode;
		}
	}else //�����ڵ�
	{
		PGridGroup_  *pGroup=PGrid_GetGroup(hEle,groupID);
		if(pGroup)
		{
			if(NULL==pGroup->pItemList)
			{
				pGroup->pItemList=pData;
				pGroup->pItemLast=pData;
			}else
			{
				pGroup->pItemLast->pNext=pData;
				pGroup->pItemLast=pData;
			}
		}
	}
	pObj->bAdjust=TRUE;
	return  pData->id;
}

/// @brief ��������Ԫ��,��ȡָ����Ԫ�صľ��.ͨ�����صľ���޸����ֵ.
/// @param hEle  Ԫ�ؾ��.
/// @param itemID  ��ID��ʾ��.
/// @return ��ID��ʾ����Ӧ��Ԫ�ؾ��.
HELE WINAPI XPGrid_GetItemHEle(HELE hEle,int itemID)
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridItem_ *pItem=PGrid_GetItem(hEle,itemID);
	if(pItem)
	{
		return pItem->hEle;
	}
	return NULL;
}

/// @brief ��������Ԫ��,����������,�������ַ���(PGRID_STRING,PGRID_EDIT,PGRID_COMBOBOX)���͵�����Ч.
/// @param hEle  Ԫ�ؾ��.
/// @param itemID  ��ID��ʾ��.
/// @param pText   ���ı�����.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XPGrid_SetItemString(HELE hEle,int itemID,wchar_t *pText)
{
	IsPGridDebug(hEle,__FUNCTION__);
	if(NULL==pText) return FALSE;

	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridItem_ *pItem=PGrid_GetItem(hEle,itemID);
	if(pItem)
	{
		switch(pItem->type)
		{
		case PGRID_STRING:
			{
				if(pItem->pValue)
				{
					free(pItem->pValue);
				}
				int size=wcslen(pText)+1;
				pItem->pValue=(wchar_t*)malloc(size*sizeof(wchar_t));
				wcscpy_s(pItem->pValue,size,pText);
				return TRUE;
			}
		case PGRID_EDIT_FILE:
		case PGRID_EDIT:
			{
				XEdit_SetText(pItem->hEle,pText);
				return TRUE;
			}
		case PGRID_COMBOBOX:
			{
				XComboBox_SetText(pItem->hEle,pText);
				return TRUE;
			}
		}
	}
	return FALSE;
}

/// @brief ��������Ԫ��,����������,������PGRID_CHOOSECOLOR���͵���.
/// @param hEle  Ԫ�ؾ��.
/// @param itemID  ��ID��ʾ��.
/// @param color   ��ɫֵ.
/// @return �ɹ�����TRUE,�����෴.
BOOL WINAPI XPGrid_SetItemColor(HELE hEle,int itemID,COLORREF color)
{
	IsPGridDebug(hEle,__FUNCTION__);

	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridItem_ *pItem=PGrid_GetItem(hEle,itemID);
	if(pItem)
	{
		if(PGRID_CHOOSECOLOR==pItem->type)
		{
			XCHColor_SetColor(pItem->hEle,color);
			return TRUE;
		}
	}
	return FALSE;
}

/// @brief ��������Ԫ��,��ȡָ�����ֵ.
/// @param hEle  Ԫ�ؾ��.
/// @param itemID  ��ID��ʾ��.
/// @param pOut   �������ݻ�����.
/// @param len    pOut����������
void WINAPI XPGrid_GetItemValue(HELE hEle,int itemID,wchar_t *pOut,int len)
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridItem_ *pItem=PGrid_GetItem(hEle,itemID);
	if(NULL==pItem) return;

	switch(pItem->type)
	{
	case PGRID_STRING:
		{
			wmemcpy_s(pOut,len,pItem->pValue,wcslen(pItem->pValue));
		}break;
	case PGRID_EDIT_FILE:
	case PGRID_EDIT:
		{
			if(pItem->hEle)
				XEdit_GetText(pItem->hEle,pOut,len);
		}break;
	case PGRID_COMBOBOX:
		{
			if(pItem->hEle)
				XComboBox_GetText(pItem->hEle,pOut,len);
		}break;
	case PGRID_CHOOSECOLOR:
		{
			if(len<7) return;
			wchar_t color[8]={0};
			XEdit_GetText(pItem->hEle,pOut,7);
		}break;
	}
}

/// @brief ��������Ԫ��,ɾ����.
/// @param hEle  Ԫ�ؾ��.
/// @param itemID  ��Ҫɾ�����ID��ʾ��.
void WINAPI XPGrid_DeleteItem(HELE hEle,int itemID)  //ɾ����
{
	IsPGridDebug(hEle,__FUNCTION__);

	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridNode_  *pNode=pObj->pItemList;

	PGridNode_  *pNodeFront=NULL;
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			PGridGroup_ *pGroup=(PGridGroup_*)pNode->pItem;
			PGridItem_ *pItem=pGroup->pItemList;
			PGridItem_  *pItemFront=NULL;
			while(pItem)
			{
				if(itemID==pItem->id)
				{
					if(pItem->hEle)
						XEle_Destroy(pItem->hEle);
					if(pItem->pName)
						free(pItem->pName);
					if(pItem->pValue)
						free(pItem->pValue);

					if(pItemFront)
					{
						pItemFront->pNext=pItem->pNext;
						if(NULL==pItem->pNext)
						{
							pGroup->pItemLast=pItemFront;
						}
					}else
					{
						if(pItem->pNext)
						{
							pGroup->pItemList=pItem->pNext;
							pGroup->pItemLast=pItem->pNext;
						}else
						{
							pGroup->pItemList=NULL;
							pGroup->pItemLast=NULL;
						}
					}
					free(pItem);
					break;
				}
				pItemFront=pItem;
				pItem=pItem->pNext;
			}
		}else if(2==pNode->type) //��
		{
			PGridItem_  *pItem=(PGridItem_*)pNode->pItem;
			if(itemID==pItem->id)
			{
				if(pItem->hEle)
					XEle_Destroy(pItem->hEle);
				if(pItem->pName)
					free(pItem->pName);
				if(pItem->pValue)
					free(pItem->pValue);

				free(pItem);

				if(pNodeFront)
				{
					pNodeFront->pNext=pNode->pNext;
					if(NULL==pNode->pNext)
					{
						pObj->pItemLast=pNodeFront;
					}
				}else
				{
					if(pNode->pNext)
					{
						pObj->pItemList=pNode->pNext;
						pObj->pItemLast=pNode->pNext;
					}else
					{
						pObj->pItemList=NULL;
						pObj->pItemLast=NULL;
					}
				}
				free(pNode);
				break;
			}
		}

		pNodeFront=pNode;
		pNode=pNode->pNext;
	}
	if(itemID==pObj->selId)
		pObj->selId=-1;

	if(pObj->pTemp)
	{
		free(pObj->pTemp);
		pObj->pTemp=NULL;
	}

	pObj->bAdjust=TRUE;
}

/// @brief ��������Ԫ��,��������.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XPGrid_Adjust(HELE hEle)   //��������
{
	IsPGridDebug(hEle,__FUNCTION__);
	PGrid_Adjust(hEle);
}

/// @brief ��������Ԫ��,ɾ��ָ����.
/// @param hEle  Ԫ�ؾ��.
/// @param groupID  ��Ҫɾ������ID��ʾ��.
void WINAPI XPGrid_DeleteGroup(HELE hEle,int groupID)  //ɾ����
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridNode_  *pNode=pObj->pItemList;
	PGridNode_  *pNodeFront=NULL;
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			PGridGroup_ *pDelGroup=(PGridGroup_*)pNode->pItem;
			if(groupID==pDelGroup->id)
			{
				PGridItem_  *pDelItem=NULL;
				PGridItem_ *pItem=pDelGroup->pItemList;
				while(pItem)
				{
					pDelItem=pItem;
					pItem=pItem->pNext;

					if(pDelItem->hEle)
						XEle_Destroy(pDelItem->hEle);
					if(pDelItem->pName)
						free(pDelItem->pName);
					if(pDelItem->pValue)
						free(pDelItem->pValue);
					free(pDelItem);
				}

				if(pDelGroup->pName)
					free(pDelGroup->pName);

				free(pDelGroup);

				if(pNodeFront)
				{
					pNodeFront->pNext=pNode->pNext;
					if(NULL==pNode->pNext)
					{
						pObj->pItemLast=pNodeFront;
					}
				}else
				{
					if(pNode->pNext)
					{
						pObj->pItemList=pNode->pNext;
						pObj->pItemLast=pNode->pNext;
					}else
					{
						pObj->pItemList=NULL;
						pObj->pItemLast=NULL;
					}
				}
				free(pNode);
				break ;
			}
		}
		pNodeFront=pNode;
		pNode=pNode->pNext;
	}
	if(groupID==pObj->selId)
		pObj->selId=-1;
	pObj->bAdjust=TRUE;
}

/// @brief ��������Ԫ��,ɾ��������.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XPGrid_DeleteAll(HELE hEle)  //ɾ������
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridNode_  *pNode=pObj->pItemList;

	PGridItem_  *pDelItem=NULL;
	PGridNode_  *pDelNode=NULL;
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			PGridGroup_ *pDelGroup=(PGridGroup_*)pNode->pItem;
			PGridItem_ *pItem=pDelGroup->pItemList;
			while(pItem)
			{
				pDelItem=pItem;
				pItem=pItem->pNext;

				if(pDelItem->hEle)
					XEle_Destroy(pDelItem->hEle);
				if(pDelItem->pName)
					free(pDelItem->pName);
				if(pDelItem->pValue)
					free(pDelItem->pValue);
				free(pDelItem);
			}

			if(pDelGroup->pName)
				free(pDelGroup->pName);

		}else if(2==pNode->type) //��
		{
			pDelItem=(PGridItem_*)pNode->pItem;
			if(pDelItem->hEle)
				XEle_Destroy(pDelItem->hEle);
			if(pDelItem->pName)
				free(pDelItem->pName);
			if(pDelItem->pValue)
				free(pDelItem->pValue);
		}
		free(pNode->pItem);

		pDelNode=pNode;
		pNode=pNode->pNext;
		free(pDelNode);
	}
	pObj->pItemList=NULL;
	pObj->pItemLast=NULL;
	pObj->uid=0;
	pObj->selId=-1;

	if(pObj->pTemp)
	{
		free(pObj->pTemp);
		pObj->pTemp=NULL;
	}

	pObj->bAdjust=TRUE;
}

/// @brief ���÷ָ��߻���X����λ��.
/// @param hEle  Ԫ�ؾ��.
/// @param point  ����X����λ��.
void WINAPI XPGrid_SetSpacePoint(HELE hEle,int point) //���÷ֿ���λ��
{
	IsPGridDebug(hEle,__FUNCTION__);
	((propertyGrid_*)hEle)->spacePoint=point;
	PGrid_Adjust(hEle);
}

/// @brief ��ȡ��ǰѡ����.
/// @param hEle  Ԫ�ؾ��.
/// @return ���ص�ǰѡ�����ID��ʾ��.
int WINAPI XPGrid_GetSelectItem(HELE hEle) //��ȡ��ǰѡ����
{
	IsPGridDebug(hEle,__FUNCTION__);
	return ((propertyGrid_*)hEle)->selId;
}

///@}

BOOL CALLBACK PGrid_OnEleDraw(HELE hEle,HDRAW hDraw)
{
	if(((propertyGrid_*)hEle)->bAdjust)
	{
		PGrid_Adjust(hEle);
	}
	return FALSE;
}

BOOL CALLBACK PGrid_OnDrawScrollView(HELE hEle,HDRAW hDraw)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	int viewWidth=XSView_GetViewWidth(hEle)-XSView_GetHViewPos(hEle);
	int viewHeight=XSView_GetViewHeight(hEle);
	int left=/*XSView_GetSpacingLeft(hEle)-*/XSView_GetHViewPos(hEle);
	int top=/*XSView_GetSpacingTop(hEle)-*/XSView_GetVViewPos(hEle);

	//������౳��
	RECT rcLeft={left,top,left+pObj->indent,pObj->bottom};
	XDraw_FillSolidRect_(hDraw,&rcLeft,RGB(212,208,200));

	HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(212,208,200));
	HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);

	HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(0,0,0));

	PGridNode_ *pNode=pObj->pItemList;
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			PGridGroup_ *pGroup=(PGridGroup_*)pNode->pItem;
			PGrid_DrawGroup(hEle,pGroup,left,viewWidth+left,hDraw,hBrush);
			//	XTRACEW(L"������:%s\n",pGroup->pName);
		}else //��
		{
			PGridItem_ *pItem=(PGridItem_*)pNode->pItem;
			//������
			PGrid_DrawItem(hEle,pItem,left,viewWidth+left,hDraw);
			//	XTRACEW(L"������:%s\n",pItem->pName);
		}
		pNode=pNode->pNext;
		//XDraw_RestoreGDIOBJ_(hDraw);
	}

//	DeleteObject(hBrush);
//	SelectObject(hdc,hOldPen);
//	DeleteObject(hPen);
	
	return TRUE;
}

void PGrid_DrawGroup(HELE hEle,PGridGroup_ *pGroup,int left,int right,HDRAW hDraw,HBRUSH hBrush) //������
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	//�����鱳��
	RECT rc={left+pObj->indent,pGroup->posy,right,pGroup->posy+pObj->itemHeight};
	XDraw_FillSolidRect_(hDraw,&rc,RGB(212,208,200));

	//չ����ť
	RECT rcBtn={left+pObj->indentBtn,pGroup->posy+pObj->itemHeight/2-5,left+pObj->indentBtn+9,
		pGroup->posy+(pObj->itemHeight/2)+4};
	XDraw_FrameRect_(hDraw,&rcBtn,hBrush);
	//չ����ť������
	HPEN hPen1=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(0,0,0));
	HGDIOBJ hOldPen1=XDraw_SelectObject_(hDraw,hPen1);
	XDraw_MoveToEx_(hDraw,rcBtn.left+2,rcBtn.top+4,NULL);
	XDraw_LineTo_(hDraw,rcBtn.right-2,rcBtn.top+4);
	if(FALSE==pGroup->bExpand)
	{
		XDraw_MoveToEx_(hDraw,rcBtn.left+4,rcBtn.top+2,NULL);
		XDraw_LineTo_(hDraw,rcBtn.left+4,rcBtn.bottom-2);
	}
	XDraw_SelectObject_(hDraw,hOldPen1);
	XDraw_DeleteObject_(hDraw,hPen1);

	//������
	if(pGroup->pName)
	{
		rc.left+=2;
		XDraw_DrawText_(hDraw,pGroup->pName,wcslen(pGroup->pName),&rc,DT_VCENTER | DT_SINGLELINE);
	}
	
	//�����������,������
	if(pGroup->bExpand)
	{
		PGridItem_ *pItem=pGroup->pItemList;
		while(pItem) 
		{
			PGrid_DrawItem(hEle,pItem,left,right,hDraw);
			pItem=pItem->pNext;
		}
	}
}

void PGrid_DrawItem(HELE hEle,PGridItem_ *pItem,int left,int right,HDRAW hDraw)  //������
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	int bottom=pItem->posy+pObj->itemHeight;
	//��������
	RECT rc={left+pObj->indent,pItem->posy,pObj->spacePoint,bottom};
	if(pObj->selId==pItem->id)
		XDraw_FillSolidRect_(hDraw,&rc,RGB(51,153,255)); //ѡ����

	if(pItem->pName)
	{
		RECT rcText=rc;
		rcText.left+=3;
		XDraw_DrawText_(hDraw,pItem->pName,wcslen(pItem->pName),&rcText,DT_VCENTER | DT_SINGLELINE);
	}
	//����ֵ
	RECT rcItem={pObj->spacePoint+3,pItem->posy,right,bottom};
	switch(pItem->type)
	{
	case PGRID_STRING:
		{
			if(pItem->pValue)
				XDraw_DrawText_(hDraw,pItem->pValue,wcslen(pItem->pValue),&rcItem,DT_VCENTER | DT_SINGLELINE);
		}break;
	case PGRID_EDIT_FILE:
	case  PGRID_EDIT:
		if(pItem->hEle)
		{
			wchar_t text[MAX_PATH]={0};
			XEdit_GetText(pItem->hEle,text,MAX_PATH-1);
			int len=wcslen(text);
			if(len>0)
				XDraw_DrawText_(hDraw,text,len,&rcItem,DT_VCENTER | DT_SINGLELINE);
		}break;
	case PGRID_COMBOBOX:
		if(pItem->hEle)
		{
			wchar_t text[MAX_PATH]={0};
			XComboBox_GetText(pItem->hEle,text,MAX_PATH-1);
			int len=wcslen(text);
			if(len>0)
				XDraw_DrawText_(hDraw,text,len,&rcItem,DT_VCENTER | DT_SINGLELINE);
		}break;
	case PGRID_CHOOSECOLOR:
		{
			int size=rcItem.bottom-rcItem.top-5;

			wchar_t color[8]={0};
			XEdit_GetText(pItem->hEle,color,7);
			rcItem.left=pObj->spacePoint+size+4;
			XDraw_DrawText_(hDraw,color,wcslen(color),&rcItem,DT_VCENTER | DT_SINGLELINE);

			
			RECT rcColor={pObj->spacePoint+2,rcItem.top+2,pObj->spacePoint+size,rcItem.top+size+2};
			XDraw_FillSolidRect_(hDraw,&rcColor,((chooseColor_*)pItem->hEle)->color);
		}break;
	}

	XDraw_MoveToEx_(hDraw,left+pObj->indent,bottom-1,NULL);
	XDraw_LineTo_(hDraw,right,bottom-1);

	XDraw_MoveToEx_(hDraw,pObj->spacePoint,pItem->posy,NULL);
	XDraw_LineTo_(hDraw,pObj->spacePoint,bottom);
}

void PGrid_HideEle(HELE hEle)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridItem_  *pItem=PGrid_GetItem(hEle,pObj->selId);
	if(pItem && pItem->hEle)
	{
		XEle_ShowEle(pItem->hEle,FALSE);
	}
}

void PGrid_ShowEle(HELE hEle,PGridItem_ *pItem)//��ʾָ����
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	pObj->selId=pItem->id;
	if(pItem->hEle)
	{
		//������ʱ����
		switch(pItem->type)
		{
		case PGRID_STRING:   break;
		case PGRID_EDIT_FILE:
		case PGRID_EDIT:
			{
				if(pObj->pTemp)
				{
					free(pObj->pTemp);
					pObj->pTemp=NULL;
				}
				int len=XEdit_GetTextLength(pItem->hEle);
				len = (len+1)*sizeof(wchar_t);
				pObj->pTemp=(wchar_t*)malloc(len); 
				memset(pObj->pTemp,0,len);
				XEdit_GetText(pItem->hEle,pObj->pTemp,len/sizeof(wchar_t)); 
			}break;
		case PGRID_COMBOBOX:  
			{
				if(pObj->pTemp)
				{
					free(pObj->pTemp);
					pObj->pTemp=NULL;
				}
				int len=XEdit_GetTextLength(pItem->hEle);
				len = (len+1)*sizeof(wchar_t);
				pObj->pTemp=(wchar_t*)malloc(len); 
				memset(pObj->pTemp,0,len);
				XEdit_GetText(pItem->hEle,pObj->pTemp,len/sizeof(wchar_t)); 
			}
			break;
		case PGRID_CHOOSECOLOR:
			{
				if(pObj->pTemp)
				{
					free(pObj->pTemp);
					pObj->pTemp=NULL;
				}
				int len=XEdit_GetTextLength(pItem->hEle);
				len = (len+1)*sizeof(wchar_t);
				pObj->pTemp=(wchar_t*)malloc(len); 
				memset(pObj->pTemp,0,len);
				XEdit_GetText(pItem->hEle,pObj->pTemp,len/sizeof(wchar_t)); 
			}
			break;
		}
		XEle_ShowEle(pItem->hEle,TRUE);
	}
}

void PGrid_CheckValueChange(HELE hEle,PGridItem_ *pItem)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	if(pItem)
	{
		if(pItem->hEle)
		{
			switch(pItem->type)
			{
			case PGRID_STRING: break;
			case PGRID_EDIT_FILE:
			case PGRID_EDIT: 
				{
					if(NULL==pObj->pTemp)
					{
						XTRACE("PGrid_CheckValueChange() ����\n");
					}

					int len=XEdit_GetTextLength(pItem->hEle);
					len = (len+1)*sizeof(wchar_t);
					wchar_t *pTemp=(wchar_t*)malloc(len); 
					memset(pTemp,0,len);
					XEdit_GetText(pItem->hEle,pTemp,len/sizeof(wchar_t)); 

					if(0!=wcscmp(pTemp,pObj->pTemp))
					{
						free(pObj->pTemp);
						pObj->pTemp=pTemp;

						Ele_SendEvent(hEle,XE_PGRID_VALUECHANGE,pItem->id,0,TRUE);
						//XTRACE("����ֵ�ı��¼� id=%d \n",pItem->id);
						//::MessageBox(NULL,L"ֵ�ı��¼�",L"��ʾ",0);
					}else
					{
						free(pTemp);
						//XTRACE("����ֵno�¼� id=%d \n",pItem->id);
					}
				//	if(XEle_IsFocus(pItem->hEle))
				//		XEle_SetFocus(pItem->hEle,FALSE);
				}break;
			case PGRID_COMBOBOX: 
				{
					if(NULL==pObj->pTemp)
					{
						XTRACE("PGrid_CheckValueChange() ����\n");
					}

					int len=XEdit_GetTextLength(pItem->hEle);
					len = (len+1)*sizeof(wchar_t);
					wchar_t *pTemp=(wchar_t*)malloc(len); 
					memset(pTemp,0,len);
					XEdit_GetText(pItem->hEle,pTemp,len/sizeof(wchar_t)); 

					if(0!=wcscmp(pTemp,pObj->pTemp))
					{
						free(pObj->pTemp);
						pObj->pTemp=pTemp;
						Ele_SendEvent(hEle,XE_PGRID_VALUECHANGE,pItem->id,0,TRUE);
						//XTRACE("����ֵ�ı��¼� id=%d \n",pItem->id);
					}else
					{
						free(pTemp);
						//XTRACE("����ֵno�¼� id=%d \n",pItem->id);
					}

				//	if(XEle_IsFocus(pItem->hEle))
				//		XEle_SetFocus(pItem->hEle,FALSE);
				}
				break;
			case PGRID_CHOOSECOLOR: 
				{
					if(NULL==pObj->pTemp)
					{
						XTRACE("PGrid_CheckValueChange() ����\n");
					}

					int len=XEdit_GetTextLength(pItem->hEle);
					len = (len+1)*sizeof(wchar_t);
					wchar_t *pTemp=(wchar_t*)malloc(len); 
					memset(pTemp,0,len);
					XEdit_GetText(pItem->hEle,pTemp,len/sizeof(wchar_t)); 

					if(0!=wcscmp(pTemp,pObj->pTemp))
					{
						free(pObj->pTemp);
						pObj->pTemp=pTemp;
						Ele_SendEvent(hEle,XE_PGRID_VALUECHANGE,pItem->id,0,TRUE);
						//XTRACE("����ֵ�ı��¼� id=%d \n",pItem->id);
					}else
					{
						free(pTemp);
						//XTRACE("����ֵno�¼� id=%d \n",pItem->id);
					}

				//	if(XEle_IsFocus(pItem->hEle))
				//		XEle_SetFocus(pItem->hEle,FALSE);
				}break;
			}
		}
	}
}

// ����  : ��ȡָ����ڵ�
PGridGroup_ *PGrid_GetGroup(HELE hEle,int groupID)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	PGridNode_ *pNode=pObj->pItemList;
	while(pNode)
	{
		if(1==pNode->type)
		{
			if(groupID==((PGridGroup_*)pNode->pItem)->id)
				return (PGridGroup_*)pNode->pItem;
		}
		pNode=pNode->pNext;
	}
	return NULL;
}

PGridItem_ *PGrid_GetItem(HELE hEle,int itemID)  //��ȡָ����ڵ�
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	PGridNode_ *pNode=pObj->pItemList;
	while(pNode)
	{
		if(1==pNode->type) //��
		{
			PGridItem_ *pItem=((PGridGroup_*)pNode->pItem)->pItemList;
			while(pItem)
			{
				if(itemID==pItem->id)
					return pItem;
				pItem=pItem->pNext;
			}
		}else if(2==pNode->type) //��
		{
			if(itemID==((PGridItem_*)pNode->pItem)->id)
				return (PGridItem_*)pNode->pItem;
		}
		pNode=pNode->pNext;
	}
	return NULL;
}

BOOL CALLBACK PGrid_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	if(pPt->x<pObj->spacePoint &&  pPt->x>(pObj->spacePoint-5))
	{
		pObj->bDown=TRUE;
		XEle_SetCapture(hEle);
		SetCursor(LoadCursor(NULL,IDC_SIZEWE));
		return FALSE;
	}
	RECT rcView;
	XSView_GetViewRect(hEle,&rcView);
	if(FALSE==PtInRect(&rcView,*pPt))
		return FALSE;

	POINT pt=*pPt;
	pt.y-=XSView_GetVViewPos(hEle);

	int left=XSView_GetSpacingLeft(hEle)-XSView_GetHViewPos(hEle);

	PGridNode_ *pNode=pObj->pItemList;
	while(pNode)
	{
		if(1==pNode->type)  //��
		{
			PGridGroup_ *pGroup=(PGridGroup_*)pNode->pItem;
			RECT rcBtn={left+pObj->indentBtn,pGroup->posy+pObj->itemHeight/2-5,
				left+pObj->indentBtn+9,pGroup->posy+(pObj->itemHeight/2)+4};
			if(PtInRect(&rcBtn,pt))
			{
				if(pGroup->bExpand)
				{
					pGroup->bExpand=FALSE;
				}else
				{
					pGroup->bExpand=TRUE;
				}
				if(-1!=pObj->selId)
				{
					int oldSel=pObj->selId;
					PGrid_HideEle(hEle);
					//	PGrid_CheckValueChange(hEle,PGrid_GetItem(hEle,oldSel));
					pObj->selId=-1;
					Ele_SendEvent(hEle,XE_PGRID_SELCHANGE,oldSel,pObj->selId);
				}
				PGrid_Adjust(hEle);
				XEle_RedrawEle(hEle);
				return FALSE;
			}else
			{
				if(pGroup->bExpand)
				{
					//����
					PGridItem_ *pItem=pGroup->pItemList;
					while(pItem)
					{
						if(PGrid_LButtonDownItem(hEle,pItem,&pt))
							return FALSE;
						pItem=pItem->pNext;
					}
				}
			}
		}else //��
		{
			if(PGrid_LButtonDownItem(hEle,(PGridItem_*)pNode->pItem,&pt))
				return FALSE;
		}
		pNode=pNode->pNext;
	}

	//����ڿհ״�
	if(-1!=pObj->selId)
	{
		int oldSel=pObj->selId;
		PGrid_HideEle(hEle);
		//	PGrid_CheckValueChange(hEle,PGrid_GetItem(hEle,oldSel));
		pObj->selId=-1;
		Ele_SendEvent(hEle,XE_PGRID_SELCHANGE,oldSel,pObj->selId);

	}
	XEle_RedrawEle(hEle);

	return FALSE;
}

BOOL CALLBACK PGrid_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	if(pObj->bDown)
	{
		pObj->bDown=FALSE;
		XEle_ReleaseCapture(hEle);
	}
	return FALSE;
}

BOOL CALLBACK PGrid_OnMouseMove(HELE hEle,UINT flags,POINT *pPt)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	if(pObj->bDown)
	{
		int width=((ele_*)pObj)->rect.right-((ele_*)pObj)->rect.left-50;
		if(pPt->x>50 && pPt->x<width)
			pObj->spacePoint=pPt->x+1;
		XPGrid_SetSpacePoint(hEle,pObj->spacePoint);
		SetCursor(LoadCursor(NULL,IDC_SIZEWE));
		XEle_RedrawEle(hEle);
	}else
	{
		if(pPt->x<pObj->spacePoint &&  pPt->x>(pObj->spacePoint-5))
		{
			SetCursor(LoadCursor(NULL,IDC_SIZEWE));
		}
	}
	return FALSE;
}

BOOL PGrid_LButtonDownItem(HELE hEle,PGridItem_ *pItem,POINT *pPt)
{
	propertyGrid_ *pObj=(propertyGrid_*)hEle;

	if(pPt->y>pItem->posy && pPt->y<(pItem->posy+pObj->itemHeight))
	{
		if(pObj->selId!=pItem->id)
		{
			int oldSel=pObj->selId;
			PGrid_HideEle(hEle);
			//	PGrid_CheckValueChange(hEle,PGrid_GetItem(hEle,oldSel));
			PGrid_ShowEle(hEle,pItem);

			Ele_SendEvent(hEle,XE_PGRID_SELCHANGE,oldSel,pObj->selId);

			XEle_RedrawEle(hEle);
		}
		//TODO:��ʱע��
		//	else if(pPt->x<=pObj->spacePoint)
		//	{
		//		PGrid_CheckValueChange(hEle,pItem);
		//	}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK PGrid_OnEventKillFocus(HELE hEle,HELE hEventEle) //ʧȥ����
{
	//�ж��Ƿ���Ԫ�ػ�ý���
	/*	HELE hFocus=XWnd_GetFocusEle(XEle_GetHWindow(hEle));
	if(hFocus)
	{
	if(XEle_IsChildEle(hEle,hFocus))
	{
	return FALSE;
	}
	}

	//��ȡ��ѡ��
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	if(-1!=pObj->selId)
	{
	int oldSel=pObj->selId;
	PGrid_HideEle(hEle);
	pObj->selId=-1;
	Ele_SendEvent(hEle,XE_PGRID_SELCHANGE,oldSel,pObj->selId);
	}
	XEle_RedrawEle(hEle);
	*/

	return FALSE;
}

BOOL CALLBACK PGrid_OnEventSize(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
		PGrid_Adjust(hEle);
	return FALSE;
}

void CALLBACK PGrid_OnDestroy(HELE hEle)  //����
{
	XPGrid_DeleteAll(hEle);
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	if(pObj->pTemp)
	{
		free(pObj->pTemp);
		pObj->pTemp=NULL;
	}
	
	window_ *pWindow=(window_*)XEle_GetHWindow(hEle);
	XArray_Delete(pWindow->hArrayPGrids,hEle);
}
