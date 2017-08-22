/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#ifdef _DEBUG  //CRT�ڴ�й©���  //_CrtSetBreakAlloc(int number);   //���öϵ�
#define   _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#include <crtdbg.h>
#endif  

#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <atltime.h>
#include <atlcomtime.h>
#include <stdio.h>
#include <assert.h>
#include <atlwin.h>  //IE�ؼ���Ҫʹ��

#define GDIPVER 0x0110
#include <unknwn.h>
#include <Imm.h>
#include <Commdlg.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib,"Imm32.lib")

#pragma warning(disable:4996)

#include "tinyxml/tinyxml.h"

#import "flash/flash11e.dll"

#define XCGUI_CLASS_NAME  L"XCGUI"


#include "xcgui.h"
#include "xcdef.h"
#include "debug.h"
#include "ResourceManager.h"
#include "string_x.h"
#include "array_x.h"
#include "multiTree_x.h"
#include "image_x.h"
#include "XCAPI.h"
#include "font_x.h"


#include "dc.h"
#include "xcapp.h"
#include "ele.h"
#include "button.h"
#include "check.h"
#include "radio.h"
#include "scrollBar.h"
#include "scrollView.h"
#include "edit.h"
#include "richEdit.h"
#include "editFile.h"
#include "imageList.h"
#include "list.h"
#include "listView.h"
#include "Tree.h"
#include "listBox.h"
#include "comboBox.h"
#include "menuBar.h"
#include "propertyPage.h"
#include "sliderBar.h"
#include "progressBar.h"
#include "toolBar.h"
#include "static_x.h"
#include "groupBox.h"
#include "picture.h"
#include "monthCal.h"
#include "propertyGrid.h"
#include "chooseColor.h"
#include "outlook.h"
#include "textLink.h"
#include "tabBar.h"
#include "gif.h"


#include "layoutCell.h"
#include "Pier.h"


#include "window.h"
#include "comboBoxWindow.h"
#include "menu.h"
#include "modalWindow.h"
#include "dateTimeWindow.h"
#include "frameWnd.h"

#include "pane.h"

//#include "sendEMail.h"
//#include "xmlRes.h"
//#include "xcxml.h"
#include "WebBrowser.h"
#include "flash.h"


#include "GuiDesigner/xml.h"
#include "GuiDesigner/xmlRes.h"
//#include "Main.h"


//-----------------------------------------------------------


/// @defgroup groupWindows UI����ģ���б�


/// @defgroup groupElements UIԪ��ģ���б�

/// @defgroup groupOther ����ģ��

/// @defgroup msgAndEvents ��Ϣ���¼�


/// @defgroup wndMSG  ������Ϣ
/// @ingroup msgAndEvents
/// @details������Ϣ-����ϵͳ�ǿͻ�����Ϣ


/// @defgroup wndNCMSG  ���ڷǿͻ�����Ϣ
/// @ingroup msgAndEvents
/// ���ڷǿͻ�����Ϣ-�߼��ϵķǿͻ���


/// @defgroup eleMSG Ԫ����Ϣ
/// @ingroup msgAndEvents


/// @defgroup eleEvents  Ԫ���¼�
/// @ingroup msgAndEvents

/// @defgroup macroDefine �궨��

/// @defgroup groupGlobalAPI  ȫ��API

/// @defgroup groupGuiDesigner  UI�����֧��


////////////////////////////////////////////////////////////////////////


