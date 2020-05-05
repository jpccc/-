#pragma once
#include<string>
#include<iostream>
#include<vector>
#include <set>
#include<stack>
#include<fstream>
using namespace std;
enum TokenType {
	ID,//标识符
	ReservedWord,//保留字
	INTC,//无符号整数
	OneCharDelimiter,//单字符分界符
	TwoCharDelimiter,//双字符分界符
	CommentHeader,//注释头符
	CommentTerminator,//注释结束符
	Character,//字符起始和结束符
	ArraySubscript//数组下标界限符
};
enum State {//状态机中的状态
	error=-1,
	S0,
	S1,
	S2, S3, S4, S5, S6
};
// State(error-S7)直接转向伐状态机中的状态,State(error-S2)状态转换矩阵法中的状态
const int reserved_count = 21;
static const char* reserved_word[reserved_count] = { "char","int","var","Program","integer","procedure","array","begin","while","if","then","else","endwh",
"end","read","of","record","fi","return","write","type" };
const int OneCharDelimiter_count = 16;
static const char oneChar_delimiter[OneCharDelimiter_count] = { '+','-','*','/','<','=','>','(',')','[',']','.',';',EOF,' ','\n' };
struct Token {
	TokenType type;//类型
	string value;//内容
	Token* next;
	Token();
	Token(TokenType type, string value);
};

struct Symbol {//文法符号
	bool isTerminal;//是否是终极符
	string value;//符号内容
	Symbol* next;//链表指针
	Symbol(string value);
	Symbol(const Symbol& symbol);//拷贝函数
	Symbol();
};
struct Production {//产生式
	Symbol Left;//产生式左部
	Symbol* Right;//产生式右部,链表形式
	Symbol* RightRear;//产生式右部链表尾指针
	void insertRight(Symbol* symbol);//产生式右部增加符号
	void printProduction();
	vector<Symbol*>* findSymbolInRight(Symbol symbol);//在产生式右部找到该符号并返回
	Production();
};
bool isLetter(char ch);//判断字符是否为字母
bool isNumber(char ch);//判断字符是否为数字
bool isNumberExcpZero(char ch);//判断字符是否为非0的数字
bool isOneCharDelimiter(char ch);//判断字符是否为单字符分界符
bool isReservedWord(string st);//判断是否为保留字