/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//�Ųʽ����ͼƬ���� 

//#define  XC_IMAGE_BMP    1
//#define  XC_IMAGE_ICON   2
//#define  XC_IMAGE_PNG    3
//#define  XC_IMAGE_JPG    4
//#define  XC_IMAGE_GIF    5


//�Ųʿ�ͨ��ͼƬ����
struct ximage_
{
	object_ object;
	//-----------------------
	Image  *pImage; //ͼƬ����
	int    type;    //ͼƬ����
	int    refCount; //���ü���,��ֵΪ0ʱ ���ٶ���
	int    flag;    //ƽ��
	BOOL   bAutoDestroy;

	int   imageWidth;
	int   imageHeight;
	int   imageX1;
	int   imageX2;
	int   imageY1;
	int   imageY2;

//Bitmap
	BOOL   bBitmap; //�Ƿ�Ϊ����λͼ
	Bitmap *pBitmap;

	BOOL   bTransparentColor;  //�Ƿ�ָ��͸��ɫ
	Color transparentColor; //ָ��͸��ɫ
};

//��ͼƬ������õ�UIԪ�غ�,UIԪ�ػ��Զ��ͷŸ�ͼƬ���,����Ҫ�û��ֶ��ͷ�.

//���ڴ��м���ͼƬ

XC_API HIMAGE WINAPI XImage_LoadFile(wchar_t *pImageName,BOOL bStretch=FALSE);//���ļ��м���ͼƬ
XC_API HIMAGE WINAPI XImage_LoadRes(int id,wchar_t *pType,BOOL bStretch=FALSE);//����Դ�м���ͼƬ
XC_API HIMAGE WINAPI XImage_LoadZip(wchar_t *pZipFileName,wchar_t *pImageName,wchar_t *pPassword=NULL,BOOL bStretch=FALSE);//��ZIP�м���ͼƬ

//����ӦͼƬ
XC_API HIMAGE WINAPI XImage_LoadFileAdaptive(wchar_t *pImageName,int x1,int x2,int y1,int y2);//���ļ��м���ͼƬ
XC_API HIMAGE WINAPI XImage_LoadResAdaptive(int id,wchar_t *pType,int x1,int x2,int y1,int y2);//����Դ�м���ͼƬ
XC_API HIMAGE WINAPI XImage_LoadZipAdaptive(wchar_t *pZipFileName,wchar_t *pImageName,wchar_t *pPassword,int x1,int x2,int y1,int y2);//��ZIP�м���ͼƬ

//����ͼƬ,ָ������
XC_API HIMAGE WINAPI XImage_LoadFileRect(wchar_t *pImageName,int x,int y,int cx,int cy);

XC_API BOOL WINAPI XImage_IsStretch(HIMAGE hImage);   //�Ƿ�����ͼƬ
XC_API BOOL WINAPI XImage_IsAdaptive(HIMAGE hImage);  //�Ƿ�Ϊ����ӦͼƬ
XC_API BOOL WINAPI XImage_IsTile(HIMAGE hImage);      //�Ƿ�Ϊƽ��ͼƬ

XC_API BOOL WINAPI XImage_SetDrawType(HIMAGE hImage,int type);//����ͼƬ��������
XC_API BOOL WINAPI XImage_SetDrawTypeAdaptive(HIMAGE hImage,int x1,int x2,int y1,int y2);//����ͼƬ����Ӧ
XC_API void WINAPI XImage_SetTranColor(HIMAGE hImage,COLORREF color); //����͸��ɫ
XC_API void WINAPI XImage_SetTranColorEx(HIMAGE hImage,COLORREF color,byte tranColor); //����͸��ɫ
XC_API void WINAPI XImage_EnableTranColor(HIMAGE hImage,BOOL bEnable); //����͸��ɫ

XC_API void WINAPI XImage_EnableAutoDestroy(HIMAGE hImage,BOOL bEnable); //���û�ر��Զ�����,����UIԪ�ع���ʱ��Ч

//��ȡͼƬ��������
XC_API int WINAPI XImage_GetDrawType(HIMAGE hImage);

XC_API int WINAPI XImage_GetWidth(HIMAGE hImage);
XC_API int WINAPI XImage_GetHeight(HIMAGE hImage);

XC_API void WINAPI XImage_Destroy(HIMAGE hImage);

//˽�з���:
void  Image_AddImage(HIMAGE &hImage,HIMAGE hImageNew); //ͼƬ��Ԫ�ع������������ü���
HIMAGE Image_AddRef(HIMAGE hImage); //�������ü���

HIMAGE Image_LoadFile(wchar_t *pImageName);
HIMAGE Image_LoadRes(int id,wchar_t *pType);//����Դ�м���ͼƬ
HIMAGE Image_LoadZip(wchar_t *pZipFileName,wchar_t *pImageName,wchar_t *pPassword=NULL);//��ZIP�м���ͼƬ


void *do_extract_currentfile(void *uf,const char* password,int &outSize);
void *do_extract_onefile(void *uf, const char* filename, const char* password,int &outSize);

//*****************************************************************************
//ZIPѹ��������


//���ļ��м���ZIP��
//����Դ�м���ZIP��
//�Ӱ��л�ȡͼƬ,�����Ų�ͼƬ���
//�Ӱ��л�ȡ�ļ�
//�Ƿ�ZIP���


BOOL ImageFromIDResource(int nID, wchar_t *pType,Image * &pImg); //��ԴID,��Դ����
BOOL ImageFromIDResourceToBitmap(int nID, wchar_t *pType,HBITMAP &hBitmap);