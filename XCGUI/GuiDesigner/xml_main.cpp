#include "StdAfx.h"
#include "xml_main.h"

BOOL CALLBACK OnInit()    //1 UI�ļ��������ʼ��
{
	printf("��ʼ�� \n");

	return true;
}

BOOL CALLBACK OnExit()    //2 UI�ļ��������ͷ�
{
	printf("�˳� \n");

	return true;
}

BOOL CALLBACK OnCreateWindow(HWINDOW hWindow) // 3 ���ڴ���
{
	printf("���ڴ��� \n");

	return true;
}

BOOL CALLBACK OnCreateElement(HELE hEle)    // 4 Ԫ�ش���
{
	printf("Ԫ�ش��� \n");

	return true;
}


void My_Main() //ru kou
{

	XML_Register(XC_XML_INIT,OnInit);
	XML_Register(XC_XML_EXIT,OnExit);
	XML_Register(XC_XML_CREATE_WINDOW,OnCreateWindow);
	XML_Register(XC_CML_CREATE_ELEMENT,OnCreateElement);
}


/*
#include <vector>
extern std::vector< HXMLRES >		g_Reslist;

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//My_Main();
	XInitXCGUI(); //������ʼ��
	
	//::MessageBox(0,0,0,0);
	//��������

	///HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"123");
	//XWnd_ShowWindow(hWindow,SW_SHOW);
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	std::vector< std::wstring > strList;
	std::wstring str = lpCmdLine;
	std::wstring strItem;
	int nIndex = str.find( L"|" );
	while ( nIndex != -1 )
	{
		strItem = str.substr( 0 , nIndex );
		strList.push_back( strItem );
		str.erase( 0 , nIndex + 1 );
		nIndex = str.find( L"|" );
	}

	for ( int i = 0 ; i < strList.size() ; i ++ )
	{
		int nIndex = strList[i].find( L"res" );
		if ( nIndex != -1 )
		{
			HXMLRES  hRes=XXmlRes_Load((wchar_t*)strList[i].c_str());	//������Դ
			if(NULL==hRes)
			{
				MessageBox(NULL,L"������Դʧ��",L"����",0);
				return 0;
			}
		}
	}
	HWINDOW hWindow;
	for ( int i = 0 ; i < strList.size() ; i ++ )
	{
		int nIndex = strList[i].find( L"xml" );
		if ( nIndex != -1 )
		{
			hWindow=XC_LoadXML_Window((wchar_t*)strList[i].c_str(),NULL); //��������
			if(NULL==hWindow)
			{
				MessageBox(NULL,L"����XMLʧ��",L"����",0);
				return 0;
			}
		}
	}

	for ( int i = 0 ; i < strList.size() ; i ++ )
	{
		int nIndex = strList[i].find( L"css" );
		if ( nIndex != -1 )
		{
			if(FALSE==XC_LoadXML_Style(hWindow,(wchar_t*)strList[i].c_str(),NULL))	//������ʽ�ļ�
			{
				MessageBox(NULL,L"������ʽʧ��",L"����",0);
				return 0;
			}
		}
	}

// 	HXMLRES  hRes=XXmlRes_Load(L"1234\\resources.res");	//������Դ
// 	if(NULL==hRes)
// 	{
// 		MessageBox(NULL,L"������Դʧ��",L"����",0);
// 		return 0;
// 	}
// 
// 	g_Reslist.push_back(hRes);


// 	HWINDOW hWindow=XC_LoadXML_Window(L"1234\\layout.xml",NULL); //��������
// 	if(NULL==hWindow)
// 	{
// 		MessageBox(NULL,L"����XMLʧ��",L"����",0);
// 		return 0;
// 	}

// 	if(FALSE==XC_LoadXML_Style(hWindow,L"1234\\style.css",hRes))	//������ʽ�ļ�
// 	{
// 		MessageBox(NULL,L"������ʽʧ��",L"����",0);
// 		return 0;
// 	}


	XRunXCGUI(); //����
	return 0;
}


int main()
{
	_tWinMain( NULL , NULL , NULL , NULL );
	return 0;
}*/