#pragma once
#include <iostream>
#include "PublicSource.h"
class LexicalAnalyzerByJPC {//�ʷ�������
private:
	string input;
	Token* TokenHead;//tokenͷ
	Token* TokenTail;//tokenβ
public:
	LexicalAnalyzerByJPC(string st) {
		input = st;
		TokenHead = NULL;
		TokenTail = NULL;
	}
	void insert_List(Token* token);
	char readOne(int& count);//�����봮����һ���ַ�
	void backOne(int& count, char& CurrentChar, char& NextChar);//����һ���ַ�
	void makeTokenList();//��Դ����ת��Ϊtoken����
	Token* getToken();//�﷨���������ã���token�����з���һ��token
};
