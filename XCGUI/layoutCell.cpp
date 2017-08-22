/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"



layoutCell_* Cell_Create(HWINDOW hWindow,HELE hPane,align_type_ align)
{
	layoutCell_ *pNew=(layoutCell_*)malloc(sizeof(layoutCell_));
	if(pNew)
	{
		memset(pNew,0,sizeof(layoutCell_));
		pNew->object.type=XC_PANE_CELL;
		pNew->align=align;
		pNew->type;
		//pNew->hWindow=hWindow;
		pNew->hPane=hPane;
		pNew->hDragBar;
	//	pNew->minSize=20;

		pNew->hArrayList=XArray_Create();

		if(hPane)
			((layoutPane_*)hPane)->pCell=pNew;

		return pNew;
	}
	return NULL;
}

void Cell_Destroy(layoutCell_ *pCell)
{
	if(pCell)
	{
		if(pCell->hArrayList)
		{
			XArray_Destroy(pCell->hArrayList);
			pCell->hArrayList=NULL;
			if(pCell->hPane)
			{
				((layoutPane_*)pCell->hPane)->pCell=NULL;
			}
		}
		free(pCell);
	}
}

void Cell_OnSize(layoutCell_ *pCell,HWINDOW hWindow,BOOL bFixedSize) //��������
{
	if(NULL==pCell)
		return ;

	int type=XC_GetObjectType(hWindow);
	if(XC_FRAMEWND==type)
	{
		if(NULL==pCell->pParentCell)
		{
			if(FALSE==Cell_IsChildInLayout(pCell))
				return ;

			XWnd_GetClientRect(hWindow,&pCell->rect);

			frameWnd_ *pFrame=(frameWnd_*)hWindow;
			if(pFrame->hPierLeft)
				pCell->rect.left=((ele_*)pFrame->hPierLeft)->rect.right;

			if(pFrame->hPierTop)
				pCell->rect.top=((ele_*)pFrame->hPierTop)->rect.bottom;

			if(pFrame->hPierRight)
				pCell->rect.right=((ele_*)pFrame->hPierRight)->rect.left;

			if(pFrame->hPierBottom)
				pCell->rect.bottom=((ele_*)pFrame->hPierBottom)->rect.top;

			Cell_OnSize2(pCell, hWindow,TRUE,bFixedSize);
		}
	}else if(XC_FLOATWND==type)
	{
		//	XWnd_GetClientRect(hWindow,&pCell->rect);
		//	Cell_OnSize2(pCell, hWindow,TRUE);
	}
}

void Cell_OnSize2(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust,BOOL bFixedSize) //��������
{
	if(NULL==pCell) return ;

	//pCell->hWindow=hWindow;

	switch(pCell->type)
	{
	case cell_type_top_bottom:
		Cell_OnSize_top_bottom(pCell,hWindow,bAdjust,bFixedSize);
		break;
	case cell_type_left_right:
		Cell_OnSize_left_right(pCell,hWindow,bAdjust,bFixedSize);
		break;
	case cell_type_pane:
		Cell_OnSize_pane(pCell,hWindow,bAdjust);
		break;
	case cell_type_group:
		Cell_OnSize_group(pCell,hWindow,bAdjust);
		break;
	}
}

