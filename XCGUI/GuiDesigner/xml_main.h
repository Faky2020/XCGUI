#pragma once

//ע�ắ������
#define  XC_XML_INIT            1  // 1 UI�ļ��������ʼ��
#define  XC_XML_EXIT            2  // 2 UI�ļ��������ͷ�
#define  XC_XML_CREATE_WINDOW   3  // 3 ���ڴ���
#define  XC_CML_CREATE_ELEMENT  4  // 4 Ԫ�ش���


BOOL CALLBACK OnInit();    //1 UI�ļ��������ʼ��
BOOL CALLBACK OnExit();    //2 UI�ļ��������ͷ�
BOOL CALLBACK OnCreateWindow(HWINDOW hWindow);  // 3 ���ڴ���
BOOL CALLBACK OnCreateElement(HELE hEle);    // 4 Ԫ�ش���
