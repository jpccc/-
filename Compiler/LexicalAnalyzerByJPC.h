#pragma once
#include <iostream>
#include"PublicSource.h"
using namespace std;
class LexicalAnalyzerByJPC {//�ʷ�������
private:
	Token* TokenList;//token����
public:
	LexicalAnalyzerByJPC() {
		TokenList = NULL;
	}
	void insert_List(Token* token);
	int srearch_ReservedWord(string st);
	void makeTokenList(string input);//��Դ����ת��Ϊtoken����
	Token* getToken();//�﷨���������ã���token�����з���һ��token
};
