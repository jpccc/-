#pragma once
#include<string>
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
	S2, S3, S4, S5, S6, S7
};
// State(error-S7)直接转向伐状态机中的状态,State(error-S2)状态转换矩阵法中的状态
const int reserved_count = 21;
static const char* reserved_word[reserved_count] = { "char","int","var","program","integer","procedure","array","begin","while","if","then","else","endwh",
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
bool isLetter(char ch);//判断字符是否为字母
bool isNumber(char ch);//判断字符是否为数字
bool isNumberExcpZero(char ch);//判断字符是否为非0的数字
bool isOneCharDelimiter(char ch);//判断字符是否为单字符分界符
bool isReservedWord(string st);//判断是否为保留字