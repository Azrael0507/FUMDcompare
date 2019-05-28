#include "stdafx.h"
#include "CMDapi.h"
#include "CMDspi.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "OtherFunc.h"

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

	//��ȡ��������Ŀ¼�µ�MDconfig.ini�ļ�
	char currpath[500];
	string temp_path = "";
	GetModuleFileNameA(NULL, currpath, 500);
	temp_path = (string)currpath;
	int pos = temp_path.find_last_of('\\', temp_path.length());
	temp_path = temp_path.substr(0, pos + 1);
	temp_path += "MDconfig.ini";
	MDCfgFilePath = const_cast<char*>(temp_path.data());

	//�жϽ��̺ţ��Ӳ�ͬ���������ȡ����
	if (processnumber == 1)
	{
		//�������ļ���ȡ����ǰ�õ�ַ
		readConfigFile(MDCfgFilePath, "frontaddr1", tmp_pszFrontAddr);
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//�������ļ���ȡbrokerid���͹�˾���
		readConfigFile(MDCfgFilePath, "brokerid1", tmp_pszBrokerId);
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//�������ļ���ȡ��¼�˻�
		readConfigFile(MDCfgFilePath, "userid1", tmp_pszUserId);
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//�������ļ���ȡ��¼����
		readConfigFile(MDCfgFilePath, "password1", tmp_pszPasswd);
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//�������ļ���ȡ�ͻ��˱�ʶ,��һ�ͻ��˱�ʾ������11���ֽڵ����ƣ���������֤֮�ã���˿���������д�����ϳ��ȼ���
		readConfigFile(MDCfgFilePath, "proinfo1", tmp_pszProInfo);
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//�������ļ���ȡ��¼��ע��Ϣ
		readConfigFile(MDCfgFilePath, "remark1", tmp_pszRemark);
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//�������ļ���ȡѡ��ĺ�Լ��Ϣ
		readConfigFile(MDCfgFilePath, "instrument1", tmp_pszInstrument);
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//�������ļ���ȡ����ļ���Ϣ
		readConfigFile(MDCfgFilePath, "filepath1", tmp_pszOutFilePath);
		m_pszOutFilePath = const_cast<char*>(tmp_pszOutFilePath.data());
	}
	else if (processnumber == 2)
	{
		//�������ļ���ȡ����ǰ�õ�ַ
		readConfigFile(MDCfgFilePath, "frontaddr2", tmp_pszFrontAddr);
		m_pszFrontAddr = const_cast<char*>(tmp_pszFrontAddr.data());

		//�������ļ���ȡbrokerid���͹�˾���
		readConfigFile(MDCfgFilePath, "brokerid2", tmp_pszBrokerId);
		m_pszBrokerId = const_cast<char*>(tmp_pszBrokerId.data());

		//�������ļ���ȡ��¼�˻�
		readConfigFile(MDCfgFilePath, "userid2", tmp_pszUserId);
		m_pszUserId = const_cast<char*>(tmp_pszUserId.data());

		//�������ļ���ȡ��¼����
		readConfigFile(MDCfgFilePath, "password2", tmp_pszPasswd);
		m_pszPasswd = const_cast<char*>(tmp_pszPasswd.data());

		//�������ļ���ȡ�ͻ��˱�ʶ,��һ�ͻ��˱�ʾ������11���ֽڵ����ƣ���������֤֮�ã���˿���������д�����ϳ��ȼ���
		readConfigFile(MDCfgFilePath, "proinfo2", tmp_pszProInfo);
		m_pszProInfo = const_cast<char*>(tmp_pszProInfo.data());

		//�������ļ���ȡ��¼��ע��Ϣ
		readConfigFile(MDCfgFilePath, "remark2", tmp_pszRemark);
		m_pszRemark = const_cast<char*>(tmp_pszRemark.data());

		//�������ļ���ȡѡ��ĺ�Լ��Ϣ
		readConfigFile(MDCfgFilePath, "instrument2", tmp_pszInstrument);
		m_pszInstrument = const_cast<char*>(tmp_pszInstrument.data());

		//�������ļ���ȡ����ļ���Ϣ
		readConfigFile(MDCfgFilePath, "filepath2", tmp_pszOutFilePath);
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
