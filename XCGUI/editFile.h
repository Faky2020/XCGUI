#pragma once


//�ļ�ѡ��༭��



struct editFile_
{
	edit_  edit; //�̳�
	//-------------
	BOOL    bEdit;      //�ɱ༭����
	int     heights;    //�ܸ߶�
	BOOL    bOpenBrowseFile; //�Ƿ���ļ��������

	HSTRING  hType;  //���ļ�����
	HSTRING  hDefaultFile;  //Ĭ��Ŀ¼
	HSTRING  hRelativeDir;  //���Ŀ¼ Relative directory

	//������ť:
	struct
	{
		RECT rcButton;//������ť
		int  state;   //״̬
	}button_;

	//��ͼ
	HIMAGE hImage_stay; //���ͣ��
	HIMAGE hImage_down; //��갴��
};

//API:
XC_API HELE WINAPI XEditFile_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);

XC_API void WINAPI XEditFile_SetOpenFileType(HELE hEle,wchar_t *pType); //���ô��ļ�����
XC_API void WINAPI XEditFile_SetDefaultFile(HELE hEle,wchar_t *pFile); //����Ĭ��Ŀ¼�ļ�
XC_API void WINAPI XEditFile_SetRelativeDir(HELE hEle,wchar_t *pDir); //TODO:�������·��

//˽�з���:
void EditFile_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
void EditFile_Adjust(HELE hEle);
void EditFile_DrawBk(HELE hEle,HDRAW hDraw); //���Ʊ���
void EditFile_BrowseFile(HELE hEle); //����ļ�

//�ص�����:
BOOL CALLBACK EditFile_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK EditFile_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK EditFile_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);

BOOL CALLBACK EditFile_OnRButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK EditFile_OnRButtonUp(HELE hEle,UINT flags,POINT *pPt);

BOOL CALLBACK EditFile_OnEventMouseLeave(HELE hEle,HELE hEventEle);
BOOL CALLBACK EditFile_OnEventKillFocus(HELE hEle,HELE hEventEle);

BOOL CALLBACK EditFile_OnEventSetFocus(HELE hEle,HELE hEventEle);
BOOL CALLBACK EditFile_OnEventSize(HELE hEle,HELE hEventEle);

BOOL CALLBACK EditFile_OnDraw(HELE hEle,HDRAW hDraw);
void CALLBACK EditFile_OnDestroy(HELE hEle); //����

BOOL CALLBACK EditFile_OnDrawButton(HELE hEle,HDRAW hDraw); //����������ť