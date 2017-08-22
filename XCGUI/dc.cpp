/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HBITMAP XDraw_CreateDIBSection(HDC hdc,int cx,int cy)
{
	void *pBits;
	BITMAPINFO info;
	memset(&info.bmiHeader,0,sizeof(BITMAPINFOHEADER));
	info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biBitCount=32;
	info.bmiHeader.biCompression=BI_RGB;
	info.bmiHeader.biPlanes=1;
	info.bmiHeader.biWidth=cx;
	info.bmiHeader.biHeight=cy;
	return CreateDIBSection(hdc,&info,DIB_RGB_COLORS,&pBits,NULL,0);
}


void WINAPI XDraw_FillSolidRect(HDC hdc,RECT *pRect,COLORREF clr)
{
	if(hdc)
	{
		::SetBkColor(hdc, clr);
		::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, pRect, NULL, 0, NULL);
	}
}

BOOL WINAPI XDraw_GradientFill2(HDC hdc,COLORREF color1,COLORREF color2, RECT *pRect,int mode)
{
	BYTE r1=GetRValue(color1);
	BYTE g1=GetGValue(color1);
	BYTE b1=GetBValue(color1);
	BYTE r2=GetRValue(color2);
	BYTE g2=GetGValue(color2);
	BYTE b2=GetBValue(color2);

	if(GRADIENT_FILL_RECT_V==mode)  //��ֱ���
	{
		TRIVERTEX  vert[2];
		vert[0].x=pRect->left;
		vert[0].y=pRect->top;
		vert[0].Red=r1<<8;
		vert[0].Green=g1<<8;
		vert[0].Blue=b1<<8;
		vert[0].Alpha=0;

		vert[1].x=pRect->right;
		vert[1].y=pRect->bottom;
		vert[1].Red=r2<<8;
		vert[1].Green=g2<<8;
		vert[1].Blue=b2<<8;
		vert[1].Alpha=0;

		GRADIENT_RECT  Crect[1];
		Crect[0].UpperLeft=0;
		Crect[0].LowerRight=1;
		return GradientFill(hdc,vert,2,Crect,1,GRADIENT_FILL_RECT_V);
	}else if(GRADIENT_FILL_RECT_H==mode)
	{
		TRIVERTEX  vert[2];
		vert[0].x=pRect->left;
		vert[0].y=pRect->top;
		vert[0].Red=r1<<8;
		vert[0].Green=g1<<8;
		vert[0].Blue=b1<<8;
		vert[0].Alpha=0;

		vert[1].x=pRect->right;
		vert[1].y=pRect->bottom;
		vert[1].Red=r2<<8;
		vert[1].Green=g2<<8;
		vert[1].Blue=b2<<8;
		vert[1].Alpha=0;

		GRADIENT_RECT  Crect[1];
		Crect[0].UpperLeft=0;
		Crect[0].LowerRight=1;
		return GradientFill(hdc,vert,2,Crect,1,GRADIENT_FILL_RECT_H);
	}
	return FALSE;
}

BOOL WINAPI XDraw_GradientFill4(HDC hdc,COLORREF color1,COLORREF color2,COLORREF color3,COLORREF color4,RECT *pRect,int mode)
{
	BYTE r1=GetRValue(color1);
	BYTE g1=GetGValue(color1);
	BYTE b1=GetBValue(color1);
	BYTE r2=GetRValue(color2);
	BYTE g2=GetGValue(color2);
	BYTE b2=GetBValue(color2);
	BYTE r3=GetRValue(color3);
	BYTE g3=GetGValue(color3);
	BYTE b3=GetBValue(color3);
	BYTE r4=GetRValue(color4);
	BYTE g4=GetGValue(color4);
	BYTE b4=GetBValue(color4);

	if(GRADIENT_FILL_RECT_V==mode)  //��ֱ���
	{
		int halfY=pRect->top+(pRect->bottom-pRect->top)/2; //�м�����
		TRIVERTEX  vert[4];
		vert[0].x=pRect->left;
		vert[0].y=pRect->top;
		vert[0].Red=r1<<8;
		vert[0].Green=g1<<8;
		vert[0].Blue=b1<<8;
		vert[0].Alpha=0;

		vert[1].x=pRect->right;
		vert[1].y=halfY;
		vert[1].Red=r2<<8;
		vert[1].Green=g2<<8;
		vert[1].Blue=b2<<8;
		vert[1].Alpha=0;

		vert[2].x=pRect->left;
		vert[2].y=halfY;
		vert[2].Red=r3<<8;
		vert[2].Green=g3<<8;
		vert[2].Blue=b3<<8;
		vert[2].Alpha=0;

		vert[3].x=pRect->right;
		vert[3].y=pRect->bottom;
		vert[3].Red=r4<<8;
		vert[3].Green=g4<<8;
		vert[3].Blue=b4<<8;
		vert[3].Alpha=0;

		GRADIENT_RECT  Crect[2];
		Crect[0].UpperLeft=0;
		Crect[0].LowerRight=1;

		Crect[1].UpperLeft=2;
		Crect[1].LowerRight=3;
		return GradientFill(hdc,vert,4,Crect,2,GRADIENT_FILL_RECT_V);
	}else if(GRADIENT_FILL_RECT_H==mode)
	{
		int halfX=pRect->left+(pRect->right-pRect->left)/2; //�м�����
		TRIVERTEX  vert[4];
		vert[0].x=pRect->left;
		vert[0].y=pRect->top;
		vert[0].Red=r1<<8;
		vert[0].Green=g1<<8;
		vert[0].Blue=b1<<8;
		vert[0].Alpha=0;

		vert[1].x=halfX;
		vert[1].y=pRect->bottom;
		vert[1].Red=r2<<8;
		vert[1].Green=g2<<8;
		vert[1].Blue=b2<<8;
		vert[1].Alpha=0;

		vert[2].x=halfX;
		vert[2].y=pRect->top;
		vert[2].Red=r3<<8;
		vert[2].Green=g3<<8;
		vert[2].Blue=b3<<8;
		vert[2].Alpha=0;

		vert[3].x=pRect->right;
		vert[3].y=pRect->bottom;
		vert[3].Red=r4<<8;
		vert[3].Green=g4<<8;
		vert[3].Blue=b4<<8;
		vert[3].Alpha=0;

		GRADIENT_RECT  Crect[2];
		Crect[0].UpperLeft=0;
		Crect[0].LowerRight=1;

		Crect[1].UpperLeft=2;
		Crect[1].LowerRight=3;
		return GradientFill(hdc,vert,4,Crect,2,GRADIENT_FILL_RECT_H);
	}
	return FALSE;
}

void XDraw_Dottedline(HDC hdc,int x,int y,int length,COLORREF color,BOOL bHorizontal)  //��������
{
	int len=length/2;
	if(bHorizontal)
	{
		for(int i=0;i<len;i++)
		{
			::SetPixel(hdc,x,y,color);
			x+=2;
		}
	}else
	{
		for(int i=0;i<len;i++)
		{
			::SetPixel(hdc,x,y,color);
			y+=2;
		}
	}
}

void WINAPI XDraw_Check(HDC hdc,int x,int y,COLORREF color,BOOL bCheck)
{
	int top=y;
	int left=x;
	//���Ʊ߿�
	HPEN hPenBk=CreatePen(PS_SOLID,1,color);
	HGDIOBJ hOld=SelectObject(hdc,hPenBk);
	Rectangle(hdc,left,top,left+13,top+13);
	SelectObject(hdc,hOld);
	DeleteObject(hPenBk);

	//���Ʊ���
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	LinearGradientBrush  brush(Rect(left+1,top+1,10,10),Color(180,180,180),Color(255,255,255),LinearGradientModeForwardDiagonal);
	graphics.FillRectangle(&brush,Rect(left+1,top+1,10,10));

	if(bCheck)
	{
		//���ƹ�ѡ
		HPEN hPen=CreatePen(PS_SOLID,2,RGB(66,100,147));
		HGDIOBJ hOld=SelectObject(hdc,hPen);
		MoveToEx(hdc,left+2,top+6,NULL);
		LineTo(hdc,left+5,top+9);

		MoveToEx(hdc,left+4,top+9,NULL);
		LineTo(hdc,left+10,top+3);

		SelectObject(hdc,hOld);
		DeleteObject(hPen);
	}
}

