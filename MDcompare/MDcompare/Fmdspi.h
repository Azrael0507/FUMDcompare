#pragma once
#include <windows.h>

class Fmdapi;

class Fmdspi :
	public CUstpFtdcMduserSpi
{
public:
	Fmdspi(Fmdapi *pMdApi, int processnumber);
	virtual ~Fmdspi();

	virtual void OnFrontConnected();
	virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pDepthMarketData);
	virtual void OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

public:
	Fmdapi * m_pMdApi;

	//用于统计本地写入时间，精确到毫秒
	SYSTEMTIME currtime;

	//spi中用于记载进程号的变量
	int spipronum;
};

