#include "StdAfx.h"

/// @defgroup font_xc  �Ų�����(FontX)
/// @ingroup groupOther
/// @{


/// @brief �����Ų�����,����������Ԫ�ع�����,���Զ��ͷ�.
/// @param size   �����С.
/// @return ������.
HFONTX WINAPI XFont_Create(int size)  //��������
{
	LOGFONT info;
	info.lfHeight=size;
	info.lfWidth=0;
	info.lfEscapement=0;
	info.lfOrientation=0;
	info.lfWeight=FW_NORMAL;
	info.lfItalic=FALSE;
	info.lfUnderline=FALSE;
	info.lfStrikeOut=FALSE;
	info.lfCharSet=GB2312_CHARSET;
	info.lfOutPrecision=OUT_DEFAULT_PRECIS;
	info.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	info.lfQuality=DEFAULT_QUALITY;
	info.lfPitchAndFamily= DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(info.lfFaceName,L"����");

	return XFont_CreateEx(&info);
}

/// @brief �����Ų�����.
/// @param  pName  ��������.
/// @param  size   �����С.
/// @param  bBold  �Ƿ�Ϊ����.
/// @param  bItalic  �Ƿ�Ϊб��.
/// @param  bUnderline   �Ƿ����»���.
/// @param  bStrikeOut   �Ƿ���ɾ����.
/// @return ������.
HFONTX WINAPI XFont_Create2(wchar_t *pName,int size,BOOL bBold,BOOL bItalic,BOOL bUnderline,BOOL bStrikeOut)
{
	LOGFONT info;
	DWORD nWeight=FW_NORMAL;
	if(bBold)
		nWeight=FW_BOLD;

	info.lfHeight=size;
	info.lfWidth=0;
	info.lfEscapement=0;
	info.lfOrientation=0;
	info.lfWeight=nWeight;
	info.lfItalic=bItalic;
	info.lfUnderline=bUnderline;
	info.lfStrikeOut=bStrikeOut;
	info.lfCharSet=GB2312_CHARSET;
	info.lfOutPrecision=OUT_DEFAULT_PRECIS;
	info.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	info.lfQuality=DEFAULT_QUALITY;
	info.lfPitchAndFamily= DEFAULT_PITCH | FF_DONTCARE;

	wcscpy_s(info.lfFaceName,pName);
	
	return XFont_CreateEx(&info);
}
/// @brief �����Ų�����.
/// @param  pFontInfo  ������Ϣ.
/// @return ������.
HFONTX WINAPI XFont_CreateEx(LOGFONT *pFontInfo)
{
	HFONT  hFont=CreateFontIndirect(pFontInfo);
	if(NULL==hFont)
		return NULL;

	font_xc_  *pFont_xc=(font_xc_*)malloc(sizeof(font_xc_));
	if(pFont_xc)
	{
		memset(pFont_xc,0,sizeof(font_xc_));

		pFont_xc->hFont=hFont;
		pFont_xc->info=*pFontInfo;
		pFont_xc->refCount=0;
		pFont_xc->object.type=XC_FONT;
	}

	return (HFONTX)pFont_xc;
}
/// @brief �����Ų�����.
/// @param  hFontX ������.
void WINAPI XFont_Destroy(HFONTX hFontX)
{
	IsFontDebug(hFontX,__FUNCTION__);
	font_xc_  *pFont_xc=(font_xc_*)hFontX;

	if(pFont_xc->refCount==1)
	{
		if(pFont_xc->hFont)
			DeleteObject(pFont_xc->hFont);

		free(pFont_xc);
	}else
		pFont_xc->refCount--;
}

/// @brief ��ȡ����HFONT���..
/// @param  hFontX ������.
/// @return ����HFONT���.
HFONT WINAPI XFont_GetHFONT(HFONTX hFontX)
{
	if(hFontX)
		return ((font_xc_*)hFontX)->hFont;
	return (HFONT)GetStockObject(DEFAULT_GUI_FONT);
}

void Font_AddFontX(HFONTX &hFontX,HFONTX hFontXNew) //������Ԫ�ع������������ü���
{
	if(hFontX)
	{
		XFont_Destroy(hFontX);
		hFontX=NULL;
	}
	if(hFontXNew)
	{
		IsFontDebug(hFontXNew,__FUNCTION__);
		hFontX=hFontXNew;
		Font_AddRef(hFontXNew);
	}
}

HFONTX Font_AddRef(HFONTX hFontX)   //�������ü���
{
	if (hFontX)
	{
		((font_xc_*)hFontX)->refCount++;
		return hFontX;
	}
	return NULL;
}

/// @}