Status XDraw_GraphicsDrawImage(HDC hdc,Image *image,int x,int y)
{
	Graphics graphics(hdc);
	Status status=graphics.DrawImage(image,x,y,image->GetWidth(),image->GetHeight());
	return status;
}

Status XDraw_GraphicsDrawImageEx(HDC hdc,Image *image,int x,int y,int width,int height)
{
	Graphics graphics(hdc);
	Status status=graphics.DrawImage(image,x,y,width,height);
	return status;
}

//������ͼƬ
//x:Ŀ��X
//y:Ŀ��Y
void WINAPI XDraw_HImage(HDC hdc,HIMAGE hImage,int x,int y)
{
	if(NULL==hdc) return ;
	IsHImageDebug(hImage,__FUNCTION__);

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;

	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	if(!pImage->bTransparentColor)
	{
		Graphics graphics(hdc);
		graphics.DrawImage(pImageX,x,y,pImageX->GetWidth(),pImageX->GetHeight());
	}else
	{
		Graphics graphics(hdc);
		Rect destRect;
		destRect.X=x;
		destRect.Y=y;
		destRect.Width=pImageX->GetWidth();
		destRect.Height=pImageX->GetHeight();

		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);

		ImageAttributes ImgAtt;
		ImgAtt.SetRemapTable(1,&newToold);

		graphics.DrawImage(pImageX, destRect, 0, 0,
			pImageX->GetWidth(),
			pImageX->GetHeight(),
			UnitPixel, &ImgAtt);
	}
}

//������ͼ
//x:Ŀ��X
//y:Ŀ��Y
//height:Ŀ����
//height:Ŀ��߶�
void WINAPI XDraw_HImageStretch(HDC hdc,HIMAGE hImage,int x,int y,int width,int height)
{
	if(NULL==hdc) return ;
	IsHImageDebug(hImage,__FUNCTION__);

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	ImageAttributes ImgAtt;
	if(pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1,&newToold);
	}

	Graphics graphics(hdc);
	Rect destRect;
	destRect.X=x;
	destRect.Y=y;
	destRect.Width=width;
	destRect.Height=height;

	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(pImageX, destRect, 0, 0,
		pImageX->GetWidth(),
		pImageX->GetHeight(),
		UnitPixel, &ImgAtt);
}

//����ͼƬ����,�Զ�����:��ͨ,����,����ӦͼƬ
//pRect:Ŀ������
void WINAPI XDraw_HImageSuper(HDC hdc,HIMAGE hImage,RECT *pRect)
{
	if(NULL==hdc) return ;
	IsHImageDebug(hImage,__FUNCTION__);
	switch(XImage_GetDrawType(hImage))
	{
	case XC_IMAGE_DEFAULT:
		XDraw_HImage(hdc,hImage,pRect->left,pRect->top);
		break;
	case XC_IMAGE_STRETCH:
		XDraw_HImageStretch(hdc,hImage,pRect->left,pRect->top,pRect->right-pRect->left,
			pRect->bottom-pRect->top);
		break;
	case XC_IMAGE_ADAPTIVE:
		XDraw_HImageAdaptive(hdc,hImage,pRect);
		break;
	case XC_IMAGE_TILE:
		XDraw_HImageExTile(hdc,hImage,pRect);
		break;
	}
}

//����ͼƬָ������
void WINAPI XDraw_HImageEx(HDC hdc,HIMAGE hImage,int x,int y,int width,int height,int srcX,int srcY)
{
	Graphics graphics(hdc);

	Rect destRect;			
	destRect.X=x;
	destRect.Y=y;
	destRect.Width=width;
	destRect.Height=height;

	ImageAttributes ImgAtt;

	ximage_  *pImage=(ximage_*)hImage;

	int srcWidth=width;
	int srcHeight=height;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	if(pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1,&newToold);
	}

	if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
		destRect,                
		srcX,    //srcX
		srcY,       //srcY
		destRect.Width,   //cx
		destRect.Height,   //cy
		UnitPixel,&ImgAtt,NULL,NULL))
	{ 
		XTRACE("ͼƬ��Ч \n");
	}
}

void WINAPI XDraw_HImageExTile(HDC hdc,HIMAGE hImage,RECT *pRect,int flag)
{
	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	RECT rect=*pRect;

	Graphics graphics(hdc);
	HRGN hRgn=CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
	SelectClipRgn(hdc,hRgn);
	if(0==flag)
	{
		int posx=rect.left;
		int posy=rect.top;
		int posx2=posx;
		int posy2=posy;
		int imageWidth=pImageX->GetWidth();
		int imageHeight=pImageX->GetHeight();

		while(posy2<rect.bottom)
		{
			while(posx2<rect.right)
			{
				XDraw_HImage(hdc,hImage,posx2,posy2);
				posx2+=imageWidth;
			}
			posx2=posx;
			posy2+=imageHeight;
		}
	}else if(1==flag)
	{
		int posx=rect.left;
		int posy=rect.bottom;
		int posx2=posx;
		int posy2=posy;
		int imageWidth=pImageX->GetWidth();
		int imageHeight=pImageX->GetHeight();

		while(posy2>pRect->top)
		{
			posy2-=imageHeight;
			while(posx2<rect.right)
			{
				XDraw_HImage(hdc,hImage,posx2,posy2);
				posx2+=imageWidth;
			}
			posx2=posx;
		}
	}
	DeleteObject(hRgn);
	SelectClipRgn(hdc,NULL);
}

void WINAPI XDraw_HImageAdaptive(HDC hdc,HIMAGE hImage,RECT *pRect)
{
	if(NULL==hdc) return ;
	IsHImageDebug(hImage,__FUNCTION__);

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	int  rectWidth=pRect->right-pRect->left;
	int  rectHeight=pRect->bottom-pRect->top;

	RECT rect=*pRect;

	Graphics graphics(hdc);
	Rect destRect1,destRect2,destRect3,destRect4,destRect5,destRect6,destRect7,destRect8,destRect9;

	destRect1.X=rect.left;
	destRect1.Y=rect.top;
	destRect1.Width=pImage->imageX1;
	destRect1.Height=pImage->imageY1;

	destRect3.Y=rect.top;
	destRect3.Width=pImage->imageWidth-pImage->imageX2;
	destRect3.Height=pImage->imageY1;
	destRect3.X=rect.right-destRect3.Width;

	destRect2.X=rect.left+pImage->imageX1;
	destRect2.Y=rect.top;
	destRect2.Width=rectWidth-destRect1.Width-destRect3.Width;
	destRect2.Height=pImage->imageY1;

	destRect7.X=rect.left;
	destRect7.Width=pImage->imageX1;
	destRect7.Height=pImage->imageHeight-pImage->imageY2;
	destRect7.Y=rect.bottom-destRect7.Height;

	destRect4.X=rect.left;
	destRect4.Y=rect.top+pImage->imageY1;
	destRect4.Width=pImage->imageX1;
	destRect4.Height=rectHeight-destRect1.Height-destRect7.Height;

	destRect9.Height=destRect7.Height;
	destRect9.Width=destRect3.Width;
	destRect9.X=rect.right-destRect9.Width;
	destRect9.Y=rect.bottom-destRect9.Height;

	//6
	destRect6.Height=rectHeight-destRect3.Height-destRect9.Height;
	destRect6.Width=destRect3.Width;
	destRect6.X=rect.right-destRect6.Width;
	destRect6.Y=rect.top+pImage->imageY1;

	//8
	destRect8.X=rect.left+pImage->imageX1;
	destRect8.Height=destRect7.Height;
	destRect8.Width=destRect2.Width;
	destRect8.Y=rect.bottom-destRect8.Height;

	//5
	destRect5.X=rect.left+pImage->imageX1;
	destRect5.Y=rect.top+pImage->imageY1;
	destRect5.Height=destRect4.Height;
	destRect5.Width=destRect2.Width;

	ImageAttributes ImgAtt;
    ImgAtt.SetWrapMode(WrapModeTileFlipXY);

	if(pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1,&newToold);
	}

	//1
	if(destRect1.Width>0 && destRect1.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect1,                
			0,                //srcX
			0,                //srcY
			pImage->imageX1,  //cx
			pImage->imageY1,  //cy
			UnitPixel,&ImgAtt,NULL,NULL)) { XTRACE("ͼƬ��Ч \n"); }
	}

	//2
	if(destRect2.Width>0 && destRect2.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect2,                
			pImage->imageX1,  //srcX
			0,                //srcY
			pImage->imageX2-pImage->imageX1,//cx
			pImage->imageY1,  //cy
			UnitPixel,&ImgAtt,NULL,NULL)){ XTRACE("ͼƬ��Ч \n"); }
	}

	//3
	if(destRect3.Width>0 && destRect3.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect3,                
			pImage->imageX2,   //srcX
			0,                 //srcY
			destRect3.Width,   //cx
			pImage->imageY1,   //cy
			UnitPixel,&ImgAtt,NULL,NULL)) { XTRACE("ͼƬ��Ч \n"); }
	}

	//4
	if(destRect4.Width>0 && destRect4.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect4,                
			0,                              //srcX
			pImage->imageY1,                //srcY
			pImage->imageX1,                //cx
			pImage->imageY2-pImage->imageY1,//cy
			UnitPixel,&ImgAtt,NULL,NULL)) { XTRACE("ͼƬ��Ч \n"); }
	}
	//5
	if(destRect5.Width>0 && destRect5.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect5,                
			pImage->imageX1,                              //srcX
			pImage->imageY1,                //srcY
			pImage->imageX2-pImage->imageX1,                //cx
			pImage->imageY2-pImage->imageY1,//cy
			UnitPixel,&ImgAtt,NULL,NULL)) { XTRACE("ͼƬ��Ч \n"); }
	}
	//6
	if(destRect6.Width>0 && destRect6.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect6,                
			pImage->imageX2,         //srcX
			pImage->imageY1,         //srcY
			destRect6.Width,         //cx
			pImage->imageY2-pImage->imageY1,//cy
			UnitPixel,&ImgAtt,NULL,NULL))  { XTRACE("ͼƬ��Ч \n"); }
	}
	//7
	if(destRect7.Width>0 && destRect7.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect7,                
			0,                       //srcX
			pImage->imageY2,         //srcY
			pImage->imageX1,         //cx
			destRect7.Height,        //cy
			UnitPixel,&ImgAtt,NULL,NULL))  { XTRACE("ͼƬ��Ч \n"); }
	}
	//8
	if(destRect7.Width>0 && destRect7.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect8,                
			pImage->imageX1,         //srcX
			pImage->imageY2,         //srcY
			pImage->imageX2-pImage->imageX1,  //cx
			destRect8.Height,        //cy
			UnitPixel,&ImgAtt,NULL,NULL)) { XTRACE("ͼƬ��Ч \n"); }
	}
	//9
	if(destRect7.Width>0 && destRect7.Height>0)
	{
		if(Gdiplus::Ok!=graphics.DrawImage(pImageX,
			destRect9,                
			pImage->imageX2,         //srcX
			pImage->imageY2,         //srcY
			destRect9.Width,         //cx
			destRect9.Height,        //cy
			UnitPixel,&ImgAtt,NULL,NULL)) { XTRACE("ͼƬ��Ч \n"); }
	}
//	BitBlt(hdc,pRect->left,pRect->top,rectWidth,rectHeight,memDC,0,0,SRCCOPY);
//	DeleteDC(memDC);
//	DeleteObject(memBM);
}

//GDI+ ����Բ�Ǿ���
GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded)
{
	//ASSERT (percentageRounded >= 1 && percentageRounded <= 100);

	INT left  = min(topLeft.X, bottomRight.X);
	INT right = max(topLeft.X, bottomRight.X);

	INT top    = min(topLeft.Y, bottomRight.Y);
	INT bottom = max(topLeft.Y, bottomRight.Y);

	INT offsetX = (right-left)*percentageRounded/100;  
	INT offsetY = (bottom-top)*percentageRounded/100;

	GraphicsPath pt;
	GraphicsPath * path = pt.Clone();

	path->AddArc(right-offsetX, top, offsetX, offsetY, 270, 90);
	path->AddArc(right-offsetX, bottom-offsetY, offsetX, offsetY, 0, 90);
	path->AddArc(left, bottom - offsetY, offsetX, offsetY, 90, 90);
	path->AddArc(left, top, offsetX, offsetY, 180, 90);
	path->AddLine(left + offsetX, top, right - offsetX/2, top);
	return path;
}

//GDI+���ƾ�����Ӱ
void DrawShadow(Graphics &g, GraphicsPath *ButtonPath)
{
    g.SetPageUnit(UnitPixel); //����Graphics�����굥λΪ����

    GraphicsPath &ShadowPath = *(ButtonPath->Clone());    //����һ����ť����·���ĸ���������������Ӱ����·��

    // �����Ӱ����
    Matrix ShadowMatrix;
    ShadowMatrix.Translate(5, 5 );// ƽ�ƣ�ShadowSize����Ӱ����������������������������·��ƶ��ģ����Ը���ʵ������޸ġ�
    ShadowPath.Transform(&ShadowMatrix);    // Ӧ�þ���

    Region ButtonRegion(ButtonPath);  //���ð�ť��·��������ť����
    Region ShadowRegion(&ShadowPath);  //������Ӱ·��������Ӱ������
    
    ShadowRegion.Exclude(&ButtonRegion); // �����������͵ó��˴������Ӱ�����ų�����Ӱ����Ͱ�ť�����غϵĲ��֡�
    
    // ��ʼ�����仭ˢ
    PathGradientBrush brush(&ShadowPath);
    brush.SetCenterColor(Color(255,0,0,0)); // �������õ���·�����仭ˢ
    Color colors[] ={Color(0, 0, 0, 0)};
    int count = 1;
    brush.SetSurroundColors(colors, &count);
    brush.SetFocusScales(0.75f, 0.75f);  //�Խ���Ч�����е�����ʹ�������Ȼ������ʵ�������ǶԽ���Ч���������š������Ǻ�����������������ű�����

    g.FillRegion(&brush, &ShadowRegion);

    delete &ShadowPath; //������ɾ��Clone�����ĸ�����
}

void Draw_GetData(HDC hdc,bitmap_info_ &info)
{
	if(NULL==hdc) return ;
	HBITMAP  hBitmap=(HBITMAP)GetCurrentObject(hdc,OBJ_BITMAP);

	BITMAP  bitmap;
	int res=GetObject(hBitmap,sizeof(BITMAP),(LPSTR)&bitmap);
	if(0==res) return ;

	if(bitmap.bmWidth<1 || bitmap.bmHeight<1 )
		return ;

	int bitSize=bitmap.bmWidth*bitmap.bmHeight*4; //rcCli.right*rcCli.bottom*4;  //�ܴ�С
	int lenrow=bitmap.bmWidth*4;     //rcCli.right*4; //�г���

	BYTE *pData=(BYTE*)malloc(bitSize);

	GetBitmapBits(hBitmap,bitSize,pData);

	info.hBitmap=hBitmap;
	info.data=pData;
	info.bitSize=bitSize;
	info.width=bitmap.bmWidth;
	info.height=bitmap.bmHeight;
}

