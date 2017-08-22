/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


enum rictEdit_ItemType_ //������
{
	richEdit_itemType_char,	
	richEdit_itemType_image,
	richEdit_itemType_gif,
	richEdit_itemType_ele,
};

//������Ϣ
struct richEdit_font_Info_
{
	HFONT    hFont;
	LOGFONT  info;
	int      index; //��������
};

//�ж���
struct richEdit_line_
{
	HARRAY   hArrayItem; //������  richEdit_item_*
	int      lenPixel;        //�ַ�����ʾ���ȣ�����
	int      maxItemHeight;  //��߶�,ȡ������������ֵ

	//�Ƿ�Ϊ������,�������Զ�����
	//�м��,���Ϊ-1ʹ��Ĭ�ϼ��

	int  top; //�е��ϱ߽�,�±߽�����ϱ߽��maxItemHeight
};

//��С��Ԫ����
struct richEdit_item_
{
	rictEdit_ItemType_ type; //����
	richEdit_line_     *pLine; // �����нڵ�
	SIZE               size;
};

struct richEdit_item_char_  //�ַ�
{
	richEdit_item_  item;
	wchar_t   ch;

	//////�Զ�������/////////////////////////
	HFONT     hFont;     //�Զ�������
	richEdit_font_Info_  *pFontInfo; 
	BOOL      bColor;    //��ɫ�Ƿ���Ч
	COLORREF  color;     //��ɫ
	                     //�Զ����ַ����
};

struct richEdit_item_iamge_  //ͼƬ
{
	richEdit_item_  item;
	HIMAGE          hImage;
	HSTRING         hString;  //ͼƬ·��
};

class ImageEx;
struct richEdit_item_gif_    //GIF����
{
	richEdit_item_  item;
	ImageEx         *pGif;
	HSTRING         hString;  //ͼƬ·��

	HELE            hView;   //RichEdit ��
	DWORD           timer;   //�ϴμ�¼ʱ��
	DWORD           ms;      // ��ǰ֡��ʱ
};

struct richEdit_item_ele_    //Ԫ��
{
	richEdit_item_  item;
	HELE           hEle;
};

struct richEdit_
{
	scrollView_  scrollView;   //�̳�
	//---------------------

	HARRAY hArrayLine;    //�ַ��������б� richEdit_line_*
	HARRAY hArrayFont;    //�����б�,��ֹ�ظ�������ͬ������ richEdit_font_Info_*
	BOOL   bCaretCreate;  //������Ƿ񴴽�
	BOOL   bReadOnly;     //����ֻ���ı�

	//ȫ������------------------
	//�ı��������ӿڱ߿�ļ��,������Ԫ�ر߿�ļ��
	int   spacLeft;  //����
	int   spacTop;   //�ϼ��

	int   row;       //��ǰ�� ��0��ʼ
	int   rowCount;  //������ ��1��ʼ
	int   column;    //��ǰ�� ��0��ʼ,һ���ַ�Ϊһ��

	BOOL bAdjust;
	BOOL bAdjustCaret;     //��Ҫ��������� 
	BOOL bAdjustCalculate; //��Ҫ���¼�����������

	//������
	//�м��

	//�Զ�����
	//�Ƿ����TAB����

	int   maxLine;       //���,�к�,����0����

	//�»���
	int   lineHeight;     //��Ĭ�ϸ߶�

	POINT caretPt;       //�����λ��
	int   caretHeight;   //������߶�

	int   visibleBegin;  //���ӵ�һ��,�к�,����0����
	int   visibleEnd;    //�������һ��,�к�,����0����

	//�ı�ѡ��
	BOOL  bDown;        //��갴��,׼��ѡ���ı�
	BOOL  bDrawSelect;  //����ѡ���ı�����ɫ
	int   downRow;      //��
	int   downColumn;   //��
	int   endRow;
	int   endColumn;
};
//�е�ʵ�ʸ߶�=(�����ĸ߶� || Ĭ�ϸ߶�)+�м��

//API:
XC_API HELE WINAPI XRichEdit_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);

XC_API BOOL WINAPI XRichEdit_InsertText(HELE hEle,wchar_t *pText,int row,int column); //�����ı�����
XC_API BOOL WINAPI XRichEdit_InsertTextEx(HELE hEle,wchar_t *pText,int row,int column,LOGFONT *pFont,BOOL bColor=FALSE,COLORREF color=0);
XC_API BOOL WINAPI XRichEdit_InsertData(HELE hEle,void *pData,int row,int column); 
// BOOL WINAPI XRichEdit_InsertEle(HELE hEle,HELE hNew); //����Ԫ��,����ǰλ��
XC_API BOOL WINAPI XRichEdit_InsertImage(HELE hEle,HIMAGE hImage,wchar_t *pImagePath,int row,int column); //����ͼƬ,����ǰλ��
XC_API BOOL WINAPI XRichEdit_InsertImageGif(HELE hEle,wchar_t *pImageName,int row,int column);//����GIFͼƬ,����ǰλ��
//���볬����

XC_API void WINAPI XRichEdit_SetText(HELE hEle,wchar_t *pText);  //�����ı�����,�����֮ǰ������
XC_API BOOL WINAPI XRichEdit_SetPos(HELE hEle,int row,int column); //���ò����λ��
// BOOL WINAPI XRichEdit_SetItemFont(HELE hEle,int row,int column,HFONT hFont);//����������
XC_API BOOL WINAPI XRichEdit_SetItemFontEx(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,LOGFONT *pFont);

// BOOL WINAPI XRichEdit_SetItemColor(HELE hEle,int row,int column,COLORREF color);//������ɫ
XC_API BOOL WINAPI XRichEdit_SetItemColorEx(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,COLORREF color);
XC_API void WINAPI XRichEdit_SetRowHeight(HELE hEle,int height); //����Ĭ���и�
XC_API void WINAPI XRichEdit_SetReadOnly(HELE hEle,BOOL bRead);  //����ֻ������

XC_API int WINAPI XRichEdit_GetItemCount(HELE hEle); //��ȡ��������,����ͼƬ
XC_API void WINAPI XRichEdit_GetText(HELE hEle,HSTRING hString); //��ȡ�ı�����
XC_API void WINAPI XRichEdit_GetHTMLFormat(HELE hEle,HSTRING hString);  //��ȡHTML��ʽ����
XC_API void* WINAPI XRichEdit_GetData(HELE hEle);
XC_API void WINAPI XRichEdit_GetCurrentPos(HELE hEle,out_ int *pRow,out_ int *pColumn);//��ȡ�����λ��,��ǰ�к���
XC_API BOOL WINAPI XRichEdit_GetSelectPos(HELE hEle,out_ int *pBeginRow,out_ int *pBeginColumn,out_ int *pEndRow,out_ int *pEndColumn);//��ȡѡ������λ��
XC_API int  WINAPI XRichEdit_GetSelectText(HELE hEle,wchar_t *pOut,int len);//��ȡѡ������
XC_API int  WINAPI XRichEdit_GetRowCount(HELE hEle);   //��ȡ������
XC_API int  WINAPI XRichEdit_GetRowItemCount(HELE hEle,int row);   //��ȡָ������������
XC_API void WINAPI XRichEdit_GetVisibleRow(HELE hEle,out_ int *pBeginRow,out_ int *pEndRow); //��ȡ�����з�Χ
XC_API int  WINAPI XRichEdit_GetRowHeight(HELE hEle); //��ȡĬ���и�
XC_API int  WINAPI XRichEdit_GetFontCount(HELE hEle);  //��ȡ��������

XC_API BOOL WINAPI XRichEdit_IsEmpty(HELE hEle);  //�ж������Ƿ�Ϊ��
XC_API BOOL WINAPI XRichEdit_CancelSelect(HELE hEle); //ȡ��ѡ��
XC_API void WINAPI XRichEdit_SelectAll(HELE hEle);  //ȫѡ  ѡ�������ı�

XC_API void WINAPI XRichEdit_ClearFontTable(HELE hEle); //���������,����δʹ�õ�����

XC_API BOOL WINAPI XRichEdit_DeleteEx(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn); //ɾ��ָ������
XC_API BOOL WINAPI XRichEdit_DeleteSelect(HELE hEle); //ɾ��ѡ������
XC_API void WINAPI XRichEdit_DeleteAll(HELE hEle); //�������

XC_API BOOL WINAPI XRichEdit_Menu_Cut(HELE hEle);        //����  ɾ��ѡ����ı�,�����ı����������а���
XC_API BOOL WINAPI XRichEdit_Menu_Copy(HELE hEle);       //����  ����ѡ����ı������а���
XC_API BOOL WINAPI XRichEdit_Menu_Paste(HELE hEle);      //ճ��  �����а��е��ı����뵱ǰ���λ��
// void WINAPI XRichEdit_Clear(HELE hEle);      //ɾ��  ɾ��ѡ����ı�,��ֻ������ʱ�޷�ɾ���ı�

XC_API void WINAPI XRichEdit_Adjust(HELE hEle,int startIndex=0); //����

void RichEdit_Clipboard_Copy_Text(wchar_t *pText,int charLen);
void RichEdit_Clipboard_Copy_Data(HELE hEle,HARRAY hArrayItem,int dataSize);
void RichEdit_Clipboard_Copy_HTMLFormat(wchar_t *pText,int charLen);

BOOL RichEdit_Clipboard_Paste_Text(HELE hEle);
BOOL RichEdit_Clipboard_Paste_Data(HELE hEle);

BOOL RichEdit_SetItemFontExSingleLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,richEdit_font_Info_ *pFontInfo);
BOOL RichEdit_SetItemFontExMultiLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,richEdit_font_Info_ *pFontInfo);

BOOL RichEdit_SetItemColorExSingleLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,COLORREF color);
BOOL RichEdit_SetItemColorExMultiLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,COLORREF color);

int RichEdit_GetSelectSingleLine(HELE hEle,wchar_t *pOut,int len);
int RichEdit_GetSelectMultiLine(HELE hEle,wchar_t *pOut,int len);

