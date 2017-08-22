/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HXCGUI XMTree_Create()
{
	multiTree_  *pObject=(multiTree_*)malloc(sizeof(multiTree_));
	if(NULL==pObject) return NULL;
	pObject->pRootNode=NULL;
	pObject->pRootNodeEnd=NULL;
	pObject->pTraverseData=NULL;
	return pObject;
}

void XMTree_Destroy(HXCGUI hMTree) //����
{
	MTree_TraverseDestroy(((multiTree_*)hMTree)->pRootNode);
	free(hMTree);
}

BOOL XMTree_AddNode(HXCGUI hMTree,int parentID,void *pNodeData,int nodeID) //��ӽڵ�
{
	if(parentID<XMTREE_ROOT) return FALSE;

	multiTree_  *pObject=(multiTree_*)hMTree;

	//�½ڵ�
	multiTree_node_ *pNewNode=(multiTree_node_*)malloc(sizeof(multiTree_node_));
	memset(pNewNode,0,sizeof(multiTree_node_));
	pNewNode->id=nodeID;
	pNewNode->pData=pNodeData;

	//���ڵ�
	if(XMTREE_ROOT==parentID)
	{
		if(NULL==pObject->pRootNode)
		{
			pObject->pRootNode=pNewNode;
			pObject->pRootNodeEnd=pNewNode;
		}else
		{
			pNewNode->pParentNode=pObject->pRootNodeEnd;
			pObject->pRootNodeEnd->pDown=pNewNode;
			pNewNode->pUp=pObject->pRootNodeEnd;
			pObject->pRootNodeEnd=pNewNode;
		}
		return TRUE;
	}

	//�ӽڵ�
	multiTree_node_ *pParentItem=MTree_GetNode(pObject,parentID);
	if(NULL==pParentItem)
	{
		free(pNewNode);
		return FALSE;
	}
	pNewNode->pParentItem=pParentItem;
	if(pParentItem->pChild)
	{
		pNewNode->pParentNode=pParentItem->pChildEnd;
		pParentItem->pChildEnd->pDown=pNewNode;
		pNewNode->pUp=pParentItem->pChildEnd;
		pParentItem->pChildEnd=pNewNode;
	}else
	{
		pNewNode->pParentNode=pParentItem;
		pParentItem->pChild=pNewNode;
		pParentItem->pChildEnd=pNewNode;
	}
	return TRUE;
}

void XMTree_InsertNode(HXCGUI hMTree,void *pNodeData,int nodeID,int insertID)
{
	multiTree_  *pObject=(multiTree_*)hMTree;

	//�½ڵ�
	multiTree_node_ *pNewNode=(multiTree_node_*)malloc(sizeof(multiTree_node_));
	memset(pNewNode,0,sizeof(multiTree_node_));
	pNewNode->id=nodeID;
	pNewNode->pData=pNodeData;

	multiTree_node_ *pInsertNode=MTree_GetNode((multiTree_*)hMTree, insertID);  //��ȡ�ڵ�
	if(pInsertNode)
	{
		if(NULL==pInsertNode->pParentItem) //���ڵ��
		{
			if(pObject->pRootNode==pInsertNode) //�׽ڵ�
			{
				pObject->pRootNode=pNewNode;
				pNewNode->pDown=pInsertNode;
				pInsertNode->pUp=pNewNode;
			}else //�м�ڵ�
			{
				pInsertNode->pUp->pDown=pNewNode;
				pNewNode->pUp=pInsertNode->pUp;
				pNewNode->pParentNode=pInsertNode->pUp;
				pNewNode->pDown=pInsertNode;
				pInsertNode->pUp=pNewNode;
				pInsertNode->pParentNode=pNewNode;
			}
		}else
		{
			if(pInsertNode==pInsertNode->pParentItem->pChild) //��ǰ���׽ڵ�
			{
				pNewNode->pParentItem=pInsertNode->pParentItem;
				pNewNode->pParentItem->pChild=pNewNode;
				pNewNode->pDown=pInsertNode;
				pInsertNode->pUp=pNewNode;
				pInsertNode->pParentNode=pNewNode;
			}else //�м�ڵ�
			{
				pNewNode->pParentItem=pInsertNode->pParentItem;
				pInsertNode->pUp->pDown=pNewNode;
				pNewNode->pUp=pInsertNode->pUp;
				pNewNode->pParentNode=pInsertNode->pUp;
				pNewNode->pDown=pInsertNode;
				pInsertNode->pUp=pNewNode;
				pInsertNode->pParentNode=pNewNode;
			}
		}
	}
}

