/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//����Ԫ��
#define MONTHCAL_WIDTH   192  //MonthCal_width  ���
#define MONTHCAL_HEIGHT  136  //MonthCal_height �߶�


struct monthCalBtn_
{
	RECT rect;  //����
	int  value; //ֵ
	int  state; //״̬
	int  flags; //0���� 1���� 2����
};

struct monthCal_  //����Ԫ��
{
	ele_  ele; //�̳�
	//---------------------------
	int   type; //��ǰ�������� 0:����ѡ�� 1:��ѡ�� 2:��ѡ�� 3:ʮ������ѡ��
	BOOL  bAdjust; //����
	monthCalBtn_  btn[42]; //ѡ��

	HELE hBtnLeft;  //��ť
	HELE hBtnRight; //�Ұ�ť
	int  left;      //�������
	int  top;       //�϶�����
	COleDateTime  time;    //��ǰ����
	COleDateTime  timeOld; //������ǰʱ��,������������Ƿ�ı�
	monthCalBtn_ *pSel;  //��ǰѡ��
};


//API:
XC_API HELE WINAPI XMonthCal_Create(int x, int y,int cx,int cy,HXCGUI hParent=NULL);
XC_API void WINAPI XMonthCal_SetSpacingLeft(HELE hEle,int left); //�������
XC_API void WINAPI XMonthCal_SetSpacingTop(HELE hEle,int top); //�϶�����
XC_API void WINAPI XMonthCal_SetDate(HELE hEle,int year,int month,int day);  //����ʱ��

XC_API int WINAPI XMonthCal_GetYear(HELE hEle);
XC_API int WINAPI XMonthCal_GetMonth(HELE hEle);
XC_API int WINAPI XMonthCal_GetDay(HELE hEle);

//˽�з���:
void MonthCal_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);
void MonthCal_Adjust(HELE hEle);
void MonthCal_AdjustDayWeek(HELE hEle); //����
void MonthCal_AdjustMonth(HELE hEle);
void MonthCal_AdjustYear(HELE hEle);
void MonthCal_AdjustYear10Year(HELE hEle);

void MonthCal_DrawDayWeek(HELE hEle,HDRAW hDraw); //������������
void MonthCal_DrawMonth(HELE hEle,HDRAW hDraw);  //������ѡ��
void MonthCal_DrawYear(HELE hEle,HDRAW hDraw);   //������ѡ��
void MonthCal_Draw10Year(HELE hEle,HDRAW hDraw); //����10����ѡ��

void MonthCal_LButtonDownDayWeek(HELE hEle,POINT *pPt);
void MonthCal_LButtonDownMonth(HELE hEle,POINT *pPt);
void MonthCal_LButtonDownYear(HELE hEle,POINT *pPt);
void MonthCal_LButtonDown10Year(HELE hEle,POINT *pPt);

void MonthCal_Change(HELE hEle,BOOL bView1); //��������Ƿ�ı�

//�ص�����:
BOOL CALLBACK MonthCal_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK MonthCal_OnEleLButtonDown(HELE hEle,UINT flags,POINT *pPt);

BOOL CALLBACK MonthCal_OnEventBtnClickLeft(HELE hEle,HELE hEventEle); //��ť
BOOL CALLBACK MonthCal_OnEventBtnClickRight(HELE hEle,HELE hEventEle);//�Ұ�ť


//////////////////////////////////

//DateTime
struct dateTime_  //����Ԫ��
{
	ele_  ele; //�̳�
	//------------------------
	HELE  hButton;  //������ť

	int   state; //״̬
	COleDateTime  time; //ʱ��
	int   year;  //��
	int   month;  //��
	int   day;   //��

	BOOL  bYear;  //���Ƿ�ѡ�� TRUEѡ��
	BOOL  bMonth; //���Ƿ�ѡ��
	BOOL  bDay;   //���Ƿ�ѡ��

	RECT rcYear;  //����ʾ����
	RECT rcMonth; //����ʾ����
	RECT rcDay;   //����ʾ����
	HWINDOW hPopupWnd; //��������

	//��ͼ:
	HIMAGE   hImage_bk;
//	COLORREF borderColor; //�߿���ɫ
};

//API:
XC_API HELE WINAPI XDateTime_Create(int x, int y,int cx,int cy,HXCGUI hParent=NULL);
XC_API void WINAPI XDateTime_SetDate(HELE hEle,int year,int month,int day);  //����ʱ��
XC_API int WINAPI XDateTime_GetYear(HELE hEle);
XC_API int WINAPI XDateTime_GetMonth(HELE hEle);
XC_API int WINAPI XDateTime_GetDay(HELE hEle);
XC_API HELE WINAPI XDateTime_GetButton(HELE hEle);  //��ȡ������ť


//��ͼ:
XC_API void WINAPI XDateTime_SetImage(HELE hEle,HIMAGE hImage);


//˽�з���:
void DateTime_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
void DateTime_DestroyPopupWnd(HELE hEle,BOOL bSel);  //���ٵ�������,���bSel����,�ı�����
void DateTime_Change(HELE hEle);//���ڸı�

//�ص�����:
void CALLBACK DateTime_OnDestroy(HELE hEle);  //����
BOOL CALLBACK DateTime_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK DateTime_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK DateTime_OnEventKillFocus(HELE hEle,HELE hEventEle); //ʧȥ����
BOOL CALLBACK DateTime_OnEventChar(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK DateTime_OnEventSize(HELE hEle,HELE hEventEle);

BOOL CALLBACK DateTime_OnEventBtnClick(HELE hEle,HELE hEventEle);  //������ť���
BOOL CALLBACK DateTime_OnDrawButton(HELE hEle,HDRAW hDraw); //����������ť