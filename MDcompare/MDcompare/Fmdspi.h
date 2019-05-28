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

	//����ͳ�Ʊ���д��ʱ�䣬��ȷ������
	SYSTEMTIME currtime;

	//spi�����ڼ��ؽ��̺ŵı���
	int spipronum;
};

