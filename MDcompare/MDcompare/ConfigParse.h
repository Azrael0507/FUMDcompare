#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

using namespace std;

class ConfigParse
{
public:
	ConfigParse(string CfgName);
	~ConfigParse();

	//读取信息返回函数
	char * readsetcharp(string option);
	string readsetstring(string option);
public:
	//拼接ini文件路径变量
	char* CfgFilePath;
	string temp_path;


};
