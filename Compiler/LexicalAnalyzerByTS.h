#pragma once
#include <iostream>
#include"PublicSource.h"
using namespace std;
class LexicalAnalyzerByTS {//�ʷ�������
private:
	Token* TokenList;//token����ͷָ��
	Token* TokenListRear;//token����βָ��
public:
	LexicalAnalyzerByTS();
	void insert_List(Token* token);//token���в������
	void makeTokenList(string input);//��Դ����ת��Ϊtoken����
	Token getToken();//�﷨���������ã���token�����з���һ��token
	Token getLastToken();//��ȡ�������token�������ʷ��������ܵ�ʵ��
	static void debugging();//���Գ���
	bool testIDandReservedWord(string input);//����ʶ��һ����ʶ�������������֣�����ʶ����
	bool testINTC(string input);//����ʶ��һ���޷�������
	bool testOtherChar(string input);//����ʶ�������ķ���
};
