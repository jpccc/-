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
int LexicalAnalyzerByTS::srearch_ReservedWord(string st) {
	int exist = 0;
	for (int i = 0; i < reserved_count; i++) {
		if (st.compare(reserved_word[i]))
			exist = i + 1;
	}
	return exist;
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
		input.append("#");
		while (input[0]!= '#') {
			bool getWord=false;//标记单词识别是否成功
			if (la->testId(input)) {//识别标识符
				cout << "识别标识符成功" << endl;
				getWord = true;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//去掉刚识别成功的单词
			}
			if (!getWord)
				break;
		}	
		if (input[0] == '#') {
			cout << "词法分析成功" << endl;
			
		}else {
			cout << "词法分析失败，有无法识别单词" << endl;
		}
		cout << "token序列如下" << endl;
		cout << "类型 单词" << endl;
		for (Token* ptr = la->TokenList; ptr != nullptr; ptr = ptr->next) {
			cout << ptr->value << " " << ptr->type << endl;
		}
	}
}
bool LexicalAnalyzerByTS::testId(string input) {
	State state = S0;
	int index = 0;//输入字符串的索引
	char curChar = input[index];
	State matrix[3][2] = { S1,error,S2,S2,S2,S2 };//状态转换矩阵
	while (curChar != '#'&&state!=error) {
		if (isLetter(curChar)) 
			state = matrix[state][0];
		else if (isNumber(curChar)) 
			state = matrix[state][1];
		else
			break;
		curChar = input[++index];
	}
	if (state == 2 || state == 3) {
		string word = input.substr(0, index);//截取识别的单词
		insert_List(new Token(ID, word));//单词放入token序列
		return true;
	}
	else
	{
		return false;
	}
}