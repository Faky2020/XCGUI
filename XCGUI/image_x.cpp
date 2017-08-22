/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

//#include <direct.h>
//#include <errno.h>

#include "zlib/unzip.h"
#pragma comment(lib,"unzip.lib")

#define CASESENSITIVITY   (0)
#define MAXFILENAME       (256)
#define WRITEBUFFERSIZE   (8192)


/// @defgroup image ͼƬ����
/// @ingroup groupOther
/// ͼƬ�����ӿ�,�ṩ��ͼƬ�ļ���,���ټ����UIԪ�ص���ͼ��ʾ,��ͼƬ�ӿڹ�����һ��UIԪ�غ�,�����Զ�����ͼƬ�ӿ�,������Ҫ���ֶ�����.<br>
/// ��Ҫ֧��:����ͼƬ�ļ���ʽ,bmp,jpg,png,gif,ico.���ļ�����,�ӳ�����Դ����,��ѹ�����м���,����ӦͼƬ,ƽ��,͸��ɫ֧��.
/// @{

void *do_extract_currentfile(void *uf,const char* password,int &outSize)
{
	char  filename_inzip[256];
	int   err=UNZ_OK;
	void* buf;
	unsigned int size_buf;
	unz_file_info64 file_info;
	err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);//��ȡ�ļ���Ϣ
	if (err!=UNZ_OK)
	{
		XTRACE("error %d with zipfile in unzGetCurrentFileInfo\n",err);
		return NULL;
	}

	//�������
	err = unzOpenCurrentFilePassword(uf,password);
	if (err!=UNZ_OK)
	{
		XTRACE("error %d with zipfile in unzOpenCurrentFilePassword\n",err);
		return NULL;
	}

	//�����ڴ�
	size_buf =(unsigned int)file_info.uncompressed_size; // WRITEBUFFERSIZE;
	buf = (void*)malloc(size_buf);
	if (buf==NULL)
	{
		printf("Error allocating memory\n");
		return NULL;
	}

	//��ȡ����
	err = unzReadCurrentFile(uf,buf,size_buf);
	if (err<0)
	{
		XTRACE("error %d with zipfile in unzReadCurrentFile\n",err);
	}
	outSize=err;

	//�رյ�ǰ�ļ�
	if(err>=0)
	{
		err = unzCloseCurrentFile(uf);
		if (err!=UNZ_OK)
		{
			XTRACE("error %d with zipfile in unzCloseCurrentFile\n",err);
		}else
		{
			return buf;
		}
	}else
	{
		unzCloseCurrentFile(uf); 
	}

	free(buf);
	return NULL;
}


//��ȡһ���ļ�
void *do_extract_onefile(void *uf, const char* filename, const char* password,int &outSize)
{
	int err = UNZ_OK;
	if (unzLocateFile(uf,filename,CASESENSITIVITY)!=UNZ_OK)
	{
		XTRACE("file %s not found in the zipfile\n",filename);
		return NULL;
	}

	return do_extract_currentfile(uf,password,outSize);
}

/// @brief ����ͼƬ��ZIPѹ����.
/// @param pZipFileName  ZIPѹ�����ļ���.
/// @param pImageName ͼƬ�ļ���.
/// @param pPassword  ZIPѹ��������.
/// @param bStretch   �Ƿ�����ͼƬ
/// @return  ͼƬ���.
HIMAGE WINAPI XImage_LoadZip(wchar_t *pZipFileName,wchar_t *pImageName,wchar_t *pPassword,BOOL bStretch)
{
	if(NULL==pZipFileName || NULL==pImageName)
	{
		return NULL;
	}

	IsImageTypeDebug(_T(__FUNCTION__),pImageName);

	HIMAGE hImage=Image_LoadZip(pZipFileName,pImageName,pPassword);
	if(hImage)
	{
		if(bStretch)
			((ximage_*)hImage)->flag=XC_IMAGE_STRETCH;
		return hImage;
	}
	return NULL;
}

