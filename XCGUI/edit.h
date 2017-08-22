/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct editStrList_
{
	HSTRING  hString;
	int      len;      //�ַ���ʾ���ȣ�����
};

struct edit_
{
	scrollView_  scrollView;   //�̳�
	//--------------------
	HARRAY hArrayEdit;   //�ַ����� editStrList_*

	POINT caretPt;       //�����λ��
	BOOL  bCaretCreate;  //������Ƿ񴴽�
	BOOL  bMoreLine;     //��������
	BOOL  bReadOnly;     //����ֻ���ı�
	BOOL  bMenu;         //���õ����˵�

	//�ı��������ӿڱ߿�ļ��,������Ԫ�ر߿�ļ��
	int   spacLeft;  //����
	int   spacTop;   //�ϼ��
//	int   spacRight; //�Ҽ��
//	int   spacBottom;//�¼��

	int   rowHeight; //�и�
	int   row;       //��ǰ�� ��0��ʼ
	int   rows;      //������ ��0��ʼ
	int   column;    //��ǰ�� ��0��ʼ,һ���ַ�Ϊһ��
	int   maxLine;   //����� �к�

	//�ı�ѡ��
	BOOL  bDown;        //��갴��,׼��ѡ���ı�
	BOOL  bDrawSelect;  //����ѡ���ı�����ɫ
	int   downX;        //����λ��
	int   downRow;      //��
	int   downColumn;   //��
	int   endX;
	int   endRow;
	int   endColumn;

	BOOL  bNumber;  //����

	int   caretWidth; //��������
	//////�����/////////////////���������ʾ,�����Զ���
	BOOL  bPass;     //�����
	SIZE  sizePass;  //�����ַ���С
	////////////////////////
	COLORREF selColor; //ѡ���ı���ɫ
	BOOL  bMouseStay; //���ͣ��

	//��ͼ
	HIMAGE hImage_stay; //���ͣ��
};


//API:
XC_API HELE WINAPI XEdit_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);
XC_API void WINAPI XEdit_EnableMultiLine(HELE hEle,BOOL b);  //���ö�������
XC_API void WINAPI XEdit_EnablePassBox(HELE hEle,BOOL bPass); //���������
XC_API void WINAPI XEdit_EnableNumber(HELE hEle,BOOL bNumber); //ֻ����������
XC_API void WINAPI XEdit_EnablePopupMenu(HELE hEle,BOOL bEnable);  //��������Ҽ��˵�

XC_API void WINAPI XEdit_InsertText(HELE hEle,wchar_t *pText,int row=-1,int column=-1); //�����ı�,row=-1ĩβ��,column=-1ĩβ��;
XC_API void WINAPI XEdit_DeleteSelectText(HELE hEle); //ɾ��ѡ���ı�,��ֻ������ʱ,Ҳ����ɾ���ı�
XC_API void WINAPI XEdit_SetText(HELE hEle,wchar_t *pText);  //�����ı�
XC_API void WINAPI XEdit_SetInt(HELE hEle,int value);  //������������
XC_API void WINAPI XEdit_SetReadOnly(HELE hEle,BOOL bRead);  //����ֻ���ı�
XC_API void WINAPI XEdit_SetTextSpacingLeft(HELE hEle,int spacing);  //���������������
XC_API void WINAPI XEdit_SetTextSpacingTop(HELE hEle,int spacing);  //���������϶�����
XC_API void WINAPI XEdit_SetPos(HELE hEle,int line,int column); //���ò����λ��
XC_API void WINAPI XEdit_SetCaretWidth(HELE hEle,int width); //���ñ༭���������
XC_API void WINAPI XEdit_SetBackspace(HELE hEle);  //�˸�
XC_API void WINAPI XEdit_SetSelectTextBkColor(HELE hEle,COLORREF color);//����ѡ���ı�������ɫ

XC_API void WINAPI XEdit_GetSelectText(HELE hEle,wchar_t *pOut,int len);  //��ȡѡ������
XC_API int  WINAPI XEdit_GetTextLength(HELE hEle); //��ȡ���ݳ���
XC_API void WINAPI XEdit_GetText(HELE hEle,wchar_t *pOut,int len); //��ȡ�ı�
XC_API int  WINAPI XEdit_GetInt(HELE hEle); //��ȡ��������

XC_API int WINAPI XEdit_GetRowCount(HELE hEle);   //��ȡ������
XC_API int WINAPI XEdit_GetColumnCount(HELE hEle,int row); //��ȡָ�����ַ���,row=-1ĩβ��;
XC_API int WINAPI XEdit_GetCurrentRow(HELE hEle);  //��ȡ�����λ�õ�ǰ��
XC_API int WINAPI XEdit_GetCurrentColumn(HELE hEle); //��ȡ�����λ�õ�ǰ��

XC_API BOOL WINAPI XEdit_IsEmpty(HELE hEle); //�ж������Ƿ�Ϊ��
XC_API void WINAPI XEdit_DeleteAll(HELE hEle);  //���  ɾ�������ı�

