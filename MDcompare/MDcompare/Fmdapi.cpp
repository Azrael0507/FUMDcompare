#include "stdafx.h"
#include "Fmdapi.h"
#include "Fmdspi.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "ConfigParse.h"

using namespace std;

//构造函数定义
Fmdapi::Fmdapi(int processnumber)
{
	//默认配置项目，用于测试
	m_pszFrontAddr = const_cast<char*>("tcp://192.168.100.174:8005");
	m_pszBrokerId = const_cast<char*>("0001");
	m_pszUserId = const_cast<char*>("6257705");
	m_pszPasswd = const_cast<char*>("123456");

	//将进程序号获取到实例中，进程序号用于获取不同的config配置，以及显示输出不同的打印信息
	apipronum = processnumber;

	//创建ini文件读取实例
	ConfigParse* configset = new ConfigParse("MDconfig.ini");

	//判断进程号，从不同的配置项读取配置
	if (apipronum == 1)
	{
		//从配置文件读取交易前置地址
		//readConfigFile(MDCfgFilePath, "frontaddr1", tmp_pszFrontAddr);
		tmp_pszFrontAddr = configset->readsetstring("frontaddr1");
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//从配置文件读取brokerid经纪公司编号
		//readConfigFile(MDCfgFilePath, "brokerid1", tmp_pszBrokerId);
		tmp_pszBrokerId = configset->readsetstring("brokerid1");
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//从配置文件读取登录账户
		//readConfigFile(MDCfgFilePath, "userid1", tmp_pszUserId);
		tmp_pszUserId = configset->readsetstring("userid1");
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//从配置文件读取登录密码
		//readConfigFile(MDCfgFilePath, "password1", tmp_pszPasswd);
		tmp_pszPasswd = configset->readsetstring("password1");
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//从配置文件读取客户端标识,这一客户端标示由于有11个字节的限制，并不做认证之用，因此可以自由填写，符合长度即可
		//readConfigFile(MDCfgFilePath, "proinfo1", tmp_pszProInfo);
		tmp_pszProInfo = configset->readsetstring("proinfo1");
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//从配置文件读取登录备注信息
		//readConfigFile(MDCfgFilePath, "remark1", tmp_pszRemark);
		tmp_pszRemark = configset->readsetstring("remark1");
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//从配置文件读取选择的合约信息
		//readConfigFile(MDCfgFilePath, "instrument1", tmp_pszInstrument);
		tmp_pszInstrument = configset->readsetstring("instrument1");
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//从配置文件读取输出文件信息
		//readConfigFile(MDCfgFilePath, "filepath1", tmp_pszOutFilePath);
		tmp_pszOutFilePath = configset->readsetstring("filepath1");
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}
	else if (apipronum == 2)
	{
		//从配置文件读取交易前置地址
		//readConfigFile(MDCfgFilePath, "frontaddr1", tmp_pszFrontAddr);
		tmp_pszFrontAddr = configset->readsetstring("frontaddr2");
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//从配置文件读取brokerid经纪公司编号
		//readConfigFile(MDCfgFilePath, "brokerid1", tmp_pszBrokerId);
		tmp_pszBrokerId = configset->readsetstring("brokerid2");
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//从配置文件读取登录账户
		//readConfigFile(MDCfgFilePath, "userid1", tmp_pszUserId);
		tmp_pszUserId = configset->readsetstring("userid2");
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//从配置文件读取登录密码
		//readConfigFile(MDCfgFilePath, "password1", tmp_pszPasswd);
		tmp_pszPasswd = configset->readsetstring("password2");
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//从配置文件读取客户端标识,这一客户端标示由于有11个字节的限制，并不做认证之用，因此可以自由填写，符合长度即可
		//readConfigFile(MDCfgFilePath, "proinfo1", tmp_pszProInfo);
		tmp_pszProInfo = configset->readsetstring("proinfo2");
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//从配置文件读取登录备注信息
		//readConfigFile(MDCfgFilePath, "remark1", tmp_pszRemark);
		tmp_pszRemark = configset->readsetstring("remark2");
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//从配置文件读取选择的合约信息
		//readConfigFile(MDCfgFilePath, "instrument1", tmp_pszInstrument);
		tmp_pszInstrument = configset->readsetstring("instrument2");
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//从配置文件读取输出文件信息
		//readConfigFile(MDCfgFilePath, "filepath1", tmp_pszOutFilePath);
		tmp_pszOutFilePath = configset->readsetstring("filepath2");
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}


	//返回值变量设置初始值
	m_iRequestId = 0;
}

//初始化函数定义，其中包含了五家交易所的默认行情主题定义

void Fmdapi::Init()
{
	m_pMDApi = CUstpFtdcMduserApi::CreateFtdcMduserApi("");
	m_pMDSpi = new Fmdspi(this, apipronum);

	m_pMDApi->RegisterSpi(m_pMDSpi);


	//行情主题号，是订阅行情的类型，由交易所指定。
	//各交易所的生产环境行情主题号分别为： 中金所 100 上期所 1001 大商所 3101 郑商所 4101 能源中心 5101
	//行情订阅号是飞马客户订阅行情时填的值，默认和行情主题号一致。
	//具体由期货公司自行配置，一般各交易所默认为： 中金所 100 上期所 21001 大商所 3101 郑商所 4101 能源中心 5101

	//中金所默认行情主题
	m_pMDApi->SubscribeMarketDataTopic(100, USTP_TERT_QUICK);
	//上期所默认行情主题
	m_pMDApi->SubscribeMarketDataTopic(21001, USTP_TERT_QUICK);
	//大商所默认行情主题
	m_pMDApi->SubscribeMarketDataTopic(3101, USTP_TERT_QUICK);
	//郑商所默认行情主题
	m_pMDApi->SubscribeMarketDataTopic(4101, USTP_TERT_QUICK);
	//能源中心默认行情主题
	m_pMDApi->SubscribeMarketDataTopic(5101, USTP_TERT_QUICK);

	m_pMDApi->RegisterFront(m_pszFrontAddr);



	m_pMDApi->Init();
}


Fmdapi::~Fmdapi()
{

}

//行情登录函数定义
void Fmdapi::MDRequestLogin()
{
	CUstpFtdcReqUserLoginField reqMDlogin = {};

	strcpy_s(reqMDlogin.BrokerID, m_pszBrokerId);
	strcpy_s(reqMDlogin.UserID, m_pszUserId);
	strcpy_s(reqMDlogin.Password, m_pszPasswd);

	int iRet = m_pMDApi->ReqUserLogin(&reqMDlogin, m_iRequestId++);
}

//发起合约行情查询请求
void Fmdapi::MDRequestMarketData()
{
	cout << "发出合约请求！" << endl;
	char **ppInstrumentID = new char*[50];
	ppInstrumentID[0] = m_pszInstrument;

	int iRetMD = m_pMDApi->SubMarketData(ppInstrumentID, 1);
}


