#include "CRData.h"

int main()
{
	//初始化
	CRData data("trainning_set.txt","validation_set.txt");
	//读取数据
	data.GetData();
	//训练模型
	data.TrainModel();
	//写入结果
	data.WriteData("result.txt");
	//程序结束
	return 0;
}