#ifndef EM_H
#define EM_H

namespace ker
{
	class cEm
	{
	private:
		int _nVec;     //������������ĸ���
		int _nDim;     //������ά��
		int _nPat;     //�����

		double **_pplfVector;   //�����������
		double **_pplfZ;        //��i���������ڵ�j��ĸ���
		double **_pplfU;        //����ÿһ������ľ�ֵ����
		double *_plfPi;         //����ÿһ��������������
		double ***_ppplfDelta;  //����ÿһ�������Э�������

		double _lfL;            //�洢log likelihood����ֵ,��ֵ��E-Step����м���
		//����Ŀ�꼴Ҫʹ��ֵ���

	public:
		/**
		���캯���������ڴ��ʼ��
		param nVec �������������Ŀ
		param nDim �����������ά��
		param nPat ����Ϊ������
		*/
		cEm(int nVec, int nDim, int nPat);

		/**
		�����������ͷ�����������ڴ�
		*/
		virtual ~cEm();

		/**
		����
		param pplfVector ��������������������ά���Լ������ڹ��캯����ָ��
		*/
		void Cluster(double **pplfVector);

	private:
		/**
		E-Step
		*/
		void Expectation();

		/**
		M-Step
		*/
		void Maximization();

		/**
		����������ʽ
		param pplfMat ��������ʽ�ľ���
		����ֵ ����ʽ��ֵ
		*/
		double Determinant(double **pplfMat);

		/**
		��������
		param pplfMat ������ľ���
		����ֵ double��ָ���ָ�룬ָ���¿��ٴ洢�ռ䣬���б�����ԭ�������
		*/
		double ** Inverse(double **pplfMat);

		/**
		��ά��˹�ֲ��ܶȺ���
		param plfVec ��ά�ռ��еĵ����꣬��Ҫ��õ��ϵĸ����ܶ�
		param plfU ��˹�ֲ��ľ�ֵ����
		param pplfDelta ��˹�ֲ���Э�������
		����ֵ ��ά�ռ��ж�Ӧ��ĸ����ܶ�
		*/
		double Gaussian(double *plfVec, double *plfU, double **pplfDelta);
	};
}

#endif