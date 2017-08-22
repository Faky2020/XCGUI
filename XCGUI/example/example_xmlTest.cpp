/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

/*
////////////////////////////////////////////////////////////////
//UI����� - XML���Գ���
struct layout_file_info_
{
	std::wstring  layout;        //�����ļ�λ��
	std::wstring  layout_res;    //������Դ�ļ�

	std::wstring  layout_style;  //��ʽ�ļ�
	std::wstring  layout_style_res;     //������Դ�ļ�

	BOOL  bWindow;  //����: TRUE ���ڲ����ļ�, FALSE ҳ�����ļ�
	int   pageLeft;
	int   pageTop;
	int   pageWidth; //�����ҳ�����ļ�,ҳ��С
	int   pageHeight;
};

BOOL handle_path(layout_file_info_ *pInfo,wchar_t *pPaths)
{
	pInfo->bWindow=TRUE;
	pInfo->pageLeft=0;
	pInfo->pageTop=0;
	pInfo->pageWidth=300;
	pInfo->pageHeight=200;
	wchar_t *pBegin=NULL;
	wchar_t *pEnd=NULL;
	wchar_t temp[MAX_PATH]={0};
	int     len=0;

	pBegin=wcsstr(pPaths,L"left:"); //����ҳ���
	if(pBegin)
	{
		pBegin+=5;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->pageLeft=_wtoi(temp);
			}
		}
	}

	pBegin=wcsstr(pPaths,L"top:"); //����ҳ���
	if(pBegin)
	{
		pBegin+=4;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->pageTop=_wtoi(temp);
			}
		}
	}

	pBegin=wcsstr(pPaths,L"type:");
	if(pBegin)
	{
		pBegin+=5;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				if(0==wcscmp(temp,L"page")) //����ҳ�ļ�
				{
					pInfo->bWindow=FALSE;
				}
			}
		}
	}

	pBegin=wcsstr(pPaths,L"width:"); //����ҳ���
	if(pBegin)
	{
		pBegin+=6;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->pageWidth=_wtoi(temp);
				if(pInfo->pageWidth<10)
					return FALSE;
		
			}
		}
	}

	pBegin=wcsstr(pPaths,L"height:"); //����ҳ�߶�
	if(pBegin)
	{
		pBegin+=7;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->pageHeight=_wtoi(temp);
				if(pInfo->pageHeight<10)
					return FALSE;
		
			}
		}
	}

	pBegin=wcsstr(pPaths,L"layout:");
	if(pBegin)
	{
		pBegin+=7;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->layout=temp;
			}
		}
	}

	pBegin=wcsstr(pPaths,L"layout_res:");
	if(pBegin)
	{
		pBegin+=11;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->layout_res=temp;
			}
		}
	}

	pBegin=wcsstr(pPaths,L"layout_style:");
	if(pBegin)
	{
		pBegin+=13;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->layout_style=temp;
			}
		}
	}

	pBegin=wcsstr(pPaths,L"layout_style_res:");
	if(pBegin)
	{
		pBegin+=17;
		pEnd=wcschr(pBegin,L'|');
		if(pEnd)
		{
			len=pEnd-pBegin;
			if(len>0)
			{
				wmemcpy(temp,pBegin,len);
				temp[len]=0;
				pInfo->layout_style_res=temp;
			}
		}
	}

	return TRUE;
}

BOOL Handle_Window(layout_file_info_ &info)
{
	if(info.layout.size()>0)
	{
		XInitXCGUI();

		HXMLRES  hLayout_res=NULL;
		if(info.layout_res.size()>0)
		{
			hLayout_res=XXmlRes_Load((wchar_t*)info.layout_res.c_str());
			if(NULL==hLayout_res)
			{
				MessageBox(NULL,L"���ش�����Դʧ��!!",L"��ʾ",0);
				return FALSE;
			}else
			{
			//	MessageBox(NULL,L"���ش�����Դ�ɹ�!!",L"��ʾ",0);
			}
		}

		HWINDOW hWindow=XC_LoadXML_Window((wchar_t*)info.layout.c_str(),hLayout_res);
		if(NULL==hWindow)
		{
			MessageBox(NULL,L"��������ʧ��!",L"��ʾ",0);
			return FALSE;
		}else
		{
		//	MessageBox(NULL,L"�������ڳɹ�!",L"��ʾ",0);
		}

		if(info.layout_style.size()>0)
		{
			HXMLRES  hLayout_style_res=NULL;
			if(info.layout_style_res.size()>0)
			{
				hLayout_style_res=XXmlRes_Load((wchar_t*)info.layout_style_res.c_str());
				if(NULL==hLayout_style_res)
				{
					MessageBox(NULL,L"������ʽ��Դʧ��!",L"��ʾ",0);
					return FALSE;
				}else
				{
			//		MessageBox(NULL,L"������ʽ��Դ�ɹ�!",L"��ʾ",0);
				}
			}

			if(FALSE==XC_LoadXML_Style(hWindow,(wchar_t*)info.layout_style.c_str(),hLayout_style_res))
			{
				MessageBox(NULL,L"������ʽʧ��!",L"��ʾ",0);
				return FALSE;
			}else
			{
			//	MessageBox(NULL,L"������ʽ�ɹ�!",L"��ʾ",0);
			}
			if(hLayout_style_res)
				XXmlRes_Destroy(hLayout_style_res);
		}
		if(hLayout_res)
			XXmlRes_Destroy(hLayout_res);

		XWnd_ShowWindow(hWindow,SW_SHOW);
		XRunXCGUI();
		return TRUE;
	}else
	{
		MessageBox(NULL,L"�޿�����Ϣ!",L"��ʾ",0);
	}

	return FALSE;
}

BOOL Handle_Page(layout_file_info_ &info)
{
	if(info.layout.size()>0)
	{
		XInitXCGUI();

		HXMLRES  hLayout_res=NULL;
		if(info.layout_res.size()>0)
		{
			hLayout_res=XXmlRes_Load((wchar_t*)info.layout_res.c_str());
			if(NULL==hLayout_res)
			{
				MessageBox(NULL,L"���ش�����Դʧ��!!",L"��ʾ",0);
				return FALSE;
			}else
			{
			//	MessageBox(NULL,L"���ش�����Դ�ɹ�!!",L"��ʾ",0);
			}
		}

		HWINDOW hWindow=XWnd_CreateWindow(0,0,info.pageLeft+info.pageWidth+16+10,info.pageTop+info.pageHeight+16+20+28,L"�Ųʽ����:���Բ���ҳ�ļ�");
		if(NULL==hWindow)
		{
			MessageBox(NULL,L"��������ʧ��!",L"��ʾ",0);
			return FALSE;
		}else
		{
		//	MessageBox(NULL,L"�������ڳɹ�!",L"��ʾ",0);
		}

		if(FALSE==XC_LoadXML_Page(hWindow,(wchar_t*)info.layout.c_str(),hLayout_res))
		{
			MessageBox(NULL,L"���ز���ҳ�ļ�ʧ��!",L"��ʾ",0);
			return FALSE;
		}

		if(info.layout_style.size()>0)
		{
			HXMLRES  hLayout_style_res=NULL;
			if(info.layout_style_res.size()>0)
			{
				hLayout_style_res=XXmlRes_Load((wchar_t*)info.layout_style_res.c_str());
				if(NULL==hLayout_style_res)
				{
					MessageBox(NULL,L"������ʽ��Դʧ��!",L"��ʾ",0);
					return FALSE;
				}else
				{
			//		MessageBox(NULL,L"������ʽ��Դ�ɹ�!",L"��ʾ",0);
				}
			}

			if(FALSE==XC_LoadXML_Style(hWindow,(wchar_t*)info.layout_style.c_str(),hLayout_style_res))
			{
				MessageBox(NULL,L"������ʽʧ��!",L"��ʾ",0);
				return FALSE;
			}else
			{
			//	MessageBox(NULL,L"������ʽ�ɹ�!",L"��ʾ",0);
			}
			if(hLayout_style_res)
				XXmlRes_Destroy(hLayout_style_res);
		}
		
		if(hLayout_res)
			XXmlRes_Destroy(hLayout_res);

		XWnd_ShowWindow(hWindow,SW_SHOW);
		XRunXCGUI();
		return TRUE;
	}else
	{
		MessageBox(NULL,L"�޿�����Ϣ!",L"��ʾ",0);
	}

	return FALSE;
}

//UI����� - XML���Գ���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//����|������Դ|��ʽ|��ʽ��Դ:
	//wchar_t path_ss[]=L"layout:layout.xml|layout_res:layout_res.res|layout_style:layout_style.css|layout_style_res:layout_style_res.res|";
	//wchar_t path_ss[]=L"layout:xml\\layout.xml|layout_res:xml\\resources.res|";
	//wchar_t path_ss[]=L"type:page|width:300|height:200|layout:xml\\layout.xml|layout_res:xml\\resources.res|";
	//wchar_t path_ss[] = L"layout:F:\\��Ŀ\\UI�����\\GuiDesigner(2012_03_10)\\Debug\\360\\mainPage2.xml|type:page|width:300|height:200|";
	//wchar_t path_ss[]=L"layout:F:\\��Ŀ\\UI�����\\GuiDesigner(2012_03_10)\\Debug\\360\\mainPage2.xml|layout_res:F:\\��Ŀ\\UI�����\\GuiDesigner(2012_03_10)\\Debug\\360\\mainFrame.res|layout_style:F:\\��Ŀ\\UI�����\\GuiDesigner(2012_03_10)\\Debug\\360\\mainFrame.css|layout_style_res:F:\\��Ŀ\\UI�����\\GuiDesigner(2012_03_10)\\Debug\\360\\mainFrame.res|type:page|width:300|height:200|";
	
	wchar_t *path_ss=lpCmdLine;

	//_CrtSetBreakAlloc(588);

	//wchar_t path_ss[]=L"layout:360\\mainFrame.xml|layout_style:360\\mainFrame.css|layout_res:360\\mainFrame.res|layout_style_res:360\\mainFrame.res|";

	//wchar_t path_ss[]=L"layout:xml\\layout.xml|";

	layout_file_info_  info;
	handle_path(&info,path_ss);

	if(info.bWindow)
		Handle_Window(info);
	else
		Handle_Page(info);

	return 0;
}
*/