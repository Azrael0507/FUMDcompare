#include "stdafx.h"
#include "Fmdspi.h"
#include "Fmdapi.h"
#include <iostream>

#include "OtherFunc.h"


Fmdspi::Fmdspi(Fmdapi *pMDApi, int processnumber)
{
	m_pMdApi = pMDApi;
	//��api�еĽ��̱�Ŵ��ݸ�spi�࣬���ڴ�ӡ��ʾ
	spipronum = processnumber;
}


Fmdspi::~Fmdspi()
{

}

//���뺯�����ã������е��������¼����
void Fmdspi::OnFrontConnected()
{
	printf("���̺ţ�%d MDfront connected!!\r\n", spipronum);
	m_pMdApi->MDRequestLogin();
}

void Fmdspi::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo && pRspInfo->ErrorID == 0)
	{
		printf("%s�û���¼�ɹ�,MD����ǰ�õ�½\r\n", pRspUserLogin->UserID);
		printf("errorID=%d   errorMSG=%s\r\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		m_pMdApi->MDRequestMarketData();
	}
	else
	{
		printf("%s�û���¼ʧ��\r\n", pRspUserLogin->UserID);
		printf("errorID=%d   errorMSG=%s\r\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	}
}

void Fmdspi::OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pDepthMarketData)
{
	//��ȡ��������ʱ�ĵ�ǰϵͳʱ�䣬��ȷ������
	GetLocalTime(&currtime);

	printf("���̺ţ�%d �յ������!!\r\n", spipronum);

	//����������ݹ��˴���������ֵתΪ0������Ʃ�������У�������Ϊδ��ʼ���ĳ���ֵ����ʵӦ��Ϊ��
	DEAL_TOO_MAX(pDepthMarketData->PreOpenInterest);
	DEAL_TOO_MAX(pDepthMarketData->PreClosePrice);
	DEAL_TOO_MAX(pDepthMarketData->PreSettlementPrice);
	DEAL_TOO_MAX(pDepthMarketData->ClosePrice);
	DEAL_TOO_MAX(pDepthMarketData->SettlementPrice);
	DEAL_TOO_MAX(pDepthMarketData->OpenInterest);
	DEAL_TOO_MAX(pDepthMarketData->LastPrice);
	DEAL_TOO_MAX(pDepthMarketData->UpperLimitPrice);
	DEAL_TOO_MAX(pDepthMarketData->LowerLimitPrice);
	DEAL_TOO_MAX(pDepthMarketData->HighestPrice);
	DEAL_TOO_MAX(pDepthMarketData->LowestPrice);
	DEAL_TOO_MAX(pDepthMarketData->OpenPrice);
	DEAL_TOO_MAX(pDepthMarketData->LowestPrice);
	//DEAL_TOO_MAX(pDepthMarketData->Turnover);

	//����ע������Ϊ��Ļ�����ɽ��������ݷſ�ע�ͣ�������Ļ��ӡ

	//cout << "=====����������=====" << endl;
	//cout << "������,��Լ����,���¼�,����,��߼�,��ͼ�,����,�ɽ����,�ֲ���,������,���ν����,����ʱ��,���º���" << endl;
	//cout << pDepthMarketData->TradingDay << ","
	//	<< pDepthMarketData->InstrumentID << ","
	//	<< pDepthMarketData->LastPrice << ","
	//	<< pDepthMarketData->OpenPrice << ","
	//	<< pDepthMarketData->HighestPrice << ","
	//	<< pDepthMarketData->LowestPrice << ","
	//	<< pDepthMarketData->Volume << ","
	//	<< pDepthMarketData->Turnover << ","
	//	<< pDepthMarketData->OpenInterest << ","
	//	<< pDepthMarketData->ClosePrice << ","
	//	<< pDepthMarketData->SettlementPrice << ","
	//	<< pDepthMarketData->UpdateTime << ","
	//	<< pDepthMarketData->UpdateMillisec << endl;

	//д���ļ������ʽ���������ʱ������뱾��ʱ���д���ļ���ͨ����ͬһ�����ʱ�������Ӧ�ı���ʱ������жԱȣ����Ƚ��������鵽�����
	char filePath[100] = { '\0' };
	sprintf_s(filePath, m_pMdApi->m_pszOutFilePath);
	ofstream outFile;
	outFile.open(filePath, ios::app);
	outFile
		//<< pDepthMarketData->TradingDay << ","
		//<< pDepthMarketData->InstrumentID << ","
		//<< pDepthMarketData->LastPrice << ","
		//<< pDepthMarketData->OpenPrice << ","
		//<< pDepthMarketData->HighestPrice << ","
		//<< pDepthMarketData->LowestPrice << ","
		//<< pDepthMarketData->Volume << ","
		//<< pDepthMarketData->Turnover << ","
		//<< pDepthMarketData->OpenInterest << ","
		//<< pDepthMarketData->ClosePrice << ","
		//<< pDepthMarketData->SettlementPrice << endl
		<< "�����ʱ�����"
		<< pDepthMarketData->UpdateTime << ":"
		<< pDepthMarketData->UpdateMillisec << "\t\t����ʱ�����"
		<< currtime.wHour << ":" << currtime.wMinute << ":" << currtime.wSecond << ":" << currtime.wMilliseconds << endl;

}

void Fmdspi::OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "��Լ����Ϊ��" << pSpecificInstrument->InstrumentID << endl;
}