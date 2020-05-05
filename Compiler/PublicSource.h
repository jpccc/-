#pragma once
#include<string>
#include<iostream>
#include<vector>
#include <set>
#include<stack>
#include<fstream>
using namespace std;
enum TokenType {
	ID,//��ʶ��
	ReservedWord,//������
	INTC,//�޷�������
	OneCharDelimiter,//���ַ��ֽ��
	TwoCharDelimiter,//˫�ַ��ֽ��
	CommentHeader,//ע��ͷ��
	CommentTerminator,//ע�ͽ�����
	Character,//�ַ���ʼ�ͽ�����
	ArraySubscript//�����±���޷�
};
enum State {//״̬���е�״̬
	error=-1,
	S0,
	S1,
	S2, S3, S4, S5, S6
};
// State(error-S7)ֱ��ת��״̬���е�״̬,State(error-S2)״̬ת�������е�״̬
const int reserved_count = 21;
static const char* reserved_word[reserved_count] = { "char","int","var","Program","integer","procedure","array","begin","while","if","then","else","endwh",
"end","read","of","record","fi","return","write","type" };
const int OneCharDelimiter_count = 16;
static const char oneChar_delimiter[OneCharDelimiter_count] = { '+','-','*','/','<','=','>','(',')','[',']','.',';',EOF,' ','\n' };
struct Token {
	TokenType type;//����
	string value;//����
	Token* next;
	Token();
	Token(TokenType type, string value);
};

struct Symbol {//�ķ�����
	bool isTerminal;//�Ƿ����ռ���
	string value;//��������
	Symbol* next;//����ָ��
	Symbol(string value);
	Symbol(const Symbol& symbol);//��������
	Symbol();
};
struct Production {//����ʽ
	Symbol Left;//����ʽ��
	Symbol* Right;//����ʽ�Ҳ�,������ʽ
	Symbol* RightRear;//����ʽ�Ҳ�����βָ��
	void insertRight(Symbol* symbol);//����ʽ�Ҳ����ӷ���
	void printProduction();
	vector<Symbol*>* findSymbolInRight(Symbol symbol);//�ڲ���ʽ�Ҳ��ҵ��÷��Ų�����
	Production();
};
bool isLetter(char ch);//�ж��ַ��Ƿ�Ϊ��ĸ
bool isNumber(char ch);//�ж��ַ��Ƿ�Ϊ����
bool isNumberExcpZero(char ch);//�ж��ַ��Ƿ�Ϊ��0������
bool isOneCharDelimiter(char ch);//�ж��ַ��Ƿ�Ϊ���ַ��ֽ��
bool isReservedWord(string st);//�ж��Ƿ�Ϊ������