/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup string �ַ�������
/// @ingroup  groupOther
/// @{

/// @brief �����ַ����ӿ�.
/// @param pString ��ʼ�ַ���.
/// @return �ַ��ӿھ��.
HSTRING WINAPI XStr_Create(wchar_t *pString)
{
	int size=sizeof(string_);
	void *pObj=malloc(size);
	if(pObj)
	{
		memset(pObj,0,size);
		((object_*)pObj)->type=XC_STRING;
		string_ *pStr=(string_*)pObj;

		Str_Init((HSTRING)pStr);
		
		if(pString)
			XStr_SetString((HSTRING)pStr,pString);

		return (HSTRING)pStr;
	}
	return NULL;
}

/// @brief �����ַ����ӿ�.
/// @param hStr �ַ����ӿھ��.
void WINAPI XStr_Destroy(HSTRING hStr)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(hStr)
	{
		string_ *pStr=(string_*)hStr;
		if(pStr->pData)
		{
			free(pStr->pData);
			pStr->pData=NULL;
		}
		free(hStr);
		hStr=NULL;
	}
}

void Str_Init(HSTRING hStr)
{
	string_ *pStr=(string_*)hStr;
	pStr->sum=STRING_SUM;
	pStr->grow=STRING_GROW;
	pStr->count=0;

	int size=sizeof(wchar_t) * pStr->sum;
	pStr->pData=(wchar_t*)malloc(size);
	if(NULL==pStr->pData)
		assert(FALSE);
	memset(pStr->pData,0,size);
}

/// @brief ����ַ���.
/// @param hStr �ַ����ӿھ��.
void WINAPI XStr_Empty(HSTRING hStr)   //���
{
	IsStringDeBug(hStr,__FUNCTION__);

	if(((string_*)hStr)->pData)
	{	
		free(((string_*)hStr)->pData);
		((string_*)hStr)->pData=NULL;
	}
	Str_Init(hStr);
}

void Str_Allocate(HSTRING hStr,int sum) //�ռ䲻�� ���·���ռ�
{
	string_ *pStr=(string_*)hStr;
	if(sum<1) 
		assert(FALSE);
	pStr->sum=sum;
	int size=sizeof(wchar_t) * pStr->sum;
	wchar_t *pData=(wchar_t*)malloc(size);
	if(NULL==pData)
		assert(FALSE);
	memset(pData,0,size);
	if(pStr->count>0)
		wmemcpy(pData,pStr->pData,pStr->count);
	if(pStr->pData)
		free(pStr->pData);
	pStr->pData=pData;
}

/// @brief �����ַ���ָ��λ��.
/// @param hStr �ַ����ӿھ��.
/// @param index ����λ��.
/// @param ch    �����ַ�.
void WINAPI XStr_InsertChar(HSTRING hStr,int index, wchar_t ch) //����
{
	IsStringDeBug(hStr,__FUNCTION__);
	string_ *pStr=(string_*)hStr;
	if(pStr->count>(pStr->sum-2))
	{
		Str_Allocate(hStr,pStr->sum+pStr->grow);
	}
	if(index<=pStr->count)
	{
		for(int i=pStr->count; i>index;i--) //������λ�ú����Ԫ��������һ��
		{
			pStr->pData[i]=pStr->pData[i-1];
		}
		pStr->pData[index]=ch;
		pStr->count++;
	}
}

/// @brief �����ַ�����ָ��λ��.
/// @param hStr �ַ����ӿھ��.
/// @param index  ����λ��.
/// @param pStr   �����ַ���.
void WINAPI XStr_InsertString(HSTRING hStr,int index, wchar_t *pStr)
{
	IsStringDeBug(hStr,__FUNCTION__);
	string_ *pString=(string_*)hStr;

	if(NULL==pStr) return;
	int len=wcslen(pStr);
	if(len<1) return;

	int lens=len+pString->count;
	if(lens>=pString->sum)
		pString->sum=lens+pString->grow;
	int size=sizeof(wchar_t)*pString->sum;
	wchar_t *data=(wchar_t*)malloc(size);
	if(NULL==data) assert(FALSE);
	wmemset(data,0,pString->sum);
	if(0==index)
	{
		wmemcpy(data,pStr,len);
		wmemcpy(data+len,pString->pData,pString->count);
	}else if(pString->count==index)
	{
		wmemcpy(data,pString->pData,pString->count);
		wmemcpy(data+pString->count,pStr,len);
	}else
	{
		wmemcpy(data,pString->pData,index);
		wmemcpy(data+index,pStr,len);
		wmemcpy(data+index+len,pString->pData+index,pString->count-index);
	}
	pString->count+=len;
	free(pString->pData);
	pString->pData=data;
}

/// @brief �����ַ���Դ�ı�����.
/// @param hStr �ַ����ӿھ��.
/// @param pStr �ı�����.
void WINAPI XStr_SetString(HSTRING hStr, wchar_t *pStr) //�����ı�
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(pStr)
	{
		string_ *pString=(string_*)hStr;
		if(pString->count>0)
			XStr_Empty(hStr);

		int len=wcslen(pStr);
		if(len<1)
			return ;

		if(len>(pString->sum-2))
		{
			Str_Allocate(hStr,len+pString->grow);
		}
		wmemcpy(pString->pData,pStr,len);
		pString->count=len;
	}
}