/// @brief ����ͼƬ��ZIPѹ����,����ӦͼƬ.
/// @param pZipFileName  ZIPѹ�����ļ���.
/// @param pImageName ͼƬ�ļ���.
/// @param pPassword  ZIPѹ��������,���û����NULL.
/// @param x1 ����.
/// @param x2 ����.
/// @param y1 ����.
/// @param y2 ����.
/// @return  ͼƬ���.
HIMAGE WINAPI XImage_LoadZipAdaptive(wchar_t *pZipFileName,wchar_t *pImageName,wchar_t *pPassword,int x1,int x2,int y1,int y2) //��ZIP�м���ͼƬ
{
	if(x1>x2) return NULL;
	if(y1>y2) return NULL;

	HIMAGE hImage=XImage_LoadZip(pZipFileName,pImageName,pPassword);
	if(hImage)
	{
		ximage_ *pXImage=(ximage_*)hImage;

		pXImage->flag=XC_IMAGE_ADAPTIVE;
		pXImage->imageWidth=pXImage->pImage->GetWidth();
		pXImage->imageHeight=pXImage->pImage->GetHeight();
		pXImage->imageX1=x1;
		pXImage->imageX2=x2;
		pXImage->imageY1=y1;
		pXImage->imageY2=y2;
		return hImage;
	}
	return NULL;
}

/// @brief ����ͼƬ���ļ�.
/// @param pImageName ͼƬ�ļ�.
/// @param bStretch   �Ƿ�����ͼƬ
/// @return  ͼƬ���.
HIMAGE WINAPI XImage_LoadFile(wchar_t *pImageName,BOOL bStretch)
{
	if(NULL==pImageName) return NULL;

	IsImageTypeDebug(_T(__FUNCTION__),pImageName);

	HIMAGE hImage= Image_LoadFile(pImageName);
	if(hImage)
	{
		if(bStretch)
			((ximage_*)hImage)->flag=XC_IMAGE_STRETCH;
		return hImage;
	}
	return NULL;
}

/// @brief ����ͼƬ���ļ�,����ӦͼƬ.
/// @param pImageName ͼƬ�ļ�.
/// @param x1 ����.
/// @param x2 ����.
/// @param y1 ����.
/// @param y2 ����.
/// @return  ͼƬ���.
HIMAGE WINAPI XImage_LoadFileAdaptive(wchar_t *pImageName,int x1,int x2,int y1,int y2) //���ļ��м���ͼƬ
{
	if(x1>x2) return NULL;
	if(y1>y2) return NULL;

	HIMAGE hImage=XImage_LoadFile(pImageName);
	if(hImage)
	{
		ximage_ *pXImage=(ximage_*)hImage;
		pXImage->flag=XC_IMAGE_ADAPTIVE;
		pXImage->imageWidth=pXImage->pImage->GetWidth();
		pXImage->imageHeight=pXImage->pImage->GetHeight();
		pXImage->imageX1=x1;
		pXImage->imageX2=x2;
		pXImage->imageY1=y1;
		pXImage->imageY2=y2;

		return hImage;
	}
	return NULL;
}

/// @brief ����ͼƬ,ָ����λ�ü���С.
/// @param pImageName ͼƬ�ļ�.
/// @param x ����.
/// @param y ����.
/// @param cx ���.
/// @param cy �߶�.
/// @return ͼƬ���.
HIMAGE WINAPI XImage_LoadFileRect(wchar_t *pImageName,int x,int y,int cx,int cy)
{
	//����ͼƬ
	Image image(pImageName);
	if(Gdiplus::Ok!=image.GetLastStatus())
	{
		XTRACEW(L"XImage_LoadFileRect(\"%s\"),����ͼƬ·������ \n",pImageName);
		return NULL;
	}

	//����ͼƬ
	Bitmap *pBitmap=new Bitmap(cx,cy);

	//��ͼƬ���Ƶ�����
	Graphics* imageGraphics = Graphics::FromImage(pBitmap);

	Rect destRect;			
	destRect.X=0;
	destRect.Y=0;
	destRect.Width=cx;
	destRect.Height=cy;

	ImageAttributes ImgAtt;

	if(Gdiplus::Ok!=imageGraphics->DrawImage(&image,
		destRect,                
		x,    //srcX
		y,    //srcY
		cx,   //cx
		cy,   //cy
		UnitPixel,&ImgAtt,NULL,NULL)) 
	{
		XTRACE("XImage_LoadFileSize() ���� \n");

		delete imageGraphics;
		return NULL;
	}

	ximage_ *pXImage=(ximage_*)malloc(sizeof(ximage_));
	memset(pXImage,0,sizeof(ximage_));
	pXImage->object.type=XC_IMAGE;
	pXImage->type=0;
	pXImage->refCount=0;
	pXImage->flag=XC_IMAGE_DEFAULT;
	pXImage->pImage=NULL;
	pXImage->bBitmap=TRUE;
	pXImage->pBitmap=pBitmap;
	pXImage->bAutoDestroy=TRUE;

	delete imageGraphics;
	return (HIMAGE)pXImage;
}

