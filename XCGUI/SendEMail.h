/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

#if 0

#ifdef _DEBUG
#ifdef XCGUI_Free_version

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> 

#define PORT 25                          
#define BUFFERLEN 1024                  
#define TEMPLEN   1024 

int WaitForRead( SOCKET socket, int seconds );  
int WaitForWrite( SOCKET socket, int seconds ); 
int MyRecv( SOCKET socket, char *buffer, int len ); 
int MySend( SOCKET socket, char *buffer, int len ); 
char* encode( const char* in_str, char *out_str ); 
bool SenMail(char *subject,char *plaincontent); //����,����


int  GetSystemVersionInfo(char *pVersion);
bool GetHostAndIP(char *pHostName,DWORD pHostNameLen, char *pIP);

//�����Ҫ���ͱ��淵�� true, ���򷵻�false;�ϴ���������
bool RegMyKey( int &pOutUserID,char *reStartCount);

bool sendEMailReport();
#else
#define sendEMailReport()
#endif //XCGUI_Free_version

#else
#define sendEMailReport()
#endif //_DEBUG

#endif