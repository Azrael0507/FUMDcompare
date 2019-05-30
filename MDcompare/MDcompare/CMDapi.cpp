#include "stdafx.h"
#include "CMDapi.h"
#include "CMDspi.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "ConfigParse.h"

using namespace std;

CMDapi::CMDapi(int processnumber)
{
	//������Ĭ��������Ŀ���ݣ���ֹ�����ո�ֵ���
	m_pszFrontAddr = const_cast<char*>("tcp://192.168.100.152:49214");
	m_pszBrokerId = const_cast<char*>("0001");
	m_pszUserId = const_cast<char*>("19920324");
	m_pszPasswd = const_cast<char*>("123456");
	m_pszProInfo = const_cast<char*>("mdtest");
	m_pszRemark = const_cast<char*>("������Ա�ע");

	//��������Ż�ȡ��ʵ���У�����������ڻ�ȡ��ͬ��config���ã��Լ���ʾ�����ͬ�Ĵ�ӡ��Ϣ
	apipronum = processnumber;

	//����ini�ļ���ȡʵ��
	ConfigParse* configset = new ConfigParse("MDconfig.ini");

	//�жϽ��̺ţ��Ӳ�ͬ���������ȡ����
	if (processnumber == 1)
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
	else if (processnumber == 2)
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


CMDapi::~CMDapi()
{
}

//��ʼ������api����
void CMDapi::Init()
{
	m_pMDApi = CThostFtdcMdApi::CreateFtdcMdApi("");
	m_pMDSpi = new CMDspi(this, apipronum);

	m_pMDApi->RegisterSpi(m_pMDSpi);
	m_pMDApi->RegisterFront(m_pszFrontAddr);

	m_pMDApi->Init();
}

//����ǰ�õ�¼����
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

//����������麯��
void CMDapi::MDRequestMarketData()
{
	//����ѯ�ĺ�Լ���봫�ݸ���������ֻ֧�ֲ�ѯһ��
	char **ppInstrumentID = new char*[50];
	ppInstrumentID[0] = m_pszInstrument;

	int iRetMD = m_pMDApi->SubscribeMarketData(ppInstrumentID, 1);
}
