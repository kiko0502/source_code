#pragma once
#ifndef  _CRDATA_
#define  _CRDATA_
#include <iostream>
#include<string>
#include<vector>
using namespace std;
#include<math.h>
#include"Global.h"

class CRData
{
//����
public:
	CRData(); //���캯��
	CRData(char* Tranfilename,char* Testfilename); //���캯��
	~CRData();
	void GetData(); //��ȡ����
	void TrainModel(); //ѵ������
	void WriteData(char* Result_filename);
//����
public:
	char* m_tranfilename;  
	char* m_testfilename;
	vector<DataSet> m_train; //ѵ������
	float Aver_m_height; //����߾�ֵ
	float Aver_f_height; //Ů��߾�ֵ
	float SD_m_height; //����߱�׼��
	float SD_f_height; //Ů��߱�׼��
	float Aver_m_weight; //�����ؾ�ֵ
	float Aver_f_weight; //Ů���ؾ�ֵ
	float SD_m_weight; //�����ر�׼��
	float SD_f_weight; //Ů���ر�׼��
};


#endif