void Draw_SetPixelValue(bitmap_info_ &info,int x,int y,COLORREF color)
{
	COLORREF *pArray=(COLORREF*)info.data;
	
	int pos=y*info.width+x;
	pArray[pos]=color;
}

//����ֱ�߻�����
void Draw_DrawStraightLine(bitmap_info_ &info,int x1,int y1,int x2,int y2,COLORREF color)
{
	COLORREF *pArray=(COLORREF*)info.data;
	for(int x=x1;x<=x2;x++)
	{
		for(int y=y1;y<=y2;y++)
		{
			int pos=y*info.width+x;
			pArray[pos]=color;
		}
	}
}

void Draw_SetData(bitmap_info_ &info)
{
	SetBitmapBits(info.hBitmap,info.bitSize,info.data);
	free(info.data);
}

void Draw_DrawShadowLine(HDC hdc,RECT *pRect,bitmap_info_ &info)
{
	BYTE color=0;
	BYTE add[8]={4, 10, 20, 30, 60, 83,111, 255};  //15
	for(int i=0;i<7;i++)
	{
		color=add[i];
		//��
		Draw_DrawStraightLine(info,pRect->left+i-7,pRect->top+5,pRect->left+i-7,pRect->bottom-5,RGBA(color,0,0,0));
		//��
		Draw_DrawStraightLine(info,pRect->left+5,pRect->top+i-7,pRect->right-5,pRect->top+i-7,RGBA(color,0,0,0));
		//��
		Draw_DrawStraightLine(info,pRect->right+7-i,pRect->top+5,pRect->right+7-i,pRect->bottom-7,RGBA(color,0,0,0));
		//��
		Draw_DrawStraightLine(info,pRect->left+5,pRect->bottom+7-i,pRect->right-5,pRect->bottom+7-i,RGBA(color,0,0,0));
	}
}//Draw_DrawShadowLine()

BYTE shadow_data[16][16]=
{  //0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15
	{0, 0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  3,  3,  3,  4,  4},  //0
	{0, 0,  0,  0,  1,  1,  2,  3,  5,  6,  7,  8,  9,  10, 11, 10}, //1
	{0, 0,  1,  1,  2,  4,  5,  8,  10, 13, 15, 18, 20, 21, 22, 20}, //2
	{0, 0,  1,  3,  4,  7,  10, 14, 18, 23, 27, 30, 33, 36, 38, 30}, //3
	{0, 1,  2,  5,  8,  12, 17, 23, 29, 35, 41, 47, 51, 54, 57, 60}, //4
	{0, 2,  4,  7,  12, 18, 25, 33, 43, 51, 60, 67, 72, 77, 80, 83}, //5
	{1, 2,  6,  10, 17, 25, 35, 47, 59, 70, 81, 90, 98, 103,107,111}, //6
	{1, 3,  8,  14, 23, 34, 47, 62, 78, 255,255,255,255,255,255,255}, //7
	{1, 5,  10, 18, 29, 43, 59, 78, 255}, //8
	{2, 6,  13, 23, 36, 52, 71, 78, 255}, //9
	{2, 7,  15, 27, 42, 60, 81, 255}, //10
	{3, 8,  18, 31, 47, 67, 90, 255}, //11
	{3, 10, 20, 34, 51, 73, 98, 255}, //12
	{3, 10, 21, 36, 55, 77,104, 255}, //13
	{4, 11, 22, 38, 57, 80,108, 255}, //14
	{4, 10, 20, 30, 60, 83,111, 255}, //15
};
void Draw_DrawWndShadow(HDC hdc,RECT *pRect)
{
	RECT rect=*pRect;
	rect.right--;
	rect.bottom--;
	bitmap_info_ info;
	Draw_GetData(hdc,info);

	Draw_DrawShadowLine(hdc,&rect,info);

	BYTE color=0;
	for(int x=0;x<16;x++)
	{
		for(int y=0;y<16;y++)
		{
			color=shadow_data[x][y];
			if(255==color)
				break;

			//���Ͻ�
			Draw_SetPixelValue(info,rect.left-7+x,rect.top-7+y,RGBA(color,0,0,0));

			//���½�
			Draw_SetPixelValue(info,rect.left-7+x,rect.bottom+7-y,RGBA(color,0,0,0));

			//���Ͻ�
			Draw_SetPixelValue(info,rect.right+7-x,rect.top-7+y,RGBA(color,0,0,0));

			//���½�
			Draw_SetPixelValue(info,rect.right+7-x,rect.bottom+7-y,RGBA(color,0,0,0));
		}
	}
	Draw_SetData(info);
}

///////////////////////////////////////////////////////////

void Draw_SetTransparent(HDC hdc,BYTE alpha)  //�ֲ㴰�� ����ָ������͸����
{
	if(NULL==hdc) return ;
	HBITMAP  hBitmap=(HBITMAP)GetCurrentObject(hdc,OBJ_BITMAP);

	BITMAP  bitmap;
	int res=GetObject(hBitmap,sizeof(BITMAP),(LPSTR)&bitmap);
	if(0==res) return ;

	if(bitmap.bmWidth<1 || bitmap.bmHeight<1 )
		return ;

	int bitSize=bitmap.bmWidth*bitmap.bmHeight*4; //�ܴ�С
	int lenrow=bitmap.bmWidth*4;     //�г���

	BYTE *pBuf=(BYTE*)malloc(bitSize);

	GetBitmapBits(hBitmap,bitSize,pBuf);

	for(int i=0;i<bitSize;i+=4)
	{
		pBuf[i+3]=alpha; 
	}

	SetBitmapBits(hBitmap,bitSize,pBuf);
	free(pBuf);
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

/// @defgroup xc_draw ͼ�λ���
/// @ingroup  groupOther
/// ͼ�λ��ƽӿ�,֧�ֻ���ƫ��������,���GDI��������,�Լ�Ԥ��GDIй¶,���ٴ�����д.\n
/// XDraw_Destroy_()����ͼ�λ���ģ��ʵ�����,���û�����GDI����(λͼ,��ˢ,����,����)��������,ͼ�λ���ģ������ʱ���Զ����û�����,��ֹGDIй¶,���һ�ԭ����ʼ״̬.\n
/// XDraw_GetOffset_()��ԭ��ʼ״̬,���û����øú���,��ԭ����ʼ��״̬,�ͷ��û�������GDI����,�ָ���ʼѡ������(λͼ,��ˢ,����,����).
/// @{


/// @brief    ����ͼ�λ���ģ��ʵ��.
/// @param hdc  �豸�����ľ��HDC.
/// @return  ͼ�λ���ģ��ʵ�����.
HDRAW WINAPI XDraw_Create_(HDC hdc) //����
{
	if(NULL==hdc) return NULL;
	draw_xc_ *pDraw=(draw_xc_*)malloc(sizeof(draw_xc_));
	if(pDraw)
	{
		memset(pDraw,0,sizeof(draw_xc_));
		pDraw->hdc=hdc;
		pDraw->hArrayTemp=XArray_Create();
		pDraw->object.type=XC_HDRAW;
		return (HDRAW)pDraw;
	}
	return NULL;
}

/// @brief    ����ͼ�λ���ģ��ʵ�����.
/// @param hDraw  ͼ�λ��ƾ��.
void  WINAPI XDraw_Destroy_(HDRAW hDraw) //����
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	XDraw_RestoreGDIOBJ_(hDraw);
	XArray_Destroy(pDraw->hArrayTemp);
	free(hDraw);
}

/// @brief  ��������ƫ����,X����ƫ��Ϊ����,����ƫ��Ϊ����.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param x  X��ƫ����.
/// @param y  Y��ƫ����.
void  WINAPI XDraw_SetOffset_(HDRAW hDraw,int x,int y) //��������ƫ����
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	pDraw->x=x;
	pDraw->y=y;
}

