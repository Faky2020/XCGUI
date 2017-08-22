/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"
#include "edit.h"

/// @defgroup edit �༭��(Edit)
/// @ingroup groupElements
/// @{

/// @brief �����༭��Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XEdit_Create(int x, int y, int cx, int cy,HXCGUI hParent)
{
	edit_ *pEdit=(edit_*)malloc(sizeof(edit_));
	if (pEdit)
	{
		memset(pEdit,0,sizeof(edit_));
		Edit_Init((HELE)pEdit,x,y,cx,cy,XC_EDIT,hParent);
	}
	return (HELE)pEdit;
}

void Edit_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	SView_Init( hEle,x,y,cx,cy,eleType,hParent);

	AddTypeDebug(hEle,XC_EDIT);

	edit_  *pEdit=EDIT(hEle);
	pEdit->spacLeft=3;
	pEdit->spacTop=3;
	pEdit->hArrayEdit=XArray_Create();
	pEdit->bNumber=FALSE;
	pEdit->bMenu=TRUE;
	pEdit->caretWidth=1;
	pEdit->selColor=RGB(83,132,213);

	HDC hdc = GetDC(NULL);
	HGDIOBJ hOld=SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX) );

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	EDIT(hEle)->rowHeight=tm.tmHeight; //�и�

	SIZE size;
	GetTextExtentPoint32W(hdc,L"*",1,&size);
	EDIT(hEle)->sizePass.cx=size.cx;
	EDIT(hEle)->sizePass.cy=size.cy;

	SelectObject(hdc, hOld);
	ReleaseDC(NULL,hdc);

	editStrList_  *pList=(editStrList_*)malloc(sizeof(editStrList_));
	memset(pList,0,sizeof(editStrList_));

	pList->hString=XStr_Create();
	XArray_Add(pEdit->hArrayEdit,pList);

	SCROLLVIEW(hEle)->sizeLine.cy=tm.tmHeight;
	SCROLLVIEW(hEle)->sizeLine.cx=tm.tmMaxCharWidth;

	if(cy<EDIT(hEle)->rowHeight*3)  //���ع�����
	{
		XSView_EnableHScroll(hEle,FALSE);
		XSView_EnableVScroll(hEle,FALSE);
	}

	HELE hView=((scrollView_*)hEle)->hView;
	XEle_RegisterMessage(hView,XM_LBUTTONDOWN,Edit_OnLButtonDown_View);
	XEle_RegisterMessage(hView,XM_LBUTTONUP,Edit_OnLButtonUp_View);
	XEle_RegisterMessage(hView,XM_MOUSEMOVE,Edit_OnMouseMove_View);
	XEle_RegisterMessage(hView,XM_RBUTTONDOWN,Edit_OnRButtonDown_View);
	XEle_RegisterMessage(hView,XM_RBUTTONUP,Edit_OnRButtonUp_View);

	XSView_SetDrawScrollView(hEle,Edit_OnDrawScrollView);

	XEle_RegisterMessage(hEle,XM_PAINT,Edit_OnDraw);

	XEle_RegisterEvent(hEle,XE_HSCROLLVIEW,Edit_OnEventHScrollView);
	XEle_RegisterEvent(hEle,XE_VSCROLLVIEW,Edit_OnEventVScrollView);
	XEle_RegisterEvent(hEle,XE_SETFOCUS,Edit_OnEventSetFocus);
	XEle_RegisterEvent(hEle,XE_KILLFOCUS,Edit_OnEventKillFocus);
	XEle_RegisterEvent(hEle,XE_CHAR,Edit_OnEventChar);
	XEle_RegisterEvent(hEle,XE_KEYDOWN,Edit_OnEventKeyDown);
	XEle_RegisterEvent(hEle,XE_MENUSELECT,Edit_OnEventMenuSelect);
	XEle_RegisterEvent(hEle,XE_DESTROY,Edit_OnDestroy);
	XEle_RegisterEvent(hEle,XE_SIZE,Edit_OnEventSize);
	XEle_RegisterEvent(hEle,XE_SETFONT,Edit_OnEventSetFont);

	XEle_RegisterEvent(hEle,XE_MOUSESTAY,Edit_OnEventMouseStay);
	XEle_RegisterEvent(hEle,XE_MOUSELEAVE,Edit_OnEventMouseLeave);
}

void CALLBACK Edit_OnDestroy(HELE hEle)  //����
{
	int count=XArray_GetCount(EDIT(hEle)->hArrayEdit);
	editStrList_ *pObj=NULL;
	for(int i=0;i<count;i++)
	{
		pObj=Array_GetAtEdit(EDIT(hEle)->hArrayEdit,i);
		if(pObj->hString)
			XStr_Destroy(pObj->hString);
		free(pObj);
	}
	XArray_Destroy(EDIT(hEle)->hArrayEdit);

	if(EDIT(hEle)->hImage_stay) XImage_Destroy(EDIT(hEle)->hImage_stay);
}

/// @brief ���ñ༭��Ԫ�ض������빦��.
/// @param hEle  Ԫ�ؾ��.
/// @param b    TRUE֧�ֶ�������,�����෴.
void WINAPI XEdit_EnableMultiLine(HELE hEle,BOOL b) //���ö�������
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->bMoreLine=b;
}

/// @brief ����ֻ�������ֹ���.
/// @param hEle  Ԫ�ؾ��.
/// @param bNumber  ���ֵΪTRUEֻ�ܽ�������,�����෴.
void WINAPI XEdit_EnableNumber(HELE hEle,BOOL bNumber) //ֻ����������
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->bNumber=bNumber;
}

/// @brief �༭��Ԫ�������������빦��,����ֻ�ܵ�������.
/// @param hEle  Ԫ�ؾ��.
/// @param bPass  TRUEΪ�����,�����෴.
void WINAPI XEdit_EnablePassBox(HELE hEle,BOOL bPass)   //���������
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->bPass=bPass;
}

/// @brief �༭�����û�ر�����Ҽ������˵�.
/// @param hEle  Ԫ�ؾ��.
/// @param bEnable  ֵΪTRUE����,�����෴.
void WINAPI XEdit_EnablePopupMenu(HELE hEle,BOOL bEnable)  //��������Ҽ��˵�
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->bMenu=bEnable;
}

/// @brief ɾ��ѡ����ı�,��ֻ������ʱ,Ҳ����ɾ���ı�.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_DeleteSelectText(HELE hEle)      //ɾ��ѡ���ı�
{
	IsEditDebug(hEle,__FUNCTION__);

	if(Edit_DeleteSelectText( hEle))
		Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
}

//����ַ����Ƿ�Ϊ����
BOOL Edit_SetText_ExamineStringNumber(HELE hEle,wchar_t *pText)
{
	edit_ *pEdit=EDIT(hEle);

	if(pEdit->bNumber) //����
	{
		wchar_t *pCeck=pText;
		while(pCeck)
		{
			if(0==*pCeck)
				break;

			if((L'\r'!=*pCeck) && (L'\n'!=*pCeck))
			{
				if(*pCeck <48 || *pCeck>57)
				{
					XTRACE("edit ���ܽ����ַ�\n");
					return FALSE;
				}
			}
			pCeck++;
		}
	}
	return TRUE;
}

//����ģʽ
void Edit_SetText_SingleLine(HELE hEle,wchar_t *pText)
{
	edit_ *pEdit=EDIT(hEle);

	wchar_t *pWChar=pText;
	int len=0;
	while(1)  
	{
		if(VK_TAB==*pWChar)//��TAB�滻�ɿո�
			*pWChar=L' ';
		if(L'\n'==*pWChar) //�������нض�
		{
			len=pWChar-pText;
			if( L'\r'==*(pWChar-1) )
			{
				len--;
			}
			break;
		}else if(0==*pWChar)
		{
			len=pWChar-pText;
			break;
		}
		pWChar++;
	}
	if(len>0)
	{
		pEdit->row=0;
		pEdit->rows=0;

		editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row);
		XStr_AddStringLength(pST->hString,pText,len);

		if(pEdit->bPass) //�����
		{
			pST->len=pEdit->sizePass.cx*len;
			pEdit->caretPt.x=pEdit->sizePass.cx*len;
		}else //��������
		{
			SIZE size; //�ַ�������
			HDC hdc=GetDC(NULL);
			HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32W(hdc,pText,len,&size);
			SelectObject(hdc,hOldFont);
			ReleaseDC(NULL,hdc);
			pST->len=size.cx;
			pEdit->caretPt.x+=size.cx;
		}
		pEdit->column=len;
		Edit_SetCaretPos(hEle);
	}else
	{
		//XTRACE("edit ��ֵ\n");
		return;
	}

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);
}

//����ģʽ
void Edit_SetText_MoreLine(HELE hEle,wchar_t *pText)
{
	edit_ *pEdit=EDIT(hEle);

	SIZE size; //�ַ�������
	HDC hdc=GetDC(NULL);
	HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));

	wchar_t *pBegin=pText;
	wchar_t *pWChar=pText;
	while(1)
	{
		if(VK_TAB==*pWChar)//��TAB�滻�ɿո�
			*pWChar=L' ';
		if(L'\n'==*pWChar) //����
		{
			int len=pWChar-pBegin;
			if( L'\r'==*(pWChar-1) )
			{
				len--;
			}
			if(len>0)
			{
				editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row);
				XStr_AddStringLength(pST->hString,pBegin,len);
				//�ַ�������
				GetTextExtentPoint32W(hdc,pBegin,len,&size);
				pST->len=size.cx;

				editStrList_ *pNew=(editStrList_*)malloc(sizeof(editStrList_));
				pNew->hString=XStr_Create();
				pNew->len=0;

				XArray_Add(pEdit->hArrayEdit,pNew);
				pEdit->row++;
				pEdit->rows++;

				pBegin=pWChar+1;
			}else if(0==len)
			{			//XTRACE("����\n");
				editStrList_ *pNew=(editStrList_*)malloc(sizeof(editStrList_));
				pNew->hString=XStr_Create();
				pNew->len=0;

				XArray_Add(pEdit->hArrayEdit,pNew);
				pEdit->row++;
				pEdit->rows++;

				pBegin=pWChar+1;
			}else
			{
				XTRACE("����1\n");
				break;
			}
		}else if(0==*pWChar)
		{
			int len=pWChar-pBegin;
			if(len>0)
			{
				editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row);
				XStr_AddStringLength(pST->hString,pBegin,len);
				//�ַ�������
				GetTextExtentPoint32W(hdc,pBegin,len,&size);
				pST->len=size.cx;
				pEdit->column=len;
			}else if(0==len) //����
			{
			}else
			{
				XTRACE("����2\n");
			}
			break;
		}
		pWChar++;
	}
	SelectObject(hdc,hOldFont);
	ReleaseDC(NULL,hdc);

	//��������
	for(int i=0;i<=pEdit->rows;i++)
	{
		if(Array_GetAtEdit(pEdit->hArrayEdit,i)->len > Array_GetAtEdit(pEdit->hArrayEdit,pEdit->maxLine)->len)
		{
			pEdit->maxLine=i;
		}
	}

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);

	editStrList_ *pSTS=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row);
	pEdit->caretPt.x=pSTS->len;
	pEdit->caretPt.y=pEdit->rows*pEdit->rowHeight;

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
}