void Cell_OnSize_top_bottom(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust,BOOL bFixedSize)
{
	//1 ���Ҵ�����ʾ
	//2 �󴰸���ʾ,�Ҳ���ʾ
	//3 �Ҵ�����ʾ,����ʾ
	//4 ������ʾ


	// 1 ���Ҷ�Ϊ����
	// 2 ���Ҷ�Ϊ��
	// 3 ���Ҷ�Ϊcell_type_left_right��cell_type_top_bottom

	// 4 ��Ϊ����,��Ϊ��
	// 5 ��Ϊ����,��Ϊ��

	// 6 ��Ϊ����,��Ϊcell_type_left_right��cell_type_top_bottom
	// 7 ��Ϊ����,��Ϊcell_type_left_right��cell_type_top_bottom

	// 8 ��Ϊ��, ��Ϊcell_type_left_right��cell_type_top_bottom
	// 9 ��Ϊ��, ��Ϊcell_type_left_right��cell_type_top_bottom

	if(FALSE==bAdjust) //������ʾ,����Ҫ����,����Ҫ���ز���Ҫ��ʾ��Ԫ��
	{
		if(pCell->hDragBar)
		{
			XEle_Destroy(pCell->hDragBar);
			pCell->hDragBar=NULL;
		}

		Cell_OnSize2(pCell->pCell1,hWindow,bAdjust,bFixedSize);
		Cell_OnSize2(pCell->pCell2,hWindow,bAdjust,bFixedSize);
		return ;
	}

	BOOL bShowDragBar=FALSE; //�Ƿ���ʾ�϶���

	// 1 ���Ҷ�Ϊ����
	if(cell_type_pane==pCell->pCell1->type && cell_type_pane==pCell->pCell2->type)
	{
		bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
	}else

		// 2 ���Ҷ�Ϊ��
		if(cell_type_group==pCell->pCell1->type && cell_type_group==pCell->pCell2->type)
		{
			bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
		}else

			// 3 ���Ҷ�Ϊcell_type_left_right��cell_type_top_bottom
			if((cell_type_left_right==pCell->pCell1->type || cell_type_top_bottom==pCell->pCell1->type)&& 
				(cell_type_left_right==pCell->pCell2->type || cell_type_top_bottom==pCell->pCell2->type))
			{
				bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
			}else

				// 4 ��Ϊ����,��Ϊ��
				if(cell_type_pane==pCell->pCell1->type && cell_type_group==pCell->pCell2->type)
				{
					bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
				}else

					// 5 ��Ϊ����,��Ϊ��
					if(cell_type_group==pCell->pCell1->type && cell_type_pane==pCell->pCell2->type)
					{
						bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
					}else

						// 6 ��Ϊ����,��Ϊcell_type_left_right��cell_type_top_bottom
						if(cell_type_pane==pCell->pCell1->type && (cell_type_left_right==pCell->pCell2->type || cell_type_top_bottom==pCell->pCell2->type))
						{
							bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
						}else

							// 7 ��Ϊ����,��Ϊcell_type_left_right��cell_type_top_bottom
							if(cell_type_pane==pCell->pCell2->type && (cell_type_left_right==pCell->pCell1->type || cell_type_top_bottom==pCell->pCell1->type))
							{
								bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
							}else

								// 8 ��Ϊ��, ��Ϊcell_type_left_right��cell_type_top_bottom
								if(cell_type_group==pCell->pCell1->type && (cell_type_left_right==pCell->pCell2->type || cell_type_top_bottom==pCell->pCell2->type))
								{
									bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
								}else

									// 9 ��Ϊ��, ��Ϊcell_type_left_right��cell_type_top_bottom
									if(cell_type_group==pCell->pCell2->type && (cell_type_left_right==pCell->pCell1->type || cell_type_top_bottom==pCell->pCell1->type))
									{
										bShowDragBar=Cell_OnSize_top_bottom_1(pCell,hWindow,bFixedSize);
									}

									if(bShowDragBar)
									{
										//����϶���
										if(pCell->hDragBar)
										{
											RECT rcBar=pCell->pCell1->rect;
											rcBar.top=rcBar.bottom;
											rcBar.bottom=rcBar.bottom+PANE_DRAGBAR_WIDTH;
											XEle_SetRect(pCell->hDragBar,&rcBar);
										}else
										{
											pCell->hDragBar=DragBar_Create(pCell->pCell1->rect.left,pCell->pCell1->rect.bottom,pCell->pCell1->rect.right-pCell->pCell1->rect.left,PANE_DRAGBAR_WIDTH,TRUE,hWindow);
											DrawBar_SetCell(pCell->hDragBar,pCell);
										}
									}else
									{
										if(pCell->hDragBar)
										{
											XEle_Destroy(pCell->hDragBar);
											pCell->hDragBar=NULL;
										}
									}
}