/// @brief ����ַ�����ĩβ.
/// @param hStr �ַ����ӿھ��.
/// @param pStr �ı�����.
void WINAPI XStr_AddString(HSTRING hStr, wchar_t *pStr) //����ı���ĩβ
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(pStr)
	{
		string_ *pString=(string_*)hStr;
		int len=wcslen(pStr);

		if(len<1) return ;
		int lens=pString->count+len;

		if(lens>(pString->sum-2))
		{
			Str_Allocate(hStr,lens+pString->grow);
		}
		wchar_t *pDes=wmemcpy(pString->pData+pString->count,pStr,len);
		if(pDes)
			pString->count+=wcslen(pDes);
	}
}

/// @brief ���ָ�������ַ�����ĩβ.
/// @param hStr �ַ����ӿھ��.
/// @param pStr �ı�����.
/// @param strLen ����ı�����.
void WINAPI XStr_AddStringLength(HSTRING hStr, wchar_t *pStr, int strLen) //����ı���ĩβ
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(pStr)
	{
		string_ *pString=(string_*)hStr;

		if(strLen<1) return ;
		int lens=pString->count+strLen;

		if(lens>(pString->sum-2))
		{
			Str_Allocate(hStr,lens+pString->grow);
		}
		wchar_t *pDes=wmemcpy(pString->pData+pString->count,pStr,strLen);
		if(pDes)
			pString->count+=wcslen(pDes);
	}
}

/// @brief �����ַ�������,����Ľ�ȥ��.
/// @param hStr �ַ����ӿھ��.
/// @param length �ַ�������.
void WINAPI XStr_SetLength(HSTRING hStr,int length)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(length>0)
	{
		string_ *pString=(string_*)hStr;
		if(length>=pString->count)
			return;
		
		pString->count=length; 
		pString->sum=length+pString->grow;
		int size=sizeof(wchar_t)*pString->sum;
		wchar_t *data=(wchar_t*)malloc(size);
		if(NULL==data)
		{
			assert(FALSE);
			return;
		}
		wmemset(data,0,pString->sum);
		wmemcpy(data,pString->pData,length);
		free((void*)(pString->pData));
		pString->pData=data;
	}else if(0==length)
	{
		XStr_Empty(hStr);
	}
}

/// @brief �滻ָ�����ַ���.
/// @param hStr �ַ����ӿھ��.
/// @param pStrOld ��Ҫ�滻���ַ���.
/// @param pStrNew �滻�������.
void WINAPI XStr_Replace(HSTRING hStr,wchar_t *pStrOld,wchar_t *pStrNew) //�ַ����滻 Replace
{
	IsStringDeBug(hStr,__FUNCTION__);
	int len=wcslen(pStrOld);
	if(len<1) return;

	string_ *pString=(string_*)hStr;
	wchar_t *pIndex=NULL;
	int index=0;
	while(pIndex=wcsstr(pString->pData,pStrOld))
	{
		index=pIndex-pString->pData;
		XStr_DeleteLength(hStr,index,len);
		XStr_InsertString(hStr,index,pStrNew);
	}
}

/// @brief ��ȡ�ַ���������ָ��.
/// @param hStr �ַ����ӿھ��.
/// @return �ַ���������ָ��.
wchar_t* WINAPI XStr_GetBuffer(HSTRING hStr)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(hStr)
		return ((string_*)hStr)->pData;
	return NULL;
}

/// @brief ��ȡ�ַ�������.
/// @param hStr �ַ����ӿھ��.
/// @return �ַ�������.
int WINAPI XStr_GetLength(HSTRING hStr)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(hStr)
		return ((string_*)hStr)->count;
	return 0;
}

/// @brief �����ַ�,���ظ��ַ�����λ��ָ��.
/// @param hStr �ַ����ӿھ��.
/// @param ch    Ҫ���ҵ��ַ�.
/// @param strart  ��ʼ����λ��
/// @return ���ַ�����λ��ָ��.
wchar_t*  WINAPI XStr_Find(HSTRING hStr,wchar_t ch, int strart) //����
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(strart>=((string_*)hStr)->count)
		return NULL;
	return wcschr( ((string_*)hStr)->pData+strart,ch);
}

/// @brief ����ָ��λ���ַ�.
/// @param hStr �ַ����ӿھ��.
/// @param index �ַ�λ��.
/// @param ch  �ַ���ֵ.
void WINAPI XStr_SetAt(HSTRING hStr,int index, wchar_t ch)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(index<((string_*)hStr)->count && index>=0)
		((string_*)hStr)->pData[index]=ch;
}

/// @brief ��ȡָ��λ���ַ�.
/// @param hStr �ַ����ӿھ��.
/// @param index �ַ�λ��.
/// @return  ��λ�õ��ַ�.
wchar_t WINAPI XStr_GetAt(HSTRING hStr,int index)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(hStr)
		return ((string_*)hStr)->pData[index];
	return NULL;
}