/// @brief �����ı�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pText �ı�����.
void WINAPI XEdit_SetText(HELE hEle,wchar_t *pText)  //�����ı�
{
	IsEditDebug(hEle,__FUNCTION__);
	edit_ *pEdit=EDIT(hEle);

	BOOL bSendEvent=FALSE; //�Ƿ����¼�

	if (FALSE==XEdit_IsEmpty(hEle))
	{
		XEdit_DeleteAll(hEle);//����ı�
		bSendEvent=TRUE;
	}
	pEdit->maxLine=0;

	if(NULL==pText) 
	{
		if(bSendEvent)
			Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
		return ;
	}

	if(pEdit->bNumber) //����
	{
		if(FALSE==Edit_SetText_ExamineStringNumber(hEle,pText))
			return;
	}

	if(pEdit->bPass || FALSE==pEdit->bMoreLine) //����� ���� ����
	{
		Edit_SetText_SingleLine(hEle,pText);
		Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
		return ;
	}else
	{
		Edit_SetText_MoreLine(hEle,pText);
		Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
	}
}


/// @brief ������������(int).
/// @param hEle  Ԫ�ؾ��.
/// @param value �ı�����.
void WINAPI XEdit_SetInt(HELE hEle,int value)  //������������
{
	IsEditDebug(hEle,__FUNCTION__);
	wchar_t text[MAX_PATH]={0};
	_itow_s(value,text,10);
	XEdit_SetText(hEle,text);
}

void Edit_InsertText_SingleLine(HELE hEle,wchar_t *pText,wchar_t *pBuf,int row,int column)
{
	edit_ *pEdit=EDIT(hEle);
	wchar_t *pBegin=pText;
	wchar_t *pWChar=pText;
	int len=0;
	while(1)
	{
		if(VK_TAB==*pWChar)//��TAB�滻�ɿո�
			*pWChar=L' ';
		if(L'\n'==*pWChar) //����
		{
			len=pWChar-pBegin;
			if( L'\r'==*(pWChar-1) )
			{
				len--;
			}
			break;
		}else if(0==*pWChar)
		{
			len=pWChar-pBegin;
			break;
		}
		pWChar++;
	}
	if(len>0)
	{
		editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,row);
		XStr_AddStringLength(pST->hString,pBegin,len);

		if(pBuf) //��Ӳ���λ�ú�����ַ���
		{
			XStr_AddString(pST->hString,pBuf);
			free(pBuf);
		}

		if(pEdit->bPass) //�����
		{
			pST->len+=pEdit->sizePass.cx*len;
			pEdit->caretPt.x+=pEdit->sizePass.cx*len;
		}else //��������
		{
			SIZE size; //�ַ�������
			HDC hdc=GetDC(NULL);
			HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32W(hdc,pBegin,len,&size);
			SelectObject(hdc,hOldFont);
			ReleaseDC(NULL,hdc);
			pST->len+=size.cx;
			pEdit->caretPt.x+=size.cx;
		}
		pEdit->column=column+len;
		Edit_SetCaretPos(hEle);
	}else
	{
		XTRACE("����\n"); return;
	}

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);

	//�����ϵ�����������,ˮƽ����
	Edit_ScrollH(hEle);

	XEle_RedrawEle(hEle);
}

void Edit_InsertText_MoreLine(HELE hEle,wchar_t *pText,wchar_t *pBuf,int row,int column)
{
	edit_ *pEdit=EDIT(hEle);
	{
		SIZE size; //�ַ�������
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));

		wchar_t *pBegin=pText;
		wchar_t *pWChar=pText;
		while(1)
		{
			if(VK_TAB==*pWChar)//��TAB�滻�ɿո�
				*pWChar=L' ';
			if(L'\n'==*pWChar) //����
			{
				int len=pWChar-pBegin;
				if( L'\r'==*(pWChar-1) )
				{
					len--;
				}

				if(len>0)
				{
					editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,row);
					XStr_AddStringLength(pST->hString,pBegin,len);

					wchar_t *pStr=XStr_GetBuffer(pST->hString);
					len=XStr_GetLength(pST->hString);
					//�ַ�������
					GetTextExtentPoint32W(hdc,pStr,len,&size);
					pST->len=size.cx;

					editStrList_ *pNew=(editStrList_*)malloc(sizeof(editStrList_));
					pNew->hString=XStr_Create();
					pNew->len=0;

					XArray_insert(pEdit->hArrayEdit,pNew,row+1);
					row++;
					pEdit->rows++;

					pBegin=pWChar+1;
				}else if(0==len) //����
				{
					//XTRACE("����\n");
					editStrList_ *pNew=(editStrList_*)malloc(sizeof(editStrList_));
					pNew->hString=XStr_Create();
					pNew->len=0;

					XArray_insert(pEdit->hArrayEdit,pNew,row+1);
					row++;
					pEdit->rows++;

					pBegin=pWChar+1;
				}else
				{
					XTRACE("����1\n");
					return ;
				}
			}else if(0==*pWChar)
			{
				int len=pWChar-pBegin;
				if(len>0)
				{
					editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,row);
					XStr_AddStringLength(pST->hString,pBegin,len);

					wchar_t *pStr=XStr_GetBuffer(pST->hString);
					len=XStr_GetLength(pST->hString);
					//���������λ��
					GetTextExtentPoint32W(hdc,pStr,len,&size);
					column=len;
					pEdit->caretPt.x=size.cx;
					pST->len=size.cx;

					if(pBuf) //��Ӳ���λ�ú�����ַ���
					{
						XStr_AddString(pST->hString,pBuf);
						free(pBuf);
						pStr=XStr_GetBuffer(pST->hString);
						len=XStr_GetLength(pST->hString);
						if(pStr) //�ַ�������
						{
							GetTextExtentPoint32W(hdc,pStr,len,&size);
							pST->len=size.cx;
						}
					}
				}else if(0==len) //������
				{
					column=0;
					pEdit->caretPt.x=0;
				}else
				{
					XTRACE("����2\n");
					return ;
				}
				break;
			}
			pWChar++;
		}
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);
	}
	///////////////////////////////////////////////////

	//������ļ��к���бȽ�
	int index=0;
	for(int i=pEdit->row;i<=row;i++)
	{
		if(Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row+index)->len > Array_GetAtEdit(pEdit->hArrayEdit,pEdit->maxLine)->len)
		{
			pEdit->maxLine=pEdit->row+index;
		}
		index++;
	}

	pEdit->row=row;
	pEdit->column=column;

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);

	pEdit->caretPt.y=row*pEdit->rowHeight;
	Edit_SetCaretPos(hEle);

	//�����ϵ�����������,ˮƽ����
	Edit_ScrollH(hEle);
	Edit_ScrollV(hEle);

	//XEle_RedrawEle(hEle);
}

/// @brief �༭������ı�����.
/// @param hEle   Ԫ�ؾ��.
/// @param pText  ������ı�����.
/// @param row    �������λ��,���ֵΪ-1���뵽ĩβ��.
/// @param column  �������λ��,���ֵΪ-1����ĩβ��
void WINAPI XEdit_InsertText(HELE hEle,wchar_t *pText,int row,int column) //�����ı�
{
	IsEditDebug(hEle,__FUNCTION__);

	if(Edit_InsertText(hEle,pText,row,column))
		Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
}

void Edit_GetSelectTextHandle(HELE hEle,HSTRING hString,int beginRow,int endRow,int beginColumn,int endColumn)
{
	edit_ *pEdit=EDIT(hEle);
	int lines=endRow-beginRow;
	//��ʼ��
	HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,beginRow)->hString;
	wchar_t *pBuf=XStr_GetBuffer(hStr);
	XStr_AddString(hString,pBuf+beginColumn);
	XStr_AddString(hString,L"\r\n");

	//�м���
	if(lines>1)
	{
		int rows=lines;
		for(int i=1;i<rows;i++)
		{
			hStr=Array_GetAtEdit(pEdit->hArrayEdit,beginRow+i)->hString;
			pBuf=XStr_GetBuffer(hStr);
			XStr_AddString(hString,pBuf);
			XStr_AddString(hString,L"\r\n");
		}
	}

	//������
	hStr=Array_GetAtEdit(pEdit->hArrayEdit,endRow)->hString;
	pBuf=XStr_GetBuffer(hStr);
	XStr_AddStringLength(hString,pBuf,endColumn);
}

//return:������ݸı䷵��TRUE
BOOL Edit_InsertText(HELE hEle,wchar_t *pText,int row,int column)
{
	edit_ *pEdit=EDIT(hEle);

	if(row<-1 || column<-1)
	{
		return FALSE;
	}
	if(row>pEdit->rows)
	{
		return FALSE;
	}
	if(-1==row) //ĩβ��
	{
		row=pEdit->rows;
	}
	if(-1==column) //ĩβ��
	{
		editStrList_ *pStruct=(editStrList_*)XArray_GetAt(pEdit->hArrayEdit,row);
		column=XStr_GetLength(pStruct->hString);
	}

	if(pEdit->bNumber) //����
	{
		if(FALSE==Edit_SetText_ExamineStringNumber(hEle,pText))
			return FALSE;
	}

	//������λ�ú���������ʱ����
	wchar_t *pBuf=NULL;
	{
		editStrList_ *pSTIN=(editStrList_*)XArray_GetAt(pEdit->hArrayEdit,row);
		if(NULL==pSTIN) return FALSE;

		int len=XStr_GetLength(pSTIN->hString);
		len=len-column; //��Ҫ��������
		if(len>0)
		{
			pBuf=(wchar_t*)malloc((len+1)*sizeof(wchar_t));
			wchar_t *pSrc=XStr_GetBuffer(pSTIN->hString);
			wmemcpy(pBuf,pSrc+column,len);
			pBuf[len]=0;
			XStr_SetLength(pSTIN->hString,column);
		}
	}
	/////////����� -��-��������/////////////////////////////////////////////
	if(pEdit->bPass || FALSE==pEdit->bMoreLine)
	{
		Edit_InsertText_SingleLine(hEle,pText,pBuf,row,column);
	}else
	{
		Edit_InsertText_MoreLine( hEle, pText, pBuf, row, column);
	}
	return TRUE;
}