/// @brief �Ƿ�Ϊ����ͼƬ���
/// @param hImage  ͼƬ���.
/// @return  ����Ƿ���TRUE,�����෴.
BOOL WINAPI XImage_IsStretch(HIMAGE hImage) //�Ƿ�����ͼƬ
{
	IsHImageDebug(hImage,__FUNCTION__);
	return XC_IMAGE_STRETCH==((ximage_*)hImage)->flag ? TRUE : FALSE;
}

/// @brief �Ƿ�Ϊ����ӦͼƬ���
/// @param hImage  ͼƬ���.
/// @return  ����Ƿ���TRUE,�����෴.
BOOL WINAPI XImage_IsAdaptive(HIMAGE hImage) //�Ƿ�Ϊ����ӦͼƬ
{
	IsHImageDebug(hImage,__FUNCTION__);
	return XC_IMAGE_ADAPTIVE==((ximage_*)hImage)->flag ? TRUE: FALSE;
}

/// @brief �Ƿ�Ϊƽ��ͼƬ
/// @param hImage  ͼƬ���.
/// @return  ����Ƿ���TRUE,�����෴.
BOOL WINAPI XImage_IsTile(HIMAGE hImage)
{
	IsHImageDebug(hImage,__FUNCTION__);
	return XC_IMAGE_TILE==((ximage_*)hImage)->flag ? TRUE: FALSE;
}

/// @brief ����ͼƬ��������
/// @param hImage  ͼƬ���.
/// @param type  ͼƬ��������.
/// @return  ����Ƿ���TRUE,�����෴.
BOOL WINAPI XImage_SetDrawType(HIMAGE hImage,int type)
{
	IsHImageDebug(hImage,__FUNCTION__);

	if(XC_IMAGE_DEFAULT || XC_IMAGE_STRETCH | XC_IMAGE_TILE)
	{
		((ximage_*)hImage)->flag=type;
		return TRUE;
	}else
	{
		::MessageBox(NULL,L"����: XImage_SetDrawType() ���������ܵ�����",L"��ʾ",0);
	}
	return NULL;
}

/// @brief ����ͼƬ����Ӧ
/// @param hImage  ͼƬ���.
/// @param x1 ����.
/// @param x2 ����.
/// @param y1 ����.
/// @param y2 ����.
/// @return  ����Ƿ���TRUE,�����෴.
BOOL WINAPI XImage_SetDrawTypeAdaptive(HIMAGE hImage,int x1,int x2,int y1,int y2) //����ͼƬ����Ӧ
{
	IsHImageDebug(hImage,__FUNCTION__);
	if(x1>x2) return FALSE;
	if(y1>y2) return FALSE;

	((ximage_*)hImage)->imageX1=x1;
	((ximage_*)hImage)->imageX2=x2;
	((ximage_*)hImage)->imageY1=y1;
	((ximage_*)hImage)->imageY1=y2;
	return TRUE;
}

/// @brief ָ��ͼƬ͸����ɫ.
/// @param hImage  ͼƬ���.
/// @param color   RGB��ɫ.
void WINAPI XImage_SetTranColor(HIMAGE hImage,COLORREF color) //����͸��ɫ
{
	IsHImageDebug(hImage,__FUNCTION__);
	((ximage_*)hImage)->transparentColor.SetFromCOLORREF(color);
}

