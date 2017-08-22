/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

#define RGBA(a,r,g,b)   ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((WORD)(BYTE)(a))<<24))


HBITMAP XDraw_CreateDIBSection(HDC hdc,int cx,int cy);

XC_API void WINAPI XDraw_FillSolidRect(HDC hdc,RECT *pRect,COLORREF clr);
XC_API BOOL WINAPI XDraw_GradientFill2(HDC hdc,COLORREF color1,COLORREF color2,RECT *pRect,int mode);
XC_API BOOL WINAPI XDraw_GradientFill4(HDC hdc,COLORREF color1,COLORREF color2,COLORREF colo3,COLORREF color4,RECT *pRect,int mode);

void XDraw_Dottedline(HDC hdc,int x,int y,int length,COLORREF color,BOOL bHorizontal=TRUE);  //��������

//���Ƹ�ѡ��
XC_API void WINAPI XDraw_Check(HDC hdc,int x,int y,COLORREF color,BOOL bCheck);


Status XDraw_GraphicsDrawImage(HDC hdc,Image *image,int x,int y);
Status XDraw_GraphicsDrawImageEx(HDC hdc,Image *image,int x,int y,int width,int height);

//������ͼƬ
XC_API void WINAPI XDraw_HImage(HDC hdc,HIMAGE hImage,int x,int y);

//������ͼ
XC_API void WINAPI XDraw_HImageStretch(HDC hdc,HIMAGE hImage,int x,int y,int width,int height);

//����ͼƬ����,�Զ�����:��ͨ,����,����ӦͼƬ
XC_API void WINAPI XDraw_HImageSuper(HDC hdc,HIMAGE hImage,RECT *pRect);


//����ͼƬָ������,������ͼƬ
XC_API void WINAPI XDraw_HImageEx(HDC hdc,HIMAGE hImage,int x,int y,int width,int height,int srcX,int srcY);

XC_API void WINAPI XDraw_HImageExTile(HDC hdc,HIMAGE hImage,RECT *pRect,int flag=0);


//��������Ӧ��ͼ
XC_API void WINAPI XDraw_HImageAdaptive(HDC hdc,HIMAGE hImage,RECT *pRect);


//////////////////////////////////////////////////////
//Ч������
//GDI+ ����Բ�Ǿ���
GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded);
//GDI+���ƾ�����Ӱ
void DrawShadow(Graphics &g, GraphicsPath *ButtonPath);
//////////////////////////////////////////////////////

struct bitmap_info_
{
	HBITMAP hBitmap;
	BYTE *data;
	int bitSize;
	int width;
	int height;
};


//���ƴ��ڱ߿���Ӱ,������Ӱ����
void Draw_DrawWndShadow(HDC hdc,RECT *pRect); //���ƴ��ڱ߿���Ӱ
void Draw_DrawShadowLine(HDC hdc,RECT *pRect,bitmap_info_ &info);


//λͼ���ݲ���,֧��͸��ͨ��
void Draw_GetData(HDC hdc,bitmap_info_ &info);
void Draw_SetPixelValue(bitmap_info_ &info,int x,int y,COLORREF color);
void Draw_DrawStraightLine(bitmap_info_ &info,int x1,int y1,int x2,int y2,COLORREF color);
void Draw_SetData(bitmap_info_ &info);

///////////////////////////////////////////////////////////////
void Draw_SetTransparent(HDC hdc,BYTE alpha);



////////////////////////////////////////////////////////////////////////
////////////////ͼ�λ���ģ��////////////////////////////////////////////


struct draw_xc_
{
	object_ object;

	HDC hdc;
	int x;  //ƫ����X
	int y;  //ƫ����Y


	//���ڻ�ԭ��ʼ״̬,�ͷź���ѡ���GDI����----------------
	HGDIOBJ OBJ_BITMAP_O;   //λͼ
	HGDIOBJ OBJ_BRUSH_O;    //HBRUSH ��ʼ�Ļ�ˢ
	HGDIOBJ OBJ_FONT_O;     //HFONT  ��ʼ������
	HGDIOBJ OBJ_PEN_O;      //HPEN   ��ʼ�Ļ���

	//��ʱGDI����----------------------
	HARRAY hArrayTemp;
};


XC_API HDRAW WINAPI XDraw_Create_(HDC hdc); //����
XC_API void  WINAPI XDraw_Destroy_(HDRAW hDraw); //����
XC_API void  WINAPI XDraw_SetOffset_(HDRAW hDraw,int x,int y); //��������ƫ����
XC_API void  WINAPI XDraw_RestoreGDIOBJ_(HDRAW hDraw);  //��ԭ״̬,�ͷ��û��󶨵�GDI����
XC_API HDC   WINAPI XDraw_GetHDC_(HDRAW hDraw);
XC_API void  WINAPI XDraw_GetOffset_(HDRAW hDraw,out_ int *pX,out_ int *pY); //��ȡ����ƫ����

XC_API COLORREF WINAPI XDraw_SetTextColor_(HDRAW hDraw,COLORREF crColor);


