#pragma once

//��ܴ���ͣ����ͷ

struct pier_item_gtoup_;
struct pier_item_gtoup_child_
{
	layoutCell_ *pCell;
	HELE        hButton;
	pier_item_gtoup_ *Parent;
};

struct pier_item_gtoup_
{
	int  type;   //����, ��һ����1,������2
	pier_item_gtoup_child_  Child; //����ǵ�һ������Ч

	HARRAY  hArrayList;     //�������Ա pier_item_gtoup_child_*
};

struct pier_
{
	ele_  ele; //�̳�
	//---------------------
	align_type_   align; //��ͷ����
	HARRAY        hArrayList; //��Ա��� pier_item_gtoup_*

	HFONTX  hFontX;
};


HELE Pier_Create(align_type_ align,HWINDOW hWindow);
void Pier_AddCell(HELE hEle, layoutCell_ *pCell);  //���Ӵ�����ͷ
void Pier_AddCellGroup(HELE hEle, layoutCell_ *pGroupCell); //�����鵽��ͷ

void Pier_RemoveCell(HELE hEle, layoutCell_ *pCell); //�Ƴ�����
void Pier_RemoveCellGroup(HELE hEle, layoutCell_ *pCell); //�Ƴ���

void Pier_SetCheck(HELE hEle,layoutCell_ *pCell);

//˽�з���
void Pier_Init(pier_ *pPier,int eleType,HWINDOW hWindow);
void Pier_AdjustLayout(HELE hEle);
void Pier_AdjustLayout_Left(HELE hEle);
void Pier_AdjustLayout_Top(HELE hEle);
void Pier_AdjustLayout_Right(HELE hEle);
void Pier_AdjustLayout_Bottom(HELE hEle);

void CALLBACK Pier_OnEventDestroy(HELE hEle);
BOOL CALLBACK Pier_Btn_OnClick(HELE hEle,HELE hEventEle);


BOOL CALLBACK Pier_Btn_OnEleDraw(HELE hEle,HDRAW hDraw); //��ť�Ի�
