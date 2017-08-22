/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//���ڶ������Ķ����--------------------------

/**************************
     N-----N-----N
	 |     |
     |     N
     |     |
	 |     N
     |
	 N-----N
	 |     |
	 N     N 
	 |
     N
****************************/

//Multi-tree

struct multiTree_node_
{
	//�û�����
	int    id;     //�ڵ�ID,�����ظ�,ֵ���ڵ���0
	void   *pData; //����

	//----------------

	multiTree_node_  *pParentItem; //����    ���ڶ�����ĸ��ڵ�
	multiTree_node_  *pParentNode; //���ڵ�  ���ڶ������ĸ��ڵ�

	multiTree_node_  *pUp;         //�Ͻڵ�
	multiTree_node_  *pDown;       //�½ڵ�
	multiTree_node_  *pChild;      //�ӽڵ�
	multiTree_node_  *pChildEnd;   //�ýڵ����һ���ӽڵ�����һ���ڵ�
};

struct multiTree_node_info_
{	
	//�û�����
	int    id;      //�ڵ�ID,�����ظ�,ֵ���ڵ���0
	void   *pData;  //����
	HXCGUI  hNode;  //�ڵ���
};

struct  multiTree_
{
	multiTree_node_  *pRootNode;    //���ڵ㿪ʼ�ڵ�
	multiTree_node_  *pRootNodeEnd; //���ڵ�ĩβ�ڵ�

	void  *pTraverseData; //���ݱ�����ʱָ��
};

HXCGUI XMTree_Create();


//����      : ��ӽڵ㵽��ǰ��ĩβ
//hMTree    : �����
//parentID  : ���ڵ�ID
//pNodeData : ����ڵ�����
//nodeID    : ����ڵ�ID
BOOL XMTree_AddNode(HXCGUI hMTree,int parentID,void *pNodeData,int nodeID); //��ӽڵ�


//����: ���뵽ָ���ڵ�ǰ��,��ǰ��λ��
//pNodeData  : �ڵ�����
//nodeID     : �ڵ�ID
//insertID   : ����IDΪ��insertID�ڵ�ǰ��λ��
void XMTree_InsertNode(HXCGUI hMTree,void *pNodeData,int nodeID,int insertID);

//����      : �����ӽڵ�
//hMTree    : �����
//parentID  : ���ڵ�ID
//pNodeData : ����ڵ�����
//nodeID    : ����ڵ�ID
//insertID  : ���뵽ָ��ID�ڵ�ǰ��
//void XMTree_InsertChildNode(HXCGUI hMTree,int parentID,void *pNodeData,int nodeID,int insertID);


//����      : �����ӽڵ㵽��λ
//hMTree    : �����
//parentID  : ���ڵ�ID
//pNodeData : ����ڵ�����
//nodeID    : ����ڵ�ID
//void XMTree_InsertChildNodeBegin(HXCGUI hMTree,int parentID,void *pNodeData,int nodeID);

//ɾ���ڵ�,������ӽڵ�ͬʱɾ��
void XMTree_DeleteNode(HXCGUI hMTree,int nodeID);

//��ȡ�ڵ�����
void *XMTree_GetNodeData(HXCGUI hMTree,int nodeID);

//����     : ��ȡ��һ���ӽڵ�
//parentID : ���ڵ�ID
void *XMTree_GetFirstChildNodeData(HXCGUI hMTree,int parentID);


//����     : ��ȡ��ǰ����һ���ڵ�
//nodeID   : ��ǰ�ڵ�ID
//����ֵ   : nodeID�¸��ڵ������,���û�з���NULL
void *XMTree_GetNextNodeData(HXCGUI hMTree,int nodeID);

//��ȡ�ڵ�����,��ȡnodeID�ڵ��µ�������,����nodeID�ڵ�
int  XMTree_GetNodeCount(HXCGUI hMTree,int nodeID);


//����     : ������һ��ڵ�,�������ӽڵ�
//parentID : ��ʼ�����ĸ��ڵ�ID
//����ֵ   : Ҫ�����Ľڵ�����,���������ڵ�,���ʧ�ܷ���-1
int  XMTree_BeginTraverse(HXCGUI hMTree,int parentID);//��ʼ����
void *XMTree_GetTraverseData(HXCGUI hMTree,int index);
void XMTree_EndTraverse(HXCGUI hMTree); //��������


//����     : ������һ��ڵ�,�������ӽڵ�
//parentID : ��ʼ�����ĸ��ڵ�ID
//����ֵ   : Ҫ�����Ľڵ�����,���ʧ�ܷ���-1
int  XMTree_BeginTraverseInfo(HXCGUI hMTree,int parentID);//��ʼ����
void *XMTree_GetTraverseInfo(HXCGUI hMTree,int index,HXCGUI *hOutNode=NULL,int *outID=NULL);
void XMTree_EndTraverseInfo(HXCGUI hMTree); //��������


//���������ӽڵ�
int  XMTree_BeginTraverseAll(HXCGUI hMTree);//��ʼ����
void *XMTree_GetTraverseAll(HXCGUI hMTree,int index);
void XMTree_EndTraverseAll(HXCGUI hMTree); //��������

//�����ڵ����ݵ�����
void MTree_TraverseNodeDataToArray(multiTree_node_ *pNode,void **pArray);

//����ڵ�����,�ýڵ��µ����нڵ�,��������ڵ�,
int  MTree_GetNodeCount(multiTree_node_  *pNode);


//���ٸ�ʵ�����
void XMTree_Destroy(HXCGUI hMTree); //����



//����API,ͨ���ڵ�������,�Ա���ʼ���-------------------------------

//����    : ��ȡ�ڵ���,ͨ�����������ȡ������ٶ�
//����ֵ  : nodeID�ڵ���
HXCGUI XMTree_GetNodeHandle(HXCGUI hMTree,int nodeID);



//����           : ��ȡ��ǰ����һ���ڵ���Ϣ
//nodeHandle     : ��ǰ�ڵ���
//outNodeHandle  : �����¸��ڵ���
//����ֵ         : �¸��ڵ�ID, ���󷵻�-1
int XMTree_GetHandleNextNodeInfo(HXCGUI hMTree,HXCGUI nodeHandle,HXCGUI *outNodeHandle);



//����     : ��ȡ��һ���ӽڵ���
//hParentNode : ���ڵ���
HXCGUI XMTree_HandleGetFirstChildNode(HXCGUI hMTree,HXCGUI hParentNode);

//˽�з���:-----------------------------------*****************************************************


//����    : ��ȡָ���ڵ�
//nodeID  : ��ȡ�ڵ�ID
multiTree_node_ *MTree_GetNode(multiTree_ *pObject,int nodeID);  //��ȡ�ڵ�
//����:�������ҽڵ�
multiTree_node_ *MTree_TraverseNode(multiTree_node_ *pNode,int nodeID);


//����:�������ٽڵ�
//pNode:Ҫ���ٵĽڵ�,ͬʱ�����ӽڵ�
void MTree_TraverseDestroy(multiTree_node_ *pNode);







/*
HXCGUI XMTree_FindNode(HXCGUI hMTree,int id); //���ҽڵ�

int  XMTree_BeginTraverse(HXCGUI hMTree,int parentID);//��ʼ����
void XMTree_EndTraverse(HXCGUI hMTree); //��������
*/
