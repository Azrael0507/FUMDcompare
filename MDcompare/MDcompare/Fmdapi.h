#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

using namespace std;
class Fmdspi;

class Fmdapi
{
public:
	Fmdapi(int processnumber);
	virtual ~Fmdapi();

	void Init();

	void MDRequestLogin();
	void MDRequestMarketData();

public:
	CUstpFtdcMduserApi * m_pMDApi;
	Fmdspi *m_pMDSpi;


	//内部存储变量
	char* m_pszFrontAddr;
	char* m_pszUserId;
	char* m_pszPasswd;
	char* m_pszBrokerId;
	char* m_pszProInfo;
	char* m_pszRemark;
	char* m_pszInstrument;
	char* m_pszOutFilePath;

	//获取内部存储变量的中间变量
	string tmp_pszFrontAddr;
	string tmp_pszUserId;
	string tmp_pszPasswd;
	string tmp_pszBrokerId;
	string tmp_pszRemark;
	string tmp_pszProInfo;
	string tmp_pszInstrument;
	string tmp_pszOutFilePath;

	//配置文件路径存储
	const char* MDCfgFilePath;

	//函数返回值存储
	int m_iRequestId;

	//api中用于记载进程号的变量
	int apipronum;
};

