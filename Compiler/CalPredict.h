#pragma once
#include<string>
#include"PublicSource.h"
using namespace std;
const string CalPredict::ProductionPath = "Debug / file / production.txt";
const string CalPredict::ExpressionPath = "Debug / file / expression.txt";
class CalPredict//�������ʽ
{
private:
	static const string ProductionPath;//�������ʽ�ļ���·��
	static const string ExpressionPath;//����Ԥ�⼯�ļ���·��
	static const int CountProduction=104;//����ʽ��Ŀ
	Production Productions[CountProduction];//���в���ʽ����
	Symbol* Predict[CountProduction];//ÿ������ʽ��Predict����������ʽ
public:
	void readProductions();//���ļ��ж������ʽ����
	void calPredict();//���ݲ���ʽ���ϼ���Predict��
	void writePredict();//��Ԥ�⼯д���ļ�
};

