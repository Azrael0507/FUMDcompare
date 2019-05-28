#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

using namespace std;
class CMDspi;

class CMDapi
{
public:
	CMDapi(int processnumber);
	virtual ~CMDapi();

	//��ʼ������
	void Init();

	//�����¼�����Լ��������������
	void MDRequestLogin();
	void MDRequestMarketData();

public:
	CThostFtdcMdApi * m_pMDApi;
	CMDspi *m_pMDSpi;

	//�ڲ��洢����
	char* m_pszFrontAddr;
	char* m_pszUserId;
	char* m_pszPasswd;
	char* m_pszBrokerId;
	char* m_pszProInfo;
	char* m_pszRemark;
	char* m_pszInstrument;
	char* m_pszOutFilePath;

	//��ȡ�ڲ��洢�������м����
	string tmp_pszFrontAddr;
	string tmp_pszUserId;
	string tmp_pszPasswd;
	string tmp_pszBrokerId;
	string tmp_pszRemark;
	string tmp_pszProInfo;
	string tmp_pszInstrument;
	string tmp_pszOutFilePath;

	//�����ļ�·���洢
	const char* MDCfgFilePath;

	//��������ֵ�洢
	int m_iRequestId;

	//api�����ڼ��ؽ��̺ŵı���
	int apipronum;

};