BOOL RichEdit_Clipboard_CopySingleLine(HELE hEle);
BOOL RichEdit_Clipboard_CopyMultiLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,BOOL bForward);

BOOL RichEdit_DeleteEx_SingleLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn);
BOOL RichEdit_DeleteEx_MultiLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn);

richEdit_font_Info_* RichEdit_GetFont(HELE hEle,LOGFONT *pFont);  //�������
BOOL RichEdit_IsUnUseFont(HARRAY hArrayLine,richEdit_font_Info_ *pFontInfo);

//˽�з���:
void RichEdit_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);

void RichEdit_Char(HELE hEle,wchar_t ch);    //�ַ�
void RichEdit_CharEnter(HELE hEle);          //�س�
void RichEdit_CharBackspace(HELE hEle);      //�˸�
void RichEdit_CharBackspaceEnter(HELE hEle); //�˸�,��ǰɾ�����ǻس�
void RichEdit_CharDeleteKey(HELE hEle);      //ɾ����

void RichEdit_Calculate_VisibleLine(HELE hEle); //���������
BOOL RichEdit_Calculate_LineMaxHeight(HELE hEle,int row); //���㵱ǰ�����߶�ֵ
BOOL RichEdit_Calculate_CaretPos(HELE hEle); //��������λ��

void RichEdit_CreateCaret(HELE hEle);
void RichEdit_SetCaretPos(HELE hEle);

void RichEdit_ScrollH(HELE hEle);
void RichEdit_ScrollV(HELE hEle);

BOOL RichEdit_TestDown(HELE hEle,POINT *pPt);

BOOL RichEdit_GetItemRect(richEdit_item_ *pItem,RECT *pRect); //��ȡ������,������ڻ��Ʒ�Χ��,����FALSE
BOOL RichEdit_GetItemRect2(HELE hEle,richEdit_item_ *pItem,RECT *pRect); //��ȡ������,�����ӿ�����,������ڻ��Ʒ�Χ��,����FALSE


void RichEidt_MouseCreatLeft(HELE hEle);   //�ƶ������ ���� ��
void RichEidt_MouseCreatRight(HELE hEle);  //�ƶ������ ���� ��
void RichEidt_MouseCreatTop(HELE hEle);    //�ƶ������ ���� ��
void RichEidt_MouseCreatBottom(HELE hEle); //�ƶ������ ���� ��

void RichEdit_FreeItem(richEdit_item_ *pItem);
void RichEdit_FreeLine(richEdit_line_ *pLine);
BOOL RichEdit_DeleteSelect(HELE hEle);
BOOL RichEdit_DeleteSelectSingleLine(HELE hEle);
BOOL RichEdit_DeleteSelectMultiLine(HELE hEle,int beginRow,int beginColumn,int endRow,int endColumn,BOOL bForward);

void RichEdit_DrawSelectBG(HELE hEle,HDRAW hDraw); //����ѡ�����ݱ���


//�ص�����:
BOOL CALLBACK RichEdit_OnEventChar(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK RichEdit_OnEventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK RichEdit_OnEventSetFocus(HELE hEle,HELE hEventEle); //��ý���
BOOL CALLBACK RichEdit_OnEventKillFocus(HELE hEle,HELE hEventEle); //ʧȥ����
BOOL CALLBACK RichEdit_OnEventSetFont(HELE hEle,HELE hEventEle); 


BOOL CALLBACK RichEdit_OnEventHScrollView(HELE hEle,HELE hEventEle,int pos);
BOOL CALLBACK RichEdit_OnEventVScrollView(HELE hEle,HELE hEventEle,int pos);

BOOL CALLBACK RichEdit_OnDrawScrollView(HELE hEle,HDRAW hDraw);
void CALLBACK RichEdit_OnEventDestroy(HELE hEle); 

//��Ԫ��
BOOL CALLBACK RichEdit_OnLButtonDown_View(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK RichEdit_OnLButtonUp_View(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK RichEdit_OnMouseMove_View(HELE hEle,UINT flags,POINT *pPt);



/////////////////////////////////////////////////
struct richEdit_clipboard_header_ //ͷ��Ϣ
{
	wchar_t    name[15]; //��ʼ��ʶ  XCGUI_RichEdit
	LOGFONT    font;     //Ĭ������
	COLORREF   color;    //Ĭ����ɫ
	int        size;     //�����ܳ���,�ֽ�Ϊ��λ
	int        itemCount;      //����������,��Ϊ�����ͼƬ
	int        fontCount; //���Ի���������
};

//struct richEdit_clipboard_fontTable_ //�����
//{
//	LOGFONT  font;  //������Ϣ
//};

struct richEdit_clipboard_char_ //����Ԫ��
{
	rictEdit_ItemType_ type;
	int       fontIndex; //��������, -1ΪĬ������
	COLORREF  color;     //��ɫ
	BOOL      bColor;    //��ɫ�Ƿ���Ч
	wchar_t   ch;        //��CH
};

struct richEdit_clipboard_iamge_//����ͼƬ
{
	rictEdit_ItemType_  type;
	int      size;          //�ֽ�Ϊ��λ����,��������ֹ��
	int      chs;  //ͼƬ��ַ
};