/// @brief  ��ȡ����ƫ����,X����ƫ��Ϊ����,����ƫ��Ϊ����.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param pX  ����X��ƫ����.
/// @param pY  ����Y��ƫ����.
void  WINAPI XDraw_GetOffset_(HDRAW hDraw,out_ int *pX,out_ int *pY) //��ȡ����ƫ����
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	*pX=pDraw->x;
	*pY=pDraw->y;
}

/// @brief ��ȡ�󶨵��豸������HDC.
/// @param hDraw  ͼ�λ��ƾ��.
/// @return ����HDC���. 
HDC WINAPI XDraw_GetHDC_(HDRAW hDraw)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	return ((draw_xc_*)hDraw)->hdc;
}

/// @brief ��ԭ״̬,�ͷ��û��󶨵�GDI����,���续ˢ,����.
/// @param hDraw  ͼ�λ��ƾ��. 
void  WINAPI  XDraw_RestoreGDIOBJ_(HDRAW hDraw)  //��ԭ״̬,�ͷ��û��󶨵�GDI����
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;

	//��ԭ�󶨵�GDI����
	if(pDraw->OBJ_BITMAP_O)
	{
		SelectObject(pDraw->hdc,pDraw->OBJ_BITMAP_O);
		pDraw->OBJ_BITMAP_O=NULL;
	}
	if(pDraw->OBJ_BRUSH_O)
	{
		SelectObject(pDraw->hdc,pDraw->OBJ_BRUSH_O);
		pDraw->OBJ_BRUSH_O=NULL;
	}
	if(pDraw->OBJ_FONT_O)
	{
		SelectObject(pDraw->hdc,pDraw->OBJ_FONT_O);
		pDraw->OBJ_FONT_O=NULL;
	}
	if(pDraw->OBJ_PEN_O)
	{
		SelectObject(pDraw->hdc,pDraw->OBJ_PEN_O);
		pDraw->OBJ_PEN_O=NULL;
	}

	//�ͷ���ʱ������GDI����
	int count=XArray_GetCount(pDraw->hArrayTemp);
	for(int i=0;i<count;i++)
	{
		DeleteObject(XArray_GetAt(pDraw->hArrayTemp,i));
	}
	XArray_DeleteAll(pDraw->hArrayTemp);
}

/// @brief �����ı�������ɫ.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param crColor RGB��ɫֵ
/// @return ������ǰ����ɫ.
COLORREF WINAPI XDraw_SetTextColor_(HDRAW hDraw,COLORREF crColor)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	return SetTextColor(((draw_xc_*)hDraw)->hdc,crColor);
}

/// @brief ѡ�����ָ�����豸�����ģ�DC��,�µĶ���,ȡ����ǰ����ͬ���͵Ķ���.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param hObj GDI����
/// @return ������ǰ��GDI����.
HGDIOBJ WINAPI XDraw_SelectObject_(HDRAW hDraw,HGDIOBJ hObj)
{
	IsDrawDebug(hDraw,__FUNCTION__);

	draw_xc_ *pDraw=(draw_xc_*)hDraw;

	DWORD type=GetObjectType(hObj);
	if(0==type) return NULL;

	HGDIOBJ hResult=SelectObject(pDraw->hdc,hObj);

	switch(type)
	{
	case OBJ_BITMAP:
		if(NULL==pDraw->OBJ_BITMAP_O)
			pDraw->OBJ_BITMAP_O=hResult;
		else if(hObj==pDraw->OBJ_BITMAP_O)
			pDraw->OBJ_BITMAP_O=NULL;
		break;
	case OBJ_BRUSH:
		if(NULL==pDraw->OBJ_BRUSH_O)
			pDraw->OBJ_BRUSH_O=hResult;
		else if(hObj==pDraw->OBJ_BRUSH_O)
			pDraw->OBJ_BRUSH_O=NULL;
		break;
	case OBJ_FONT:
		if(NULL==pDraw->OBJ_FONT_O)
			pDraw->OBJ_FONT_O=hResult;
		else if(hObj==pDraw->OBJ_FONT_O)
			pDraw->OBJ_FONT_O=NULL;
		break;
	case OBJ_PEN: 
		if(NULL==pDraw->OBJ_PEN_O)
			pDraw->OBJ_PEN_O=hResult; 
		else if(hObj==pDraw->OBJ_PEN_O)
			pDraw->OBJ_PEN_O=NULL; 
		break;
//	case OBJ_REGION: break;
	}
	return hResult;
}

/// @brief ɾ��һ���߼���,����,����,λͼ,����,���ɫ��,�ͷ���������������ϵͳ��Դ,����ɾ����,ָ���ľ��������Ч.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param hObj GDI����
/// @return ����ɹ�����ֵ��0.
BOOL WINAPI XDraw_DeleteObject_(HDRAW hDraw,HGDIOBJ hObj)
{
	IsDrawDebug(hDraw,__FUNCTION__);

	if(NULL==hObj) return FALSE;

	draw_xc_ *pDraw=(draw_xc_*)hDraw;

	HGDIOBJ hTemp=NULL;
	int count=XArray_GetCount(pDraw->hArrayTemp);
	for(int i=0;i<count;i++)
	{
		hTemp =(HGDIOBJ)XArray_GetAt(pDraw->hArrayTemp,i);
		if(hTemp==hObj)
		{
			XArray_DeleteIndex(pDraw->hArrayTemp,i);
			break;
		}
	}
	return DeleteObject(hObj);
}

/// @brief ѡ��һ��������Ϊ��ǰ�ü�����.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param hRgn  ������.
/// @return ����ֵָ�������ĸ����ԣ�����������ֵ֮һ.\n
/// NULLREGION Region is empty.\n
/// SIMPLEREGION Region is a single rectangle.\n
/// COMPLEXREGION Region is more than one rectangle.\n
/// ERROR An error occurred. (The previous clipping region is unaffected).
int WINAPI XDraw_SelectClipRgn_(HDRAW hDraw,HRGN hRgn)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	return SelectClipRgn(pDraw->hdc,hRgn);
}

/// @brief ��������ָ���Ĵ�ɫ�߼�ˢ.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param crColor ��ˢ��ɫ.
/// @return ��������ɹ�,����ֵ��ʶһ���߼�ˢ,�������ʧ��,����ֵ��NULL.
HBRUSH WINAPI XDraw_CreateSolidBrush_(HDRAW hDraw,COLORREF crColor)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	HBRUSH hBrush=CreateSolidBrush(crColor);
	if(hBrush)
	{
		XArray_Add(pDraw->hArrayTemp,hBrush);
		return hBrush;
	}
	return NULL;
}

/// @brief ����һ���߼���,��ָ������ʽ,��Ⱥ���ɫ,���ıʿ���ѡ���豸������,���ڻ�������������.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param fnPenStyle ������ɫ.
/// @param nWidth ���ʿ��.
/// @param crColor ��ɫ.
/// @return ��������ɹ�,����ֵ��һ�����,��ʶһ���߼���,�������ʧ��,����ֵ��NULL.
HPEN WINAPI XDraw_CreatePen_(HDRAW hDraw,int fnPenStyle,int nWidth,COLORREF crColor)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	HPEN hPen=CreatePen(fnPenStyle,nWidth,crColor);
	if(hPen)
	{
		XArray_Add(pDraw->hArrayTemp,hPen);
		return hPen;
	}
	return NULL;
}

/// @brief ����һ��Բ�ǵľ�������.
/// @param hDraw  ͼ�λ��ƾ��.
/// @param nLeftRect   X-��������Ͻ�.
/// @param nTopRect    Y-�������Ͻ�����
/// @param nRightRect  X-�������½�
/// @param nBottomRect Y-�������½�
/// @param nWidthEllipse   ��Բ�Ŀ��.
/// @param nHeightEllipse  ��Բ�ĸ߶�.
/// @return ��������ɹ�,����ֵ�Ǹ�����ľ��,�������ʧ��,����ֵ��NULL.
HRGN WINAPI XDraw_CreateRoundRectRgn_(HDRAW hDraw,int nLeftRect,int nTopRect,int nRightRect,int nBottomRect,int nWidthEllipse,int nHeightEllipse)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;

	HRGN hRgn= CreateRoundRectRgn(nLeftRect+pDraw->x,nTopRect+pDraw->y,nRightRect+pDraw->x,nBottomRect+pDraw->y,nWidthEllipse,nHeightEllipse);
	if(hRgn)
	{
		XArray_Add(pDraw->hArrayTemp,hRgn);
		return hRgn;
	}
	return NULL;
}