/// @brief ��ȡѡ����ı�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pOut  �������ݻ�����.
/// @param len   pOut����������,���ַ�Ϊ���ȵ�λ.
void WINAPI XEdit_GetSelectText(HELE hEle,wchar_t *pOut,int len)
{
	IsEditDebug(hEle,__FUNCTION__);

	HSTRING hString=Edit_GetSelectText(hEle);
	if(hString)
	{
		int length=XStr_GetLength(hString);
		if(length>0)
			wcscpy_s(pOut,len,XStr_GetBuffer(hString));

		XStr_Destroy(hString);
	}
}

/// @brief ��ȡ�༭�����ݳ���,�����س����з�,����������ֹ��.
/// @param hEle  Ԫ�ؾ��.
/// @return �����ַ�����.
int WINAPI XEdit_GetTextLength(HELE hEle) //��ȡ���ݳ���
{
	IsEditDebug(hEle,__FUNCTION__);
	edit_ *pEdit=EDIT(hEle);

	int length=0;
	if(0==pEdit->rows) //ֻ��һ��
	{
		editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,0);
		if(0==pST->len)  //û������
		{
			return 0;
		}
	}

	editStrList_ *pST=NULL;
	int count=pEdit->rows+1;
	for(int i=0;i<count;i++)
	{
		pST=Array_GetAtEdit(pEdit->hArrayEdit,i);
		length+= XStr_GetLength(pST->hString);

		if(i!=pEdit->rows) //����
		{
			length+=2;
		}
	}
	return length;
}


/// @brief ��ȡ�ı�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pOut �������ݻ�����.
/// @param len  pOut����������,���ַ�Ϊ���ȵ�λ.
void WINAPI XEdit_GetText(HELE hEle,wchar_t *pOut,int len) //��ȡѡ���ı�
{
	IsEditDebug(hEle,__FUNCTION__);
	edit_ *pEdit=EDIT(hEle);

	if(0==pEdit->rows) //ֻ��һ��
	{
		editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,0);
		if(0==pST->len)  //û������
		{
			return ;
		}
	}

	int pos=0;
	editStrList_ *pST=NULL;
	wchar_t  *pBuf=NULL;
	int count=pEdit->rows+1;
	for(int i=0;i<count;i++)
	{
		pST=Array_GetAtEdit(pEdit->hArrayEdit,i);
		pBuf=XStr_GetBuffer(pST->hString);
		int length=XStr_GetLength(pST->hString);
		if((pos+length)<len)
		{
			wmemcpy(pOut+pos,pBuf,length);
			pos+=length;
		}else
		{
			length=len-pos;
			wmemcpy(pOut+pos,pBuf,length);
			pos+=length;
			break ;
		}
		if(i!=pEdit->rows) //����
		{
			if((pos+1)<len)
			{
				pOut[pos]='\r';
				pos++;
				if((pos+1)<len)
				{
					pOut[pos]='\n';
					pos++;
				}
			}else
				break;
		}
	}
	if(pos<len)
		pOut[pos]=0;
}

/// @brief ��ȡ����(int)����ֵ.
/// @param hEle  Ԫ�ؾ��.
/// @return ������������ֵ.
int WINAPI XEdit_GetInt(HELE hEle) //��ȡ��������
{
	IsEditDebug(hEle,__FUNCTION__);
	wchar_t text[MAX_PATH]={0};
	XEdit_GetText(hEle,text,MAX_PATH-1);
	return _wtoi(text);
}

/// @brief ��ȡ�༭���ı�������.
/// @param hEle  Ԫ�ؾ��.
/// @return �༭���ı�������.
int WINAPI XEdit_GetRowCount(HELE hEle)   //��ȡ������
{
	IsEditDebug(hEle,__FUNCTION__);
	return EDIT(hEle)->rows;
}

/// @brief ��ȡ�༭��ָ�����ַ�����.
/// @param hEle  Ԫ�ؾ��.
/// @param row  �к�,����0������.
/// @return ָ�����ַ�����.
int WINAPI XEdit_GetColumnCount(HELE hEle,int row) //��ȡָ�����ַ���,row=-1ĩβ��;
{
	IsEditDebug(hEle,__FUNCTION__);
	if(row> EDIT(hEle)->rows || row<-1)
	{
		return -1;
	}
	if(-1==row) //ĩβ��
	{
		row=EDIT(hEle)->rows;
	}
	editStrList_ *pStruct=(editStrList_*)XArray_GetAt(EDIT(hEle)->hArrayEdit,row);
	if(pStruct)
	{
		return XStr_GetLength(pStruct->hString);
	}
	return -1;
}

/// @brief ��ȡ�����λ�õ�ǰ��(����0����).
/// @param hEle  Ԫ�ؾ��.
/// @return  �������ǰ��.
int WINAPI XEdit_GetCurrentRow(HELE hEle) //��ȡ�����λ�õ�ǰ��
{
	IsEditDebug(hEle,__FUNCTION__);
	return EDIT(hEle)->row;
}

/// @brief ��ȡ�����λ�õ�ǰ��(����0����).һ���ַ�ռһ��.
/// @param hEle  Ԫ�ؾ��.
/// @return  �������ǰ��.
int WINAPI XEdit_GetCurrentColumn(HELE hEle) //��ȡ�����λ�õ�ǰ��
{
	IsEditDebug(hEle,__FUNCTION__);
	return EDIT(hEle)->column;
}

/// @brief �жϱ༭�������Ƿ�Ϊ��.
/// @param hEle  Ԫ�ؾ��.
/// @return  �������Ϊ�շ���TRUE,�����෴.
BOOL WINAPI XEdit_IsEmpty(HELE hEle) //�ж������Ƿ�Ϊ��
{
	IsEditDebug(hEle,__FUNCTION__);
	edit_ *pEdit=EDIT(hEle);

	int count=XArray_GetCount(pEdit->hArrayEdit);
	if(count<1) return TRUE;

	if(1==count)
	{
		editStrList_ *pItem=(editStrList_*)XArray_GetAt(pEdit->hArrayEdit,0);
		if(NULL==pItem) return TRUE;

		if(NULL==pItem->hString) return TRUE;

		if(XStr_GetLength(pItem->hString)<1)
		{
			return TRUE; //����Ϊ��
		}
	}
	return FALSE;
}

void WINAPI XEdit_DeleteAll(HELE hEle)  //���  ɾ�������ı�
{
	IsEditDebug(hEle,__FUNCTION__);

	edit_ *pEdit=EDIT(hEle);
	int count=Array_GetCount(pEdit->hArrayEdit);
	HSTRING hString;
	for(int i=count-1;i>0;i--)
	{
		hString=Array_GetAtEdit(pEdit->hArrayEdit,i)->hString;
		XStr_Destroy(hString);
		delete Array_GetAtEdit(pEdit->hArrayEdit,i);
		XArray_DeleteIndex(pEdit->hArrayEdit,i);
	}

	hString=Array_GetAtEdit(pEdit->hArrayEdit,0)->hString;
	Array_GetAtEdit(pEdit->hArrayEdit,0)->len=0;
	XStr_Empty(hString);

	if(pEdit->bDrawSelect)
		pEdit->bDrawSelect=FALSE;
	pEdit->row=0;
	pEdit->column=0;
	pEdit->rows=0;

	pEdit->caretPt.x=0;
	pEdit->caretPt.y=0;
	pEdit->maxLine=0;

	Edit_SetCaretPos(hEle);
	Edit_AdjustViewSize(hEle); //������ͼ���ݴ�С
}

/// @brief ��ձ༭������.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_Menu_DeleteAll(HELE hEle) //���  ɾ�������ı�
{
	IsEditDebug(hEle,__FUNCTION__);
	if(EDIT(hEle)->bReadOnly)
		return ;

	XEdit_DeleteAll(hEle);
}

/// @brief ��������뿪״̬��ʾ��ͼƬ.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
void WINAPI XEdit_SetImageLeave(HELE hEle,HIMAGE hImage) //����뿪
{
	IsEditDebug(hEle,__FUNCTION__);
	XSView_SetImage(hEle,hImage);
}

/// @brief ���������Ԫ����ͣ��״̬ʱ��ʾ��ͼƬ.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
void WINAPI XEdit_SetImageStay(HELE hEle,HIMAGE hImage) //���ͣ��
{
	IsEditDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(EDIT(hEle)->hImage_stay,hImage);
}

HSTRING Edit_GetSelectText(HELE hEle)
{
	edit_ *pEdit=EDIT(hEle);
	if(FALSE==pEdit->bDrawSelect) return NULL;

	HSTRING hString=XStr_Create();
	if(pEdit->downRow == pEdit->endRow)  //����
	{
		HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->downRow)->hString;
		wchar_t *pBuf=XStr_GetBuffer(hStr);
		if(pEdit->downX<pEdit->endX) //���ѡ��
		{
			int len=pEdit->endColumn-pEdit->downColumn;
			XStr_AddStringLength(hString,pBuf+pEdit->downColumn,len);
		}else //��ǰѡ��
		{
			int len=pEdit->downColumn-pEdit->endColumn;
			XStr_AddStringLength(hString,pBuf+pEdit->endColumn,len);
		}
	}else if(pEdit->downRow < pEdit->endRow) //����ѡ��
	{
		Edit_GetSelectTextHandle(hEle,hString,pEdit->downRow,pEdit->endRow,pEdit->downColumn,pEdit->endColumn);
	}else   //����ѡ��
	{
		Edit_GetSelectTextHandle(hEle,hString,pEdit->endRow,pEdit->downRow,pEdit->endColumn,pEdit->downColumn);
	}
	return hString;
}

