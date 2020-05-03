#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>

#include"PublicSource.h"
using namespace std;
struct LinkListPoints {//������βָ��
	Symbol* head;
	Symbol* rear;
	LinkListPoints(Symbol* head, Symbol* rear) {
		this->head = head;
		this->rear = rear;
	}
};
struct OrderNum {
	int num;
	OrderNum* next;
};
class CalPredict//�������ʽ
{
private:
	static const string ProductionPath;//�������ʽ�ļ���·��
	static const string ExpressionPath;//����Ԥ�⼯�ļ���·��
	int CountProduction;//����ʽ��Ŀ
	Production* Productions;//���в���ʽ����
	Symbol** Predict;//ÿ������ʽ��Predict����������ʽ
	bool* TruePredict;//���predict���Ƿ��Ѿ����������ռ���
	Symbol** PredictRear;//Predict����βָ��	
	Symbol** history;//ÿ������ʽ����һ���������ڱ��������¼����ֹ��ζ�ͬһ������ʽ����ͬ�����ŵĺ�������(insertFollowSymbol����ר��)
public:
	CalPredict();
	static void debugging();//���Գ���
	void readProductions();//���ļ��ж������ʽ����
	void calPredict();//���ݲ���ʽ���ϼ���Predict��
	void calFakePredict();//������з��ռ�����predict��
	void writePredict();//��Ԥ�⼯д���ļ�
	Production string_to_Production( string str_Prod,char sep);//����ȡ��һ���ַ���תΪ����ʽ����
	void getTerminalInfo();//������ʽ�е�����symbol���Ͷ����isTerminal��Ա�������ж��Ƿ�Ϊ�ռ������޸�Ϊ��ȷ�ģ��ն������ʽʱȫ��Ĭ��Ϊ�ռ���
	
	void printProductions();//��ӡȫ������ʽ
	void printPredict(int orderNum);//��ӡ��������ʽ��predict��
	void printPredicts();//��ӡȫ��predict��
	
	void insertPredict(int orderNum,Symbol* symbol);//����Ӧ����ʽ��Predict����������
	void insertPredict(int orderNum, LinkListPoints llp);//����Ӧ����ʽ��Predict��������������,����llpΪ��βָ��
	int getCountProduction(ifstream &inFile);//�����ļ�������ȷ������ʽ����
	void insertFollowSymbol(int i,Symbol symbol);//���÷��ŵĺ������ż����Ӧ����ʽ��predict�����������ռ���
	bool inHistory(Symbol** history, int orderNum, Symbol symbol);//�ж��Ƿ��ڲ�����¼��(insertFollowSymbol����ר��)
	void insertHistory(Symbol** history, int orderNum, Symbol symbol);//���������¼����(insertFollowSymbol����ר��)
	Symbol* findInPredict(int orderNum, Symbol symbol);//�жϷ����Ƿ��ڶ�Ӧpredict����
	bool calFinish();//�ж�predict�����Ƿ��з��ռ���
	void killNTsymbol();//��predict���еķ��ռ����滻Ϊ��Ӧ�ռ�����Ҳ�������滻Ϊ�÷��ռ�����predict��
	bool isTruePredict(int orderNum);//�ж��Ƿ�Ϊ���������ռ�����predict��
	void setTruePredict();//�ж�����predict���Ƿ񲻰������ռ�������Ϣ�������������
	vector<int>* isTruePredict(Symbol symbol);//�÷���Ϊ�󲿵Ĳ���ʽ��predict���Ƿ񲻰������ռ��������򷵻ز���ʽ��ŵ�vector�����򷵻ؿ�
	void replaceNT(Symbol symbol, vector<int>* v);//�����в���ʽ��predict�����滻���÷��ռ���
	void removePredict(int orderNum, Symbol* symbol);//ɾ��predict���з���
};
