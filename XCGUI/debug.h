/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


#ifdef _DEBUG

#define  DebugBox(msg) MessageBoxW(NULL,msg,L"�Ųʽ����-������ʾ!",MB_OK);

//�����������ʾ
void DebugBox_CheckHandle(char *pFunName,char *pHandle);

void AddTypeDebug(HXCGUI hXCGUI,int type);//�����ڻ�Ԫ��������ӵ�����

void IsWindowDebug(HWINDOW hWindow,char *pFunName); //�Ѵ���
void IsModalWindowDebug(HWINDOW hWindow,char *pFunName); //�Ѵ���
//void IsPopupMenuWindowDebug(HWINDOW hWindow,char *pFunName); //�Ѵ���
void IsFrameWindowDebug(HWINDOW hWindow,char *pFunName); //�Ѵ���

void IsEleDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsButtonDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsCheckDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsRadioDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsEditDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsComboBoxDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsScrollBarDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsScrollViewDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsListDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsListBoxDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsTreeDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsMenuBarDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsPropertyPageDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsSliderDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsProgressBarDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsToolBarDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsToolBarBtnDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsStaticDebug(HELE hEle,char *pFunName); //�Ѵ���
void IsGroupBoxDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsPictureDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsMonthCalDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsDateTimeDebug(HELE hEle,char *pFunName);  //�Ѵ���
void IsPGridDebug(HELE hEle,char *pFunName);  //��������
void IsChooseColorDebug(HELE hEle,char *pFunName);  //��ɫѡ��
void IsTextLinkDebug(HELE hEle,char *pFunName); //��̬�ı�����
void IsTabBarDebug(HELE hEle,char *pFunName); //TabBar
void IsGifDebug(HELE hEle,char *pFunName);  //GIF
void IsListViewDebug(HELE hEle,char *pFunName);  //ListView
void IsEditFileDebug(HELE hEle,char *pFunName);  //EditFile
void IsPaneDebug(HELE hEle,char *pFunName); //pane
void IsRichEditDebug(HELE hEle,char *pFunName); //RichEdit

//Outlook

void IsArrayDebug(HARRAY hArray,char *pFunName); //�Ѵ���
void IsStringDeBug(HSTRING hString,char *pFunName); //�Ѵ���
void IsImageListDebug(HXCGUI hImageList,char *pFunName); //�Ѵ���
void IsMenuDebug(HMENUX hMenu,char *pFunName); //���˵�
void IsHImageDebug(HIMAGE hImage,char *pFunName); //�Ų�ͼƬ
void IsDrawDebug(HDRAW hDraw,char *pFunName);
void IsFontDebug(HFONTX hFontX,char *pFunName);

void IsImageTypeDebug(wchar_t *pFunName,wchar_t *pImageFile); //���ͼƬ����



#else
#define  DebugBox(msg)

#define AddTypeDebug(hXCGUI,type);//�����ڻ�Ԫ��������ӵ�����

#define IsWindowDebug(hWindow,pFunName); //�Ѵ���
#define IsModalWindowDebug(hWindow,pFunName);  //�Ѵ���
//#define IsPopupMenuWindowDebug(hWindow,pFunName);  //�Ѵ���
#define IsFrameWindowDebug(hWindow,pFunName);  //�Ѵ���

#define IsEleDebug(hEle,pFunName);  //�Ѵ���
#define IsButtonDebug(hEle,pFunName); //�Ѵ���
#define IsCheckDebug(hEle,pFunName); //�Ѵ���
#define IsRadioDebug(hEle,pFunName); //�Ѵ���
#define IsEditDebug(hEle,pFunName);  //�Ѵ���
#define IsComboBoxDebug(hEle,pFunName); //�Ѵ���
#define IsScrollBarDebug(hEle,pFunName); //�Ѵ���
#define IsScrollViewDebug(hEle,pFunName); //�Ѵ���
#define IsListDebug(hEle,pFunName); //�Ѵ���
#define IsListBoxDebug(hEle,pFunName); //�Ѵ���
#define IsTreeDebug(hEle,pFunName);  //�Ѵ���
#define IsMenuBarDebug(hEle,pFunName); //�Ѵ���
#define IsPropertyPageDebug(hEle,pFunName); //�Ѵ���
#define IsSliderDebug(hEle,pFunName); //�Ѵ���
#define IsProgressBarDebug(hEle,pFunName); //�Ѵ���
#define IsToolBarDebug(hEle,pFunName); //�Ѵ���
#define IsToolBarBtnDebug(hEle,pFunName);  //�Ѵ���
#define IsStaticDebug(hEle,pFunName); //�Ѵ���
#define IsGroupBoxDebug(hEle,pFunName); //�Ѵ���
#define IsPictureDebug(hEle,pFunName); //�Ѵ���
#define IsMonthCalDebug(hEle,pFunName); //�Ѵ���
#define IsDateTimeDebug(hEle,pFunName); //�Ѵ���
#define IsPGridDebug(hEle,pFunName); //�Ѵ���
#define IsChooseColorDebug(hEle,pFunName); //��ɫѡ��
#define IsTextLinkDebug(hEle,pFunName); //��̬�ı�����
#define IsTabBarDebug(hEle,pFunName);  //TabBar
#define IsGifDebug(hEle,pFunName);  //GIF
#define IsListViewDebug(hEle,pFunName);  //ListView
#define IsEditFileDebug(hEle,pFunName);  //EditFile
#define IsPaneDebug(hEle,pFunName);
#define IsRichEditDebug(hEle,pFunName); //RichEdit

#define IsArrayDebug(hArray,pFunName); //�Ѵ���
#define IsStringDeBug(hString,pFunName); //�Ѵ���
#define IsImageListDebug(hImageList,pFunName); //�Ѵ���
#define IsMenuDebug(hMenu,pFunName);//�Ѵ���
#define IsHImageDebug(hImage,pFunName); //�Ų�ͼƬ
#define IsDrawDebug(hDraw,pFunName);
#define IsFontDebug(hFontX,pFunName);

#define IsImageTypeDebug(pFunName,pImageFile); //���ͼƬ����
#endif