//return:�����ݱ�ɾ������TRUE,û��ɾ���κ����ݷ���FALSE
BOOL Edit_DeleteSelectText(HELE hEle)
{
	edit_ *pEdit=EDIT(hEle);

	if(FALSE==pEdit->bDrawSelect) return FALSE;

	pEdit->bDrawSelect=FALSE;

	if(pEdit->downRow == pEdit->endRow ) //ֻ��һ��
	{
		if(pEdit->downColumn==pEdit->endColumn) //û��ѡ��
		{
			return FALSE;
		}else if( pEdit->downColumn < pEdit->endColumn) //���ѡ��
		{
			HSTRING hString=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->downRow)->hString;
			XStr_DeleteLength(hString,pEdit->downColumn,pEdit->endColumn - pEdit->downColumn);
			pEdit->column=pEdit->downColumn;
			pEdit->caretPt.x=pEdit->downX;

			//����
			wchar_t *pText=XStr_GetBuffer(hString);
			SIZE size={0,0}; 
			if(pText) //�ַ�����
			{
				if(FALSE==pEdit->bPass)
				{
					HDC hdc=GetDC(NULL);
					HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
					GetTextExtentPoint32W(hdc,pText,XStr_GetLength(hString),&size);
					SelectObject(hdc,hOldFont);
					ReleaseDC(NULL,hdc);
				}else
				{
					size.cx=pEdit->sizePass.cx;
				}
			}
			Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len=size.cx;

			Edit_SetCaretPos(hEle);
		}else //��ǰѡ��
		{
			HSTRING hString=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->downRow)->hString;
			XStr_DeleteLength(hString,pEdit->endColumn, pEdit->downColumn - pEdit->endColumn);
			pEdit->column=pEdit->endColumn;
			pEdit->caretPt.x=pEdit->endX;

			//����
			wchar_t *pText=XStr_GetBuffer(hString);
			SIZE size={0,0}; 
			if(pText) //�ַ�����
			{
				if(FALSE==pEdit->bPass)
				{
					HDC hdc=GetDC(NULL);
					HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
					GetTextExtentPoint32W(hdc,pText,XStr_GetLength(hString),&size);
					SelectObject(hdc,hOldFont);
					ReleaseDC(NULL,hdc);
				}else
				{
					size.cx=pEdit->sizePass.cx;
				}
			}
			Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len=size.cx;

			Edit_SetCaretPos(hEle);
		}
	}else if(pEdit->downRow < pEdit->endRow)  //����ѡ��
	{
		Edit_DeleteSelectTextHandle(hEle,pEdit->downRow,pEdit->endRow,
			pEdit->downColumn,pEdit->endColumn,pEdit->downX);
	}else  //����ѡ��
	{
		Edit_DeleteSelectTextHandle(hEle,pEdit->endRow,pEdit->downRow,
			pEdit->endColumn,pEdit->downColumn,pEdit->endX);
	}

	//��м��
	//������ͼ���ݴ�С
	if(pEdit->maxLine>pEdit->rows)
	{
		pEdit->maxLine=0;
	}

	//��������
	if(pEdit->row!=pEdit->maxLine)
	{
		if(Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len > Array_GetAtEdit(pEdit->hArrayEdit,pEdit->maxLine)->len)
		{
			pEdit->maxLine=pEdit->row;
		}
	}

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);

	//�����ϵ�����������,ˮƽ����
	Edit_ScrollH(hEle);
	return TRUE;
}

void Edit_DeleteSelectTextHandle(HELE hEle,int beginRow, int endRow, int beginColumn,int endColumn,int beginX) //ɾ��ѡ���ı�(����ѡ��)
{
	edit_ *pEdit=EDIT(hEle);
	int lines=endRow-beginRow;  //ѡ��������

	if(lines>1)	//ɾ���м���
	{
		int dels=lines-1;
		for(int i=0;i<dels;i++)
		{
			HSTRING hString=Array_GetAtEdit(pEdit->hArrayEdit,beginRow+1)->hString;
			XStr_Destroy(hString);
			delete Array_GetAtEdit(pEdit->hArrayEdit,beginRow+1);
			XArray_DeleteIndex(pEdit->hArrayEdit,beginRow+1);
			endRow--;

			pEdit->rows--;
		}
	}

	//ɾ����ʼ��ѡ���ַ�
	HSTRING hString=Array_GetAtEdit(pEdit->hArrayEdit,beginRow)->hString;
	int len=XStr_GetLength(hString);
	if(beginColumn<len)
	{
		XStr_DeleteFront(hString,beginColumn-1);
	}

	HSTRING hString2=Array_GetAtEdit(pEdit->hArrayEdit,endRow)->hString;
	//ɾ��������ѡ���ַ�
	if(endColumn>0)
	{
		XStr_DeleteBack(hString2,endColumn); //
	}
	//����ʼ��������кϲ�
	wchar_t *pText=XStr_GetBuffer(hString2);
	XStr_AddString(hString,pText);

	//ɾ��������
	XStr_Destroy(hString2);
	delete Array_GetAtEdit(pEdit->hArrayEdit,endRow);
	XArray_DeleteIndex(pEdit->hArrayEdit,endRow);
	pEdit->rows--;

	//����
	pText=XStr_GetBuffer(hString);
	SIZE size={0,0}; 
	if(pText) //�ַ�����
	{
		if(FALSE==pEdit->bPass)
		{
			HDC hdc=GetDC(NULL);
			HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32W(hdc,pText,XStr_GetLength(hString),&size);
			SelectObject(hdc,hOldFont);
			ReleaseDC(NULL,hdc);
		}else
		{
			size.cx=pEdit->sizePass.cx;
		}
	}
	Array_GetAtEdit(pEdit->hArrayEdit,beginRow)->len=size.cx;
	pEdit->row=beginRow;
	pEdit->column=beginColumn;

	pEdit->caretPt.x=beginX;
	pEdit->caretPt.y=pEdit->row*pEdit->rowHeight;
	Edit_SetCaretPos(hEle);
}

/// @brief ���ñ༭��Ԫ��Ϊֻ������,������ͨ���������뼰ճ��.
/// @param hEle  Ԫ�ؾ��.
/// @param bRead TRUEֻ������,�����෴.
void WINAPI XEdit_SetReadOnly(HELE hEle,BOOL bRead)  //����ֻ���ı�
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->bReadOnly=bRead;
}

/// @brief �����ı��������.
/// @param hEle  Ԫ�ؾ��.
/// @param spacing ����С.
void WINAPI XEdit_SetTextSpacingLeft(HELE hEle,int spacing)  //���������������
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->spacLeft=spacing;
}

/// @brief �����ı��϶�����.
/// @param hEle  Ԫ�ؾ��.
/// @param spacing ����С.
void WINAPI XEdit_SetTextSpacingTop(HELE hEle,int spacing)  //���������϶�����
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->spacTop=spacing;
}

/// @brief ���ò����λ��
/// @param hEle  Ԫ�ؾ��.
/// @param line   ��λ��,����0����,0�����һ��.
/// @param column  ��λ��,����0����,0�����һ��.
void WINAPI XEdit_SetPos(HELE hEle,int line,int column) //���ò����λ��
{
	IsEditDebug(hEle,__FUNCTION__);

	if(line<0 || column<0) return;

	edit_ *pObject=EDIT(hEle);

	int lineCount=XArray_GetCount(pObject->hArrayEdit);
	if(line>=lineCount) return ;

	editStrList_ *pInfo=(editStrList_*)XArray_GetAt(pObject->hArrayEdit,line);

	int charLen=XStr_GetLength(pInfo->hString);

	if(column>charLen) return ;

	wchar_t *pStr=XStr_GetBuffer(pInfo->hString);

	SIZE size;
	HDC hdc=GetDC(NULL);
	HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
	int posx=0;
	for(int i=0;i<column;i++)
	{
		GetTextExtentPoint32(hdc,pStr+i,1,&size);
		posx+=size.cx;

	}
	SelectObject(hdc,hOldFont);
	ReleaseDC(NULL,hdc);

	pObject->row=line;
	pObject->column=column;

	pObject->caretPt.x=posx;
	pObject->caretPt.y=pObject->rowHeight*line;

	Edit_SetCaretPos(hEle);

	//������ͼ
	//Edit_ScrollVTop(hEle);
	Edit_ScrollH(hEle);
	Edit_ScrollV(hEle);
}

/// @brief ���ñ༭���������.
/// @param hEle  Ԫ�ؾ��.
/// @param width ��������,Ĭ��Ϊ1.
void WINAPI XEdit_SetCaretWidth(HELE hEle,int width) //���ñ༭���������
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->caretWidth=width;
}

/// @brief �˸�,ɾ�������ǰ���һ���ַ�..
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_SetBackspace(HELE hEle)  //�˸�
{
	IsEditDebug(hEle,__FUNCTION__);
	Edit_CharBackspace(hEle);
}

/// @brief ����ѡ���ı�������ɫ..
/// @param hEle  Ԫ�ؾ��.
/// @param color ѡ���ı�������ɫ.
void WINAPI XEdit_SetSelectTextBkColor(HELE hEle,COLORREF color) //����ѡ���ı�������ɫ
{
	IsEditDebug(hEle,__FUNCTION__);
	EDIT(hEle)->selColor=color;
}

/// @brief ����ѡ����ı�.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_Menu_Cut(HELE hEle) //����  ɾ��ѡ����ı�,�����ı����������а���
{
	IsEditDebug(hEle,__FUNCTION__);
	XEdit_Menu_Copy(hEle);              //����
	if(FALSE==EDIT(hEle)->bReadOnly)
	{
		if(Edit_DeleteSelectText(hEle))  //ɾ��ѡ����ı�
			Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
	}
}

/// @brief ����ѡ����ı������а�.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_Menu_Copy(HELE hEle) //����  ����ѡ����ı������а���
{
	IsEditDebug(hEle,__FUNCTION__);
	HSTRING hString=Edit_GetSelectText(hEle);
	if(NULL==hString)
		return;
	int len=XStr_GetLength(hString);
	wchar_t *pStr=XStr_GetBuffer(hString);
	if(OpenClipboard(((ele_*)hEle)->pWindow->hWnd))
	{
		EmptyClipboard();
		HGLOBAL hClip=GlobalAlloc(GMEM_MOVEABLE,sizeof(wchar_t)*(len+1));
		wchar_t *pBuf=(wchar_t*)GlobalLock(hClip);
		wmemcpy(pBuf,pStr,len);
		pBuf[len]=0;
		GlobalUnlock(hClip);
		SetClipboardData(CF_UNICODETEXT,hClip);
		CloseClipboard();
	}
	XStr_Destroy(hString);
}

/// @brief �����а��е��ı�,ճ������ǰ�����λ��.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_Menu_Paste(HELE hEle) //ճ��  �����а��е��ı����뵱ǰ���λ��
{
	IsEditDebug(hEle,__FUNCTION__);
	if(EDIT(hEle)->bReadOnly)
		return;

	BOOL bSendEvent=Edit_DeleteSelectText(hEle);

	if(NULL==OpenClipboard( ((ele_*)hEle)->pWindow->hWnd ))
		return ;
	HANDLE hGlb=GetClipboardData(CF_UNICODETEXT);
	if(NULL==hGlb) return ;
	wchar_t *pText=(wchar_t*)GlobalLock(hGlb);
	if(NULL==pText) return ;

	int len=wcslen(pText);
	if(len>0)
	{
	//	XEdit_InsertText(hEle,pText,EDIT(hEle)->row,EDIT(hEle)->column); //�����ı�
		if (bSendEvent || Edit_InsertText(hEle,pText,EDIT(hEle)->row,EDIT(hEle)->column))
		{
			Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
		}
	}
	GlobalUnlock(hGlb);
	CloseClipboard();
}