void *XMTree_GetNodeData(HXCGUI hMTree,int nodeID)
{
	multiTree_node_ *pNode=MTree_GetNode((multiTree_*)hMTree,nodeID);
	if(pNode)
		return pNode->pData;
	return NULL;
}

void XMTree_DeleteNode(HXCGUI hMTree,int nodeID)
{
	multiTree_  *pObject=(multiTree_*)hMTree;

	multiTree_node_ *pNode=MTree_GetNode((multiTree_*)hMTree,nodeID);	//Ҫɾ���Ľڵ�
	if(pNode)
	{
		if(NULL==pNode->pParentItem) //���ڵ��
		{
			if(pObject->pRootNode==pNode) //�׽ڵ�
			{
				if(pNode->pDown)
				{
					pObject->pRootNode=pNode->pDown;
					pNode->pDown->pUp=NULL;
					pNode->pDown->pParentNode=NULL;
				}else //ĩβ�ڵ�
				{
					pObject->pRootNode=NULL;
					pObject->pRootNodeEnd=NULL;
				}
			}else //�м�ڵ�
			{
				if(pNode->pDown)
				{
					pNode->pUp->pDown=pNode->pDown;
					pNode->pDown->pUp=pNode->pUp;
					pNode->pDown->pParentNode=pNode->pUp;
				}else //ĩβ�ڵ�
				{
					pNode->pUp->pDown=NULL;
					pObject->pRootNodeEnd=pNode->pUp;
				}
			}
		}else
		{
			if(pNode==pNode->pParentItem->pChild) //��ǰ���׽ڵ�
			{
				if(pNode->pDown)
				{
					pNode->pParentItem->pChild=pNode->pDown;
					pNode->pDown->pUp=NULL;
					pNode->pDown->pParentNode=pNode->pParentItem;
				}else
				{
					pNode->pParentItem->pChild=NULL;
				}
			}else //�м�ڵ�
			{
				if(pNode->pDown)
				{
					pNode->pUp->pDown=pNode->pDown;
					pNode->pDown->pUp=pNode->pUp;
					pNode->pDown->pParentNode=pNode->pUp;
				}else //ĩβ�ڵ�
				{
					pNode->pParentItem->pChildEnd=pNode->pUp;
					pNode->pUp->pDown=NULL;
				}
			}
		}
		//delete pNode
		pNode->pDown=NULL;
		MTree_TraverseDestroy(pNode);
	}
}

void *XMTree_GetFirstChildNodeData(HXCGUI hMTree,int parentID)
{
	if(parentID<XMTREE_ROOT) return NULL;
	
	multiTree_  *pObject=(multiTree_*)hMTree;
	if(XMTREE_ROOT==parentID)
	{
		return pObject->pRootNode->pData;
	}else
	{
		multiTree_node_ *pNode=MTree_GetNode((multiTree_*)hMTree,parentID);
		if(pNode && pNode->pChild)
			return pNode->pChild->pData;
	}
	return NULL;
}

void *XMTree_GetNextNodeData(HXCGUI hMTree,int nodeID)
{
	multiTree_node_ *pNode=MTree_GetNode((multiTree_*)hMTree,nodeID);
	if(pNode)
	{
		if(pNode->pDown)
			return pNode->pDown->pData;
	}
	return NULL;
}

int  XMTree_GetNodeCount(HXCGUI hMTree,int nodeID)
{
	multiTree_node_  *pNode=NULL;
	if(XMTREE_ROOT==nodeID)
	{
		pNode=((multiTree_*)hMTree)->pRootNode;
	}else
	{
		pNode=MTree_GetNode((multiTree_*)hMTree,nodeID);
	}
	if(pNode)
		return MTree_GetNodeCount(pNode);
	else
		return 0;
}

HXCGUI XMTree_GetNodeHandle(HXCGUI hMTree,int nodeID)
{
	multiTree_node_ *pNode=MTree_GetNode((multiTree_*)hMTree,nodeID);
	return pNode;
}

