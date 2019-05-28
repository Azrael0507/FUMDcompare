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
	//����ͳ�Ʊ���д��ʱ�䣬��ȷ������
	SYSTEMTIME currtime;

	//spi�����ڼ��ؽ��̺ŵı���
	int spipronum;

	//spi�����ڼ���ȫ�ּ�����
	int* spiwcount;
};

