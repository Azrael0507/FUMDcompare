#include "stdafx.h"
#include "CMDapi.h"
#include "CMDspi.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "OtherFunc.h"

using namespace std;

CMDapi::CMDapi(int processnumber)
{
	//以下是默认配置项目内容，防止产生空赋值情况
	m_pszFrontAddr = const_cast<char*>("tcp://192.168.100.152:49214");
	m_pszBrokerId = const_cast<char*>("0001");
	m_pszUserId = const_cast<char*>("19920324");
	m_pszPasswd = const_cast<char*>("123456");
	m_pszProInfo = const_cast<char*>("mdtest");
	m_pszRemark = const_cast<char*>("行情测试备注");

	//将进程序号获取到实例中，进程序号用于获取不同的config配置，以及显示输出不同的打印信息
	apipronum = processnumber;

	//获取程序启动目录下的MDconfig.ini文件
	char currpath[500];
	string temp_path = "";
	GetModuleFileNameA(NULL, currpath, 500);
	temp_path = (string)currpath;
	int pos = temp_path.find_last_of('\\', temp_path.length());
	temp_path = temp_path.substr(0, pos + 1);
	temp_path += "MDconfig.ini";
	MDCfgFilePath = const_cast<char*>(temp_path.data());

	//判断进程号，从不同的配置项读取配置
	if (processnumber == 1)
	{
		//从配置文件读取交易前置地址
		readConfigFile(MDCfgFilePath, "frontaddr1", tmp_pszFrontAddr);
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//从配置文件读取brokerid经纪公司编号
		readConfigFile(MDCfgFilePath, "brokerid1", tmp_pszBrokerId);
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//从配置文件读取登录账户
		readConfigFile(MDCfgFilePath, "userid1", tmp_pszUserId);
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//从配置文件读取登录密码
		readConfigFile(MDCfgFilePath, "password1", tmp_pszPasswd);
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//从配置文件读取客户端标识,这一客户端标示由于有11个字节的限制，并不做认证之用，因此可以自由填写，符合长度即可
		readConfigFile(MDCfgFilePath, "proinfo1", tmp_pszProInfo);
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//从配置文件读取登录备注信息
		readConfigFile(MDCfgFilePath, "remark1", tmp_pszRemark);
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//从配置文件读取选择的合约信息
		readConfigFile(MDCfgFilePath, "instrument1", tmp_pszInstrument);
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//从配置文件读取输出文件信息
		readConfigFile(MDCfgFilePath, "filepath1", tmp_pszOutFilePath);
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}
	else if (processnumber == 2)
	{
		//从配置文件读取交易前置地址
		readConfigFile(MDCfgFilePath, "frontaddr2", tmp_pszFrontAddr);
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//从配置文件读取brokerid经纪公司编号
		readConfigFile(MDCfgFilePath, "brokerid2", tmp_pszBrokerId);
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//从配置文件读取登录账户
		readConfigFile(MDCfgFilePath, "userid2", tmp_pszUserId);
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//从配置文件读取登录密码
		readConfigFile(MDCfgFilePath, "password2", tmp_pszPasswd);
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//从配置文件读取客户端标识,这一客户端标示由于有11个字节的限制，并不做认证之用，因此可以自由填写，符合长度即可
		readConfigFile(MDCfgFilePath, "proinfo2", tmp_pszProInfo);
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//从配置文件读取登录备注信息
		readConfigFile(MDCfgFilePath, "remark2", tmp_pszRemark);
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//从配置文件读取选择的合约信息
		readConfigFile(MDCfgFilePath, "instrument2", tmp_pszInstrument);
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//从配置文件读取输出文件信息
		readConfigFile(MDCfgFilePath, "filepath2", tmp_pszOutFilePath);
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}




	//返回值变量设置初始值
	m_iRequestId = 0;

}


CMDapi::~CMDapi()
{
}

//初始化行情api内容
void CMDapi::Init()
{
	m_pMDApi = CThostFtdcMdApi::CreateFtdcMdApi("");
	m_pMDSpi = new CMDspi(this, apipronum);

	m_pMDApi->RegisterSpi(m_pMDSpi);
	m_pMDApi->RegisterFront(m_pszFrontAddr);

	m_pMDApi->Init();
}

//行情前置登录函数
void CMDapi::MDRequestLogin()
{
	CThostFtdcReqUserLoginField reqMDlogin;

	strcpy_s(reqMDlogin.BrokerID, m_pszBrokerId);
	strcpy_s(reqMDlogin.UserID, m_pszUserId);
	strcpy_s(reqMDlogin.Password, m_pszPasswd);
	strcpy_s(reqMDlogin.UserProductInfo, m_pszProInfo);
	strcpy_s(reqMDlogin.LoginRemark, m_pszRemark);

	int iRet = m_pMDApi->ReqUserLogin(&reqMDlogin, m_iRequestId++);
}

//请求深度行情函数
void CMDapi::MDRequestMarketData()
{
	//将查询的合约代码传递给函数，先只支持查询一个
	char **ppInstrumentID = new char*[50];
	ppInstrumentID[0] = m_pszInstrument;

	int iRetMD = m_pMDApi->SubscribeMarketData(ppInstrumentID, 1);
}