//�����ʾ�϶�������TRUE,�����෴
BOOL Cell_OnSize_top_bottom_1(layoutCell_ *pCell,HWINDOW hWindow,BOOL bFixedSize)
{

	//1 ���Ҵ�����ʾ
	//2 �󴰸���ʾ,�Ҳ���ʾ
	//3 �Ҵ�����ʾ,����ʾ
	//4 ������ʾ
	RECT rect=pCell->rect;
	BOOL bShow1=Cell_IsChildInLayout(pCell->pCell1);//������Ƿ�����ʾ�Ĵ���
	BOOL bShow2=Cell_IsChildInLayout(pCell->pCell2);//������Ƿ�����ʾ�Ĵ���

	//1 ���Ҵ�����ʾ
	if(bShow1 && bShow2)
	{
		int fixedSize=0;
		if(bFixedSize)
		{
			fixedSize=Cell_OnSize_top_bottom_FixedSize(pCell);
		}

		int  height=rect.bottom-rect.top-PANE_DRAGBAR_WIDTH;

		if(1==fixedSize)
		{
			if(0==pCell->pCell1->rect.top && 0==pCell->pCell1->rect.bottom)
			{
				rect.bottom=height/2;
				pCell->pCell1->rect=rect;

				rect.top=rect.bottom+PANE_DRAGBAR_WIDTH;
				rect.bottom=pCell->rect.bottom;
				pCell->pCell2->rect=rect;
			}else
			{
				int size=pCell->pCell1->rect.bottom-pCell->pCell1->rect.top;
				if(size<height)
					rect.bottom=rect.top+size;
				else
					rect.bottom=rect.bottom-PANE_DRAGBAR_WIDTH-1; //height/2;

				pCell->pCell1->rect=rect;

				rect.top=rect.bottom+PANE_DRAGBAR_WIDTH;
				rect.bottom=pCell->rect.bottom;
				pCell->pCell2->rect=rect;
			}
		}else if(2==fixedSize)
		{
			if(0==pCell->pCell2->rect.top && 0==pCell->pCell2->rect.bottom)
			{
				rect.top=rect.bottom-height/2;
				pCell->pCell2->rect=rect;

				rect.bottom=rect.top-PANE_DRAGBAR_WIDTH;
				rect.top=pCell->rect.top;
				pCell->pCell1->rect=rect;
			}else
			{
				int size=pCell->pCell2->rect.bottom-pCell->pCell2->rect.top;
				if(size<height)
					rect.top=rect.bottom-size;
				else
					rect.top=rect.top+PANE_DRAGBAR_WIDTH+1;

				pCell->pCell2->rect=rect;

				rect.bottom=rect.top-PANE_DRAGBAR_WIDTH;
				rect.top=pCell->rect.top;
				pCell->pCell1->rect=rect;
			}
		}else
		{
			rect.bottom=rect.top+(height*pCell->pCell1->scale)/100;
			pCell->pCell1->rect=rect;

			rect.top=rect.bottom+PANE_DRAGBAR_WIDTH;
			rect.bottom=pCell->rect.bottom;
			pCell->pCell2->rect=rect;
		}
		Cell_OnSize2(pCell->pCell1,hWindow,TRUE,bFixedSize);
		Cell_OnSize2(pCell->pCell2,hWindow,TRUE,bFixedSize);
		return TRUE;
	}else

		//2 �󴰸���ʾ,�Ҳ���ʾ
		if(bShow1)
		{
			pCell->pCell1->rect=rect;
			Cell_OnSize2(pCell->pCell1,hWindow,TRUE,bFixedSize);
			Cell_OnSize2(pCell->pCell2,hWindow,FALSE,bFixedSize);
		}else

			//3 �Ҵ�����ʾ,����ʾ
			if(bShow2)
			{
				pCell->pCell2->rect=rect;
				Cell_OnSize2(pCell->pCell1,hWindow,FALSE,bFixedSize);
				Cell_OnSize2(pCell->pCell2,hWindow,TRUE,bFixedSize);
			}

			return FALSE;
}

//����ֵ:�ĸ�����̶���С,0�ռ䲻��, 1�ϴ��� ,2�´���
int Cell_OnSize_top_bottom_FixedSize(layoutCell_ *pCell)
{
	RECT rect=pCell->rect;
	int width=rect.bottom-rect.top-PANE_DRAGBAR_WIDTH;
	int  index=-1;//�̶���������, 1�ϴ��� ,2�´���
	if(width<100)
	{
		index=0; //�ռ䲻��
		return index;
	}else if(cell_type_pane==pCell->pCell1->type && ((layoutPane_*)pCell->pCell1->hPane)->bFixedSize)
	{
		index=1; //�󴰸�̶�
		return index;
	}else if(cell_type_pane==pCell->pCell2->type && ((layoutPane_*)pCell->pCell2->hPane)->bFixedSize)
	{
		index=2; //�Ҵ���̶�
		return index;
	}else if(cell_type_group==pCell->pCell1->type)
	{
		int count=XArray_GetCount(pCell->pCell1->hArrayList);
		for(int i=0;i<count;i++)
		{
			layoutCell_ *pChid=(layoutCell_*)XArray_GetAt(pCell->pCell1->hArrayList,i);
			if( ((layoutPane_*)pChid->hPane)->bInFrame && ((layoutPane_*)pChid->hPane)->bFixedSize )
			{
				index=1;  //�󴰸�̶�
				return index;
				break;
			}
		}
	}else  if(cell_type_group==pCell->pCell2->type)
	{
		int count=XArray_GetCount(pCell->pCell2->hArrayList);
		for(int i=0;i<count;i++)
		{
			layoutCell_ *pChid=(layoutCell_*)XArray_GetAt(pCell->pCell2->hArrayList,i);
			if( ((layoutPane_*)pChid->hPane)->bInFrame && ((layoutPane_*)pChid->hPane)->bFixedSize )
			{
				index=2; //�Ҵ���̶�
				return index;
			}
		}
	}
	return 0;
}

