#include "stdafx.h"
#include "ConfigParse.h"

//���캯��������ͨ��ini���ļ���������ȡִ�г���ͬĿ¼������
ConfigParse::ConfigParse(string CfgName)
{
	char currpath[500];
	temp_path = "";
	GetModuleFileNameA(NULL, currpath, 500);
	temp_path = (string)currpath;
	int pos = temp_path.find_last_of('\\', temp_path.length());
	temp_path = temp_path.substr(0, pos + 1);
	temp_path += CfgName;
	CfgFilePath = const_cast<char*>(temp_path.data());

	//cout << "CfgFilePath:" << CfgFilePath <<  endl;



}

//ʵ��ͨ��keyֵ��ȡ�Ⱥź��valueֵ
static bool readConfigFile(const char * cfgfilepath, const string & key, string & value)
{
	fstream cfgFile;
	cfgFile.open(cfgfilepath);//���ļ�	
	if (!cfgFile.is_open())
	{
		cout << "can not open cfg file!" << endl;
		return false;
	}
	char tmp[1000];
	while (!cfgFile.eof())//ѭ����ȡÿһ��
	{
		cfgFile.getline(tmp, 1000);//ÿ�ж�ȡǰ1000���ַ���1000��Ӧ���㹻��
		string line(tmp);
		size_t pos = line.find('=');//�ҵ�ÿ�еġ�=����λ�ã�֮ǰ��key֮����value
		if (pos == string::npos) return false;
		string tmpKey = line.substr(0, pos);//ȡ=��֮ǰ
		if (key == tmpKey)
		{
			value = line.substr(pos + 1);//ȡ=��֮��
			return true;
		}
	}
	return false;
}

ConfigParse::~ConfigParse()
{
}

//��ȡ���غ���������char*���ͣ���������ָ�����⣬��̫����
char * ConfigParse::readsetcharp(string option)
{
	string tempvalue;
	readConfigFile(CfgFilePath, option, tempvalue);

	return const_cast<char*>(tempvalue.data());


}

//��ȡ���غ���������string���ͣ�ʵ�ʿ�ʹ��
string ConfigParse::readsetstring(string option)
{
	string tempvalue;
	readConfigFile(CfgFilePath, option, tempvalue);

	//cout << "��ȡ��keyΪ��" << option << "����valueֵΪ��" << tempvalue << endl;

	return tempvalue;


}
