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
	void insert_List(Token* token);
	int srearch_ReservedWord(string st);
	void makeTokenList(string input);//��Դ����ת��Ϊtoken����
	Token getToken();//�﷨���������ã���token�����з���һ��token
	Token getLastToken();//��ȡ�������token�������ʷ��������ܵ�ʵ��
	static void debugging();//���Գ���
	bool testId(string input);//����ʶ��һ����ʶ��������ʶ����

};