XC_API void WINAPI XEdit_Menu_Cut(HELE hEle);        //����  ɾ��ѡ����ı�,�����ı����������а���
XC_API void WINAPI XEdit_Menu_Copy(HELE hEle);       //����  ����ѡ����ı������а���
XC_API void WINAPI XEdit_Menu_Paste(HELE hEle);      //ճ��  �����а��е��ı����뵱ǰ���λ��
XC_API void WINAPI XEdit_Menu_Clear(HELE hEle);      //ɾ��  ɾ��ѡ����ı�,��ֻ������ʱ�޷�ɾ���ı�
XC_API void WINAPI XEdit_Menu_SelectAll(HELE hEle);  //ȫѡ  ѡ�������ı�
XC_API void WINAPI XEdit_Menu_DeleteAll(HELE hEle);  //���  ɾ�������ı�


//��ͼ:
XC_API void WINAPI XEdit_SetImageLeave(HELE hEle,HIMAGE hImage=NULL); //����뿪
XC_API void WINAPI XEdit_SetImageStay(HELE hEle,HIMAGE hImage=NULL); //���ͣ��

//˽�з���:
void Edit_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
void Edit_CreateCaret(HELE hEle);
void Edit_SetCaretPos(HELE hEle);
void Edit_TestDown(HELE hEle,in_out_ POINT *pPt);

void Edit_AdjustViewSize(HELE hEle); //��ս��ͼ���ݴ�С
void Edit_ScrollH(HELE hEle);    //�����ϵ�����������,ˮƽ����
void Edit_ScrollV(HELE hEle);  //�����϶�������,��ֱ����

BOOL Edit_SetText_ExamineStringNumber(HELE hEle,wchar_t *pText);
void Edit_SetText_SingleLine(HELE hEle,wchar_t *pText);
void Edit_SetText_MoreLine(HELE hEle,wchar_t *pText);

void Edit_InsertText_SingleLine(HELE hEle,wchar_t *pText,wchar_t *pBuf,int row,int column);
void Edit_InsertText_MoreLine(HELE hEle,wchar_t *pText,wchar_t *pBuf,int row,int column);

void Edit_Char(HELE hEle,wchar_t ch);  //�ַ�
void Edit_CharEnter(HELE hEle);   //�س�
void Edit_CharBackspace(HELE hEle);  //�˸�
void Edit_CharBackspaceEnter(HELE hEle); //�˸�,��ǰɾ�����ǻس�
void Edit_CharDeleteKey(HELE hEle); //Delete��

void Eidt_MouseCreatLeft(HELE hEle);   //�ƶ������ ���� ��
void Eidt_MouseCreatRight(HELE hEle);  //�ƶ������ ���� ��
void Eidt_MouseCreatTop(HELE hEle);    //�ƶ������ ���� ��
void Eidt_MouseCreatBottom(HELE hEle); //�ƶ������ ���� ��

HSTRING Edit_GetSelectText(HELE hEle); //��ȡѡ���ı�

BOOL Edit_DeleteSelectText(HELE hEle); 
void Edit_DeleteSelectTextHandle(HELE hEle,int beginRow, int endRow,int beginColumn,int endColumn,int beginX); //ɾ��ѡ���ı�
void Edit_GetSelectTextHandle(HELE hEle,HSTRING hString,int beginRow,int endRow,int beginColumn,int endColumn);

BOOL Edit_InsertText(HELE hEle,wchar_t *pText,int row,int column);


//�����ı�ѡ��
void Edit_DrawSelect(HELE hEle,HDRAW hDraw); //����ѡ���ı�����
void Edit_DrawSelectBottom(HELE hEle,HDRAW hDraw,HBRUSH hBrush);
void Edit_DrawSelectTop(HELE hEle,HDRAW hDraw,HBRUSH hBrush);

//�ص�����:
void CALLBACK Edit_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Edit_OnDraw(HELE hEle,HDRAW hDraw); 
BOOL CALLBACK Edit_OnDrawScrollView(HELE hEle,HDRAW hDraw);
BOOL CALLBACK Edit_OnEventMouseStay(HELE hEle,HELE hEventEle);
BOOL CALLBACK Edit_OnEventMouseLeave(HELE hEle,HELE hEventEle);

BOOL CALLBACK Edit_OnEventHScrollView(HELE hEle,HELE hEventEle,int pos);
BOOL CALLBACK Edit_OnEventVScrollView(HELE hEle,HELE hEventEle,int pos);
BOOL CALLBACK Edit_OnEventSetFocus(HELE hEle,HELE hEventEle); //��ý���
BOOL CALLBACK Edit_OnEventKillFocus(HELE hEle,HELE hEventEle); //ʧȥ����
BOOL CALLBACK Edit_OnEventChar(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK Edit_OnEventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK Edit_OnEventMenuSelect(HELE hEle,HELE hEventEle,int id); //�˵�ѡ���¼�
BOOL CALLBACK Edit_OnEventSize(HELE hEle,HELE hEventEle); //Ԫ�ش�Сλ�øı�
BOOL CALLBACK Edit_OnEventSetFont(HELE hEle,HELE hEventEle);


BOOL CALLBACK Edit_OnLButtonDown_View(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK Edit_OnLButtonUp_View(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK Edit_OnMouseMove_View(HELE hEle,UINT flags,POINT *pPt);

BOOL CALLBACK Edit_OnRButtonDown_View(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK Edit_OnRButtonUp_View(HELE hEle,UINT flags,POINT *pPt);