/// @brief ����һ�����������.
/// @param hDraw ͼ�λ��ƾ��.
/// @param pPt  POINT����.
/// @param cPoints �����С.
/// @param fnPolyFillMode ��������ģʽ,ָ������ȷ���ڸõ������������ģʽ,�����������������ֵ֮һ.\n
///  ALTERNATE Selects alternate mode (fills area between odd-numbered and even-numbered polygon sides on each scan line).\n
///  WINDING Selects winding mode (fills any region with a nonzero winding value).
/// @return  ��������ɹ�,����ֵ�Ǹ�����ľ��,�������ʧ��,����ֵ��NULL.
HRGN WINAPI XDraw_CreatePolygonRgn_(HDRAW hDraw,POINT *pPt,int cPoints,int fnPolyFillMode)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	for(int i=0;i<cPoints;i++)
	{
		pPt[i].x+=pDraw->x;
		pPt[i].y+=pDraw->y;
	}
	HRGN hRgn= CreatePolygonRgn(pPt, cPoints, fnPolyFillMode);
	if(hRgn)
	{
		XArray_Add(pDraw->hArrayTemp,hRgn);
		return hRgn;
	}
	return NULL;
}
/// @brief ͨ��ʹ��ָ����ˢ�����һ������,�˹��ܰ������Ͷ����ı߽�,�����������ε��ұߺ͵ײ��߽�.
/// @param hDraw ͼ�λ��ƾ��.
/// @param pRect ��������.
/// @param hbr ��ˢ���.
/// @return ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
int WINAPI XDraw_FillRect_(HDRAW hDraw,RECT *pRect,HBRUSH hbr)
{
	IsDrawDebug(hDraw,__FUNCTION__);

	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rc=*pRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;

	return FillRect(pDraw->hdc, &rc, hbr);
}
/// @brief ͨ��ʹ��ָ���Ļ�ˢ���һ������.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hrgn ������.
/// @param hbr ��ˢ���.
/// @return ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
BOOL WINAPI XDraw_FillRgn_(HDRAW hDraw,HRGN hrgn,HBRUSH hbr)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	return FillRgn(((draw_xc_*)hDraw)->hdc, hrgn, hbr);
}

/// @brief ���ָ������,ʹ�ø�������ɫ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param pRect ��������
/// @param clr   RGB��ɫ.
void WINAPI XDraw_FillSolidRect_(HDRAW hDraw,RECT *pRect,COLORREF clr)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rc=*pRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;

	::SetBkColor(pDraw->hdc, clr);
	::ExtTextOut(pDraw->hdc, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
}

/// @brief �������,��һ����ɫ���ɵ���һ����ɫ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param color1 ��ʼ��ɫ.
/// @param color2 ������ɫ.
/// @param pRect ��������.
/// @param mode  ģʽ.
/// GRADIENT_FILL_RECT_H ˮƽ��� .
/// GRADIENT_FILL_RECT_V ��ֱ���.
/// GRADIENT_FILL_TRIANGLE ������.
/// @return ��������ɹ�������ֵΪTRUE,�������ʧ��,����ֵ��FALSE.
BOOL WINAPI XDraw_GradientFill2_(HDRAW hDraw,COLORREF color1,COLORREF color2,RECT *pRect,int mode)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rc=*pRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;

	return XDraw_GradientFill2(pDraw->hdc,color1,color2,&rc,mode);
}

/// @brief �������,��һ����ɫ���ɵ���һ����ɫ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param color1 ��ʼ��ɫ.
/// @param color2 ������ɫ,�м�.
/// @param color3 ��ʼ��ɫ,�м�.
/// @param color4 ������ɫ.
/// @param pRect ��������.
/// @param mode  ģʽ.
/// GRADIENT_FILL_RECT_H ˮƽ���. 
/// GRADIENT_FILL_RECT_V ��ֱ���.
/// GRADIENT_FILL_TRIANGLE ������.
/// @return ��������ɹ�������ֵΪTRUE,�������ʧ��,����ֵ��FALSE.
BOOL WINAPI XDraw_GradientFill4_(HDRAW hDraw,COLORREF color1,COLORREF color2,COLORREF color3,COLORREF color4,RECT *pRect,int mode)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rc=*pRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;

	return XDraw_GradientFill4(((draw_xc_*)hDraw)->hdc,color1,color2,color3,color4 ,&rc,mode);
}

/// @brief ���Ʊ߿�,ʹ��ָ���Ļ�ˢ����ָ��������ı߿�.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hrgn ������.
/// @param hbr  ��ˢ���.
/// @param nWidth �߿���,��ֱ��.
/// @param nHeight �߿�߶�,ˮƽ��.
/// @return ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
BOOL WINAPI XDraw_FrameRgn_(HDRAW hDraw,HRGN hrgn,HBRUSH hbr,int nWidth,int nHeight)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	return FrameRgn(((draw_xc_*)hDraw)->hdc,hrgn,hbr,nWidth,nHeight);
}

/// @brief ���ƾ��α߿�,ʹ��ָ���Ļ�ˢ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param pRect ��������
/// @param hbr ��ˢ���.
/// @return  ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
int WINAPI XDraw_FrameRect_(HDRAW hDraw,RECT *pRect,HBRUSH hbr)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rc=*pRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;
	return FrameRect(((draw_xc_*)hDraw)->hdc,&rc,hbr);
}

/// @brief ���ƽ������.
/// @param hDraw ͼ�λ��ƾ��.
/// @param pRect ��������.
/// @return ��ʹ��.
BOOL WINAPI XDraw_FocusRect_(HDRAW hDraw,RECT *pRect)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;

	RECT rc=*pRect;

	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;

	XDraw_Dottedline(pDraw->hdc,rc.left,rc.top,rc.right-rc.left,RGB(0,0,0));
	XDraw_Dottedline(pDraw->hdc,rc.left,rc.bottom-1,rc.right-rc.left,RGB(0,0,0));

	XDraw_Dottedline(pDraw->hdc,rc.left,rc.top,rc.bottom-rc.top,RGB(0,0,0),FALSE);
	XDraw_Dottedline(pDraw->hdc,rc.right-1,rc.top,rc.bottom-rc.top,RGB(0,0,0),FALSE);

	return TRUE;
}

/// @brief ���ƾ���,ʹ�õ�ǰ�Ļ�ˢ�ͻ���.
/// @param hDraw ͼ�λ��ƾ��.
/// @param nLeftRect ���Ͻ�X����.
/// @param nTopRect  ���Ͻ�Y����.
/// @param nRightRect ���½�X����.
/// @param nBottomRect  ���½�Y����.
/// @return ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
BOOL WINAPI XDraw_Rectangle_(HDRAW hDraw,int nLeftRect,int nTopRect,int nRightRect,int nBottomRect)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	return Rectangle(pDraw->hdc,nLeftRect+pDraw->x,nTopRect+pDraw->y,nRightRect+pDraw->x,nBottomRect+pDraw->y);
}

/// @brief ���µ�ǰλ�õ�ָ���㣬��������ǰ��λ�á�
/// @param hDraw ͼ�λ��ƾ��.
/// @param X ����.
/// @param Y ����.
/// @param lpPoint ������ǰ�ĵ�ǰλ�õ�һ��POINT�ṹ��ָ��,������������NULLָ��,û�з���ԭ����λ��.
/// @return ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
BOOL WINAPI XDraw_MoveToEx_(HDRAW hDraw,int X,int Y,LPPOINT lpPoint)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	return MoveToEx(((draw_xc_*)hDraw)->hdc,X+pDraw->x, Y+pDraw->y,lpPoint);
}

