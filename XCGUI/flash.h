/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


using namespace ShockwaveFlashObjects;

struct flash_
{
	IShockwaveFlash  *m_pShwaveflash;
};


XC_API HXCGUI WINAPI XFlash_Create(HWINDOW hWindow);
XC_API void  WINAPI XFlash_OpenFlashFile(HXCGUI hFlash,wchar_t *pFlashFile);
XC_API void* WINAPI XFlash_GetControl(HXCGUI hFlash);//��ȡ�ؼ��ӿ�
XC_API void  WINAPI XFlash_Destroy(HXCGUI hFlash);