/// @brief �ж��ַ����Ƿ�Ϊ��.
/// @param hStr �ַ����ӿھ��.
/// @return  ���Ϊ�շ���TRUE,�����෴.
BOOL WINAPI XStr_IsEmpty(HSTRING hStr)
{
	IsStringDeBug(hStr,__FUNCTION__);
	if(0==((string_*)hStr)->count)
		return TRUE;
	else
		return FALSE;
}

/// @brief ɾ��ָ���ַ�.
/// @param hStr �ַ����ӿھ��.
/// @param ch   Ҫɾ�����ַ�.
void WINAPI XStr_Delete(HSTRING hStr,wchar_t ch)
{
	IsStringDeBug(hStr,__FUNCTION__);
	string_ *pString=(string_*)hStr;
	int start=0;
	while(1)
	{
		int index(-1);
		for(int i=start;i<pString->count;i++)
		{
			if(ch==pString->pData[i])
			{
				pString->pData[i]=0;
				index=i;
				pString->count--;
				break;
			}
		}
		if(index!=(-1)) //������������ǰ��һ��
		{
			start=index;
			for(int i=index;i<pString->count;i++)
			{
				pString->pData[i]=pString->pData[i+1];
			}
			pString->pData[pString->count]=0;
		}else
		{
			return ;
		}
	}
}

/// @brief ��ָ��λ��ɾ��N���ַ�.
/// @param hStr �ַ����ӿھ��.
/// @param index  ��ʼɾ���ַ���λ��.
/// @param count  Ҫɾ�����ַ�����.
void WINAPI XStr_DeleteLength(HSTRING hStr,int index, int count)
{
	IsStringDeBug(hStr,__FUNCTION__);
	string_ *pString=(string_*)hStr;

	if(index<0 || index>=pString->count)
		return ;

	if(count>= pString->count) //���
	{
		XStr_Empty(hStr);
		return ;
	}

	if(0==index) //��ͷ
	{
		pString->sum=pString->count-count+pString->grow;
		int size=sizeof(wchar_t) * pString->sum;
		wchar_t *data=(wchar_t*)malloc(size);
		wmemset(data,0,pString->sum);
		wmemcpy(data,pString->pData+count,pString->count-count);
		pString->count-=count;
		if(pString->pData)
			free(pString->pData);
		pString->pData=data;
	}else if((index+count)>=pString->count) //ĩβ
	{
		if(index<(pString->sum-10))
			pString->sum=index+pString->grow;
		int size=sizeof(wchar_t)*pString->sum;
		wchar_t *data=(wchar_t*)malloc(size);
		wmemset(data,0,pString->sum);
		wmemcpy(data,pString->pData,pString->count-count);
		pString->count=pString->count-count;
		if(pString->pData)
			free(pString->pData);
		pString->pData=data;
	}else //�м�
	{
		pString->sum=pString->count-count+pString->sum;
		int size=sizeof(wchar_t) * pString->sum;
		wchar_t *data=(wchar_t*)malloc(size);
		wmemset(data,0,pString->sum);
		wmemcpy(data,pString->pData,index);
		wmemcpy(data+index,pString->pData+index+count,pString->count-index-count);
		pString->count=pString->count-count;
		if(pString->pData)
			free(pString->pData);
		pString->pData=data;
	}
}

/// @brief ɾ��ָ��λ��֮����ַ���.
/// @param hStr �ַ����ӿھ��.
/// @param index  Ҫɾ����λ��.
void WINAPI XStr_DeleteFront(HSTRING hStr, int index) //ɾ��ָ��λ��֮����ַ�
{
	IsStringDeBug(hStr,__FUNCTION__);
	string_ *pString=(string_*)hStr;
	if(index<-1) return ;

	if(pString->count>0)
	{
		if(index>=pString->count)
			index=pString->count-1;

		pString->sum=index+pString->grow+1;

		int size=sizeof(wchar_t) * pString->sum;
		wchar_t *data=(wchar_t*)malloc(size);
		wmemset(data,0,pString->sum);
		wmemcpy(data,pString->pData,index+1);
		pString->count=index+1;
		if(pString->pData)
			free(pString->pData);
		pString->pData=data;
	}
}

/// @brief ɾ��ָ��λ��֮ǰ���ַ���.
/// @param hStr �ַ����ӿھ��.
/// @param index  Ҫɾ����λ��.
void WINAPI XStr_DeleteBack(HSTRING hStr, int index) //ɾ��ָ��λ��֮ǰ���ַ�
{
	IsStringDeBug(hStr,__FUNCTION__);
	string_ *pString=(string_*)hStr;
	if(index<1) return;

	if(pString->count>0)
	{
		if(index<=pString->count)
		{
			int count=pString->count-index;
			pString->sum=count+pString->grow;

			int size=sizeof(wchar_t)*pString->sum;
			wchar_t *data=(wchar_t*)malloc(size);
			wmemset(data,0,pString->sum);

			wmemcpy(data,pString->pData+index,count);
			pString->count=count;
			if(pString->pData)
				free(pString->pData);
			pString->pData=data;
		}
	}
}
///@}