/// @brief ɾ��ѡ����ı�����.��ֻ������ʱ�޷�ɾ���ı�.����:����Ҽ������˵���,[ɾ��ѡ���ı�]����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_Menu_Clear(HELE hEle) //ɾ��  ɾ��ѡ����ı�
{
	IsEditDebug(hEle,__FUNCTION__);
	if(EDIT(hEle)->bReadOnly)
		return;
	if(Edit_DeleteSelectText(hEle))
		Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
}

/// @brief ѡ�������ı�����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XEdit_Menu_SelectAll(HELE hEle) //ȫѡ  ѡ�������ı�
{
	IsEditDebug(hEle,__FUNCTION__);
	edit_ *pEdit=EDIT(hEle);

	if(0==Array_GetAtEdit(pEdit->hArrayEdit,0)->len)
		return ;

	pEdit->downX=0;
	pEdit->downRow=0;
	pEdit->downColumn=0;

	editStrList_ *pST=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->rows);
	pEdit->endX=pST->len;
	pEdit->endRow=pEdit->rows;
	pEdit->endColumn=XStr_GetLength(pST->hString);
	pEdit->bDrawSelect=TRUE;

	XEle_RedrawEle(hEle);
}

BOOL CALLBACK Edit_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(EDIT(hEle)->bMouseStay || XEle_IsFocus(hEle))
	{
		if(EDIT(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw,EDIT(hEle)->hImage_stay,&rect);
		}
	}else
	{
		if(SCROLLVIEW(hEle)->hImage_bk)
		{
			XDraw_HImageSuper_(hDraw,SCROLLVIEW(hEle)->hImage_bk,&rect);
		}
	}

	if(((ele_*)hEle)->bBorder)
	{
		COLORREF color=((ele_*)hEle)->borderColor;
		if(XEle_IsFocus(hEle) || EDIT(hEle)->bMouseStay)
		{
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(GetRValue(color)+80,GetGValue(color)+80,GetBValue(color)+80));
			HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
			if(SCROLLVIEW(hEle)->left>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,0,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->top>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,rect.right,0);
			}
			if(SCROLLVIEW(hEle)->right>0)
			{
				XDraw_MoveToEx_(hDraw,rect.right-1,0,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->bottom>0)
			{
				XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
				XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
			}

			HPEN hPen2=XDraw_CreatePen_(hDraw,PS_SOLID,1,color);
			XDraw_SelectObject_(hDraw,hPen2);
			if(SCROLLVIEW(hEle)->left>1)
			{
				XDraw_MoveToEx_(hDraw,1,1,NULL);
				XDraw_LineTo_(hDraw,1,rect.bottom-1);
			}
			if(SCROLLVIEW(hEle)->top>1)
			{
				XDraw_MoveToEx_(hDraw,1,1,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,1);
			}
			if(SCROLLVIEW(hEle)->right>1)
			{
				XDraw_MoveToEx_(hDraw,rect.right-2,1,NULL);
				XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-1);
			}
			if(SCROLLVIEW(hEle)->bottom>1)
			{
				XDraw_MoveToEx_(hDraw,1,rect.bottom-2,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,rect.bottom-2);
			}
		}else
		{
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,color);
			HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
			if(SCROLLVIEW(hEle)->left>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,0,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->top>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,rect.right,0);
			}
			if(SCROLLVIEW(hEle)->right>0)
			{
				XDraw_MoveToEx_(hDraw,rect.right-1,0,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->bottom>0)
			{
				XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
				XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
			}
		}
	}

	return TRUE;
}

BOOL CALLBACK Edit_OnDrawScrollView(HELE hEle,HDRAW hDraw)
{
	edit_ *pEdit=EDIT(hEle);

	//����ѡ���ı�����
	Edit_DrawSelect(hEle,hDraw);

	int left=pEdit->spacLeft;//+SCROLLVIEW(hEle)->left;
	int top=pEdit->spacTop;//+SCROLLVIEW(hEle)->top;

	int count=Array_GetCount(pEdit->hArrayEdit);
	editStrList_ *pStrT=NULL;

	if(FALSE==pEdit->bPass)
	{
		for(int i=0;i<count;i++)
		{
			pStrT=Array_GetAtEdit(pEdit->hArrayEdit,i);
			if(pStrT)
			{
				XDraw_TextOut_(hDraw,left,top,XStr_GetBuffer(pStrT->hString),XStr_GetLength(pStrT->hString));
				top+=pEdit->rowHeight;
			}
		}
	}else //����
	{
		pStrT=Array_GetAtEdit(pEdit->hArrayEdit,0);
		if(pStrT)
		{
			int len=XStr_GetLength(pStrT->hString);
			if(len<MAX_PATH)
			{
				wchar_t pass[MAX_PATH]={0};
				wmemset(pass,L'*',len);
				XDraw_TextOut_(hDraw,left,top,pass,len);
			}
		}
	}

	//	XTRACE("��%d ,��%d ,������%d\n",pEdit->row,pEdit->column,pEdit->rows);
	//	XTRACE("column %d\n",pEdit->endColumn);
	return TRUE;
}

BOOL CALLBACK Edit_OnLButtonDown_View(HELE hEle,UINT flags,POINT *pPt)
{
	if(XEle_IsHitChildEle(hEle,pPt))
		return FALSE;

	HELE hEdit=XEle_GetParentEle(hEle);

	XEle_SetFocus(hEdit,TRUE);

	edit_ *pEdit=(edit_*)hEdit;

	SetCursor(::LoadCursor(NULL, IDC_IBEAM));

	Edit_TestDown(hEdit,pPt);
	if(EDIT(hEdit)->bCaretCreate)
	{
		Edit_SetCaretPos(hEdit);
	}
	if(EDIT(hEdit)->bDrawSelect)
	{
		EDIT(hEdit)->bDrawSelect=FALSE;
	}

	//�ı�ѡ��
	pEdit->bDown=TRUE;
	pEdit->downX=pEdit->caretPt.x;
	pEdit->downRow=pEdit->row;
	pEdit->downColumn=pEdit->column;

	XEle_SetCapture(hEle);
	XEle_RedrawEle(hEle);

	return FALSE;
}

