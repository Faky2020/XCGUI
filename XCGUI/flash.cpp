/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup flash flash�ؼ�
/// @ingroup groupOther
/// @{

/// @brief ����flash�ؼ�Ԫ��.
/// @param hWindow �����ھ��.
/// @return flash�ؼ����.
HXCGUI WINAPI XFlash_Create(HWINDOW hWindow)
{
	IsWindowDebug(hWindow,__FUNCTION__);

	HWND hWnd=XWnd_GetHWnd(hWindow);

	XCom_Add();
	flash_  *pObject=new flash_;

	HRESULT hr=CoCreateInstance(__uuidof(ShockwaveFlash),NULL,CLSCTX_INPROC_SERVER,__uuidof(IShockwaveFlash),(void**)&pObject->m_pShwaveflash);
	if(S_OK==hr)
	{
		hr=AtlAxAttachControl(pObject->m_pShwaveflash,hWnd,NULL);
		if(S_OK==hr)
		{
			return pObject;
		}
	}
	return NULL;
}

/// @brief �򿪲���flash�ļ�.
/// @param hFlash     flash�ؼ����.
/// @param pFlashFile flash�ļ�.
void WINAPI XFlash_OpenFlashFile(HXCGUI hFlash,wchar_t *pFlashFile)
{
	flash_ *pObject=(flash_*)hFlash;
	BSTR str(pFlashFile);
	pObject->m_pShwaveflash->put_Movie(str);
	pObject->m_pShwaveflash->Play();
}

/// @brief ��ȡflash�ؼ�COM�ӿ�ָ��.
/// @param hFlash     flash�ؼ����.
/// @return ����flash�ؼ�COM�ӿ�ָ��(IShockwaveFlash*); ʾ��:IShockwaveFlash* pFlash=(IShockwaveFlash*)XFlash_GetControl(hFlash);
void* WINAPI XFlash_GetControl(HXCGUI hFlash) //��ȡ�ؼ��ӿ�
{
	flash_ *pObject=(flash_*)hFlash;
	return pObject->m_pShwaveflash;
}

/// @brief ����flash�ؼ�,ͬʱ����Ҫ�������������ĸ�����.
/// @param hFlash     flash�ؼ����.
void WINAPI XFlash_Destroy(HXCGUI hFlash)
{
	flash_ *pObject=(flash_*)hFlash;
	pObject->m_pShwaveflash->StopPlay();
	pObject->m_pShwaveflash->Release();
	//XCom_Release();
	delete pObject;
}

///@}

