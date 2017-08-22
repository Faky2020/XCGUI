/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

//scrollBar

//������ˮƽ������
struct scrollBar_
{
	ele_  ele; //�̳�
	//---------------
	BOOL  bHorizon;      //TRUE:ˮƽ������, FALSE:��ֱ������
	BOOL  bShowButton2;  //�Ƿ���ʾ���¹�����ť
	int   fixedSizeButton;    //�������Ƿ�ָ����С,-1ΪĬ�ϳ���

	RECT  rcUp;    //�ϰ�ť
	RECT  rcDown;  //�°�ť
	RECT  rcBar;   //������ť

	int   rcUpState;  //״̬
	int   rcDownState;
	int   rcBarState;

	int   btnLength; //��ť����,�Ϲ�����ť���¹�����ť
	int   barLength; //���鳤��,�϶����� -1ΪĬ�ϳ���

	int   curPos;   //��ǰ������  ������
	int   range;    //������Χ    ������ ����Χ��0��,ע�⸡������
	int   spacing;  //������ť���-2 ����

	BOOL  bDownUp;   //��갴���ϰ�ť
	BOOL  bDownDown; //��갴���°�ť
	BOOL  bDownBar;  //��갴�ڻ�����
	BOOL  bDownNull; //��갴�ڿհ���
	int   downBarPos; //���ڹ����������� ����

	int   MouseTop; //1:up, 2:down, 3:bar

//��ͼ:
	HIMAGE hImage_bk; //����ͼƬ
//�ϰ�ťͼƬ:
	HIMAGE  hImage_Leave_up;
	HIMAGE  hImage_stay_up; 
	HIMAGE  hImage_down_up;
//�°�ťͼƬ:
	HIMAGE  hImage_Leave_down;
	HIMAGE  hImage_stay_down;
	HIMAGE  hImage_down_down;
//����:
	HIMAGE  hImage_Leave_slider;
	HIMAGE  hImage_stay_slider;
	HIMAGE  hImage_down_slider;
};

//API:
XC_API HELE WINAPI XSBar_Create(int x, int y, int cx, int cy,BOOL bHorizon,HXCGUI hParent=NULL);

XC_API BOOL WINAPI XSBar_ScrollUp(HELE hEle);       //�������
XC_API BOOL WINAPI XSBar_ScrollDown(HELE hEle);     //���ҹ���
XC_API BOOL WINAPI XSBar_ScrollTop(HELE hEle);      //����������
XC_API BOOL WINAPI XSBar_ScrollBottom(HELE hEle);   //�������ײ�

XC_API BOOL WINAPI XSBar_ScrollPos(HELE hEle,int pos); //������ָ����

XC_API void WINAPI XSBar_SetScrollRange(HELE hEle,int range);
XC_API void WINAPI XSBar_SetSliderLength(HELE hEle,int length); //���û��鳤��
XC_API void WINAPI XSBar_SetHorizon(HELE hEle,BOOL bHorizon);  //ˮƽ��ʾ��ֱ

XC_API int WINAPI XSBar_GetScrollPos(HELE hEle); //��ȡ��ǰ������
XC_API int WINAPI XSBar_GetButtonLength(HELE hEle); //��ť����
XC_API int WINAPI XSBar_GetSliderLength(HELE hEle); //���鳤��
XC_API int WINAPI XSBar_GetScrollRange(HELE hEle);  //��ȡ������Χ

XC_API void WINAPI XSBar_EnableScrollButton2(HELE hEle,BOOL bEnable); //�Ƿ���ʾ���¹�����ť

XC_API void WINAPI XSBar_Adjust(HELE hEle);            //����������

//��ͼ:
XC_API void WINAPI XSBar_SetImage(HELE hEle,HIMAGE hImage);     //���ñ���ͼƬ


//������ͼ�Զ�����
XC_API void WINAPI XSBar_SetImageLeaveUp(HELE hEle,HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageStayUp(HELE hEle,HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageDownUp(HELE hEle,HIMAGE hImage);

XC_API void WINAPI XSBar_SetImageLeaveDown(HELE hEle,HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageStayDown(HELE hEle,HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageDownDown(HELE hEle,HIMAGE hImage);

XC_API void WINAPI XSBar_SetImageLeaveSlider(HELE hEle,HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageStaySlider(HELE hEle,HIMAGE hImage);
XC_API void WINAPI XSBar_SetImageDownSlider(HELE hEle,HIMAGE hImage);


//˽�з���:
void SBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
void Sbar_DrawButtonUp(HELE hEle,HDRAW hDraw);
void Sbar_DrawButtonDown(HELE hEle,HDRAW hDraw);
void Sbar_DrawButtonBar(HELE hEle,HDRAW hDraw);


//�ص�����:
void CALLBACK SBar_OnDestroy(HELE hEle);  //����
BOOL CALLBACK SBar_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK SBar_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SBar_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SBar_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK SBar_OnEventMouseLeave(HELE hEle,HELE hEventEle);
BOOL CALLBACK SBar_OnEventSize(HELE hEle,HELE hEventEle);

//��ʱ��
extern scrollBar_  *g_pScrollBar;  //���ڹ����Ĺ�����
VOID CALLBACK SBar_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent,DWORD dwTime);

