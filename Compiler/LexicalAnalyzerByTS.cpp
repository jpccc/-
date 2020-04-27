#include "LexicalAnalyzerByTS.h"
LexicalAnalyzerByTS::LexicalAnalyzerByTS()
{
	TokenList = nullptr;
	TokenListRear = nullptr;
}
void LexicalAnalyzerByTS::insert_List(Token* token) {
	if (TokenList == nullptr) 
		TokenList = token;
	else 
		TokenListRear->next = token;
	token->next = nullptr;
	TokenListRear = token;
}
void LexicalAnalyzerByTS::makeTokenList(string input) {

}

Token LexicalAnalyzerByTS::getToken()
{
	return Token();
}
Token LexicalAnalyzerByTS::getLastToken()
{
	return *TokenListRear;
}
void LexicalAnalyzerByTS::debugging()
{ 
	while (true) {
		LexicalAnalyzerByTS *la = new LexicalAnalyzerByTS();
		string input;
		cout << "输入字符串" << endl;
		getline(cin,input);
		input.append(1, EOF);
		while (input[0]!= EOF) {
			if (la->testIDandReservedWord(input)) {//识别标识符，包括保留字
				cout << "识别标识符（包括保留字）成功" << endl;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//去掉刚识别成功的单词
				continue;
			}
			if (la->testINTC(input)) {//识别无符号整数
				cout << "识别无符号整数成功" << endl;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//去掉刚识别成功的单词
				continue;
			}
			if (la->testOtherChar(input)) {//识别其他符号
				cout << "识别其他符号成功" << endl;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//去掉刚识别成功的单词
				continue;
			}
			break;
		}	
		if (input[0] == EOF) {
			cout << "词法分析成功" << endl;
			
		}else {
			cout << "词法分析失败，有无法识别单词" << endl;
		}
		cout << "token序列如下" << endl;
		cout << "类型 单词" << endl;
		for (Token* ptr = la->TokenList; ptr != nullptr; ptr = ptr->next) {
			cout << ptr->type << " " << ptr->value << endl;
		}
	}
}
bool LexicalAnalyzerByTS::testIDandReservedWord(string input) {
	State state = S0;
	int index = 0;//输入字符串的索引
	char curChar = input[index];
	State matrix[3][2] = { S1,error,S2,S2,S2,S2 };//状态转换矩阵
	while (curChar !=EOF&&state!=error) {
		if (isLetter(curChar)) 
			state = matrix[state][0];
		else if (isNumber(curChar)) 
			state = matrix[state][1];
		else
			break;
		curChar = input[++index];
	}
	if (state == S1 || state == S2) {
		string word = input.substr(0, index);//截取识别的单词
		if(isReservedWord(word))
			insert_List(new Token(ReservedWord, word));//单词放入token序列
		else
			insert_List(new Token(ID, word));
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzerByTS::testINTC(string input)
{
	State state = S0;
	int index = 0;//输入字符串的索引
	char curChar = input[index];
	State matrix[3][2] = { S1,error,S2,S2,S2,S2 };//状态转换矩阵
	if (!input.compare("0")) {
		insert_List(new Token(INTC, "0"));
		return true;
	}
	while (curChar != EOF && state != error) {
		if (isNumberExcpZero(curChar))
			state = matrix[state][0];
		else if (isNumber(curChar))
			state = matrix[state][1];
		else
			break;
		curChar = input[++index];
	}
	if (state == S1 || state == S2) {
		string word = input.substr(0, index);//截取识别的单词
		insert_List(new Token(INTC, word));
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzerByTS::testOtherChar(string input)
{
	int index = 0;//输入字符串的索引
	char curChar = input[index];
	if (curChar == '.') {//识别数组下标界限符，同时识别单字符分界符“.”
		curChar = input[++index];
		if (curChar == '.') {
			insert_List(new Token(TokenType::ArraySubscript, ".."));
			return true;
		}
		else {
			insert_List(new Token(TokenType::OneCharDelimiter, "."));
			return true;
		}
	}
	if (isOneCharDelimiter(curChar)) {//识别单字符分界符
		string word = input.substr(0, 1);//截取识别的单词
		insert_List(new Token(TokenType::OneCharDelimiter, word));
		return true;
	}
	if (curChar == ':') {//识别双字符分界符
		curChar = input[++index];
		if (curChar == '=') {
			insert_List(new Token(TokenType::TwoCharDelimiter, ":="));
			return true;
		}
		else {
			return false;
		}
	}
	if (curChar == '{') {//识别注释头符
		insert_List(new Token(TokenType::CommentHeader, "{"));
		return true;
	}
	if (curChar == '}') {//识别注释结束符
		insert_List(new Token(TokenType::CommentTerminator, "}"));
		return true;
	}
	if (curChar == '\'') {//识别字符起始符和结束符
		insert_List(new Token(TokenType::Character, "\'"));
		return true;
	}
}