BOOL CALLBACK Edit_OnLButtonUp_View(HELE hEle,UINT flags,POINT *pPt)
{
	HELE hEdit=XEle_GetParentEle(hEle);
	if(EDIT(hEdit)->bDown)
	{
		EDIT(hEdit)->bDown=FALSE;
		XEle_ReleaseCapture(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnMouseMove_View(HELE hEle,UINT flags,POINT *pPt)
{	
	if(XEle_IsHitChildEle(hEle,pPt))
		return FALSE;

	HELE hEdit=XEle_GetParentEle(hEle);

	RECT rect;
	XSView_GetViewRect(hEdit,&rect);
	if(EDIT(hEdit)->bDown)  //�������ѡ���ı�
	{
		SetCursor(::LoadCursor(NULL, IDC_IBEAM));
		if(pPt->x<rect.left)
		{
			XSView_ScrollLeftLine(hEdit);
			//XTRACE("edit �����϶������� ��\n");
		}
		if(pPt->x>rect.right )
		{
			XSView_ScrollRightLine(hEdit);
			//XTRACE("edit �����϶������� ��\n");
		}
		if(pPt->y<rect.top)
		{
			XSView_ScrollTopLine(hEdit);
			//XTRACE("edit �����϶�������  ��\n");
		}
		if(pPt->y>rect.bottom)
		{
			XSView_ScrollDownLine(hEdit);
			//XTRACE("edit �����϶�������  ��\n");
		}

		int row=EDIT(hEdit)->row;
		int column=EDIT(hEdit)->column;

		Edit_TestDown(hEdit,pPt);

		if(row!=EDIT(hEle)->row || column!=EDIT(hEle)->column) //λ�øı�
		{
			Edit_SetCaretPos(hEdit);
			EDIT(hEdit)->bDrawSelect=TRUE;

			EDIT(hEdit)->endX=EDIT(hEdit)->caretPt.x;
			EDIT(hEdit)->endRow=EDIT(hEdit)->row;
			EDIT(hEdit)->endColumn=EDIT(hEdit)->column;
			XEle_RedrawEle(hEle); //����ѡ���ı�����
			//XTRACE("λ�øı�\n");
		}
	}else
	{
		SetCursor(::LoadCursor(NULL, IDC_IBEAM));
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnRButtonDown_View(HELE hEle,UINT flags,POINT *pPt)
{	
	if(XEle_IsHitChildEle(hEle,pPt))
		return FALSE;

	HELE hEdit=XEle_GetParentEle(hEle);

//	if(FALSE==XEle_IsFocus(hEle))
//	{
		XEle_SetFocus(hEdit,TRUE);
		//XTRACE("edit setFocus\n");
//	}

	RECT rect;
	XSView_GetViewRect(hEdit,&rect);
//	if(PtInRect(&rect,*pPt))  //����ͼ��
//	{
		SetCursor(::LoadCursor(NULL, IDC_IBEAM));

		Edit_TestDown(hEdit,pPt);
		if(EDIT(hEdit)->bCaretCreate)
		{
			Edit_SetCaretPos(hEdit);
		}
		if(EDIT(hEdit)->bDrawSelect)
		{
			EDIT(hEdit)->bDrawSelect=FALSE;
			if(EDIT(hEdit)->bCaretCreate)
				XEle_RedrawEle(hEle);
		}
//	}
	
	return TRUE;
}

BOOL CALLBACK Edit_OnRButtonUp_View(HELE hEle,UINT flags,POINT *pPt)
{
	HELE hEdit=XEle_GetParentEle(hEle);
	if(EDIT(hEdit)->bMenu)
	{
		if(XEle_IsHitChildEle(hEle,pPt))
			return FALSE;

		POINT pt=*pPt;
		XEle_PointToNCWnd(hEle,&pt);

		HMENUX hMenu=XMenu_Create();
		XMenu_AddItem(hMenu,IDM_CLIP,L"����");
		XMenu_AddItem(hMenu,IDM_COPY,L"����");
		XMenu_AddItem(hMenu,IDM_PASTE,L"ճ��");
		XMenu_AddItem(hMenu,IDM_DELETE,L"ɾ��");
		XMenu_AddItem(hMenu,0,NULL,XMENU_ROOT,XM_SEPARATOR);
		XMenu_AddItem(hMenu,IDM_SELECTALL,L"ȫѡ");
		XMenu_AddItem(hMenu,IDM_DELETEALL,L"���");

		window_* pWindow=((ele_*)hEle)->pWindow;
		ClientToScreen(pWindow->hWnd,&pt);
		XMenu_Popup(hMenu,pWindow->hWnd,pt.x,pt.y,hEdit);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventMouseStay(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
	{
		EDIT(hEle)->bMouseStay=TRUE;
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventMouseLeave(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
	{
		EDIT(hEle)->bMouseStay=FALSE;
		XEle_RedrawEle(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventChar(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam)
{
	if(hEle!=hEventEle)
		return FALSE;

	edit_ *pEdit=EDIT(hEle);
	if(pEdit->bDown) return TRUE;

	if(VK_TAB==wParam) return TRUE;  //TAB����

	if(VK_ESCAPE==wParam) return TRUE;

	if(pEdit->bReadOnly) return TRUE; //ֻ��

	if( 0x8000 & GetKeyState(VK_CONTROL))
	{
		if(1==wParam)  //ȫѡ
		{
			XEdit_Menu_SelectAll(hEle);
		}else if(3==wParam) //����
		{
			XEdit_Menu_Copy(hEle);
		}else if(22==wParam) //ճ��
		{
			XEdit_Menu_Paste(hEle);
		}
		return TRUE;
	}

	wchar_t ch[2]={0};
	ch[0]=wParam;

	//XTRACEW(L"char=%c \n",wParam);

	if(VK_BACK==wParam)  //�˸�
	{
		Edit_CharBackspace(hEle);
		//	XTRACEW(L"wchar=�˸� \n",ch);
	}else if(VK_RETURN==wParam) //�س�����
	{
		if(pEdit->bMoreLine)
			Edit_CharEnter(hEle);
		//	XTRACEW(L"wchar=�س�");
	}else
	{
		Edit_Char(hEle,wParam);
		//	XTRACEW(L"wchar=%s \n",ch);
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam)
{
	if(hEle!=hEventEle)
		return FALSE;
	//XTRACE("keydown %d",wParam);
	switch(wParam)
	{	
	case 46:  //Delete
			Edit_CharDeleteKey(hEle);
		break;
	case 36:  //Home
		//	MoveCaretBegin();
		break;
	case 35:  //End
		//	MoveCaretEnd();
		break;
	case VK_LEFT: //37:  //��
		Eidt_MouseCreatLeft(hEle); //�ƶ�����������
		break;
	case VK_UP: //38:  //��
		Eidt_MouseCreatTop(hEle);
		break;
	case VK_RIGHT: //39:  //��
		Eidt_MouseCreatRight(hEle);
		break;
	case VK_DOWN: //40:  //��
		Eidt_MouseCreatBottom(hEle);
		break;
	}
	return TRUE;
}

void Eidt_MouseCreatLeft(HELE hEle) //�ƶ�����������
{
	edit_ *pEdit=EDIT(hEle);

	if(pEdit->bDrawSelect) //ȡ���ı�ѡ��
		pEdit->bDrawSelect=FALSE;

	if(0==pEdit->column && 0==pEdit->row)
		return;
	if(0==pEdit->column) //�ƶ�����һ��
	{
		//TODO:...
		pEdit->row--;

		HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;//��һ��
		pEdit->column=XStr_GetLength(hStr);
		pEdit->caretPt.x=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len;
		pEdit->caretPt.y-=pEdit->rowHeight;
		Edit_SetCaretPos(hEle);
		//Edit_ScrollVTop(hEle);
		Edit_ScrollV(hEle);
		//Edit_ScrollHRight(hEle);
		Edit_ScrollH(hEle);
	}else //�����ǰ��һ���ַ�
	{
		HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString; //��ǰ��
		wchar_t ch=XStr_GetAt(hStr,pEdit->column-1);//ǰһ���ַ�

		SIZE size;   //�ַ�����
		if(FALSE==pEdit->bPass)
		{
			HDC hdc=GetDC(NULL);
			HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32(hdc,&ch,1,&size);
			SelectObject(hdc,hOldFont);
			ReleaseDC(NULL,hdc);
		}else
		{
			size.cx=pEdit->sizePass.cx;
		}

		pEdit->column--;

		pEdit->caretPt.x-=size.cx;
		Edit_SetCaretPos(hEle);

		//������ͼ
		Edit_ScrollH(hEle);

		XEle_RedrawEle(hEle);
	}
}

void Eidt_MouseCreatRight(HELE hEle)  //�ƶ������ ���� ��
{
	edit_ *pEdit=EDIT(hEle);
	if(pEdit->bDrawSelect) //ȡ���ı�ѡ��
		pEdit->bDrawSelect=FALSE;

	HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString; //��ǰ��
	if(pEdit->row==pEdit->rows && pEdit->column==XStr_GetLength(hStr))//����������ĩβ
	{
		return;
	}else if(pEdit->column==XStr_GetLength(hStr)) //����
	{
		pEdit->row++;
		pEdit->column=0;
		pEdit->caretPt.x=0;
		pEdit->caretPt.y+=pEdit->rowHeight;
		Edit_SetCaretPos(hEle);
		//������ͼ
		Edit_ScrollV(hEle);
		XSView_ScrollHPos(hEle,0);
	}else //��ǰ��
	{
		wchar_t ch=XStr_GetAt(hStr,pEdit->column);//ǰһ���ַ�

		//�ַ�����
		SIZE size;
		if(FALSE==pEdit->bPass)
		{
			HDC hdc=GetDC(NULL);
			HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
			GetTextExtentPoint32(hdc,&ch,1,&size);
			SelectObject(hdc,hOldFont);
			ReleaseDC(NULL,hdc);
		}else
		{
			size.cx=pEdit->sizePass.cx;
		}

		pEdit->caretPt.x+=size.cx;
		pEdit->column++;
		Edit_SetCaretPos(hEle);
		XEle_RedrawEle(hEle);
		//������ͼ
		//Edit_ScrollHRight(hEle);
		Edit_ScrollH(hEle);
	}
}

void Eidt_MouseCreatTop(HELE hEle)    //�ƶ������ ���� ��
{
	edit_ *pEdit=EDIT(hEle);
	if(pEdit->bDrawSelect) //ȡ���ı�ѡ��
		pEdit->bDrawSelect=FALSE;

	if(0==pEdit->row)
		return;

	int lenx=pEdit->caretPt.x;
	int lenLast=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row-1)->len;
	if(lenx>lenLast) //�����Xλ�ñ���һ�д�
	{
		HSTRING hStrLast=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row-1)->hString; //��һ��
		pEdit->caretPt.x=lenLast;
		pEdit->column=XStr_GetLength(hStrLast);
	}

	pEdit->caretPt.y-=pEdit->rowHeight;
	pEdit->row--;
	Edit_SetCaretPos(hEle);
	//������ͼ
	//	Edit_ScrollVTop(hEle);
	Edit_ScrollV(hEle);
	Edit_ScrollH(hEle);
	XEle_RedrawEle(hEle);
}

void Eidt_MouseCreatBottom(HELE hEle) //�ƶ������ ���� ��
{
	edit_ *pEdit=EDIT(hEle);
	if(pEdit->bDrawSelect) //ȡ���ı�ѡ��
		pEdit->bDrawSelect=FALSE;

	if(pEdit->row==pEdit->rows)
		return;

	int lenx=pEdit->caretPt.x;
	int lenNext=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row+1)->len;
	if(lenx>lenNext) //�����Xλ�ñ���һ�д�
	{
		HSTRING hStrNext=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row+1)->hString; 
		pEdit->caretPt.x=lenNext;
		pEdit->column=XStr_GetLength(hStrNext);
	}

	pEdit->caretPt.y+=pEdit->rowHeight;
	pEdit->row++;
	Edit_SetCaretPos(hEle);
	//������ͼ
	Edit_ScrollV(hEle);
	Edit_ScrollH(hEle);
	XEle_RedrawEle(hEle);
}

void Edit_CreateCaret(HELE hEle)
{	
	if(NULL==((ele_*)hEle)->pWindow) //û���봰�ڹ���
		return;

	EDIT(hEle)->bCaretCreate=TRUE;

	//�����
	XWnd_CreateCaret((HWINDOW)((ele_*)hEle)->pWindow,((scrollView_*)hEle)->hView,EDIT(hEle)->caretWidth,EDIT(hEle)->rowHeight);

	XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow,TRUE);
	Edit_SetCaretPos(hEle);

	XEle_RedrawEle(hEle);
}

void Edit_SetCaretPos(HELE hEle)
{
	if(NULL==((ele_*)hEle)->pWindow) //û���봰�ڹ���
		return;

	int viewPosx=XSView_GetHViewPos(hEle);
	int viewPosy=XSView_GetVViewPos(hEle);

	int x=EDIT(hEle)->caretPt.x+EDIT(hEle)->spacLeft+/*SCROLLVIEW(hEle)->left*/+viewPosx;
	int y=EDIT(hEle)->caretPt.y+EDIT(hEle)->spacTop+/*SCROLLVIEW(hEle)->top*/+viewPosy;

	XWnd_SetCaretPos((HWINDOW)((ele_*)hEle)->pWindow,x,y);
/*
	//���������ʾ��Χ
	int cx=SCROLLVIEW(hEle)->left+XSView_GetViewWidth(hEle);
	int cy=SCROLLVIEW(hEle)->top+XSView_GetViewHeight(hEle);

	if(x<cx && (y+((ele_*)hEle)->pWindow->caretHeight)<=cy)
	{
		if(FALSE==((ele_*)hEle)->pWindow->bCaretShow)
			XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow,TRUE);
		//XTRACE("x=%d,��ʾ\n",x);
	}else
	{
		if(((ele_*)hEle)->pWindow->bCaretShow)
			XWnd_ShowCaret((HWINDOW)((ele_*)hEle)->pWindow,FALSE);
		//XTRACE("x=%d,����ʾ\n",x);
	}*/
}

void Edit_TestDown(HELE hEle,POINT *pPt)
{
	edit_ *pEdit=EDIT(hEle);

	int posx=XSView_GetHViewPos(hEle);
	int posy=XSView_GetVViewPos(hEle);

	int downx=pPt->x-posx-EDIT(hEle)->spacLeft;//-SCROLLVIEW(hEle)->left;
	int downy=pPt->y-posy-EDIT(hEle)->spacTop;//-SCROLLVIEW(hEle)->top;

	//����к�
	pEdit->row=downy/pEdit->rowHeight;
	if(pEdit->row>pEdit->rows)
		pEdit->row=pEdit->rows;
	else if(pEdit->row<0)
		pEdit->row=0;

	//��ǰ���ַ���
	HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;
	wchar_t *pStr=XStr_GetBuffer(hStr);
	//��
	int strCount=XStr_GetLength(hStr);//��ǰ���ַ�����
	if(strCount<1)
	{
		pEdit->column=0;
		pEdit->caretPt.x=0;
		pEdit->caretPt.y=pEdit->rowHeight*pEdit->row;
	}else
	{
		int x=0;
		SIZE size;
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
		int mouseX=downx;  //���X����
		BOOL skip=FALSE;
		for(int i=0;i<strCount;i++)
		{
			if(FALSE==pEdit->bPass)
			{
				GetTextExtentPoint32(hdc,pStr,1,&size);
			}else
			{
				size.cx=pEdit->sizePass.cx;
			}
			if(mouseX<(x+size.cx/2))
			{
				pEdit->column=i;
				skip=TRUE;
				break ;
			}
			x+=size.cx;
			pStr++;
		}
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);

		if(FALSE==skip)
		{
			pEdit->column=strCount;
		}

		pEdit->caretPt.x=x;
		pEdit->caretPt.y=pEdit->rowHeight*pEdit->row;
	}
}

void Edit_AdjustViewSize(HELE hEle) //������ͼ���ݴ�С
{
	//������ͼ���ݴ�С
	int cx=EDIT(hEle)->spacLeft+2;
	int cy=EDIT(hEle)->spacTop+2;

	cx=cx+Array_GetAtEdit(EDIT(hEle)->hArrayEdit,EDIT(hEle)->maxLine)->len;
	if(FALSE==EDIT(hEle)->bMoreLine || EDIT(hEle)->bPass)
		cy=EDIT(hEle)->rowHeight;
	else
		cy=cy+(EDIT(hEle)->rows+1)*EDIT(hEle)->rowHeight;

	XSView_SetSize(hEle,cx,cy);
}

void Edit_ScrollH(HELE hEle)   //�����ϵ�����������,ˮƽ����
{
	int posx=EDIT(hEle)->caretPt.x+XSView_GetHViewPos(hEle)+EDIT(hEle)->spacLeft;
	if(posx<0) //�����
	{
		//	int posx=EDIT(hEle)->caretPt.x+XSView_GetHViewPos(hEle)+EDIT(hEle)->spacLeft;
		int left=EDIT(hEle)->spacLeft;
		if(posx<=left)
		{
			int viewWidth=XSView_GetViewWidth(hEle);
			int pos=(EDIT(hEle)->caretPt.x+EDIT(hEle)->spacLeft)-viewWidth/2;
			pos=pos/SCROLLVIEW(hEle)->sizeLine.cx;
			if(pos<0)
				pos=0;
			XSView_ScrollHPos(hEle,pos);
			//XTRACE("���� ����\n");
		}
	}else //�ҹ���
	{
		int viewWidth=XSView_GetViewWidth(hEle);
		int posx=EDIT(hEle)->caretPt.x+XSView_GetHViewPos(hEle)+EDIT(hEle)->spacLeft;
		if(posx>=viewWidth)
		{
			int pos=((EDIT(hEle)->caretPt.x+EDIT(hEle)->spacLeft)-viewWidth)/SCROLLVIEW(hEle)->sizeLine.cx;

			XSView_ScrollHPos(hEle,pos+1);
		}
	}
}


/*
void Edit_ScrollVTop(HELE hEle)
{
int posy=EDIT(hEle)->caretPt.y+XSView_GetVViewPos(hEle)+EDIT(hEle)->spacTop;
int t2=EDIT(hEle)->spacTop;
if(posy<=t2)
{
int viewHeight=XSView_GetViewHeight(hEle);
int pos=(EDIT(hEle)->caretPt.y+EDIT(hEle)->spacTop)-viewHeight/2;
if(pos<0)
pos=0;
XSView_ScrollVPos(hEle,pos);
}
}*/

void Edit_ScrollV(HELE hEle)
{
	int posy=EDIT(hEle)->caretPt.y+XSView_GetVViewPos(hEle)+EDIT(hEle)->spacTop;
	if(posy>0) //���¹���
	{
		int viewHeight=XSView_GetViewHeight(hEle);
		posy=(EDIT(hEle)->row+1) * EDIT(hEle)->rowHeight;
		posy=posy+EDIT(hEle)->spacTop;
		int top=posy-XSView_GetVViewPos(hEle);
		if(top >= viewHeight)
		{
			int pos=(posy-viewHeight)/SCROLLVIEW(hEle)->sizeLine.cy;
			XSView_ScrollVPos(hEle,pos+1);
			//XTRACE("�س� ����... \n");
		}
	}else //���Ϲ���
	{
		int top=EDIT(hEle)->spacTop;
		if(posy<=top)
		{
			int viewHeight=XSView_GetViewHeight(hEle);
			int pos=(EDIT(hEle)->caretPt.y+EDIT(hEle)->spacTop)-viewHeight/2;
			if(pos<0)
				pos=0;
			XSView_ScrollVPos(hEle,pos);
		}
	}
}

void Edit_Char(HELE hEle,wchar_t ch)
{
	edit_ *pEdit=EDIT(hEle);

	if(pEdit->bNumber) //���� 48 - 57
	{
		if(ch<48 || ch>57)
			return ;
	}

	if(pEdit->bDrawSelect)
	{
		Edit_DeleteSelectText(hEle); //ɾ��ѡ���ı�
	}

	SIZE size;   //�ַ�����
	if(FALSE==pEdit->bPass)
	{
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
		GetTextExtentPoint32(hdc,&ch,1,&size);
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);

	}else //�����
	{
		size.cx=pEdit->sizePass.cx;
	}

	HSTRING hString=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;
	XStr_InsertChar(hString,pEdit->column,ch);
	pEdit->column++;

	pEdit->caretPt.x+=size.cx;
	Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len+=size.cx;
	if(pEdit->maxLine>pEdit->rows)
	{
		pEdit->maxLine=0;
	}

	//��������
	if(pEdit->row!=pEdit->maxLine)
	{
		if(Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len > Array_GetAtEdit(pEdit->hArrayEdit,pEdit->maxLine)->len)
		{
			pEdit->maxLine=pEdit->row;
		}
	}

	//������ͼ���ݴ�С
	if(pEdit->row==pEdit->maxLine)
	{
		Edit_AdjustViewSize(hEle);
	}

	//�����ϵ�����������,ˮƽ����
	//Edit_ScrollHRight(hEle);
	Edit_ScrollH(hEle);

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);

	XEle_RedrawEle(hEle);
}

void Edit_CharEnter(HELE hEle)
{
	edit_ *pEdit=EDIT(hEle);

	if(pEdit->bDrawSelect)
	{
		Edit_DeleteSelectText(hEle); //ɾ��ѡ���ı�
	}

	HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;
	//��ǰ���ַ���
	wchar_t *pStr=XStr_GetBuffer(hStr);
	wchar_t *pStrAdd=pStr+pEdit->column;
	int strLen=XStr_GetLength(hStr);

	editStrList_ *pNew=(editStrList_*)malloc(sizeof(editStrList_));
	pNew->hString=XStr_Create();
	pNew->len=0;

	XStr_SetString(pNew->hString,pStrAdd);

	//���һ��
	XArray_insert(pEdit->hArrayEdit,pNew,pEdit->row+1);

	//�����ַ�������
	SIZE size;   //�ַ�����
	HDC hdc=GetDC(NULL);
	HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
	GetTextExtentPoint32(hdc,pStrAdd,strLen-pEdit->column,&size);
	SelectObject(hdc,hOldFont);
	ReleaseDC(NULL,hdc);

	Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len-=size.cx;
	pNew->len=size.cx;

	XStr_SetLength(hStr,pEdit->column);

	//������
	int maxcx=0;
	for(int i=0;i<=(pEdit->rows+1);i++)
	{
		if(Array_GetAtEdit(pEdit->hArrayEdit,i)->len>maxcx)
		{
			maxcx=Array_GetAtEdit(pEdit->hArrayEdit,i)->len;
			pEdit->maxLine=i;
		}
	}

	pEdit->row++;
	pEdit->rows++;
	pEdit->column=0;

	//�����
	pEdit->caretPt.x=0;
	pEdit->caretPt.y+=pEdit->rowHeight;

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);

	//�����϶�������,��ֱ����
	Edit_ScrollV(hEle);

	XSView_ScrollHPos(hEle,0);  //�������

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);

	XEle_RedrawEle(hEle);
}

void Edit_CharBackspaceEnter(HELE hEle) //�˸�س�
{
	edit_ *pEdit=EDIT(hEle);
	//��ǰ��
	HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;

	if(0==XStr_GetLength(hStr)) //����
	{
		editStrList_ *pDel=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row);
		//pEdit->pStringList.Delete(pDel);
		XArray_DeleteIndex(pEdit->hArrayEdit,pEdit->row);
		XStr_Destroy(pDel->hString);
		free(pDel);

		pEdit->row--;
		pEdit->rows--;

		hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;
		pEdit->column=XStr_GetLength(hStr);

		pEdit->caretPt.x=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len;
		pEdit->caretPt.y=pEdit->row * pEdit->rowHeight;

		//��м��
		if(pEdit->maxLine>pEdit->row)
		{
			pEdit->maxLine--;
		}
	}else //�ǿ���
	{
		//��һ��
		HSTRING hLastRow=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row-1)->hString;
		pEdit->column=XStr_GetLength(hLastRow);//��

		//������ƶ�����һ��ĩβ
		pEdit->caretPt.x=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row-1)->len;
		pEdit->caretPt.y=(pEdit->row-1) * pEdit->rowHeight;

		XStr_AddString(hLastRow,XStr_GetBuffer(hStr)); //����ǰ���ַ�������һ��

		//��һ���ַ���ʾ��������
		Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row-1)->len+=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len;

		//ɾ����ǰ��
		editStrList_ *pDel=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row);
		XArray_DeleteIndex(pEdit->hArrayEdit,pEdit->row);
		XStr_Destroy(pDel->hString);
		free(pDel);

		pEdit->row--;
		pEdit->rows--;

		//��м��
		int maxcx=0;
		pEdit->maxLine=0;
		for(int i=0;i<=pEdit->rows;i++)
		{
			if(Array_GetAtEdit(pEdit->hArrayEdit,i)->len>maxcx)
			{
				maxcx=Array_GetAtEdit(pEdit->hArrayEdit,i)->len;
				pEdit->maxLine=i;
			}
		}
	}

	//������ͼ���ݴ�С
	Edit_AdjustViewSize(hEle);

	//�����ϵ�������
	//Edit_ScrollHRight(hEle);
	Edit_ScrollH(hEle);

	Edit_SetCaretPos(hEle);
	XEle_RedrawEle(hEle);
}

