/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


struct button_  //��ť
{
	ele_  ele; //�̳�
	//--------------------
	HSTRING hString;  //�ı�
	int    state;     //״̬
	BOOL   bCheck;    //��ѡ
	BOOL   bDown;
	int    textFlag; //�ı�����
	BOOL   bCursorHand; //���ͣ��,����Ϊ����
	POINT  offset;   //����ƫ����

	HIMAGE hImage_leave;
	HIMAGE hImage_stay;
	HIMAGE hImage_down;
	HIMAGE hImage_check;
	HIMAGE hImage_disable;

	HIMAGE hImage_icon; //ͼ��
	int    iconAlign;  //ͼ����뷽ʽ

	//��̬��ť
	BOOL   bAnimation;       //���û�ر�
	button_animation_group_  *pAnimation;  //��̬ͼƬ���� button_animation_group_
};

//API:
/// @defgroup button ��ť(Button)
/// @ingroup  groupElements
/// ��ť�ӿ��б�
/// @{


/// @brief    ������ťԪ��
/// @param x  ��ťx����
/// @param y  ��ťy����
/// @param cx ���
/// @param cy �߶�
/// @param pTitle  ����
/// @param hParent ���Ǵ��ھ����Ԫ�ؾ��.
/// @return ��ťԪ�ؾ��.
XC_API HELE WINAPI XBtn_Create(int x, int y, int cx, int cy,wchar_t *pTitle=NULL,HXCGUI hParent=NULL);  //������ť

/// @brief ��ȡ��ťԪ���ı�����
/// @param hEle Ԫ�ؾ��
/// @return �ı�����
XC_API wchar_t * WINAPI XBtn_GetText(HELE hEle);  //��ȡ�ı�

/// @brief ���ð�ť�ı�����.
/// @param hEle Ԫ�ؾ��
/// @param pText �ı�����
XC_API void  WINAPI XBtn_SetText(HELE hEle,wchar_t *pText);

/// @brief ���ð�ťѡ��״̬
/// @param hEle Ԫ�ؾ��
/// @param bCheck TRUEѡ��,�����෴
XC_API void WINAPI XBtn_SetCheck(HELE hEle,BOOL bCheck);

/// @brief �жϰ�ť�Ƿ�Ϊѡ��״̬.
/// @param hEle Ԫ�ؾ��
/// @return  �����ťѡ��״̬����TRUE,�����෴.
XC_API BOOL WINAPI XBtn_IsCheck(HELE hEle); //��ť�Ƿ�ѡ��

/// @brief ��ȡ��ť��ǰ״̬.
/// @param hEle Ԫ�ؾ��
/// @return ��ť״̬
XC_API int  WINAPI XBtn_GetState(HELE hEle);

/// @brief ��������뿪״̬��ť��ʾ��ͼƬ.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
XC_API void WINAPI XBtn_SetImageLeave(HELE hEle,HIMAGE hImage=NULL);  //����뿪ʱͼƬ

/// @brief ��������ڰ�ť��ͣ��״̬ʱ��ʾ��ͼƬ.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
XC_API void WINAPI XBtn_SetImageStay(HELE hEle,HIMAGE hImage=NULL);   //���ͣ��ʱͼƬ

/// @brief ���ð�ť����״̬ʱ��ʾ��ͼƬ.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
XC_API void WINAPI XBtn_SetImageDown(HELE hEle,HIMAGE hImage=NULL);   //��갴��ʱͼƬ

/// @brief ���ð�ť��ѡ��ʱ��ʾ��ͼƬ,���û�����״̬��ʹ��.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
XC_API void WINAPI XBtn_SetImageCheck(HELE hEle,HIMAGE hImage=NULL);  //ѡ��ʱͼƬ

/// @brief ���ð�ť����״̬��ʾ��ͼƬ.
/// @param hEle Ԫ�ؾ��
/// @param hImage ͼƬ���
XC_API void WINAPI XBtn_SetImageDisable(HELE hEle,HIMAGE hImage=NULL); //��ť����״̬ͼƬ

/// @brief �����ı�����.
/// @param hEle Ԫ�ؾ��.
/// @param flag ��ʶ,��μ�MSDN  DrawText().
XC_API void WINAPI XBtn_SetTextAlign(HELE hEle,int flag); //�����ı�����

/// @brief ���ð�ťͼ��.
/// @param hEle Ԫ�ؾ��.
/// @param hImage ͼƬ���.
XC_API void WINAPI XBtn_SetIcon(HELE hEle,HIMAGE hImage); //����ͼ��

/// @brief ����ͼ����뷽ʽ..
/// @param hEle Ԫ�ؾ��.
/// @param align ���뷽ʽ.
XC_API void WINAPI XBtn_SetIconAlign(HELE hEle,int align);

/// @brief ���û�ر�,������ƶ�����ť��ʱ,�������״��Ϊ����.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable �Ƿ�����.
XC_API void WINAPI XBtn_EnableCursorHand(HELE hEle,BOOL bEnable); //���ͣ��,����Ϊ����


/// @brief ��ʼ��ر�ͼƬ�����Ĳ���.
/// @param hEle Ԫ�ؾ��.
/// @param bEnable    ��ʼ���Ŷ���TRUE,�رղ��Ŷ���FALSE.
/// @param bLoopPlay  �Ƿ�ѭ������.
XC_API void WINAPI XBtn_EnableAnimation(HELE hEle,BOOL bEnable,BOOL bLoopPlay=FALSE);

/// @brief ��Ӷ���֡.
/// @param hEle Ԫ�ؾ��.
/// @param hImage  ͼƬ���
/// @param uElapse ͼƬ֡��ʱ,��λ����.
XC_API void WINAPI XBtn_AddAnimationFrame(HELE hEle,HIMAGE hImage,UINT uElapse);


//ɾ�����еĶ���֡

/// @brief ������������ƫ����.
/// @param  hEle Ԫ�ؾ��.
/// @param  x  ƫ����.
/// @param  y  ƫ����.
XC_API void WINAPI XBtn_SetOffset(HELE hEle,int x,int y); //������������ƫ����

///@}

//˽�з���:
void Btn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);

void Btn_DrawDisable(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawCheck(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawLeave(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawStay(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawDown(HELE hEle,HDRAW hDraw,RECT &rect);

void Btn_DrawLeave2(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawStay2(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawDown2(HELE hEle,HDRAW hDraw,RECT &rect);
void Btn_DrawDisable2(HELE hEle,HDRAW hDraw,RECT &rect);

void Btn_DrawIconAndText(HELE hEle,HDRAW hDraw,RECT &rect); //����ͼ����ı�

void Btn_StartAnimation(HELE hEle,BOOL bClockwise=TRUE);//��ʼ����

//�ص�����:
void CALLBACK Btn_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Btn_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK Btn_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK Btn_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK Btn_OnEventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam); 
BOOL CALLBACK Btn_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);

BOOL CALLBACK Btn_OnEventMouseStay(HELE hEle,HELE hEventEle);
BOOL CALLBACK Btn_OnEventMouseLeave(HELE hEle,HELE hEventEle);
BOOL CALLBACK Btn_OnEventSetFocus(HELE hEle,HELE hEventEle); //��ý���
BOOL CALLBACK Btn_OnEventKillFocus(HELE hEle,HELE hEventEle); //ʧȥ����

