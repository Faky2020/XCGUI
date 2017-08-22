/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//////////////////////////////////////////////////////////////
//�µ���Դ������


//�б��С
//100    10
//500    50
//1000   100
//2000   200
//5000   500
//5000+  1000


//�����б��� -> Ԫ���б�

struct resource_manager_window_
{
	HWINDOW   hWindow;

	resource_manager_window_  *pNext;
};

struct resource_manager_element_
{
	HELE  hEle;
	resource_manager_element_  *pNext;
};

struct resource_manager_element_header_
{
	resource_manager_element_  *pNode;
	int    count; //����
};


//������Դ����
struct resource_manager_
{
	resource_manager_window_          *pWindowList;   //resources_manager_window_*
	resource_manager_element_header_  *pArrayEle; //resource_manager_element_header_ []

	int  countWindow;//��������
	int  countEle;   //Ԫ������
	int  ArraySize;  //Ԫ�������С

	//������Դ,�����ַ���,����,ͼƬ
};


extern  resource_manager_   resource_manager;
void Resource_Init();
void Resource_AddWindow(HWINDOW hWindow);
BOOL Resource_RemoveWindow(HWINDOW hWindow);
int  Resource_GetWindowCount();

BOOL Resource_IsHWINDOW(HWINDOW hWindow);
/////////////////////////////////////////
BOOL Resource_IsHELE(HELE hEle); //���Ԫ�ؾ���Ƿ���Ч

void Resource_AddEle(HELE hEle);
BOOL Resource_RemoveEle(HELE hEle);
void Resource_Release();
/////////////////////////////////////////
int  Resource_Hash(int data);  //��ϣ

void Resource_Allocate(); //����ڴ�ռ��С�Ƿ����
void Resource_Allocate_X(int ArraySizeNew);
void Resource_Allocate_Add(resource_manager_element_  *pNew);

void Resource_Test();
