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

	//	res_image,  // ���ͼƬ��Դ:

	res_image_file, // ���ļ��м���ͼƬ
	res_image_file_stretch, // ���ļ��м���ͼƬ,����
	res_image_file_adaptive, // ���ļ��м���ͼƬ,����ӦͼƬ
	res_image_file_jiugongge, // ���ļ��м���ͼƬ,�Ź���

	res_image_vc, // �ӳ�����Դ�м���ͼƬ
	res_image_vc_stretch, // �ӳ�����Դ�м���ͼƬ,����
	res_image_vc_adaptive,// �ӳ�����Դ�м���ͼƬ,����ӦͼƬ
	res_image_vc_jiugongge,	// �ӳ�����Դ�м���ͼƬ,�Ź���

	res_image_zip, // ��zipѹ�����м���ͼƬ
	res_image_zip_stretch, // ��zipѹ�����м���ͼƬ,����
	res_image_zip_adaptive, // ��zipѹ�����м���ͼƬ,����ӦͼƬ
	res_image_zip_jiugongge,	// ��zipѹ�����м���ͼƬ,�Ź���

	res_font,
};


struct xmlRes_data_
{
	res_type_     type;   //��Դ���� res_type_
	HSTRING  name;   //����
	HSTRING  value;  //ֵ

	//ͼƬ��չ��Ϣ
	//	int zoom; //no, stretch , adaptive
	//	int from; //file, res, zip

	HSTRING  resType;  //��Դ����
	int  resID;    //��ԴID
	HSTRING  zipPicName;     //zipBag
	HSTRING zipPassword;

	int x1,x2,y1,y2;					//ͼƬѡ������
	int x11,x22,y11,y22;				//�Ź���
};

struct xmlRes_
{
	HARRAY  hArray_ID;      //ID��Դ
	HARRAY  hArray_Image;   //ͼƬ��Դ
	HARRAY  hArray_String;  //�ַ�����Դ
	HARRAY  hArray_Color;   //��ɫ��Դ
	HARRAY  hArray_Font;   //������Դ
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
HXMLRES XXmlRes_LoadX(TiXmlElement *pRoot);
HXMLRES XXmlRes_LoadRes2(char *pData);//��VC��Դ�ļ��м���
BOOL XmlRes_LoadXml(xmlRes_ *pXmlRes,TiXmlElement *pRoot);
BOOL XmlRes_HandImage(xmlRes_ *pXmlRes,TiXmlElement *pLabel,xmlRes_data_ *pItem);

BOOL CALLBACK OnInit();    //1 UI�ļ��������ʼ��
BOOL CALLBACK OnExit();    //2 UI�ļ��������ͷ�
BOOL CALLBACK OnCreateWindow(HWINDOW hWindow);  // 3 ���ڴ���
BOOL CALLBACK OnCreateElement(HELE hEle);    // 4 Ԫ�ش���