void Cell_OnSize_left_right(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust,BOOL bFixedSize)
{
	BOOL bShowDragBar=FALSE; //�Ƿ���ʾ�϶���

	// 1 ���Ҷ�Ϊ����
	if(cell_type_pane==pCell->pCell1->type && cell_type_pane==pCell->pCell2->type)
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 2 ���Ҷ�Ϊ��
	else if(cell_type_group==pCell->pCell1->type && cell_type_group==pCell->pCell2->type)
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 3 ���Ҷ�Ϊcell_type_left_right��cell_type_top_bottom
	else if((cell_type_left_right==pCell->pCell1->type || cell_type_top_bottom==pCell->pCell1->type)&& 
		(cell_type_left_right==pCell->pCell2->type || cell_type_top_bottom==pCell->pCell2->type))
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 4 ��Ϊ����,��Ϊ��
	else if(cell_type_pane==pCell->pCell1->type && cell_type_group==pCell->pCell2->type)
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 5 ��Ϊ����,��Ϊ��
	else if(cell_type_group==pCell->pCell1->type && cell_type_pane==pCell->pCell2->type)
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 6 ��Ϊ����,��Ϊcell_type_left_right��cell_type_top_bottom
	else if(cell_type_pane==pCell->pCell1->type && (cell_type_left_right==pCell->pCell2->type || cell_type_top_bottom==pCell->pCell2->type))
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 7 ��Ϊ����,��Ϊcell_type_left_right��cell_type_top_bottom
	else if(cell_type_pane==pCell->pCell2->type && (cell_type_left_right==pCell->pCell1->type || cell_type_top_bottom==pCell->pCell1->type))
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 8 ��Ϊ��, ��Ϊcell_type_left_right��cell_type_top_bottom
	else if(cell_type_group==pCell->pCell1->type && (cell_type_left_right==pCell->pCell2->type || cell_type_top_bottom==pCell->pCell2->type))
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	// 9 ��Ϊ��, ��Ϊcell_type_left_right��cell_type_top_bottom
	else if(cell_type_group==pCell->pCell2->type && (cell_type_left_right==pCell->pCell1->type || cell_type_top_bottom==pCell->pCell1->type))
	{
		bShowDragBar=Cell_OnSize_left_right_1(pCell,hWindow,bFixedSize);
	}

	if(bShowDragBar)
	{
		//����϶���
		if(pCell->hDragBar)
		{
			RECT rcBar=pCell->pCell1->rect;
			rcBar.left=rcBar.right;
			rcBar.right=rcBar.right+PANE_DRAGBAR_WIDTH;
			XEle_SetRect(pCell->hDragBar,&rcBar);
		}else
		{
			pCell->hDragBar=DragBar_Create(pCell->pCell1->rect.right,pCell->pCell1->rect.top,PANE_DRAGBAR_WIDTH,pCell->pCell1->rect.bottom-pCell->pCell1->rect.top,FALSE,hWindow);
			DrawBar_SetCell(pCell->hDragBar,pCell);
		}

	}else
	{
		if(pCell->hDragBar)
		{
			XEle_Destroy(pCell->hDragBar);
			pCell->hDragBar=NULL;
		}
	}
}

BOOL Cell_OnSize_left_right_1(layoutCell_ *pCell,HWINDOW hWindow,BOOL bFixedSize)
{
	//1 ���Ҵ�����ʾ
	//2 �󴰸���ʾ,�Ҳ���ʾ
	//3 �Ҵ�����ʾ,����ʾ
	//4 ������ʾ

	RECT rect=pCell->rect;
	BOOL bShow1=Cell_IsChildInLayout(pCell->pCell1);//������Ƿ�����ʾ�Ĵ���
	BOOL bShow2=Cell_IsChildInLayout(pCell->pCell2);//������Ƿ�����ʾ�Ĵ���

	//1 ���Ҵ�����ʾ
	if(bShow1 && bShow2)
	{
		int  width=rect.right-rect.left-PANE_DRAGBAR_WIDTH;

		int fixedSize=0; //0�ռ䲻��,1�󴰸�̶�,2�Ҵ���̶�
		if(bFixedSize)
		{
			fixedSize=Cell_OnSize_left_right_FixedSize(pCell);
		}

		if(1==fixedSize)
		{
			if(0==pCell->pCell1->rect.left && 0==pCell->pCell1->rect.right)
			{
				rect.right=width/2;
				pCell->pCell1->rect=rect;

				rect.left=rect.right+PANE_DRAGBAR_WIDTH;
				rect.right=pCell->rect.right;
				pCell->pCell2->rect=rect;
			}else
			{
				int size=pCell->pCell1->rect.right-pCell->pCell1->rect.left;
				if(size<width)
					rect.right=rect.left+size;
				else
					rect.right=rect.right-PANE_DRAGBAR_WIDTH-1; //width/2;

				pCell->pCell1->rect=rect;

				rect.left=rect.right+PANE_DRAGBAR_WIDTH;
				rect.right=pCell->rect.right;
				pCell->pCell2->rect=rect;
			}
		}else if(2==fixedSize)
		{
			if(0==pCell->pCell2->rect.left && 0==pCell->pCell2->rect.right)
			{
				rect.left=rect.right-width/2;
				pCell->pCell2->rect=rect;

				rect.right=rect.left-PANE_DRAGBAR_WIDTH;
				rect.left=pCell->rect.left;
				pCell->pCell1->rect=rect;
			}else
			{
				int size=pCell->pCell2->rect.right-pCell->pCell2->rect.left;
				if(size<width)
					rect.left=rect.right-size;
				else //�ռ䲻��
				{
					rect.left=rect.left+PANE_DRAGBAR_WIDTH+1;
				}

				pCell->pCell2->rect=rect;

				rect.right=rect.left-PANE_DRAGBAR_WIDTH;
				rect.left=pCell->rect.left;
				pCell->pCell1->rect=rect;
			}
		}else
		{
			rect.right=rect.left+(width*pCell->pCell1->scale)/100;
			pCell->pCell1->rect=rect;

			rect.left=rect.right+PANE_DRAGBAR_WIDTH;
			rect.right=pCell->rect.right;
			pCell->pCell2->rect=rect;
		}
		Cell_OnSize2(pCell->pCell1,hWindow,TRUE,bFixedSize);
		Cell_OnSize2(pCell->pCell2,hWindow,TRUE,bFixedSize);
		return TRUE;
	}else

		//2 �󴰸���ʾ,�Ҳ���ʾ
		if(bShow1)
		{
			pCell->pCell1->rect=rect;
			Cell_OnSize2(pCell->pCell1,hWindow,TRUE,bFixedSize);
			Cell_OnSize2(pCell->pCell2,hWindow,FALSE,bFixedSize);
		}else

			//3 �Ҵ�����ʾ,����ʾ
			if(bShow2)
			{
				pCell->pCell2->rect=rect;
				Cell_OnSize2(pCell->pCell1,hWindow,FALSE,bFixedSize);
				Cell_OnSize2(pCell->pCell2,hWindow,TRUE,bFixedSize);
			}

			return FALSE;
}

