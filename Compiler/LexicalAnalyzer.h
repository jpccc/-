#pragma once
#include<string>
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
};