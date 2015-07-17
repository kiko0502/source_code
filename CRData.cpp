#include "CRData.h"

CRData::CRData()
{
}
CRData::CRData(char* Tranfilename,char* Testfilename)
{
	//获得训练数据文件名
	m_tranfilename=Tranfilename;
	//获取测试数据文件名
	m_testfilename=Testfilename;

	//数据初始化
	Aver_m_height=0.0f;
	Aver_f_height=0.0f;
	SD_m_height=0.0f;
	SD_f_height=0.0f;
	Aver_m_weight=0.0f;
	Aver_f_weight=0.0f;
	SD_m_weight=0.0f;
	SD_f_weight=0.0f;
}
CRData::~CRData()
{
}
/* 读取文件 */
void CRData::GetData()
{
	FILE *file=fopen(m_tranfilename,"r");  //打开文件
	if(!file)  //如果打不开，则返回
	{
		printf("can't open file\n");
		return ;
	}
	char str[80];
	int num=0,temp_n;
	while(fscanf(file,"%s",str)==1)
	{
		if (strncmp(str,"Ni",2)==0)  //匹配字符Ni
		{	
			fscanf(file,"%d",&temp_n);
			num+=temp_n;
			m_train.resize(num);   
			for(int i=num-temp_n; i<num;i++)  //读取训练数据身高、体重与性别
			{
				fscanf(file,"%d%d%d",&(m_train[i].height),&(m_train[i].weight),&(m_train[i].sex));  
			}
		}
	}
	printf("数据读入完毕。\n");
	fclose(file);
}

//计算数据高斯分布参数
void CRData::TrainModel()
{
	//四个临时变量（求期望与标准差用）
	//计算均值
	float temp0=0,temp1=0,temp2=0,temp3=0;
	int male_num=0,female_num=0; //男女人数（本例为20,20）
	for(int i=0; i<m_train.size();i++)
	{
		if(m_train[i].sex==1){ //女
			temp0+=m_train[i].height;
			temp1+=m_train[i].weight;
			female_num++;
		}
		else{  //男
			temp2+=m_train[i].height;
			temp3+=m_train[i].weight;
			male_num++;
		}
	}
	Aver_f_height=temp0/female_num;
	Aver_m_height=temp2/male_num;
	Aver_f_weight=temp1/female_num;
	Aver_m_weight=temp3/male_num;
	//计算标准差
	temp0=0;temp1=0;temp2=0;temp3=0;
	for(int i=0; i<m_train.size();i++)
	{
		if(m_train[i].sex==1){  //女
			temp0+=pow(m_train[i].height-Aver_f_height,2);
			temp1+=pow(m_train[i].weight-Aver_f_weight,2);
		}
		else{  //男
			temp2+=pow(m_train[i].height-Aver_m_height,2);
			temp3+=pow(m_train[i].weight-Aver_m_weight,2);
		}
	}
	//标准差
	SD_f_height=sqrt(temp0/female_num);
	SD_m_height=sqrt(temp2/male_num);
	SD_f_weight=sqrt(temp1/female_num);
	SD_m_weight=sqrt(temp3/male_num);
	printf("模型训练完毕。\n");
}

//朴素贝叶斯分类模型
void CRData::WriteData(char* Result_filename)
{
	FILE *file_r=fopen(m_testfilename,"r");  //打开测试文件
	if(!file_r)
	{
		printf("can't open file\n");
		return ;
	}
	//FILE *file_w=fopen(Result_filename,"w");  //写新文件
	//if(!file_w)
	//{
	//	printf("can't create file\n");
	//	return ;
	//}

	char str[80];
	int num;
	while(fscanf(file_r,"%s",str)==1) 
	{
		if (strncmp(str,"N",1)==0)  //匹配字符
		{	
			fscanf(file_r,"%d",&num);  //读取人数
			//fprintf(file_w,"Ni  %d\n",num);
			for(int i=0; i<num;i++)
			{
				int height, weight;
				fscanf(file_r,"%d%d",&height,&weight);
				//朴素贝叶斯分类模型
				//计算女性概率与男性概率
				float pfamale=(1/SD_f_height)*exp(-0.5*pow((height-Aver_f_height)/SD_f_height,2))*
					(1/SD_f_weight)*exp(-0.5*pow((weight-Aver_f_weight)/SD_f_weight,2));
				float pmale=(1/SD_m_height)*exp(-0.5*pow((height-Aver_m_height)/SD_m_height,2))*
					(1/SD_m_weight)*exp(-0.5*pow((weight-Aver_m_weight)/SD_m_weight,2));
				//根据计算结果判断性别,读取文件的同时写入新文件
				char* sex=pfamale>pmale?"Female":"Male";
				//fprintf(file_w,"%d  %d  %d\n",height,weight,sex);
				printf("%d  %d  %s\n",height,weight,sex);
			}
		}
	}
	//关闭文件指针
	fclose(file_r);
	//fclose(file_w);
	system("pause");
}