int  Cell_OnSize_left_right_FixedSize(layoutCell_ *pCell)
{
	RECT rect=pCell->rect;
	int height=rect.right-rect.left-PANE_DRAGBAR_WIDTH;
	int  index=-1;//�̶���������, 1�ϴ��� ,2�´���

	if(height<100)
	{
		index=0; //�ռ䲻��
		return index;
	}else if(cell_type_pane==pCell->pCell1->type && ((layoutPane_*)pCell->pCell1->hPane)->bFixedSize)
	{
		index=1; //�󴰸�̶�
		return index;
	}else if(cell_type_pane==pCell->pCell2->type && ((layoutPane_*)pCell->pCell2->hPane)->bFixedSize)
	{
		index=2; //�Ҵ���̶�
		return index;
	}else if(cell_type_group==pCell->pCell1->type)
	{
		int count=XArray_GetCount(pCell->pCell1->hArrayList);
		for(int i=0;i<count;i++)
		{
			layoutCell_ *pChid=(layoutCell_*)XArray_GetAt(pCell->pCell1->hArrayList,i);
			if( ((layoutPane_*)pChid->hPane)->bInFrame && ((layoutPane_*)pChid->hPane)->bFixedSize )
			{
				index=1;  //�󴰸�̶�
				return index;
			}
		}
	}else  if(cell_type_group==pCell->pCell2->type)
	{
		int count=XArray_GetCount(pCell->pCell2->hArrayList);
		for(int i=0;i<count;i++)
		{
			layoutCell_ *pChid=(layoutCell_*)XArray_GetAt(pCell->pCell2->hArrayList,i);
			if( ((layoutPane_*)pChid->hPane)->bInFrame && ((layoutPane_*)pChid->hPane)->bFixedSize )
			{
				index=2; //�Ҵ���̶�
				return index;
			}
		}
	}

	return 0;
}

void Cell_OnSize_pane(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust)
{
	RECT rect=pCell->rect;
	pane_state_ state=((layoutPane_*)pCell->hPane)->state;
	if(pane_state_dock==state) //ͣ������ͷ
	{
		align_type_ align=pCell->align;
		if(align_group_member==pCell->align)
		{
			align=((layoutPane_*)pCell->hPane)->dockAlign;
		}

		switch(align)
		{
		case align_left:
		case align_any:
			{
				rect.right=rect.right-PANE_DRAGBAR_WIDTH;

				//����϶���
				if(pCell->hDragBar)
				{
					RECT rcBar=rect;
					rcBar.left=rect.right;
					rcBar.right=rect.right+PANE_DRAGBAR_WIDTH;
					XEle_SetRect(pCell->hDragBar,&rcBar);
				}else
				{
					pCell->hDragBar=DragBar_Create(rect.right,rect.top,PANE_DRAGBAR_WIDTH,rect.bottom-rect.top,FALSE,hWindow);
					DrawBar_SetCell(pCell->hDragBar,pCell);
					XEle_ShowEle(pCell->hDragBar,FALSE);
				}
			}break;
		case align_top:
			{
				rect.bottom=rect.bottom-PANE_DRAGBAR_WIDTH;

				//����϶���
				if(pCell->hDragBar)
				{
					RECT rcBar=rect;
					rcBar.top=rect.bottom;
					rcBar.bottom=rect.bottom+PANE_DRAGBAR_WIDTH;
					XEle_SetRect(pCell->hDragBar,&rcBar);
				}else
				{
					pCell->hDragBar=DragBar_Create(rect.left,rect.bottom,rect.right-rect.left,PANE_DRAGBAR_WIDTH,TRUE,hWindow);
					DrawBar_SetCell(pCell->hDragBar,pCell);
					XEle_ShowEle(pCell->hDragBar,FALSE);
				}
			}break;
		case align_right:
			{
				//����϶���
				if(pCell->hDragBar)
				{
					RECT rcBar=rect;
					rcBar.right=rect.left+PANE_DRAGBAR_WIDTH;
					XEle_SetRect(pCell->hDragBar,&rcBar);
				}else
				{
					pCell->hDragBar=DragBar_Create(rect.left,rect.top,PANE_DRAGBAR_WIDTH,rect.bottom-rect.top,FALSE,hWindow);
					DrawBar_SetCell(pCell->hDragBar,pCell);
					XEle_ShowEle(pCell->hDragBar,FALSE);
				}
				rect.left=rect.left+PANE_DRAGBAR_WIDTH;
			}break;
		case align_bottom:
			//����϶���
			if(pCell->hDragBar)
			{
				RECT rcBar=rect;
				rcBar.bottom=rect.top+PANE_DRAGBAR_WIDTH;
				XEle_SetRect(pCell->hDragBar,&rcBar);
			}else
			{
				pCell->hDragBar=DragBar_Create(rect.left,rect.top,rect.right-rect.left,PANE_DRAGBAR_WIDTH,TRUE,hWindow);
				DrawBar_SetCell(pCell->hDragBar,pCell);
				XEle_ShowEle(pCell->hDragBar,FALSE);
			}
			rect.top=rect.top+PANE_DRAGBAR_WIDTH;
			break;
		}
	}else if(pane_state_lock==state)
	{
	}
	XEle_SetRect(pCell->hPane,&rect);
}

