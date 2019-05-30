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

//���캯������
Fmdapi::Fmdapi(int processnumber)
{
	//Ĭ��������Ŀ�����ڲ���
	m_pszFrontAddr = const_cast<char*>("tcp://192.168.100.174:8005");
	m_pszBrokerId = const_cast<char*>("0001");
	m_pszUserId = const_cast<char*>("6257705");
	m_pszPasswd = const_cast<char*>("123456");

	//��������Ż�ȡ��ʵ���У�����������ڻ�ȡ��ͬ��config���ã��Լ���ʾ�����ͬ�Ĵ�ӡ��Ϣ
	apipronum = processnumber;

	//����ini�ļ���ȡʵ��
	ConfigParse* configset = new ConfigParse("MDconfig.ini");

	//�жϽ��̺ţ��Ӳ�ͬ���������ȡ����
	if (apipronum == 1)
	{
		//�������ļ���ȡ����ǰ�õ�ַ
		//readConfigFile(MDCfgFilePath, "frontaddr1", tmp_pszFrontAddr);
		tmp_pszFrontAddr = configset->readsetstring("frontaddr1");
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//�������ļ���ȡbrokerid���͹�˾���
		//readConfigFile(MDCfgFilePath, "brokerid1", tmp_pszBrokerId);
		tmp_pszBrokerId = configset->readsetstring("brokerid1");
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//�������ļ���ȡ��¼�˻�
		//readConfigFile(MDCfgFilePath, "userid1", tmp_pszUserId);
		tmp_pszUserId = configset->readsetstring("userid1");
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//�������ļ���ȡ��¼����
		//readConfigFile(MDCfgFilePath, "password1", tmp_pszPasswd);
		tmp_pszPasswd = configset->readsetstring("password1");
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//�������ļ���ȡ�ͻ��˱�ʶ,��һ�ͻ��˱�ʾ������11���ֽڵ����ƣ���������֤֮�ã���˿���������д�����ϳ��ȼ���
		//readConfigFile(MDCfgFilePath, "proinfo1", tmp_pszProInfo);
		tmp_pszProInfo = configset->readsetstring("proinfo1");
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//�������ļ���ȡ��¼��ע��Ϣ
		//readConfigFile(MDCfgFilePath, "remark1", tmp_pszRemark);
		tmp_pszRemark = configset->readsetstring("remark1");
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//�������ļ���ȡѡ��ĺ�Լ��Ϣ
		//readConfigFile(MDCfgFilePath, "instrument1", tmp_pszInstrument);
		tmp_pszInstrument = configset->readsetstring("instrument1");
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//�������ļ���ȡ����ļ���Ϣ
		//readConfigFile(MDCfgFilePath, "filepath1", tmp_pszOutFilePath);
		tmp_pszOutFilePath = configset->readsetstring("filepath1");
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}
	else if (apipronum == 2)
	{
		//�������ļ���ȡ����ǰ�õ�ַ
		//readConfigFile(MDCfgFilePath, "frontaddr1", tmp_pszFrontAddr);
		tmp_pszFrontAddr = configset->readsetstring("frontaddr2");
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//�������ļ���ȡbrokerid���͹�˾���
		//readConfigFile(MDCfgFilePath, "brokerid1", tmp_pszBrokerId);
		tmp_pszBrokerId = configset->readsetstring("brokerid2");
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//�������ļ���ȡ��¼�˻�
		//readConfigFile(MDCfgFilePath, "userid1", tmp_pszUserId);
		tmp_pszUserId = configset->readsetstring("userid2");
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//�������ļ���ȡ��¼����
		//readConfigFile(MDCfgFilePath, "password1", tmp_pszPasswd);
		tmp_pszPasswd = configset->readsetstring("password2");
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//�������ļ���ȡ�ͻ��˱�ʶ,��һ�ͻ��˱�ʾ������11���ֽڵ����ƣ���������֤֮�ã���˿���������д�����ϳ��ȼ���
		//readConfigFile(MDCfgFilePath, "proinfo1", tmp_pszProInfo);
		tmp_pszProInfo = configset->readsetstring("proinfo2");
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//�������ļ���ȡ��¼��ע��Ϣ
		//readConfigFile(MDCfgFilePath, "remark1", tmp_pszRemark);
		tmp_pszRemark = configset->readsetstring("remark2");
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//�������ļ���ȡѡ��ĺ�Լ��Ϣ
		//readConfigFile(MDCfgFilePath, "instrument1", tmp_pszInstrument);
		tmp_pszInstrument = configset->readsetstring("instrument2");
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//�������ļ���ȡ����ļ���Ϣ
		//readConfigFile(MDCfgFilePath, "filepath1", tmp_pszOutFilePath);
		tmp_pszOutFilePath = configset->readsetstring("filepath2");
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}


	//����ֵ�������ó�ʼֵ
	m_iRequestId = 0;
}

//��ʼ���������壬���а�������ҽ�������Ĭ���������ⶨ��

void Fmdapi::Init()
{
	m_pMDApi = CUstpFtdcMduserApi::CreateFtdcMduserApi("");
	m_pMDSpi = new Fmdspi(this, apipronum);

	m_pMDApi->RegisterSpi(m_pMDSpi);


	//��������ţ��Ƕ�����������ͣ��ɽ�����ָ����
	//��������������������������ŷֱ�Ϊ�� �н��� 100 ������ 1001 ������ 3101 ֣���� 4101 ��Դ���� 5101
	//���鶩�ĺ��Ƿ���ͻ���������ʱ���ֵ��Ĭ�Ϻ����������һ�¡�
	//�������ڻ���˾�������ã�һ���������Ĭ��Ϊ�� �н��� 100 ������ 21001 ������ 3101 ֣���� 4101 ��Դ���� 5101

	//�н���Ĭ����������
	m_pMDApi->SubscribeMarketDataTopic(100, USTP_TERT_QUICK);
	//������Ĭ����������
	m_pMDApi->SubscribeMarketDataTopic(21001, USTP_TERT_QUICK);
	//������Ĭ����������
	m_pMDApi->SubscribeMarketDataTopic(3101, USTP_TERT_QUICK);
	//֣����Ĭ����������
	m_pMDApi->SubscribeMarketDataTopic(4101, USTP_TERT_QUICK);
	//��Դ����Ĭ����������
	m_pMDApi->SubscribeMarketDataTopic(5101, USTP_TERT_QUICK);

	m_pMDApi->RegisterFront(m_pszFrontAddr);



	m_pMDApi->Init();
}


Fmdapi::~Fmdapi()
{

}

//�����¼��������
void Fmdapi::MDRequestLogin()
{
	CUstpFtdcReqUserLoginField reqMDlogin = {};

	strcpy_s(reqMDlogin.BrokerID, m_pszBrokerId);
	strcpy_s(reqMDlogin.UserID, m_pszUserId);
	strcpy_s(reqMDlogin.Password, m_pszPasswd);

	int iRet = m_pMDApi->ReqUserLogin(&reqMDlogin, m_iRequestId++);
}

//�����Լ�����ѯ����
void Fmdapi::MDRequestMarketData()
{
	cout << "������Լ����" << endl;
	char **ppInstrumentID = new char*[50];
	ppInstrumentID[0] = m_pszInstrument;

	int iRetMD = m_pMDApi->SubMarketData(ppInstrumentID, 1);
}