/// @brief ��������һ���ߴӵ�ǰλ�õ�,��������ָ����.
/// @param hDraw ͼ�λ��ƾ��.
/// @param nXEnd X����,�߽�����.
/// @param nYEnd Y����,�߽�����.
/// @return  ��������ɹ�,���ط���ֵ,�������ʧ��,����ֵ����.
BOOL WINAPI XDraw_LineTo_(HDRAW hDraw,int nXEnd,int nYEnd)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	return LineTo(((draw_xc_*)hDraw)->hdc,nXEnd+pDraw->x,nYEnd+pDraw->y);
}

/// @brief ���Ƹ�ѡ��.
/// @param hDraw ͼ�λ��ƾ��.
/// @param x  ����.
/// @param y  ����.
/// @param color �߿���ɫ.
/// @param bCheck �Ƿ�ѡ��״̬.
void WINAPI XDraw_Check_(HDRAW hDraw,int x,int y,COLORREF color,BOOL bCheck)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	XDraw_Check(((draw_xc_*)hDraw)->hdc,x+((draw_xc_*)hDraw)->x,y+((draw_xc_*)hDraw)->y,color,bCheck);
}


void WINAPI XDraw_Dottedline_(HDRAW hDraw,int x,int y,int length,COLORREF color,BOOL bHorizontal) //��������
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	XDraw_Dottedline(pDraw->hdc, x+pDraw->x, y+pDraw->y, length, color, bHorizontal); //��������
}

/// @brief ����������ָ�������굽ָ������ɫ������.
/// @param hDraw ͼ�λ��ƾ��.
/// @param X ����
/// @param Y ����
/// @param crColor RGB��ɫֵ
/// @return ��������ɹ�����RGBֵ,���ʧ�ܷ���-1.
COLORREF WINAPI XDraw_SetPixel_(HDRAW hDraw,int X,int Y,COLORREF crColor)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	return SetPixel( pDraw->hdc, X+pDraw->x, Y+pDraw->y, crColor);
}

/// @brief �μ�MSDN.
/// @param hDraw ͼ�λ��ƾ��.
/// @param xLeft
/// @param yTop
/// @param hIcon
/// @param cxWidth
/// @param cyWidth
/// @param istepIfAniCur
/// @param hbrFlickerFreeDraw
/// @param diFlags
/// @return 
BOOL WINAPI XDraw_DrawIconEx_(HDRAW hDraw,int xLeft,int yTop,HICON hIcon,int cxWidth,int cyWidth,UINT istepIfAniCur,HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	return DrawIconEx( ((draw_xc_*)hDraw)->hdc, xLeft+((draw_xc_*)hDraw)->x,yTop+((draw_xc_*)hDraw)->y,hIcon,cxWidth,cyWidth,istepIfAniCur,hbrFlickerFreeDraw,diFlags);
}

/// @brief �μ�MSDN.
/// @param hDrawDest ͼ�λ��ƾ��.
/// @param nXDest
/// @param nYDest
/// @param nWidth
/// @param nHeight
/// @param hdcSrc
/// @param nXSrc
/// @param nYSrc
/// @param dwRop
/// @return 
BOOL WINAPI XDraw_BitBlt_(HDRAW hDrawDest,int nXDest,int nYDest,int nWidth,int nHeight,HDC hdcSrc,int nXSrc,int nYSrc,DWORD dwRop)
{
	IsDrawDebug(hDrawDest,__FUNCTION__);
	return BitBlt( ((draw_xc_*)hDrawDest)->hdc, nXDest+((draw_xc_*)hDrawDest)->x, nYDest+((draw_xc_*)hDrawDest)->y, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
}

/// @brief �μ�MSDN.
/// @param hDrawDest ͼ�λ��ƾ��.
/// @param nXDest
/// @param nYDest
/// @param nWidth
/// @param nHeight
/// @param hDrawSrc
/// @param nXSrc
/// @param nYSrc
/// @param dwRop
/// @return 
BOOL WINAPI XDraw_BitBlt2_(HDRAW hDrawDest,int nXDest,int nYDest,int nWidth,int nHeight,HDRAW hDrawSrc,int nXSrc,int nYSrc,DWORD dwRop)
{
	IsDrawDebug(hDrawDest,__FUNCTION__);
	draw_xc_ *pDraw1=(draw_xc_*)hDrawDest;
	draw_xc_ *pDraw2=(draw_xc_*)hDrawSrc;
	return BitBlt( ((draw_xc_*)hDrawDest)->hdc, nXDest+pDraw1->x, nYDest+pDraw1->y, 
		nWidth, nHeight, pDraw2->hdc, nXSrc+pDraw2->x, nYSrc+pDraw2->y, dwRop);
}

/// @brief ���������ͼ�ͷ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hBrush ��ˢ.
/// @param align  ��ͷ����,��1,��2,��3,��4.
/// @param x ���ĵ�X����.
/// @param y ���ĵ�Y����.
/// @param width �����ο��.
/// @param height �����θ߶�.
void WINAPI XDraw_TriangularArrow(HDRAW hDraw,HBRUSH hBrush,int align,int x,int y,int width,int height)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	int left=x+pDraw->x;
	int top=y+pDraw->y;

	if(1==align) //left
	{
		POINT  pt[3];
		pt[0].x=left-(width/2);
		pt[0].y=top;
		pt[1].x=left+(width/2);
		pt[1].y=top+(height/2);
		pt[2].x=left+(width/2);
		pt[2].y=top-(height/2);
		HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
		XDraw_FillRgn_(hDraw,hRgn,hBrush);
		XDraw_DeleteObject_(hDraw,hRgn);
	}else if(2==align) //top
	{
		POINT  pt[3];
		pt[0].x=left-(width/2);
		pt[0].y=top+(height/2);
		pt[1].x=left+(width/2);
		pt[1].y=top+(height/2);
		pt[2].x=left;
		pt[2].y=top-(height/2);
		HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
		XDraw_FillRgn_(hDraw,hRgn,hBrush);
		XDraw_DeleteObject_(hDraw,hRgn);
	}else if(3==align) //right
	{
		POINT  pt[3];
		pt[0].x=left-(width/2);
		pt[0].y=top-(height/2);
		pt[1].x=left-(width/2);
		pt[1].y=top+(height/2);
		pt[2].x=left+(width/2);
		pt[2].y=top;
		HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
		XDraw_FillRgn_(hDraw,hRgn,hBrush);
		XDraw_DeleteObject_(hDraw,hRgn);
	}else if(4==align) //bottom
	{
		POINT  pt[3];
		pt[0].x=left-(width/2);
		pt[0].y=top-(height/2);
		pt[1].x=left;
		pt[1].y=top+(height/2);
		pt[2].x=left+(width/2);
		pt[2].y=top-(height/2);
		HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
		XDraw_FillRgn_(hDraw,hRgn,hBrush);
		XDraw_DeleteObject_(hDraw,hRgn);
	}
}

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param x
/// @param y
/// @return 
void WINAPI XDraw_HImage_(HDRAW hDraw,HIMAGE hImage,int x,int y)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	IsHImageDebug(hImage,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	x+=pDraw->x;
	y+=pDraw->y;

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;

	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	if(!pImage->bTransparentColor)
	{
		Graphics graphics(pDraw->hdc);
		graphics.DrawImage(pImageX,x,y,pImageX->GetWidth(),pImageX->GetHeight());
	}else
	{
		Graphics graphics(pDraw->hdc);
		Rect destRect;
		destRect.X=x;
		destRect.Y=y;
		destRect.Width=pImageX->GetWidth();
		destRect.Height=pImageX->GetHeight();

		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);

		ImageAttributes ImgAtt;
		ImgAtt.SetRemapTable(1,&newToold);

		graphics.DrawImage(pImageX, destRect, 0, 0,
			pImageX->GetWidth(),
			pImageX->GetHeight(),
			UnitPixel, &ImgAtt);
	}
}

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param x
/// @param y
/// @param width
/// @param height
void WINAPI XDraw_HImage2_(HDRAW hDraw,HIMAGE hImage,int x,int y,int width,int height)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	IsHImageDebug(hImage,__FUNCTION__);

	x+=((draw_xc_*)hDraw)->x;
	y+=((draw_xc_*)hDraw)->y;

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	ImageAttributes ImgAtt;
	if(pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1,&newToold);
	}

	Graphics graphics(((draw_xc_*)hDraw)->hdc);
	Rect destRect;
	destRect.X=x;
	destRect.Y=y;
	destRect.Width=width;
	destRect.Height=height;

	//ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(pImageX, destRect, 0, 0,
		width,
		height,
		UnitPixel, &ImgAtt);
}