void Cell_OnSize_group(layoutCell_ *pCell,HWINDOW hWindow,BOOL bAdjust)
{
	if(FALSE==bAdjust)
	{
		//	layoutCell_ *pChild=(layoutCell_*)XArray_GetAt(pCell->hArrayList);
		//	(pChild->hPane)
		//	
		//	if(XEle_IsShowEle(pCell->hTabBar))
		//		XEle_ShowEle(pCell->hTabBar,FALSE);
		return ;
	}

	RECT rc=pCell->rect;

	//�������ʾTAB��
	int  c=XTabBar_GetLabelCount(pCell->hTabBar);
	if(c<1)
	{
		int count=XArray_GetCount(pCell->hArrayList);
		for(int i=0;i<count;i++)
		{
			layoutCell_  *pChild=(layoutCell_*)XArray_GetAt(pCell->hArrayList,i);
			if(((layoutPane_*)pChild->hPane)->bInFrame)
			{
				XEle_SetRect(pChild->hPane,&pCell->rect);
				pChild->rect=pCell->rect;
			}
		}
		if(XEle_IsShowEle(pCell->hTabBar))
		{
			XEle_ShowEle(pCell->hTabBar,FALSE);
		}
		return ;
	}

	//��ʾTAB��
	rc.bottom=pCell->rect.bottom-25;
	int count=XArray_GetCount(pCell->hArrayList);
	for(int i=0;i<count;i++)
	{
		layoutCell_  *pChild=(layoutCell_*)XArray_GetAt(pCell->hArrayList,i);
		if(((layoutPane_*)pChild->hPane)->bInFrame)
		{
			XEle_SetRect(pChild->hPane,&rc);
			pChild->rect=rc;
		}
	}

	rc.top=pCell->rect.bottom-23;
	rc.bottom=pCell->rect.bottom;
	XEle_SetRect(pCell->hTabBar,&rc);

	if(FALSE==XEle_IsShowEle(pCell->hTabBar)) //���TABû����ʾ,������ʾ��
		XEle_ShowEle(pCell->hTabBar,TRUE);
}

BOOL Cell_IsChildInLayout(layoutCell_ *pCell) //����ӽڵ㴰���Ƿ��ڲ�����
{
	if(NULL==pCell)
		return FALSE;

	if(cell_type_pane==pCell->type)
	{
		if(((layoutPane_*)pCell->hPane)->bInFrame)
			return TRUE;
	}else if(cell_type_group==pCell->type)
	{
		int count =XArray_GetCount(pCell->hArrayList);
		layoutCell_ *pChild=NULL;
		for(int i=0;i<count;i++)
		{
			pChild=(layoutCell_*)XArray_GetAt(pCell->hArrayList,i);
			if(((layoutPane_*)pChild->hPane)->bInFrame)
				return TRUE;
		}
	}

	if(TRUE==Cell_IsChildInLayout(pCell->pCell1))
		return TRUE;
	if(TRUE==Cell_IsChildInLayout(pCell->pCell2))
		return TRUE;

	return FALSE;
}

void Cell_OnSize_FloatWnd(layoutCell_ *pCell,HWINDOW hWindow) //�������ڵ���
{
	XWnd_GetClientRect(hWindow,&pCell->rect);
	if(cell_type_group==pCell->type)
	{
		Cell_OnSize_FloatWnd_Group(pCell);
	}else if(cell_type_pane==pCell->type)
	{
		Cell_OnSize_FloatWnd_Pane(pCell);
	}
}

