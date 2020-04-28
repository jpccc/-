#pragma once
#include<string>
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
	S2, S3, S4, S5, S6, S7
};
// State(error-S7)ֱ��ת��״̬���е�״̬,State(error-S2)״̬ת�������е�״̬
const int reserved_count = 21;
static const char* reserved_word[reserved_count] = { "char","int","var","program","integer","procedure","array","begin","while","if","then","else","endwh",
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
bool isLetter(char ch);//�ж��ַ��Ƿ�Ϊ��ĸ
bool isNumber(char ch);//�ж��ַ��Ƿ�Ϊ����
bool isNumberExcpZero(char ch);//�ж��ַ��Ƿ�Ϊ��0������
bool isOneCharDelimiter(char ch);//�ж��ַ��Ƿ�Ϊ���ַ��ֽ��
bool isReservedWord(string st);//�ж��Ƿ�Ϊ������