//��������
XC_API HBRUSH WINAPI XDraw_CreateSolidBrush_(HDRAW hDraw,COLORREF crColor);
XC_API HPEN WINAPI XDraw_CreatePen_(HDRAW hDraw,int fnPenStyle,int nWidth,COLORREF crColor);
XC_API HRGN WINAPI XDraw_CreateRoundRectRgn_(HDRAW hDraw,int nLeftRect,int nTopRect,int nRightRect,int nBottomRect,int nWidthEllipse,int nHeightEllipse);
XC_API HRGN WINAPI XDraw_CreatePolygonRgn_(HDRAW hDraw,POINT *pPt,int cPoints,int fnPolyFillMode);

//ѡ�����
XC_API HGDIOBJ WINAPI XDraw_SelectObject_(HDRAW hDraw,HGDIOBJ hObj);
XC_API int WINAPI XDraw_SelectClipRgn_(HDRAW hDraw,HRGN hRgn);
XC_API BOOL WINAPI XDraw_DeleteObject_(HDRAW hDraw,HGDIOBJ hObj);

//����
XC_API int WINAPI XDraw_FillRect_(HDRAW hDraw,RECT *pRect,HBRUSH hbr);
XC_API BOOL WINAPI XDraw_FillRgn_(HDRAW hDraw,HRGN hrgn,HBRUSH hbr);

XC_API void WINAPI XDraw_FillSolidRect_(HDRAW hDraw,RECT *pRect,COLORREF clr);
XC_API BOOL WINAPI XDraw_GradientFill2_(HDRAW hDraw,COLORREF color1,COLORREF color2, RECT *pRect,int mode);
XC_API BOOL WINAPI XDraw_GradientFill4_(HDRAW hDraw,COLORREF color1,COLORREF color2,COLORREF color3,COLORREF color4,RECT *pRect,int mode);

XC_API BOOL WINAPI XDraw_FrameRgn_(HDRAW hDraw,HRGN hrgn,HBRUSH hbr,int nWidth,int nHeight);
XC_API int  WINAPI XDraw_FrameRect_(HDRAW hDraw,RECT *pRect,HBRUSH hbr);
XC_API BOOL WINAPI XDraw_FocusRect_(HDRAW hDraw,RECT *pRect);

XC_API BOOL WINAPI XDraw_Rectangle_(HDRAW hDraw,int nLeftRect,int nTopRect,int nRightRect,int nBottomRect);

XC_API BOOL WINAPI XDraw_MoveToEx_(HDRAW hDraw,int X,int Y,LPPOINT lpPoint=NULL);
XC_API BOOL WINAPI XDraw_LineTo_(HDRAW hDraw,int nXEnd,int nYEnd);

XC_API void WINAPI XDraw_Check_(HDRAW hDraw,int x,int y,COLORREF color,BOOL bCheck);

XC_API void WINAPI XDraw_Dottedline_(HDRAW hDraw,int x,int y,int length,COLORREF color,BOOL bHorizontal=TRUE);  //��������

XC_API COLORREF WINAPI XDraw_SetPixel_(HDRAW hDraw,int X,int Y,COLORREF crColor);

XC_API BOOL WINAPI XDraw_DrawIconEx_(HDRAW hDraw,int xLeft,int yTop,HICON hIcon,int cxWidth,int cyWidth,UINT istepIfAniCur,HBRUSH hbrFlickerFreeDraw, UINT diFlags);

XC_API BOOL WINAPI XDraw_BitBlt_(HDRAW hDrawDest,int nXDest,int nYDest,int nWidth,int nHeight,HDC hdcSrc,int nXSrc,int nYSrc,DWORD dwRop);
XC_API BOOL WINAPI XDraw_BitBlt2_(HDRAW hDrawDest,int nXDest,int nYDest,int nWidth,int nHeight,HDRAW hDrawSrc,int nXSrc,int nYSrc,DWORD dwRop);

//�������Ǽ�ͷ
XC_API void WINAPI XDraw_TriangularArrow(HDRAW hDraw,HBRUSH hBrush,int align,int x,int y,int width,int height);

//ͼƬ
XC_API void WINAPI XDraw_HImage_(HDRAW hDraw,HIMAGE hImage,int x,int y);
XC_API void WINAPI XDraw_HImage2_(HDRAW hDraw,HIMAGE hImage,int x,int y,int width,int height);

XC_API void WINAPI XDraw_HImageStretch_(HDRAW hDraw,HIMAGE hImage,int x,int y,int width,int height);
XC_API void WINAPI XDraw_HImageAdaptive_(HDRAW hDraw,HIMAGE hImage,RECT *pRect);

//�����½������Ͻ���,����ƽ������
//flag:ƽ������,0���Ͻ�,1�����½�
XC_API void WINAPI XDraw_HImageExTile_(HDRAW hDraw,HIMAGE hImage,RECT *pRect,int flag=0);

XC_API void WINAPI XDraw_HImageSuper_(HDRAW hDraw,HIMAGE hImage,RECT *pRect);
XC_API void WINAPI XDraw_HImageSuper2_(HDRAW hDraw,HIMAGE hImage,RECT *pRcDest,RECT *pSrcRect);



//�ı�
XC_API int WINAPI XDraw_DrawText_(HDRAW hDraw,wchar_t * lpString,int nCount,RECT* lpRect,UINT uFormat);
XC_API BOOL WINAPI XDraw_TextOut_(HDRAW hDraw,int nXStart,int nYStart,wchar_t * lpString,int cbString);