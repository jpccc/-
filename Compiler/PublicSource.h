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

const int reserved_count = 21;
static const char* reserved_word[reserved_count] = { "char","int","var","program","integer","procedure","array","begin","while","if","then","else","endwh",
"end","read","of","record","fi","return","write","type" };
struct Token {
	TokenType type;//����
	string value;//����
	Token* next;
};