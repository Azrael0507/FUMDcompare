#include "stdafx.h"
#include "CMDspi.h"
#include "CMDapi.h"
#include <iostream>
#include "OtherFunc.h"



CMDspi::CMDspi(CMDapi *pMDApi, int processnumber)
{
	m_pMdApi = pMDApi;
	//��api�еĽ��̱�Ŵ��ݸ�spi�࣬���ڴ�ӡ��ʾ
	spipronum = processnumber;
}


CMDspi::~CMDspi()
{
}

//���뺯�����ã������е��������¼����
void CMDspi::OnFrontConnected()
{
	printf("���̺ţ�%d MDfront connected!!\r\n", spipronum);
	m_pMdApi->MDRequestLogin();
}

//��¼�����غ���
void CMDspi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo && pRspInfo->ErrorID == 0)
	{
		printf("%s�û���¼�ɹ�,MD����ǰ�õ�½\r\n", pRspUserLogin->UserID);
		printf("errorID=%d   errorMSG=%s\r\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		m_pMdApi->MDRequestMarketData();
	}

}

//������鴦����
void CMDspi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//��ȡ��������ʱ�ĵ�ǰϵͳʱ�䣬��ȷ������
	GetLocalTime(&currtime);
	//*spiwcount += 1;

	//printf("���̺ţ�%d �յ������!!��Ϊȫ�ֵģ�%d �����ܰ�\r\n", spipronum, *spiwcount);
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


	DEAL_TOO_MAX(pDepthMarketData->BidPrice1);
	DEAL_TOO_MAX(pDepthMarketData->BidPrice2);
	DEAL_TOO_MAX(pDepthMarketData->AskPrice2);
	DEAL_TOO_MAX(pDepthMarketData->AskPrice1);
	DEAL_TOO_MAX(pDepthMarketData->AskPrice3);
	DEAL_TOO_MAX(pDepthMarketData->BidPrice3);
	DEAL_TOO_MAX(pDepthMarketData->AskPrice4);
	DEAL_TOO_MAX(pDepthMarketData->BidPrice4);
	DEAL_TOO_MAX(pDepthMarketData->AskPrice5);
	DEAL_TOO_MAX(pDepthMarketData->BidPrice5);

	//cout << "һ������" << endl;
	//cout << pDepthMarketData->BidPrice1 << "," << pDepthMarketData->AskPrice1 << endl;

	//cout << "��������" << endl;
	//cout << pDepthMarketData->BidPrice2 << "," << pDepthMarketData->AskPrice2 << endl;

	//cout << "��������" << endl;
	//cout << pDepthMarketData->BidPrice3 << "," << pDepthMarketData->AskPrice3 << endl;

	//cout << "�ĵ�����" << endl;
	//cout << pDepthMarketData->BidPrice4 << "," << pDepthMarketData->AskPrice4 << endl;

	//cout << "�嵵����" << endl;
	//cout << pDepthMarketData->BidPrice5 << "," << pDepthMarketData->AskPrice5 << endl;


	//д���ļ������ʽ
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