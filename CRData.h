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
//函数
public:
	CRData(); //构造函数
	CRData(char* Tranfilename,char* Testfilename); //构造函数
	~CRData();
	void GetData(); //读取数据
	void TrainModel(); //训练数据
	void WriteData(char* Result_filename);
//数据
public:
	char* m_tranfilename;  
	char* m_testfilename;
	vector<DataSet> m_train; //训练数据
	float Aver_m_height; //男身高均值
	float Aver_f_height; //女身高均值
	float SD_m_height; //男身高标准差
	float SD_f_height; //女身高标准差
	float Aver_m_weight; //男体重均值
	float Aver_f_weight; //女体重均值
	float SD_m_weight; //男体重标准差
	float SD_f_weight; //女体重标准差
};


#endif