/// @brief ָ��ͼƬ͸����ɫ��͸����.
/// @param hImage  ͼƬ���.
/// @param color   RGB��ɫ.
/// @param tranColor  ͸��ɫ��͸����.
void WINAPI XImage_SetTranColorEx(HIMAGE hImage,COLORREF color,byte tranColor) //����͸��ɫ
{
	IsHImageDebug(hImage,__FUNCTION__);
	((ximage_*)hImage)->transparentColor=Color(tranColor,GetRValue(color),GetGValue(color),GetBValue(color));
}

/// @brief ���û�ر�ͼƬ͸��ɫ.
/// @param hImage  ͼƬ���.
/// @param bEnable   ����TRUE,�ر�FALSE.
void WINAPI XImage_EnableTranColor(HIMAGE hImage,BOOL bEnable) //����͸��ɫ
{
	IsHImageDebug(hImage,__FUNCTION__);
	((ximage_*)hImage)->bTransparentColor=bEnable;
}

/// @brief ���û�ر��Զ�����,����UIԪ�ع���ʱ��Ч
/// @param hImage  ͼƬ���.
/// @param bEnable   �����Զ�����TRUE,�ر��Զ�����FALSE.
void WINAPI XImage_EnableAutoDestroy(HIMAGE hImage,BOOL bEnable) //���û�ر��Զ�����,����UIԪ�ع���ʱ��Ч
{
	IsHImageDebug(hImage,__FUNCTION__);
	ximage_ *pImage=(ximage_*)hImage;
	if(bEnable==pImage->bAutoDestroy)
		return ;

	pImage->bAutoDestroy=bEnable;
	
	if(bEnable)
	{
		pImage->refCount--;
	}else
	{
		pImage->refCount++;
	}
}

/// @brief ��ȡͼƬ��������
/// @param hImage  ͼƬ���.
/// @return  ͼƬ��������.
int WINAPI XImage_GetDrawType(HIMAGE hImage)
{
	IsHImageDebug(hImage,__FUNCTION__);
	return ((ximage_*)hImage)->flag;
}

/// @brief ����ͼƬ����Դ.
/// @param id     ��ԴID.
/// @param pType  ��Դ����.
/// @param bStretch �Ƿ�����ͼƬ
/// @return  ͼƬ���.
HIMAGE WINAPI XImage_LoadRes(int id,wchar_t *pType,BOOL bStretch)
{
	if(NULL==pType) return NULL;

	HIMAGE hImage=Image_LoadRes(id,pType);
	if(hImage)
	{
		if(bStretch)
			((ximage_*)hImage)->flag=XC_IMAGE_STRETCH;
		return hImage;
	}
	return NULL;
}

/// @brief ����ͼƬ����Դ,����ӦͼƬ.
/// @param id     ��ԴID.
/// @param pType  ��Դ����.
/// @param x1 ����.
/// @param x2 ����.
/// @param y1 ����.
/// @param y2 ����.
/// @return  ͼƬ���.
HIMAGE WINAPI XImage_LoadResAdaptive(int id,wchar_t *pType,int x1,int x2,int y1,int y2) //����Դ�м���ͼƬ
{
	if(x1>x2) return NULL;
	if(y1>y2) return NULL;

	HIMAGE hImage=XImage_LoadRes(id,pType);
	if(hImage)
	{
		ximage_ *pXImage=(ximage_*)hImage;

		pXImage->flag=XC_IMAGE_ADAPTIVE;
		pXImage->imageWidth=pXImage->pImage->GetWidth();
		pXImage->imageHeight=pXImage->pImage->GetHeight();
		pXImage->imageX1=x1;
		pXImage->imageX2=x2;
		pXImage->imageY1=y1;
		pXImage->imageY2=y2;

		return hImage;
	}
	return NULL;
}

/// @brief ��ȡͼƬ���.
/// @param hImage ͼƬ���.
/// @return  ͼƬ���.
int WINAPI XImage_GetWidth(HIMAGE hImage)
{
	IsHImageDebug(hImage,__FUNCTION__);
	ximage_  *pImage=(ximage_*)hImage;
	return pImage->pImage->GetWidth();
}

