#pragma once
#include <iostream>
#include"PublicSource.h"
using namespace std;
class LexicalAnalyzerByTS {//�ʷ�������
private:
	Token* TokenList;//token����
public:
	LexicalAnalyzerByTS() {
		TokenList = NULL;
	}
	void insert_List(Token* token);
	static int srearch_ReservedWord(string st);
	static void makeTokenList(string input);//��Դ����ת��Ϊtoken����
	static Token getToken();//�﷨���������ã���token�����з���һ��token
	static void debugging();//���Գ���
	void testId(string input);
};
