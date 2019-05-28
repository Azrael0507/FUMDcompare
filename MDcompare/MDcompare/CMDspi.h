#pragma once
#include <windows.h>

class CMDapi;
class CMDspi :
	public CThostFtdcMdSpi
{
public:
	CMDspi(CMDapi *pMdApi, int processnumber);
	virtual ~CMDspi();

	virtual void OnFrontConnected();
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

public:
	CMDapi * m_pMdApi;
	//用于统计本地写入时间，精确到毫秒
	SYSTEMTIME currtime;

	//spi中用于记载进程号的变量
	int spipronum;

	//spi中用于记载全局计数器
	int* spiwcount;
};