/// @brief ��ȡͼƬ�߶�.
/// @param hImage ͼƬ���.
/// @return  ͼƬ�߶�.
int WINAPI XImage_GetHeight(HIMAGE hImage)
{
	IsHImageDebug(hImage,__FUNCTION__);
	ximage_  *pImage=(ximage_*)hImage;
	return pImage->pImage->GetHeight();
}

/// @brief ����ͼƬ�ӿ�.
/// @param hImage ͼƬ���.
void WINAPI XImage_Destroy(HIMAGE hImage)
{
	IsHImageDebug(hImage,__FUNCTION__);

	ximage_  *pImage=(ximage_*)hImage;
	if(pImage->refCount==1)
	{
		if(pImage->pImage)
		{
			delete pImage->pImage;
		}else if(pImage->bBitmap && pImage->pBitmap)
		{
			delete pImage->pBitmap;
		}
		
		free(pImage);
	}else
		pImage->refCount--;
}


///@}

void Image_AddImage(HIMAGE &hImage,HIMAGE hImageNew)
{
	if(hImage)
	{
		XImage_Destroy(hImage);
		hImage=NULL;
	}
	if(hImageNew)
	{
		IsHImageDebug(hImageNew,__FUNCTION__);
		hImage=hImageNew;
		Image_AddRef(hImageNew);
	}
}

HIMAGE Image_AddRef(HIMAGE hImage) //�������ü���
{
	if(hImage)
	{
		((ximage_*)hImage)->refCount++;
		return hImage;
	}
	return NULL;
}

HIMAGE Image_LoadFile(wchar_t *pImageName)
{
	Image *pImg=new Image(pImageName);
	if(NULL==pImg) return NULL;
	if(Gdiplus::Ok==pImg->GetLastStatus())
	{
		ximage_ *pXImage=(ximage_*)malloc(sizeof(ximage_));
		memset(pXImage,0,sizeof(ximage_));
		pXImage->object.type=XC_IMAGE;
		pXImage->type=0;
		pXImage->refCount=0;
		pXImage->flag=XC_IMAGE_DEFAULT;//bStretch ? XC_IMAGE_STRETCH : XC_IMAGE_DEFAULT;
		pXImage->bAutoDestroy=TRUE;

		pXImage->pImage=pImg;
		return (HIMAGE)pXImage;
	}
	XTRACEW(L"XImage_LoadFile(\"%s\"),����ͼƬ·������ \n",pImageName);
	delete pImg;
	return NULL;
}

HIMAGE Image_LoadRes(int id,wchar_t *pType)
{
	Image *pImg=NULL;
	BOOL bResult=ImageFromIDResource(id,pType,pImg);
	if(pImg)
	{
		if(Gdiplus::Ok==pImg->GetLastStatus())
		{
			ximage_ *pXImage=(ximage_*)malloc(sizeof(ximage_));
			memset(pXImage,0,sizeof(ximage_));
			pXImage->object.type=XC_IMAGE;
			pXImage->type=0;
			pXImage->refCount=0;
			pXImage->flag=XC_IMAGE_DEFAULT;//bStretch ? XC_IMAGE_STRETCH : XC_IMAGE_DEFAULT;
			pXImage->pImage=pImg;
			pXImage->bAutoDestroy=TRUE;

			return (HIMAGE)pXImage;
		}
		delete pImg;
	}
	return NULL;
}

