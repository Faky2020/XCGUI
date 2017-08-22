/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//���ֵ�Ԫ��

enum cell_type_
{
	cell_type_left_right=2,
	cell_type_top_bottom,
	cell_type_pane,
	cell_type_group,
};

#define PANE_DRAGBAR_WIDTH  6  //�϶������
#define FRAME_PIER_WIDTH    25  //ͣ����ͷ���

struct layoutCell_ //���ֵ�Ԫ��
{
	object_ object;
	//-----------------------------------
	align_type_  align; //��Ԫ����뷽ʽ
	cell_type_   type;  //��Ԫ������

	HELE	  hPane;        //��Ԫ����䴰��,�������ĩ�˵�Ԫ��,��ôΪ��
	HELE	  hDragBar;     //��Ԫ���϶���

	RECT	  rect;         //��Ԫ������,���ڿͻ�������

//	int       minSize;      //�������С���,���ƴ�����϶���Χ

	layoutCell_  *pParentCell; //����Ԫ��
	layoutCell_  *pCell1;      //�ӵ�Ԫ��1
	layoutCell_  *pCell2;      //�ӵ�Ԫ��2
	int  scale;        //��һ����Ԫ����ռ���� 0-100

	//����,��Ϊ��ʱ��Ч
	HARRAY   hArrayList; //���Ա�б�,layoutCell_*
	HELE     hTabBar;    //��TABԪ��
};

layoutCell_* Cell_Create(HWINDOW hWindow,HELE hPane,align_type_ align);


//�Ƿ���̶���С״̬
void Cell_OnSize(layoutCell_ *pCell,HWINDOW hWindow,BOOL bFixedSize=FALSE); //��������
void Cell_OnSize2(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust,BOOL bFixedSize=FALSE); //��������

void Cell_OnSize_top_bottom(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust,BOOL bFixedSize);
BOOL Cell_OnSize_top_bottom_1(layoutCell_ *pCell,HWINDOW hWindow,BOOL bFixedSize);
int  Cell_OnSize_top_bottom_FixedSize(layoutCell_ *pCell);

void Cell_OnSize_left_right(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust,BOOL bFixedSize);
BOOL Cell_OnSize_left_right_1(layoutCell_ *pCell,HWINDOW hWindow,BOOL bFixedSize);
int  Cell_OnSize_left_right_FixedSize(layoutCell_ *pCell);

void Cell_OnSize_pane(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust);
void Cell_OnSize_group(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust);

BOOL Cell_IsChildInLayout(layoutCell_ *pCell); //����ӽڵ㴰���Ƿ��ڲ�����

void Cell_OnSize_FloatWnd(layoutCell_ *pCell,HWINDOW hWindow); //�������ڵ���
void Cell_OnSize_FloatWnd_Group(layoutCell_ *pCell);
void Cell_OnSize_FloatWnd_Pane(layoutCell_ *pCell);

void Cell_Destroy(layoutCell_ *pCell);



////////////////////////////////////////////////////////////////
//�����϶���

struct  layout_dragBar_
{
	ele_  ele; //�̳�
	//-------------------------------
	BOOL  bHorizontal; //ˮƽTRUE ,��ֱFALSE
	BOOL  bDown;
	layoutCell_  *pCell; //���ֵ�Ԫ��
};


HELE DragBar_Create(int x,int y,int cx,int cy,BOOL bHorizontal,HWINDOW hWindow);

void DrawBar_SetCell(HELE hEle,layoutCell_ *pCell);


void DragBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,BOOL bHorizontal,HWINDOW hWindow);


//�ص�����
BOOL CALLBACK DragBar_EleLButtonDown(HELE hEle,UINT flags,POINT *pPt);//��갴��
BOOL CALLBACK DragBar_EleLButtonUp(HELE hEle,UINT flags,POINT *pPt); //��굯��
BOOL CALLBACK DragBar_EleMouseMove(HELE hEle,UINT flags,POINT *pPt);//����ƶ