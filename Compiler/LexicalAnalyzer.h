#pragma once
#include<string>
#include <iostream>
using namespace std;
class Token {
	int type;//����
	string value;//����
};
class LexicalAnalyzer {//�ʷ�������
private :
	Token TokenList[];//token����
public:
	void makeTokenList(string input);//��Դ����ת��Ϊtoken����
	Token getToken();//�﷨���������ã���token�����з���һ��token
	void testId(string input);//����ʶ���ʶ��
};