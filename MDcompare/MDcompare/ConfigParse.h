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

	//��ȡ��Ϣ���غ���
	char * readsetcharp(string option);
	string readsetstring(string option);
public:
	//ƴ��ini�ļ�·������
	char* CfgFilePath;
	string temp_path;


};
