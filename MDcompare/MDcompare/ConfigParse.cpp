#include "stdafx.h"
#include "ConfigParse.h"

//构造函数，用于通过ini的文件名，来读取执行程序同目录下内容
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

//实际通过key值调取等号后的value值
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

ConfigParse::~ConfigParse()
{
}

//调取返回函数，返回char*类型，但是由于指针问题，不太好用
char * ConfigParse::readsetcharp(string option)
{
	string tempvalue;
	readConfigFile(CfgFilePath, option, tempvalue);

	return const_cast<char*>(tempvalue.data());


}

//调取返回函数，返回string类型，实际可使用
string ConfigParse::readsetstring(string option)
{
	string tempvalue;
	readConfigFile(CfgFilePath, option, tempvalue);

	//cout << "获取的key为：" << option << "，其value值为：" << tempvalue << endl;

	return tempvalue;


}
