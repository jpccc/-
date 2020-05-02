#pragma once
#include<string>
#include<iostream>
#include<fstream>

#include"PublicSource.h"
using namespace std;
class CalPredict//�������ʽ
{
private:
	static const string ProductionPath;//�������ʽ�ļ���·��
	static const string ExpressionPath;//����Ԥ�⼯�ļ���·��
	int CountProduction;//����ʽ��Ŀ
	Production* Productions;//���в���ʽ����
	Symbol** Predict;//ÿ������ʽ��Predict����������ʽ
	Symbol** PredictRear;//Predict����βָ��
	bool isBlank = true;
public:
	CalPredict();
	static void debugging();//���Գ���
	void readProductions();//���ļ��ж������ʽ����
	void calPredict();//���ݲ���ʽ���ϼ���Predict��
	void writePredict();//��Ԥ�⼯д���ļ�
	Production string_to_Production( string str_Prod,char sep);//����ȡ��һ���ַ���תΪ����ʽ����
	void getTerminalInfo();//������ʽ�е�����symbol���Ͷ����isTerminal��Ա�������ж��Ƿ�Ϊ�ռ������޸�Ϊ��ȷ�ģ��ն������ʽʱȫ��Ĭ��Ϊ�ռ���
	void printProductions();//��ӡȫ������ʽ
	void insertPredict(int orderNum,Symbol* symbol);//����Ӧ����ʽ��Predict����������
	int getCountProduction(ifstream &inFile);//�����ļ�������ȷ������ʽ����
};