//������ͼ
//x:Ŀ��X
//y:Ŀ��Y
//height:Ŀ����
//height:Ŀ��߶�

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param x
/// @param y
/// @param width
/// @param height
void WINAPI XDraw_HImageStretch_(HDRAW hDraw,HIMAGE hImage,int x,int y,int width,int height)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	if(NULL==hDraw) return ;
	IsHImageDebug(hImage,__FUNCTION__);

	x+=((draw_xc_*)hDraw)->x;
	y+=((draw_xc_*)hDraw)->y;

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	ImageAttributes ImgAtt;
	if(pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1,&newToold);
	}

	Graphics graphics(((draw_xc_*)hDraw)->hdc);
	Rect destRect;
	destRect.X=x;
	destRect.Y=y;
	destRect.Width=width;
	destRect.Height=height;

	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(pImageX, destRect, 0, 0,
		pImageX->GetWidth(),
		pImageX->GetHeight(),
		UnitPixel, &ImgAtt);
}

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param pRect
void WINAPI XDraw_HImageAdaptive_(HDRAW hDraw,HIMAGE hImage,RECT *pRect)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rc=*pRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;

	XDraw_HImageAdaptive(((draw_xc_*)hDraw)->hdc,hImage,&rc);
}

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param pRect
/// @param flag
void WINAPI XDraw_HImageExTile_(HDRAW hDraw,HIMAGE hImage,RECT *pRect,int flag)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	RECT rect=*pRect;

	Graphics graphics(pDraw->hdc);
	HRGN hRgn=CreateRectRgn(rect.left+pDraw->x,rect.top+pDraw->y,rect.right+pDraw->x,rect.bottom+pDraw->y);
	SelectClipRgn(pDraw->hdc,hRgn);
	if(0==flag)
	{
		int posx=rect.left;
		int posy=rect.top;
		int posx2=posx;
		int posy2=posy;
		int imageWidth=pImageX->GetWidth();
		int imageHeight=pImageX->GetHeight();

		while(posy2<rect.bottom)
		{
			while(posx2<rect.right)
			{
				XDraw_HImage_(hDraw,hImage,posx2,posy2);
				posx2+=imageWidth;
			}
			posx2=posx;
			posy2+=imageHeight;
		}
	}else if(1==flag)
	{
		int posx=rect.left;
		int posy=rect.bottom;
		int posx2=posx;
		int posy2=posy;
		int imageWidth=pImageX->GetWidth();
		int imageHeight=pImageX->GetHeight();

		while(posy2>pRect->top)
		{
			posy2-=imageHeight;
			while(posx2<rect.right)
			{
				XDraw_HImage_(hDraw,hImage,posx2,posy2);
				posx2+=imageWidth;
			}
			posx2=posx;
		}
	}
	DeleteObject(hRgn);
	SelectClipRgn(pDraw->hdc,NULL);
}

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param pRect
void WINAPI XDraw_HImageSuper_(HDRAW hDraw,HIMAGE hImage,RECT *pRect)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	IsHImageDebug(hImage,__FUNCTION__);
	switch(XImage_GetDrawType(hImage))
	{
	case XC_IMAGE_DEFAULT:
		XDraw_HImage_(hDraw,hImage,pRect->left,pRect->top);
		break;
	case XC_IMAGE_STRETCH:
		XDraw_HImageStretch_(hDraw,hImage,pRect->left,pRect->top,pRect->right-pRect->left,
			pRect->bottom-pRect->top);
		break;
	case XC_IMAGE_ADAPTIVE:
		XDraw_HImageAdaptive_(hDraw,hImage,pRect);
		break;
	case XC_IMAGE_TILE:
		//XDraw_HImageExTile_(hDraw,hImage,pRect->left,pRect->top,pRect->right-pRect->left,
		//	pRect->bottom-pRect->top);
		XDraw_HImageExTile_(hDraw,hImage,pRect,0);
		break;
	}
}

/// @brief ����ͼƬ.
/// @param hDraw ͼ�λ��ƾ��.
/// @param hImage
/// @param pRcDest
/// @param pSrcRect
void WINAPI XDraw_HImageSuper2_(HDRAW hDraw,HIMAGE hImage,RECT *pRcDest,RECT *pSrcRect)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	if(NULL==hDraw) return ;
	IsHImageDebug(hImage,__FUNCTION__);

	ximage_  *pImage=(ximage_*)hImage;

	Gdiplus::Image *pImageX=NULL;
	if(pImage->pImage)
	{
		pImageX=pImage->pImage;
	}else if(pImage->bBitmap && pImage->pBitmap)
	{
		pImageX=pImage->pBitmap;
	}

	if(NULL==pImageX) return ;

	draw_xc_ *pDraw=(draw_xc_*)hDraw;

	RECT rcDest=*pRcDest;
	RECT rcSrc=*pSrcRect;

	rcDest.left+=pDraw->x;
	rcDest.right+=pDraw->x;
	rcDest.top+=pDraw->y;
	rcDest.bottom+=pDraw->y;

	ImageAttributes ImgAtt;
	if(pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor =pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1,&newToold);
	}

	Graphics graphics(((draw_xc_*)hDraw)->hdc);

	Rect destRect;
	destRect.X=rcDest.left;
	destRect.Y=rcDest.top;
	destRect.Width=rcDest.right-rcDest.left;
	destRect.Height=rcDest.bottom-rcDest.top;

	graphics.DrawImage(pImageX, destRect, rcSrc.left,rcSrc.top,
		rcSrc.right-rcSrc.left,
		rcSrc.bottom-rcSrc.top,
		UnitPixel, &ImgAtt);
}

/// @brief �����ı�,�μ�MSDN.
/// @param hDraw ͼ�λ��ƾ��.
/// @param lpString
/// @param nCount
/// @param lpRect
/// @param uFormat
int WINAPI XDraw_DrawText_(HDRAW hDraw,wchar_t * lpString,int nCount,RECT* lpRect,UINT uFormat)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	if(uFormat & DT_CALCRECT)
	{
		return DrawText(pDraw->hdc,lpString,nCount,lpRect,uFormat);
	}

	RECT rc=*lpRect;
	rc.left+=pDraw->x;
	rc.right+=pDraw->x;
	rc.top+=pDraw->y;
	rc.bottom+=pDraw->y;
	return DrawText(pDraw->hdc,lpString,nCount,&rc,uFormat);
}

/// @brief �����ı�,�μ�MSDN.
/// @param hDraw ͼ�λ��ƾ��.
/// @param nXStart
/// @param nYStart
/// @param lpString
/// @param cbString
/// @return
BOOL WINAPI XDraw_TextOut_(HDRAW hDraw,int nXStart,int nYStart,wchar_t * lpString,int cbString)
{
	IsDrawDebug(hDraw,__FUNCTION__);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	return TextOut(pDraw->hdc, nXStart+pDraw->x, nYStart+pDraw->y, lpString, cbString);
}

///@}