void Cell_OnSize_FloatWnd_Group(layoutCell_ *pCell)
{
	RECT rc=pCell->rect;

	//�������ʾTAB��
	int  c=XTabBar_GetLabelCount(pCell->hTabBar);
	if(c<1)
	{
		int count=XArray_GetCount(pCell->hArrayList);
		for(int i=0;i<count;i++)
		{
			layoutCell_  *pChild=(layoutCell_*)XArray_GetAt(pCell->hArrayList,i);
			XEle_SetRect(pChild->hPane,&pCell->rect);
			pChild->rect=pCell->rect;
		}
		if(XEle_IsShowEle(pCell->hTabBar))
		{
			XEle_ShowEle(pCell->hTabBar,FALSE);
		}
		return ;
	}

	//��ʾTAB��
	rc.bottom=pCell->rect.bottom-25;
	int count=XArray_GetCount(pCell->hArrayList);
	for(int i=0;i<count;i++)
	{
		layoutCell_  *pChild=(layoutCell_*)XArray_GetAt(pCell->hArrayList,i);
		XEle_SetRect(pChild->hPane,&rc);
		pChild->rect=rc;
	}

	rc.top=pCell->rect.bottom-23;
	rc.bottom=pCell->rect.bottom;
	XEle_SetRect(pCell->hTabBar,&rc);
}

void Cell_OnSize_FloatWnd_Pane(layoutCell_ *pCell)
{
	RECT rect=pCell->rect;
	pane_state_ state=((layoutPane_*)pCell->hPane)->state;
	if(pane_state_float==state)
		XEle_SetRect(pCell->hPane,&rect);
}

/////////////�����϶���/////////////////////////////////////////////////////////////////

HELE DragBar_Create(int x,int y,int cx,int cy,BOOL bHorizontal,HWINDOW hWindow)
{
	layout_dragBar_ *pNew=(layout_dragBar_*)malloc(sizeof(layout_dragBar_));
	if(pNew)
	{
		memset(pNew,0,sizeof(layout_dragBar_));

		DragBar_Init((HELE)pNew,x,y,cx,cy,XC_DRAGBAR,bHorizontal,hWindow);

		return (HELE)pNew;
	}
	return NULL;
}

void DragBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,BOOL bHorizontal,HWINDOW hWindow)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hWindow);

	AddTypeDebug(hEle,XC_DRAGBAR);

	((layout_dragBar_*)hEle)->bHorizontal=bHorizontal;

	XEle_EnableBorder(hEle,false);
	XEle_SetBkColor(hEle,RGB(220,220,220));

	XEle_RegisterMessage(hEle,XM_LBUTTONDOWN,DragBar_EleLButtonDown);
	XEle_RegisterMessage(hEle,XM_LBUTTONUP,DragBar_EleLButtonUp);
	XEle_RegisterMessage(hEle,XM_MOUSEMOVE,DragBar_EleMouseMove);
}

void DrawBar_SetCell(HELE hEle,layoutCell_ *pCell)
{
	((layout_dragBar_*)hEle)->pCell=pCell;
}

BOOL CALLBACK DragBar_EleLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	((layout_dragBar_*)hEle)->bDown=TRUE;
	XEle_SetCapture(hEle);

	if(((layout_dragBar_*)hEle)->bHorizontal)
		SetCursor(LoadCursor(NULL,IDC_SIZENS));
	else
		SetCursor(LoadCursor(NULL,IDC_SIZEWE));

	return FALSE;
}

//��굯��
BOOL CALLBACK DragBar_EleLButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
	if(((layout_dragBar_*)hEle)->bDown)
	{
		((layout_dragBar_*)hEle)->bDown=FALSE;
		XEle_ReleaseCapture(hEle);
	}
	return FALSE;
}