//Delete��
void Edit_CharDeleteKey(HELE hEle)
{
//	edit_ *pEdit=EDIT(hEle);
}

void Edit_CharBackspace(HELE hEle)
{
	edit_ *pEdit=EDIT(hEle);

	if(pEdit->bDrawSelect) //ɾ��ѡ������
	{
		if(Edit_DeleteSelectText(hEle))
			Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
		XEle_RedrawEle(hEle);
		return;
	}

	if(0==pEdit->column && 0==pEdit->row)
		return;

	//ɾ���س�
	if(0==pEdit->column)
	{
		Edit_CharBackspaceEnter(hEle);
		Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);
		return;
	}

	//��ǰ��
	HSTRING hStr=Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->hString;

	wchar_t ch=XStr_GetAt(hStr,pEdit->column-1); //Ҫɾ�����ַ�
	XStr_DeleteLength(hStr,pEdit->column-1,1); //ɾ���ַ�

	//�����ַ�����
	SIZE size;   //�ַ�����
	if(FALSE==pEdit->bPass)
	{
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
		GetTextExtentPoint32(hdc,&ch,1,&size);
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);
	}else
	{
		size.cx=pEdit->sizePass.cx;
	}

	Array_GetAtEdit(pEdit->hArrayEdit,pEdit->row)->len-=size.cx;
	/////////////
	pEdit->column--;

	//��м��
	if(pEdit->row==pEdit->maxLine)
	{
		int maxcx=0;
		for(int i=0;i<=pEdit->rows;i++)
		{
			if(Array_GetAtEdit(pEdit->hArrayEdit,i)->len>maxcx)
			{
				maxcx=Array_GetAtEdit(pEdit->hArrayEdit,i)->len;
				pEdit->maxLine=i;
			}
		}
	}

	pEdit->caretPt.x-=size.cx;

	//������ͼ���ݴ�С
	if(pEdit->row==pEdit->maxLine)
	{
		Edit_AdjustViewSize(hEle);
	}

	//�����ϵ�������
	Edit_ScrollH(hEle);

	Edit_SetCaretPos(hEle);

	Ele_SendEvent(hEle,XE_EDIT_CHANGE,0,0);

	XEle_RedrawEle(hEle);
}

