#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

//以下用于处理行情数据中的超长值，将超长值转换为0
#define MAX_ACCEPTABLE_PRICE (1.0E+15)
#define DEAL_TOO_MAX( x ) if( ((x)>MAX_ACCEPTABLE_PRICE) || ((x)<(0-MAX_ACCEPTABLE_PRICE)) ) x = 0

using namespace std;

static string UTF8ToANSI(string s)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;
	const char *pszCode = s.c_str();

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	string r(pszAnsi);
	delete[] pszAnsi;
	return r;
}

//配置文件读取函数定义内容
static bool readConfigFile(const char * cfgfilepath, const string & key, string & value)
{
	fstream cfgFile;
	cfgFile.open(cfgfilepath);//打开文件	
	if (!cfgFile.is_open())
	{
		cout << "can not open cfg file!" << endl;
		return false;
	}
	char tmp[1000];
	while (!cfgFile.eof())//循环读取每一行
	{
		cfgFile.getline(tmp, 1000);//每行读取前1000个字符，1000个应该足够了
		string line(tmp);
		size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value
		if (pos == string::npos) return false;
		string tmpKey = line.substr(0, pos);//取=号之前
		if (key == tmpKey)
		{
			value = line.substr(pos + 1);//取=号之后
			return true;
		}
	}
	return false;
}

static bool readConfigFileUtf8(const char * cfgfilepath, const string & key, string & value)
{
	fstream cfgFile;
	cfgFile.open(cfgfilepath);//打开文件	
	if (!cfgFile.is_open())
	{
		cout << "can not open cfg file!" << endl;
		return false;
	}
	char tmp[1000];
	while (!cfgFile.eof())//循环读取每一行
	{
		cfgFile.getline(tmp, 1000);//每行读取前1000个字符，1000个应该足够了
		string line(tmp);
		string ansiline = UTF8ToANSI(line);
		cout << "line:" << line << "  ansiline:" << ansiline << endl;
		size_t pos = ansiline.find('=');//找到每行的“=”号位置，之前是key之后是value
		if (pos == string::npos) return false;
		string tmpKey = ansiline.substr(0, pos);//取=号之前
		if (key == tmpKey)
		{
			value = ansiline.substr(pos + 1);//取=号之后
			return true;
		}
	}
	return false;
}

//拼接出于执行程序同目录下MDconfig.ini的绝对路径
static char * ConfigPathGet()
{
	char currpath[500];
	string temp_path = "";
	GetModuleFileNameA(NULL, currpath, 500);
	temp_path = (string)currpath;
	int pos = temp_path.find_last_of('\\', temp_path.length());
	temp_path = temp_path.substr(0, pos + 1);
	temp_path += "MDconfig.ini";

	return const_cast<char*>(temp_path.data());
}