//����ƶ�
BOOL CALLBACK DragBar_EleMouseMove(HELE hEle,UINT flags,POINT *pPt)
{
	layout_dragBar_* pDrawBar=(layout_dragBar_*)hEle;

	if(FALSE==pDrawBar->bDown)
	{
		if(((layout_dragBar_*)hEle)->bHorizontal)
			SetCursor(LoadCursor(NULL,IDC_SIZENS));
		else
			SetCursor(LoadCursor(NULL,IDC_SIZEWE));
		return FALSE;
	}

	HWINDOW hWindow=XEle_GetHWindow(hEle);
	if(pDrawBar->bHorizontal)
	{
		POINT pt=*pPt;
		XEle_PointToWndClient(hEle,&pt);

		layoutPane_ *pPane=(layoutPane_*)pDrawBar->pCell->hPane;
		if(pPane && pane_state_dock==pPane->state)
		{
			RECT rcClient;
			XFrameWnd_GetLayoutAreaRect(hWindow,&rcClient);
			if(align_bottom==pPane->dockAlign)
			{
				int size=pt.y-PANE_DRAGBAR_WIDTH;
				if(size>(rcClient.top+80) && size<(rcClient.bottom-80))
					pDrawBar->pCell->rect.top=size;
			}else
			{
				int size=pt.y+PANE_DRAGBAR_WIDTH;
				if(size>(rcClient.top+80) && size<(rcClient.bottom-80))
					pDrawBar->pCell->rect.bottom=size;
			}

			Cell_OnSize2(pDrawBar->pCell,hWindow,TRUE,TRUE);
			XWnd_RedrawWnd(hWindow);
		}else
		{
			int height=pDrawBar->pCell->rect.bottom-pDrawBar->pCell->rect.top-PANE_DRAGBAR_WIDTH;

			int scale=50;
			int size=pt.y-pDrawBar->pCell->rect.top;
			if(0!=height && 0!=size)
			{
				scale=(int)(((size)/(double)height)*100);
			}

			if(scale>10 && scale<90)
			{
				pDrawBar->pCell->pCell1->scale=scale;

				//	if(cell_type_pane==pDrawBar->pCell->pCell1->type && ((layoutPane_*)pDrawBar->pCell->pCell1->hPane)->bFixedSize)
				//	{
				pDrawBar->pCell->pCell1->rect.bottom=pt.y;
				//	}else if(cell_type_pane==pDrawBar->pCell->pCell2->type && ((layoutPane_*)pDrawBar->pCell->pCell2->hPane)->bFixedSize)
				//	{
				pDrawBar->pCell->pCell2->rect.top=pDrawBar->pCell->pCell2->rect.bottom-(pDrawBar->pCell->pCell2->rect.bottom-pt.y)+PANE_DRAGBAR_WIDTH;//-pDrawBar->pCell->rect.left);
				//	}

				Cell_OnSize2(pDrawBar->pCell,hWindow,TRUE,TRUE);

				RECT rcDraw=pDrawBar->pCell->rect;
				int left=XWnd_GetClientLeft(hWindow);
				int top=XWnd_GetClientTop(hWindow);

				rcDraw.left+=left;
				rcDraw.right+=left;
				rcDraw.top+=top;
				rcDraw.bottom+=top;

				XWnd_RedrawWndRect(hWindow,&rcDraw);
			}
		}
	}else
	{
		POINT pt=*pPt;
		XEle_PointToWndClient(hEle,&pt);

		layoutPane_ *pPane=(layoutPane_*)pDrawBar->pCell->hPane;
		if(pPane && pane_state_dock==pPane->state)
		{
			RECT rcClient;
			XFrameWnd_GetLayoutAreaRect(hWindow,&rcClient);
			if(align_right==pPane->dockAlign)
			{
				int size=pt.x-PANE_DRAGBAR_WIDTH;
				if(size>(rcClient.left+80) && size<(rcClient.right-80))
					pDrawBar->pCell->rect.left=size;
			}else
			{
				int size=pt.x+PANE_DRAGBAR_WIDTH;
				if(size>(rcClient.left+80) && size<(rcClient.right-80))
					pDrawBar->pCell->rect.right=size;
			}

			Cell_OnSize2(pDrawBar->pCell,hWindow,TRUE,TRUE);
			XWnd_RedrawWnd(hWindow);
		}else
		{
			int width=pDrawBar->pCell->rect.right-pDrawBar->pCell->rect.left-PANE_DRAGBAR_WIDTH;

			int scale=50;
			int size=pt.x-pDrawBar->pCell->rect.left;
			if( 0!=width && 0!=size)
			{
				scale=(int)(((size)/(double)width)*100);
			}
			
			if(scale>10 && scale<90)
			{
				pDrawBar->pCell->pCell1->scale=scale;

				//	if(cell_type_pane==pDrawBar->pCell->pCell1->type && ((layoutPane_*)pDrawBar->pCell->pCell1->hPane)->bFixedSize)
				//	{
				pDrawBar->pCell->pCell1->rect.right=pt.x;
				//	}else if(cell_type_pane==pDrawBar->pCell->pCell2->type && ((layoutPane_*)pDrawBar->pCell->pCell2->hPane)->bFixedSize)
				//	{
				pDrawBar->pCell->pCell2->rect.left=pDrawBar->pCell->pCell2->rect.right-(pDrawBar->pCell->pCell2->rect.right-pt.x)+PANE_DRAGBAR_WIDTH;//-pDrawBar->pCell->rect.left);
				//	}

				Cell_OnSize2(pDrawBar->pCell,hWindow,TRUE,TRUE);

				RECT rcDraw=pDrawBar->pCell->rect;
				int left=XWnd_GetClientLeft(hWindow);
				int top=XWnd_GetClientTop(hWindow);

				rcDraw.left+=left;
				rcDraw.right+=left;
				rcDraw.top+=top;
				rcDraw.bottom+=top;

				XWnd_RedrawWndRect(hWindow,&rcDraw);
			}
		}
	}

	return FALSE;
}
