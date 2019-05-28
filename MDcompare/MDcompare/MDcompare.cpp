// MDcompare.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Fmdapi.h"
#include "Fmdspi.h"
#include "CMDApi.h"
#include "CMDSpi.h"
#include <iostream>
#include <thread>
#include "OtherFunc.h"

using namespace std;

//线程分支入口，通过不同的apitype标示，调用不同的api初始化
void mdtest(int num, string apitype)
{
	if (apitype.compare("ctp") == 0)
	{
		cout << "" << endl;
		cout << "启动第" << num << "个进程。" << "使用API为：" << apitype << endl;
		CMDapi* pMDApi = new CMDapi(num);
		pMDApi->Init();
	}
	else if (apitype.compare("femas") == 0)
	{
		cout << "" << endl;
		cout << "启动第" << num << "个进程。" << "使用API为：" << apitype << endl;
		Fmdapi* pMDApi = new Fmdapi(num);
		pMDApi->Init();
	}
	else
	{

		cout << "API类型设置有误，请检查，填写类型为：" << apitype << endl;
	}

}

//主程序段
int main()
{

	//获取程序启动目录下的MDconfig.ini文件
	char currpath[500];
	string temp_path = "";
	GetModuleFileNameA(NULL, currpath, 500);
	temp_path = (string)currpath;
	int pos = temp_path.find_last_of('\\', temp_path.length());
	temp_path = temp_path.substr(0, pos + 1);
	temp_path += "MDconfig.ini";
	char* apiCfgFilePath = const_cast<char*>(temp_path.data());

	//声明两个字符串，用于对比config配置想要使用的api类型
	string apitype1;
	string apitype2;

	readConfigFile(apiCfgFilePath, "apitype1", apitype1);
	//cout << "读取配置文件完成, apitype1为：" << apitype1 << " apitype2为：" << apitype2 << endl;
	readConfigFile(apiCfgFilePath, "apitype2", apitype2);
	//cout << "读取配置文件完成, apitype1为：" << apitype1 << " apitype2为：" << apitype2 << endl;


	thread t1(mdtest, 1, apitype1);
	t1.join();
	thread t2(mdtest, 2, apitype2);
	t2.join();

	getchar();

    return 0;
}


