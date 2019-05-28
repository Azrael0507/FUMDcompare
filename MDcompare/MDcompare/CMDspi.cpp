#include "stdafx.h"
#include "CMDspi.h"
#include "CMDapi.h"
#include <iostream>
#include "OtherFunc.h"



CMDspi::CMDspi(CMDapi *pMDApi, int processnumber)
{
	m_pMdApi = pMDApi;
	//将api中的进程编号传递给spi类，用于打印显示
	spipronum = processnumber;
}


CMDspi::~CMDspi()
{
}

//接入函数调用，在其中调用行情登录函数
void CMDspi::OnFrontConnected()
{
	printf("进程号：%d MDfront connected!!\r\n", spipronum);
	m_pMdApi->MDRequestLogin();
}

//登录处理返回函数
void CMDspi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo && pRspInfo->ErrorID == 0)
	{
		printf("%s用户登录成功,MD行情前置登陆\r\n", pRspUserLogin->UserID);
		printf("errorID=%d   errorMSG=%s\r\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		m_pMdApi->MDRequestMarketData();
	}

}

//深度行情处理函数
void CMDspi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//获取函数返回时的当前系统时间，精确到毫秒
	GetLocalTime(&currtime);
	//*spiwcount += 1;

	//printf("进程号：%d 收到行情包!!此为全局的：%d 个接受包\r\n", spipronum, *spiwcount);
	printf("进程号：%d 收到行情包!!\r\n", spipronum);


	//深度行情数据过滤处理，将超大值转为0，其中譬如结算价列，在盘中为未初始化的超大值，其实应该为空
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

	//以下注释内容为屏幕输出项，可将以下内容放开注释，进行屏幕打印

	//cout << "=====获得深度行情=====" << endl;
	//cout << "交易日,合约代码,最新价,今开盘,最高价,最低价,数量,成交金额,持仓量,今收盘,本次结算价,更新时间,更新毫秒" << endl;
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

	//cout << "一档行情" << endl;
	//cout << pDepthMarketData->BidPrice1 << "," << pDepthMarketData->AskPrice1 << endl;

	//cout << "二档行情" << endl;
	//cout << pDepthMarketData->BidPrice2 << "," << pDepthMarketData->AskPrice2 << endl;

	//cout << "三档行情" << endl;
	//cout << pDepthMarketData->BidPrice3 << "," << pDepthMarketData->AskPrice3 << endl;

	//cout << "四档行情" << endl;
	//cout << pDepthMarketData->BidPrice4 << "," << pDepthMarketData->AskPrice4 << endl;

	//cout << "五档行情" << endl;
	//cout << pDepthMarketData->BidPrice5 << "," << pDepthMarketData->AskPrice5 << endl;


	//写入文件处理格式
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
		<< "行情包时间戳："
		<< pDepthMarketData->UpdateTime << ":"
		<< pDepthMarketData->UpdateMillisec << "\t\t本地时间戳："
		<< currtime.wHour << ":" << currtime.wMinute << ":" << currtime.wSecond << ":" << currtime.wMilliseconds << endl;
}