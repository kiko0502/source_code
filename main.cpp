#include "CRData.h"

int main()
{
	//��ʼ��
	CRData data("trainning_set.txt","validation_set.txt");
	//��ȡ����
	data.GetData();
	//ѵ��ģ��
	data.TrainModel();
	//д����
	data.WriteData("result.txt");
	//�������
	return 0;
}