HIMAGE Image_LoadZip(wchar_t *pZipFileName,wchar_t *pImageName,wchar_t *pPassword)//��ZIP�м���ͼƬ
{
	char zipfilename[MAX_PATH]={0};
	WideCharToMultiByte(CP_ACP,NULL,pZipFileName,wcslen(pZipFileName),zipfilename,MAX_PATH,NULL,NULL);

	char filename_to_extract[MAX_PATH]={0};
	WideCharToMultiByte(CP_ACP,NULL,pImageName,wcslen(pImageName),filename_to_extract,MAX_PATH,NULL,NULL);

	char password[MAX_PATH]={0};
	if(pPassword)
		WideCharToMultiByte(CP_ACP,NULL,pPassword,wcslen(pPassword),password,MAX_PATH,NULL,NULL);

	//const char *password=NULL;
	//char *zipfilename="C:\\Users\\mengfei\\Desktop\\myzip.zip";  //ѹ����
	//char *filename_to_extract="dirtt/123.txt";   //��ȡ�ļ���
	//char *filename_to_extract="btn.bmp";   //��ȡ�ļ���

	unzFile zipFile=NULL;
	zipFile = unzOpen64(zipfilename); //��ѹ����
	if (zipFile==NULL)
	{
		return NULL;
	}

	int outSize=0;
	void  *data =NULL;
	if(pPassword)
		data=do_extract_onefile(zipFile, filename_to_extract,password,outSize);
	else
		data=do_extract_onefile(zipFile, filename_to_extract,NULL,outSize);

	unzClose(zipFile);

	if(data)
	{
		HGLOBAL   hJPG   =   ::GlobalAlloc(GMEM_MOVEABLE,   outSize); 
		LPVOID   lpJGP   =   ::GlobalLock(hJPG); 
		memcpy(lpJGP,   data,   outSize); 
		::GlobalUnlock(hJPG);
		LPSTREAM   pstm =NULL;
		HRESULT   hr   =CreateStreamOnHGlobal(hJPG,   TRUE,   &pstm); 
		assert(SUCCEEDED(hr)   &&   pstm); 
		Image *pImg=Image::FromStream(pstm);
		pstm->Release();
		
		free(data);
		if(pImg)
		{
			if(Gdiplus::Ok==pImg->GetLastStatus())
			{
				ximage_  *pXImage=(ximage_*)malloc(sizeof(ximage_));
				memset(pXImage,0,sizeof(ximage_));
				pXImage->object.type=XC_IMAGE;
				pXImage->type=0;
				pXImage->refCount=0;
				pXImage->flag=XC_IMAGE_DEFAULT; //bStretch ? XC_IMAGE_STRETCH : XC_IMAGE_DEFAULT;
				pXImage->pImage=pImg;
				pXImage->bAutoDestroy=TRUE;

				return (HIMAGE)pXImage;
			}else
				delete pImg;
		}
	}
	return NULL;
}

////////////////////////////////////
BOOL ImageFromIDResource(int nID, wchar_t *pType,Image * &pImg)
{
	HMODULE hInst=GetModuleHandle(NULL);
	if(RT_BITMAP==pType)
	{
		Bitmap BkImage(hInst, MAKEINTRESOURCEW(nID));
		RectF sourceRect(0.0f,0.0f,(REAL)(BkImage.GetWidth()),(REAL)(BkImage.GetHeight()));
		pImg = BkImage.Clone(sourceRect, PixelFormatDontCare);
	}else
	{
		wchar_t * lpRes=MAKEINTRESOURCE(nID); 
		HRSRC   hRsrc=::FindResource(hInst,lpRes,pType);
		if(NULL==hRsrc) return FALSE;
		HGLOBAL hGlobal=LoadResource(hInst,hRsrc);
		DWORD   dwSize   =SizeofResource(hInst,hRsrc); 
		LPVOID   lpData  =LockResource(hGlobal);
		HGLOBAL   hJPG   =   ::GlobalAlloc(GMEM_MOVEABLE,   dwSize); 
		LPVOID   lpJGP   =   ::GlobalLock(hJPG); 
		memcpy(lpJGP,   lpData,   dwSize); 
		::GlobalUnlock(hJPG);
		LPSTREAM   pstm =NULL;
		HRESULT   hr   =CreateStreamOnHGlobal(hJPG,   TRUE,   &pstm); 
		assert(SUCCEEDED(hr)   &&   pstm); 
		pImg=Image::FromStream(pstm);//new Image(pstm);
		pstm->Release();

		BOOL hrr=FreeResource(hGlobal);
	}
	return TRUE;
}

BOOL ImageFromIDResourceToBitmap(int nID, wchar_t *pType,HBITMAP &hBitmap)
{
	HMODULE hInst=GetModuleHandle(NULL);

	Bitmap BkImage(hInst, MAKEINTRESOURCEW(nID));
	Gdiplus::Status result=BkImage.GetHBITMAP(NULL, &hBitmap);
	if(result==Gdiplus::Ok)
		return TRUE;
	else
		return FALSE;
}