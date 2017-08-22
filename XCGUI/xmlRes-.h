/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//XML��Դ����


enum res_type_
{
	res_id,     // 1.���ID��Դ
	res_string, // 2.����ַ�����Դ
	res_color,  // 3.�����ɫ��Դ

	res_image_file, // 4.���ļ��м���ͼƬ
	res_image_file_stretch, // 5.���ļ��м���ͼƬ,����
	res_image_file_adaptive, // 6.���ļ��м���ͼƬ,����ӦͼƬ

	res_image_vc, // 7.�ӳ�����Դ�м���ͼƬ
	res_image_vc_stretch, // 8.�ӳ�����Դ�м���ͼƬ,����
	res_image_vc_adaptive,// 9.�ӳ�����Դ�м���ͼƬ,����ӦͼƬ

	res_image_zip, // 10.��zipѹ�����м���ͼƬ
	res_image_zip_stretch, // 11.��zipѹ�����м���ͼƬ,����
	res_image_zip_adaptive, // 12.��zipѹ�����м���ͼƬ,����ӦͼƬ
};


struct xmlRes_data_
{
	res_type_     type;   //��Դ���� res_type_
	HSTRING name;  //����
	HSTRING value; //ֵ

	HSTRING resType;
	HSTRING zipFile;
	int  resID;

	int x1,x2,y1,y2;
};

struct xmlRes_
{
	HARRAY  hArray_ID;      //ID��Դ
	HARRAY  hArray_Image;   //ͼƬ��Դ
	HARRAY  hArray_String;  //�ַ�����Դ
	HARRAY  hArray_Color;   //��ɫ��Դ
};

//API:
XC_API HXMLRES WINAPI XXmlRes_Load(wchar_t *pFileName);
XC_API HXMLRES WINAPI XXmlRes_LoadRes(int resID,wchar_t *pType);//��VC��Դ�ļ��м���
XC_API void WINAPI XXmlRes_Destroy(HXMLRES hXmlRes);

//����ID��Դ
XC_API int WINAPI XXmlRes_FindId(HXMLRES hXmlRes,wchar_t *pName);
//����ͼƬ��Դ
XC_API void WINAPI XXmlRes_FindImage(HXMLRES hXmlRes,wchar_t *pName,out_ wchar_t *pOut,int outLen);

//�����ַ���
XC_API void WINAPI XXmlRes_FindString(HXMLRES hXmlRes,wchar_t *pName,out_ wchar_t *pOut,int outLen);


//����ͼƬ��Դ,����ͼƬ���
XC_API HIMAGE WINAPI XXmlRes_FildHIMAGE(HXMLRES hXmlRes,wchar_t *pName);

//�����ַ�����Դ

//������ɫ��Դ


//˽��:
HXMLRES WINAPI XXmlRes_LoadX(TiXmlElement *pRoot);
HXMLRES XXmlRes_LoadRes2(char *pData);//��VC��Դ�ļ��м���
BOOL XmlRes_LoadXml(xmlRes_ *pXmlRes,TiXmlElement *pRoot);
BOOL XmlRes_HandImage(xmlRes_ *pXmlRes,TiXmlElement *pLabel,xmlRes_data_ *pItem);
