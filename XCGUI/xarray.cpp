/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HARRAY WINAPI XArray_Create() //����
{
	array_ *pObj=(array_*)malloc(sizeof(array_));
	if(pObj)
	{
		memset(pObj,0,sizeof(array_));
		pObj->grow=16;
		((object_*)pObj)->type=XC_ARRAY;
		return (HARRAY)pObj;
	}
	return NULL;
}

void  WINAPI XArray_Destroy(HARRAY hArray) //����
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;

	if(pObj->data)
		free(pObj->data);

	if(pObj->hArray_list)
	{
		int count=XArray_GetCount(pObj->hArray_list);
		for(int i=0;i<count;i++)
		{
			array_traversal_iterator_ *p=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
			p->hArray=NULL;
			p->traversal_bStart=FALSE;
		}
		XArray_Destroy(pObj->hArray_list);
	}
	
	free(pObj);
}

void Array_Allocate(HARRAY hArray)
{
	array_ *pObj=(array_*)hArray;

	int count=pObj->sum -pObj->count;
	if( count<2 || count> pObj->grow)
	{
		/////////////////////////////////////
		pObj->sum=pObj->count+pObj->grow;

		void **data=(void**)malloc(pObj->sum*sizeof(void*));
		for(int i=0;i<pObj->count;i++)//ת������
		{
			data[i]=pObj->data[i];
		}
		if(pObj->data)
			free(pObj->data); //�ͷ���ǰ���ڴ�
		pObj->data=data; //���ڴ�
	}
}

int WINAPI XArray_Add(HARRAY hArray,void *pElement)
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;

	ARRAY_CHECK_SPACE(hArray); //�ռ䲻�� ���·���

	pObj->data[pObj->count]=pElement;
	pObj->count++;

	return pObj->count-1;
}

void WINAPI XArray_AddFirst(HARRAY hArray,void *pElement) //���ӵ���ͷ
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;

	ARRAY_CHECK_SPACE(hArray); //�ռ䲻�� ���·���

	for(int i=pObj->count;i>0;i--) //������Ԫ��������һ��
	{
		pObj->data[i]=pObj->data[i-1];
	}
	pObj->data[0]=pElement;
	pObj->count++;
}


BOOL WINAPI XArray_insert(HARRAY hArray,void *pElement,int index) //���뵽ָ��λ��
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;

	if(index<0 || index>pObj->count) return FALSE;

	ARRAY_CHECK_SPACE(hArray); //�ռ䲻�� ���·���

	for(int i=pObj->count;i>index;i--)
	{
		pObj->data[i]=pObj->data[i-1];
	}
	pObj->data[index]=pElement;
	pObj->count++;

	return TRUE;
}

void WINAPI XArray_DeleteIndex(HARRAY hArray,int index)
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;
	if(pObj->count<1)
		return;

	if(index>=pObj->count || index<0)
		return;

	void *data=pObj->data[index];

	if((pObj->count+pObj->grow)<pObj->sum ) //��С�ڴ�
	{
		Array_Allocate(hArray);
	}

	pObj->count--;
	if(pObj->count==index)
	{
		pObj->data[pObj->count]=0;
	}else
	{
		for(int i=index;i<pObj->count;i++) //������������ǰ��һ��
		{
			pObj->data[i]=pObj->data[i+1];
		}
		pObj->data[pObj->count]=0;
	}

	if(pObj->hArray_list)
	{
		int count=XArray_GetCount(pObj->hArray_list);
		for(int i=0;i<count;i++)
		{
			array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
			if(pIterator->traversal_bStart)
			{
				for(int j=0;j<pIterator->traversal_count;j++)
				{
					if(data==pIterator->data[j].pData)
					{
						pIterator->data[j].bValid=FALSE;
						break;
					}
				}
			}
		}
	}
}

//ɾ��Ԫ��
void WINAPI XArray_Delete(HARRAY hArray,void *pElement)     
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;
	int index(-1);
	for(int i=0;i<pObj->count;i++)
	{
		if(pElement==pObj->data[i])
		{
			pObj->data[i]=0;
			index=i;
			pObj->count--;
			break;
		}
	}
	if(-1 != index) //������������ǰ��һ��
	{
		for(int i=index;i<pObj->count;i++)
		{
			pObj->data[i]=pObj->data[i+1];
		}
		pObj->data[pObj->count]=0;
	}

	if(pObj->hArray_list)
	{
		int count=XArray_GetCount(pObj->hArray_list);
		for(int i=0;i<count;i++)
		{
			array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
			if(pIterator->traversal_bStart)
			{
				for(int j=0;j<pIterator->traversal_count;j++)
				{
					if(pElement==pIterator->data[j].pData)
					{
						pIterator->data[j].bValid=FALSE;
						break;
					}
				}
			}
		}
	}
}

//ɾ������֮�������,��������λ��Ԫ��,���Ϊ0,�൱�����
void WINAPI XArray_DeleteEnd(HARRAY hArray,int index) //ɾ��ĩβ����
{
	IsArrayDebug(hArray,__FUNCTION__);
	
	array_ *pObj=(array_*)hArray;

	if(index>=0 && index<pObj->count)
	{
		if(pObj->hArray_list)
		{
			int count=XArray_GetCount(pObj->hArray_list);
			for (int t=index;t<pObj->count;t++)
			{
				for(int i=0;i<count;i++)
				{
					array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
					if(pIterator->traversal_bStart)
					{
						for(int j=0;j<pIterator->traversal_count;j++)
						{
							if(pObj->data[t]==pIterator->data[j].pData)
							{
								pIterator->data[j].bValid=FALSE;
								break;
							}
						}
					}
				}
			}
		}
		///////////////////////////////////////
		pObj->count=index;
		Array_Allocate(hArray);
	}
}

//ɾ��ָ����Χ����,������ʼ��ĩβ����λ
// begin :��ʼ����.
// end:  ��������.
void WINAPI XArray_DeleteRange(HARRAY hArray,int begin,int end)
{
	IsArrayDebug(hArray,__FUNCTION__);

	array_ *pObj=(array_*)hArray;
	if(pObj->count<1)
		return;

	if (begin<0 || end>=pObj->count)
		return;

	if (begin==end)
	{
		XArray_DeleteIndex(hArray,begin);
		return;
	}

	if(begin>=end) return;

	if(pObj->hArray_list)
	{
		int count=XArray_GetCount(pObj->hArray_list);
		for (int t=begin;t<=end;t++)
		{
			for(int i=0;i<count;i++)
			{
				array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
				if(pIterator->traversal_bStart)
				{
					for(int j=0;j<pIterator->traversal_count;j++)
					{
						if(pObj->data[t]==pIterator->data[j].pData)
						{
							pIterator->data[j].bValid=FALSE;
							break;
						}
					}
				}
			}
		}
	}

	int count=pObj->count-(end+1);
	for (int i=0;i<count;i++)//������������ǰ��
	{
		pObj->data[i+begin]=pObj->data[i+end+1];
	}

	pObj->count=pObj->count-(end-begin+1);

	Array_Allocate(hArray);
}

void WINAPI XArray_SetAt(HARRAY hArray,int index,void *pElement)
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;

	if(index<0 || index>=pObj->count)
		return;

	if(pObj->hArray_list) //��ΪԪ�����ݸı�,���Դӵ��������ų�
	{
		int count=XArray_GetCount(pObj->hArray_list);
		for(int i=0;i<count;i++)
		{
			array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
			if(pIterator->traversal_bStart)
			{
				for(int j=0;j<pIterator->traversal_count;j++)
				{
					if(pObj->data[index]==pIterator->data[j].pData)
					{
						pIterator->data[j].bValid=FALSE;
						break;
					}
				}
			}
		}
	}

	pObj->data[index]=pElement;
}

//���
void WINAPI XArray_DeleteAll(HARRAY hArray)
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;
	if(pObj->data)
		free(pObj->data);

	pObj->data=NULL;
	pObj->count=0;
	pObj->sum=0;

	if(pObj->hArray_list)
	{
		int count=XArray_GetCount(pObj->hArray_list);
		for(int i=0;i<count;i++)
		{
			array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)XArray_GetAt(pObj->hArray_list,i);
			pIterator->traversal_bStart=FALSE;
		}
	}
}

void* WINAPI XArray_GetAt(HARRAY hArray,int index)
{
	IsArrayDebug(hArray,__FUNCTION__);
	if(index>-1 && index<((array_*)hArray)->count)
		return ((array_*)hArray)->data[index];
	else
		return NULL;
}

int WINAPI XArray_GetCount(HARRAY hArray)
{
	IsArrayDebug(hArray,__FUNCTION__);
	return ((array_*)hArray)->count;
}

///////////////////////////////////////////////////////////
//bType:����˳��
HARRAY_ITERATOR WINAPI XArrayIterator_Create(HARRAY hArray,BOOL bType) //����������
{
	IsArrayDebug(hArray,__FUNCTION__);
	array_ *pObj=(array_*)hArray;

	array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)malloc(sizeof(array_traversal_iterator_));
	if(NULL==pIterator)
		return NULL;
	//////////////////////////
	pIterator->hArray=hArray;
	pIterator->traversal_bStart=TRUE;
	pIterator->traversal_bType=bType;
	if(bType)
	{
		pIterator->traversal_index=0;
	}else
	{
		pIterator->traversal_index=pObj->count-1;
	}

	int size=  sizeof(array_traversal_);
	size= size*pObj->count;

	pIterator->data=(array_traversal_*)malloc(size);

	for(int i=0;i<pObj->count;i++)
	{
		pIterator->data[i].bValid=TRUE;
		pIterator->data[i].pData=pObj->data[i];
	}

	pIterator->traversal_count=pObj->count;

	if(NULL==pObj->hArray_list)
		pObj->hArray_list=XArray_Create();
	XArray_Add(pObj->hArray_list,pIterator);

	return (HARRAY_ITERATOR)pIterator;
}

void* WINAPI XArrayIterator_GetAt(HARRAY_ITERATOR hArray_Iterator)
{
	if(NULL==hArray_Iterator)
		return NULL;

	array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)hArray_Iterator;
	if(FALSE==pIterator->traversal_bStart)
		return NULL;

	int index=pIterator->traversal_index;
	if(index>=0 && index<pIterator->traversal_count)
	{
		if(pIterator->traversal_bType)
			pIterator->traversal_index++; ////�������
		else
			pIterator->traversal_index--; //�������
		
		if(pIterator->data[index].bValid)
			return pIterator->data[index].pData;
		else
			return XArrayIterator_GetAt(hArray_Iterator);
	}

	return NULL;
}

void  WINAPI XArrayIterator_Destroy(HARRAY_ITERATOR hArray_Iterator)
{
	if(NULL==hArray_Iterator)
		return;

	array_traversal_iterator_ *pIterator=(array_traversal_iterator_*)hArray_Iterator;

	pIterator->traversal_index=0;
	free(pIterator->data);
	pIterator->data=NULL;

	if(pIterator->hArray)
		XArray_Delete(((array_*)pIterator->hArray)->hArray_list,hArray_Iterator);

	free(pIterator);
}