int  XMTree_BeginTraverse(HXCGUI hMTree,int parentID) //��ʼ����
{
	multiTree_node_  *pNode=NULL;
	if(XMTREE_ROOT==parentID)
	{
		pNode=((multiTree_*)hMTree)->pRootNode;
	}else
	{
		multiTree_node_ *pParentItem=MTree_GetNode((multiTree_*)hMTree,parentID);
		if(pParentItem)
			pNode=pParentItem->pChild;
	}

	if(NULL==pNode) return -1;

	int count=0;

	multiTree_node_ *pNodeBegin=pNode;
	while(pNodeBegin)
	{
		count++;
		pNodeBegin=pNodeBegin->pDown;
	}
	if(count>0)
	{
		void **data=(void **)malloc(sizeof(void*)*count);

		pNodeBegin=pNode;
		for(int i=0;i<count;i++)
		{
			data[i]=pNodeBegin->pData;
			pNodeBegin=pNodeBegin->pDown;
		}

		((multiTree_*)hMTree)->pTraverseData=data;

		return count;
	}else
		return -1;
}

void *XMTree_GetTraverseData(HXCGUI hMTree,int index)
{
	return ((void**)((multiTree_*)hMTree)->pTraverseData)[index];
}

void XMTree_EndTraverse(HXCGUI hMTree) //��������
{
	if(((multiTree_*)hMTree)->pTraverseData)
	{
		free(((multiTree_*)hMTree)->pTraverseData);
		((multiTree_*)hMTree)->pTraverseData=NULL;
	}
}

int  XMTree_BeginTraverseInfo(HXCGUI hMTree,int parentID) //��ʼ����
{
	multiTree_node_  *pNode=NULL;
	if(XMTREE_ROOT==parentID)
	{
		pNode=((multiTree_*)hMTree)->pRootNode;
	}else
	{
		multiTree_node_ *pParentItem=MTree_GetNode((multiTree_*)hMTree,parentID);
		if(pParentItem)
			pNode=pParentItem->pChild;
	}

	if(NULL==pNode) return -1;

	int count=0;

	multiTree_node_ *pNodeBegin=pNode;
	while(pNodeBegin)
	{
		count++;
		pNodeBegin=pNodeBegin->pDown;
	}
	if(count>0)
	{
		multiTree_node_info_ *data=(multiTree_node_info_*)malloc(sizeof(multiTree_node_info_)*count);

		pNodeBegin=pNode;
		for(int i=0;i<count;i++)
		{
			data[i].pData=pNodeBegin->pData;
			data[i].id=pNodeBegin->id;
			data[i].hNode=pNodeBegin;
			pNodeBegin=pNodeBegin->pDown;
		}

		((multiTree_*)hMTree)->pTraverseData=data;

		return count;
	}else
		return -1;
}

void *XMTree_GetTraverseInfo(HXCGUI hMTree,int index,HXCGUI *hOutNode,int *outID)
{
	multiTree_node_info_ *pInfo=(multiTree_node_info_*)((multiTree_*)hMTree)->pTraverseData;
	if(outID) *outID=pInfo[index].id;
	if(hOutNode) *hOutNode=pInfo[index].hNode;
	return pInfo[index].pData;
}

void XMTree_EndTraverseInfo(HXCGUI hMTree) //��������
{
	if(((multiTree_*)hMTree)->pTraverseData)
	{
		free(((multiTree_*)hMTree)->pTraverseData);
		((multiTree_*)hMTree)->pTraverseData=NULL;
	}
}

int  XMTree_BeginTraverseAll(HXCGUI hMTree) //��ʼ����
{
	multiTree_ *pObject=(multiTree_*)hMTree;

	//�����ӽڵ�����
	int count=MTree_GetNodeCount(pObject->pRootNode);

	void *data=malloc(sizeof(void*)*count);

	//���������ڵ�
	MTree_TraverseNodeDataToArray(pObject->pRootNode,(void**)data);
	((multiTree_*)hMTree)->pTraverseData=data;

	return count;
}

void *XMTree_GetTraverseAll(HXCGUI hMTree,int index)
{
	return ((void**)((multiTree_*)hMTree)->pTraverseData)[index];
}

void XMTree_EndTraverseAll(HXCGUI hMTree) //��������
{
	if(((multiTree_*)hMTree)->pTraverseData)
	{
		free(((multiTree_*)hMTree)->pTraverseData);
		((multiTree_*)hMTree)->pTraverseData=NULL;
	}
}

