/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct string_
{
	object_ object;

	wchar_t *pData;   //����
	int     count;   //��ǰ�ַ���
	int     sum;     //��ǰ�������ַ���
	int     grow;    //����ֵ //grow

};

#define STRING_SUM  8  //sum
#define STRING_GROW 8  //grow

//API:
XC_API HSTRING WINAPI XStr_Create(wchar_t *pString=NULL);
XC_API void WINAPI XStr_Destroy(HSTRING hStr);

XC_API void WINAPI XStr_InsertChar(HSTRING hStr,int index,wchar_t ch);  //����
XC_API void WINAPI XStr_InsertString(HSTRING hStr,int index,wchar_t *pStr);
XC_API void WINAPI XStr_SetString(HSTRING hStr, wchar_t *pStr); //�����ı�
XC_API void WINAPI XStr_AddString(HSTRING hStr, wchar_t *pStr); //����ı���ĩβ
XC_API void WINAPI XStr_AddStringLength(HSTRING hStr, wchar_t *pStr, int strLen); //����ı���ĩβ
XC_API void WINAPI XStr_SetLength(HSTRING hStr,int length); //�����ַ�������,������ַ�ȥ��

//pStrOld:��Ҫ�滻���ַ���,pStrNew:�滻����ַ���
XC_API void WINAPI XStr_Replace(HSTRING hStr,wchar_t *pStrOld,wchar_t *pStrNew); //�ַ����滻 Replace

XC_API wchar_t* WINAPI XStr_GetBuffer(HSTRING hStr);
XC_API int WINAPI XStr_GetLength(HSTRING hStr);
XC_API wchar_t*  WINAPI XStr_Find(HSTRING hStr,wchar_t ch, int strart=0); //�����ַ�
XC_API void WINAPI XStr_SetAt(HSTRING hStr,int index, wchar_t ch);//����ָ��λ�õ�һ���ַ�
XC_API wchar_t WINAPI XStr_GetAt(HSTRING hStr,int index); //��ȡָ��λ�õ�һ���ַ�
XC_API void WINAPI XStr_Empty(HSTRING hStr);    //���
XC_API BOOL WINAPI XStr_IsEmpty(HSTRING hStr);  //�ж��Ƿ�Ϊ��
XC_API void WINAPI XStr_Delete(HSTRING hStr,wchar_t ch); //ɾ��ch,ȫ��chɾ��
XC_API void WINAPI XStr_DeleteLength(HSTRING hStr,int index, int count=1); //��indexλ��ɾ��count���ַ�
XC_API void WINAPI XStr_DeleteFront(HSTRING hStr, int index); //ɾ��ָ��λ��֮����ַ���
XC_API void WINAPI XStr_DeleteBack(HSTRING hStr, int index);  //ɾ��ָ��λ��֮ǰ���ַ���

//˽�з���
void Str_Init(HSTRING hStr);
void Str_Allocate(HSTRING hStr,int sum);  //�ռ䲻�� ���·���ռ�

//WideCharToMultiByte(CP_ACP,NULL,pInWChar,wcslen(pInWChar),pOutChar,outCharLength,NULL,NULL);
//MultiByteToWideChar(CP_ACP,0,pInChar,-1,pOutWChar,outWCharLength);

//16�����ַ���ת10����
//int HexToDec(wchar_t *shex);

//isdigit();//�ж��Ƿ�Ϊ����
//isalpha();//�ж��Ƿ�Ϊ��ĸ
//isxdigit();//�ж��Ƿ�Ϊ16����