void Edit_DrawSelect(HELE hEle,HDRAW hDraw) //����ѡ���ı�����
{
	if(EDIT(hEle)->bDrawSelect)
	{
		HBRUSH hBrush=NULL;
		if(EDIT(hEle)->bCaretCreate)
			hBrush=XDraw_CreateSolidBrush_(hDraw,EDIT(hEle)->selColor);//RGB(83,132,213));
		else
			hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(200,200,200));

		edit_ *pEdit=EDIT(hEle);
		//��ǰ��
		if(pEdit->downRow==pEdit->endRow)
		{
			int top=pEdit->spacTop;//+XSView_GetSpacingTop(hEle);
			int left=pEdit->spacLeft;//+XSView_GetSpacingLeft(hEle);
			RECT rc;
			if(pEdit->downX<pEdit->endX)
			{
				rc.left   = left + pEdit->downX;
				rc.top    = top  + pEdit->downRow*pEdit->rowHeight;
				rc.right  = left + pEdit->endX;
				rc.bottom = rc.top + pEdit->rowHeight;
			}else
			{
				rc.left   = left + pEdit->endX;
				rc.top    = top  + pEdit->downRow*pEdit->rowHeight;
				rc.right  = left + pEdit->downX;
				rc.bottom = rc.top + pEdit->rowHeight;
			}
			XDraw_FillRect_(hDraw,&rc,hBrush);
		}else //����
		{
			if(pEdit->downRow<pEdit->endRow) //����ѡ��
			{
				Edit_DrawSelectBottom(hEle,hDraw,hBrush);

			}else //����ѡ��
			{
				Edit_DrawSelectTop(hEle,hDraw,hBrush);
			}
		}
	}
}


void Edit_DrawSelectBottom(HELE hEle,HDRAW hDraw,HBRUSH hBrush)
{
	edit_ *pEdit=EDIT(hEle);
	RECT rc;
	int top=pEdit->spacTop;//+XSView_GetSpacingTop(hEle);
	int left=pEdit->spacLeft;//+XSView_GetSpacingLeft(hEle);
	//��һ��
	rc.left  = left + pEdit->downX;
	rc.top   = top  + pEdit->downRow*pEdit->rowHeight;
	rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit,pEdit->downRow)->len;
	rc.bottom= rc.top+pEdit->rowHeight;
	XDraw_FillRect_(hDraw,&rc,hBrush);

	//�����
	rc.left  = left;
	rc.top   = top  + pEdit->endRow*pEdit->rowHeight;
	rc.right = left + pEdit->endX;
	rc.bottom= rc.top+pEdit->rowHeight;
	XDraw_FillRect_(hDraw,&rc,hBrush);

	//�м���
	int rows=pEdit->endRow-pEdit->downRow;
	if(rows>1)
	{
		for(int i=1;i<rows;i++)
		{
			rc.left  = left;
			rc.top   = top  + (pEdit->downRow+i)*pEdit->rowHeight;
			rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit,pEdit->downRow+i)->len;
			rc.bottom= rc.top+pEdit->rowHeight;
			XDraw_FillRect_(hDraw,&rc,hBrush);
		}
	}
}

void Edit_DrawSelectTop(HELE hEle,HDRAW hDraw,HBRUSH hBrush)
{
	edit_ *pEdit=EDIT(hEle);
	RECT rc;
	int top=pEdit->spacTop;//+XSView_GetSpacingTop(hEle);
	int left=pEdit->spacLeft;//+XSView_GetSpacingLeft(hEle);
	//��һ��
	rc.left   = left + pEdit->endX;
	rc.top    = top  + pEdit->endRow*pEdit->rowHeight;
	rc.right  = left + Array_GetAtEdit(pEdit->hArrayEdit,pEdit->endRow)->len;
	rc.bottom = rc.top+pEdit->rowHeight;
	XDraw_FillRect_(hDraw,&rc,hBrush);

	//�����
	rc.left  = left;
	rc.top   = top  + pEdit->downRow*pEdit->rowHeight;
	rc.right = left + pEdit->downX;
	rc.bottom= rc.top+pEdit->rowHeight;
	XDraw_FillRect_(hDraw,&rc,hBrush);

	//�м���
	int rows=pEdit->downRow-pEdit->endRow;
	if(rows>1)
	{
		for(int i=1;i<rows;i++)
		{
			rc.left  = left;
			rc.top   = top  + (pEdit->endRow+i)*pEdit->rowHeight;
			rc.right = left + Array_GetAtEdit(pEdit->hArrayEdit,pEdit->endRow+i)->len;
			rc.bottom= rc.top+pEdit->rowHeight;
			XDraw_FillRect_(hDraw,&rc,hBrush);
		}
	}
}

BOOL CALLBACK Edit_OnEventHScrollView(HELE hEle,HELE hEventEle,int pos)
{
	if(hEle!=hEventEle)
		return FALSE;
	if(EDIT(hEle)->bCaretCreate)
	{
		Edit_SetCaretPos(hEle);
		//XTRACE("x=%d,y=%d \n",XSView_GetHViewPos(hEle),XSView_GetVViewPos(hEle));
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventVScrollView(HELE hEle,HELE hEventEle,int pos)
{
	if(hEle!=hEventEle)
		return FALSE;

	//���������λ��, ������Χ����
	if(EDIT(hEle)->bCaretCreate)
	{
		Edit_SetCaretPos(hEle);
		//XTRACE("x=%d,y=%d \n",XSView_GetHViewPos(hEle),XSView_GetVViewPos(hEle));
	}
	return FALSE;
}

BOOL CALLBACK Edit_OnEventSetFocus(HELE hEle,HELE hEventEle) //��ý���
{
	if(hEle!=hEventEle)
		return FALSE;
	//XTRACE("edit ��ý���\n");

	if(FALSE==EDIT(hEle)->bCaretCreate)
	{
		Edit_CreateCaret(hEle);
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventKillFocus(HELE hEle,HELE hEventEle) //ʧȥ����
{
	//XTRACE("edit ʧȥ����\n");
	if(hEle!=hEventEle)
		return FALSE;

	if(EDIT(hEle)->bCaretCreate)
	{
		EDIT(hEle)->bCaretCreate=FALSE;
		XWnd_DestroyCaret((HWINDOW)((ele_*)hEle)->pWindow);
		XEle_RedrawEle(hEle);
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventMenuSelect(HELE hEle,HELE hEventEle,int id) //�˵�ѡ���¼�
{
	if(hEle==hEventEle)
	{
		switch(id)
		{
		case IDM_CLIP: XEdit_Menu_Cut(hEle); //XTRACE("����\n");
			break;
		case IDM_COPY: XEdit_Menu_Copy(hEle); //XTRACE("����\n");
			break;
		case IDM_PASTE: XEdit_Menu_Paste(hEle); //XTRACE("ճ��\n");
			break;
		case IDM_DELETE: XEdit_Menu_Clear(hEle); //XTRACE("ɾ��\n");
			break;
		case IDM_SELECTALL: XEdit_Menu_SelectAll(hEle); //XTRACE("ȫѡ\n");
			break;
		case IDM_DELETEALL: XEdit_Menu_DeleteAll(hEle); //XTRACE("���\n");
			break;
		}
	}
	return TRUE;
}

BOOL CALLBACK Edit_OnEventSize(HELE hEle,HELE hEventEle)  //Ԫ�ش�Сλ�øı�
{
	if(hEle!=hEventEle)
		return FALSE;

	Edit_AdjustViewSize(hEle);
	return FALSE;
}

BOOL CALLBACK Edit_OnEventSetFont(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;
	//XTRACE("Edit font changed \n");
	edit_  *pObject=(edit_*)hEle;

	//�ı�����
	HDC hdc = GetDC(NULL);
	HGDIOBJ hOld=SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX));

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	EDIT(hEle)->rowHeight=tm.tmHeight; //�и�

	SIZE size;
	GetTextExtentPoint32W(hdc,L"*",1,&size);
	EDIT(hEle)->sizePass.cx=size.cx;
	EDIT(hEle)->sizePass.cy=size.cy;

	SelectObject(hdc, hOld);
	ReleaseDC(NULL,hdc);

	int row=pObject->row;
	int column=pObject->column;

	////���¼�������/////////////////////////////////////
	int len=XEdit_GetTextLength(hEle);
	if(len>0)
	{
		wchar_t *temp=(wchar_t*)malloc((len+1)*sizeof(wchar_t));
		temp[len]=0;

		XEdit_GetText(hEle,temp,len);
		XEdit_DeleteAll(hEle);

		XEdit_SetText(hEle,temp);
		free(temp);
	}

	//���������
	if(EDIT(hEle)->bCaretCreate)
	{
		XWnd_DestroyCaret((HWINDOW)((ele_*)hEle)->pWindow);
		Edit_CreateCaret(hEle);

		XEdit_SetPos(hEle,row,column);
	}

	return FALSE;
}
///@}