//����ڵ�����
int  MTree_GetNodeCount(multiTree_node_  *pNode)
{
	multiTree_node_ *root=pNode; //���ڵ�

	int  nodeCount=0;
	int  LEFT_NO=0;   //��ڵ�δ����
	int  LEFT_YES=1;  //��ڵ��ѷ���
	int  RIGHT_YES=2; //�ҽڵ��ѷ���

	int state=LEFT_NO;
	while(pNode)
	{
		if(LEFT_NO==state)
		{
		//	XTRACE("id=%d \n",pNode->id);
			nodeCount++;
			if(pNode->pDown)
			{
				pNode=pNode->pDown;
			}else
			{
				state=LEFT_YES;
			}
		}else if(LEFT_YES==state)
		{
			if(pNode->pChild)
			{
				pNode=pNode->pChild;
				state=LEFT_NO;
			}else
			{
				if(NULL==pNode->pParentNode) break;

				if(pNode->pParentNode->pDown && pNode==pNode->pParentNode->pDown)
					state=LEFT_YES;
				else
					state=RIGHT_YES;
				pNode=pNode->pParentNode;
			}
		}else if(RIGHT_YES==state)
		{
			if(NULL==pNode->pParentNode) break;

			if(pNode==pNode->pParentNode->pDown)
				state=LEFT_YES;
			else
			{
				state=RIGHT_YES;
				if( root==pNode->pParentNode) //���ҽڵ�,���ݵ����ڵ�,�������
				{
				//	XTRACE("�������� \n");
					break;
				}
			}
			pNode=pNode->pParentNode;
		}
	}
	return nodeCount;
}

void MTree_TraverseNodeDataToArray(multiTree_node_ *pNode,void **pArray)
{
	multiTree_node_ *root=pNode; //���ڵ�

	int  nodeCount=0;
	int  LEFT_NO=0;   //��ڵ�δ����
	int  LEFT_YES=1;  //��ڵ��ѷ���
	int  RIGHT_YES=2; //�ҽڵ��ѷ���

	int state=LEFT_NO;
	while(pNode)
	{
		if(LEFT_NO==state)
		{
		//	XTRACE("id=%d \n",pNode->id);
			pArray[nodeCount]=pNode->pData;
			nodeCount++;
			if(pNode->pDown)
			{
				pNode=pNode->pDown;
			}else
			{
				state=LEFT_YES;
			}
		}else if(LEFT_YES==state)
		{
			if(pNode->pChild)
			{
				pNode=pNode->pChild;
				state=LEFT_NO;
			}else
			{
				if(NULL==pNode->pParentNode) break;

				if(pNode->pParentNode->pDown && pNode==pNode->pParentNode->pDown)
					state=LEFT_YES;
				else
					state=RIGHT_YES;
				pNode=pNode->pParentNode;
			}
		}else if(RIGHT_YES==state)
		{
			if(NULL==pNode->pParentNode) break;

			if(pNode==pNode->pParentNode->pDown)
				state=LEFT_YES;
			else
			{
				state=RIGHT_YES;
				if( root==pNode->pParentNode) //���ҽڵ�,���ݵ����ڵ�,�������
				{
				//	XTRACE("�������� \n");
					break;
				}
			}
			pNode=pNode->pParentNode;
		}
	}
	return ;
}

int XMTree_GetHandleNextNodeInfo(HXCGUI hMTree,HXCGUI nodeHandle,HXCGUI *outNodeHandle)
{
	if(nodeHandle && outNodeHandle  && ((multiTree_node_*)nodeHandle)->pDown)
	{
		*outNodeHandle=((multiTree_node_*)nodeHandle)->pDown;
		return ((multiTree_node_*)nodeHandle)->pDown->id;
	}
	return -1;
}

HXCGUI XMTree_HandleGetFirstChildNode(HXCGUI hMTree,HXCGUI hParentNode)
{
	if(hMTree && hParentNode)
	{
		return ((multiTree_node_*)hParentNode)->pChild;
	}
	return NULL;
}

multiTree_node_ *MTree_GetNode(multiTree_ *pObject,int nodeID)  //��ȡ�ڵ�
{
	if(nodeID<XMTREE_ROOT) return NULL;

	return MTree_TraverseNode(pObject->pRootNode,nodeID);
}

multiTree_node_ *MTree_TraverseNode(multiTree_node_ *pNode,int nodeID)
{
	if(NULL==pNode) return NULL;

	if(pNode->id==nodeID) return pNode;

	multiTree_node_ *pCurNode=NULL;

	pCurNode=MTree_TraverseNode(pNode->pChild,nodeID);
	if(pCurNode) return pCurNode;

	pCurNode=MTree_TraverseNode(pNode->pDown,nodeID);
	if(pCurNode) return pCurNode;

	return NULL;
}

void MTree_TraverseDestroy(multiTree_node_ *pNode)
{
	if(NULL==pNode) return;

	MTree_TraverseDestroy(pNode->pChild);

	MTree_TraverseDestroy(pNode->pDown);

	//XTRACE("���� : %d \n",pNode->id);
	free(pNode);
}