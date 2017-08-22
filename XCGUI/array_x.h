/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct ele_;

struct array_traversal_
{
	void *pData;  //����
	BOOL  bValid; //�Ƿ���Ч
};

//������
struct array_traversal_iterator_
{
	HARRAY  hArray;  //array_*
	BOOL  traversal_bStart;  //�Ƿ����ڱ���
	BOOL  traversal_bType;   //������ʽ,��ǰ������TRUE,�Ӻ���ǰ����FALSE.
	int   traversal_index;   //Traversal//��ǰ��������
	int   traversal_count;
	array_traversal_  *data;  //���Ƶ���������
};

struct array_
{
	object_ object;

	void**  data;   //Ԫ���б�ָ��
	int     count;  //Ԫ��ʵ�ʸ���
	int     sum;    //�����������
	int     grow;   //����ֵ

	HARRAY  hArray_list;//�������б�array_traversal_iterator_* 
};

//API:
XC_API HARRAY WINAPI XArray_Create(); //����
XC_API void WINAPI XArray_Destroy(HARRAY hArray); //����
XC_API int  WINAPI XArray_Add(HARRAY hArray,void *pElement);//����Ԫ�ص�ĩβ
XC_API void WINAPI XArray_AddFirst(HARRAY hArray,void *pElement); //���ӵ���ͷ
XC_API BOOL WINAPI XArray_insert(HARRAY hArray,void *pElement,int index); //���뵽ָ��λ��
XC_API void WINAPI XArray_DeleteIndex(HARRAY hArray,int index);
XC_API void WINAPI XArray_Delete(HARRAY hArray,void *pElement);
XC_API void WINAPI XArray_DeleteEnd(HARRAY hArray,int index); //ɾ��ĩβ����
XC_API void WINAPI XArray_DeleteRange(HARRAY hArray,int begin,int end);
XC_API void WINAPI XArray_DeleteAll(HARRAY hArray);
XC_API void WINAPI XArray_SetAt(HARRAY hArray,int index,void *pElement);

XC_API void* WINAPI XArray_GetAt(HARRAY hArray,int index);
XC_API int WINAPI XArray_GetCount(HARRAY hArray);

/////////////////////////////////////////////////////////////
//������,��ȫ����,�ڱ����пɶ�HARRAY�����Ա��ӻ�ɾ������,�����к�����Ӻ�ɾ���ĳ�Ա,.
XC_API HARRAY_ITERATOR WINAPI XArrayIterator_Create(HARRAY hArray,BOOL bType=TRUE);  //����������
XC_API void* WINAPI XArrayIterator_GetAt(HARRAY_ITERATOR hArray_Iterator);
XC_API void  WINAPI XArrayIterator_Destroy(HARRAY_ITERATOR hArray_Iterator);




//˽�з���:
void Array_Allocate(HARRAY hArray);

#define Array_GetCount(hArray)                (((array_*)hArray)->count)
#define Array_GetAt(hArray,index)             (((array_*)hArray)->data[index]) 
#define Array_GetAtEle(hArray,index)          ((ele_*)((array_*)hArray)->data[index])
#define Array_GetAtWnd(hArray,index)	      ((window_*)((array_*)hArray)->data[index])
#define Array_GetAtW(hArray,index)	          ((wchar_t*)((array_*)hArray)->data[index])
#define Array_GetAtEdit(hArray,index)         ((editStrList_*)((array_*)hArray)->data[index])
#define Array_GetAtImage(hArray,index)	      ((imageListItem_*)((array_*)hArray)->data[index])
#define Array_GetAtList(hArray,index)         ((listItem_*)((array_*)hArray)->data[index])
#define Array_GetAtListHeader(hArray,index)   ((listHeader_*)((array_*)hArray)->data[index])
#define Array_GetAtListSubItem(hArray,index)  ((listSubItem_*)((array_*)hArray)->data[index])
#define Array_GetAtMenu(hArray,index)	      ((menu_*)((array_*)hArray)->data[index])
#define Array_GetAtMenuBarItem(hArray,index)  ((menuBarItem_*)((array_*)hArray)->data[index])

//Array_CheckSpace(HXCGUI hArray) //����ڴ�ռ䣬����������ռ�
#define ARRAY_CHECK_SPACE(hArray) {if(((array_*)hArray)->count>=((array_*)hArray)->sum) Array_Allocate(hArray);} //�ռ䲻�� ���·���