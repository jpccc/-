#include "LexicalAnalyzerByTS.h"
void LexicalAnalyzerByTS::insert_List(Token* token) {
	Token* start = TokenList;
	if (TokenList == NULL) {
		TokenList = token
	}
	else
	{
		while ()
	}
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

	int count = 0;	//输入串遍历指针
	unsigned int iSize = input.size();

	string word = "";//即将要加入TokenList的单词
	char NextChar;//上次读取的字符
	char CurrentChar;//当前读取的字符

	int judge = 0;//选择执行哪一个分支
	int reserved_Location;//保留字在表中的位置

	while (count < iSize) {
		CurrentChar = input[count];
		NextChar = CurrentChar;
		count++;		//输入串指针移动

		switch (judge) {
		case 0:		//起始状态
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z'))
			{
				judge = 1;
				break;
			}
			if ('0' <= CurrentChar && CurrentChar <= '9')
			{
				judge = 2;
				break;
			}
			judge = 3;//其他，暂时测试
			if (CurrentChar = '#')//结束标志
			{
				judge = 10;	//	暂时设定
				break;
			}
			break;
		case 1:		//字母
			CurrentChar = input[count];		//后期加上判断，防止越界
			count++;		//输入串指针移动
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z') || ('0' <= CurrentChar && CurrentChar <= '9'))
			{
				word = word + CurrentChar;//拼接
				NextChar = CurrentChar;
				break;
			}
			count--;			//不是标识符，Back
			CurrentChar = NextChar;
			reserved_Location = srearch_ReservedWord(word);
			if (reserved_Location == 0)				//保留字? 若返回0，表里找不到，则为标识符，
			{
				Token* reserved_word = new Token();
				reserved_word->type = 2;
				reserved_word->value = word;
				reserved_word->next = NULL;
			}

			break;
		case 2:		//数字

			break;
		}

		if (judge == 10)	//跳出while循环	
			break;
	}


}

Token LexicalAnalyzerByTS::getToken()
{
	return Token();
}
void LexicalAnalyzerByTS::debugging()
{
	 LexicalAnalyzerByTS *la = new LexicalAnalyzerByTS();
 string input;
 while (true) {
	 cout << "输入字符串" << endl;
	 cin >> input;
	 input.append("#");
	 cout << "你输入了" << input << endl;
	 la->testId(input);
 } 
}
void LexicalAnalyzerByTS::testId(string input) {
	int state = 0;
	int curIndex = 0;
	char curChar = input[curIndex];
	cout << "curchar=" << curChar << endl;
	enum { error = -1 };
	int matrix[3][2] = { 1,error,2,2,2,2 };
	cout << "matrix:" << matrix[1][0] << " " << matrix[1][1] << endl;
	while (curChar != '#' && state != error) {
		if ((curChar >= 'a' && curChar <= 'z') || (curChar >= 'A' && curChar <= 'Z')) {
			state = matrix[state][0];
		}
		else if (curChar >= '0' && curChar <= '9') {
			state = matrix[state][1];
		}
		else
		{
			state = error;
		}
		curChar = input[++curIndex];
	}
	if (state == 2 || state == 3) {
		cout << "识别成功" << endl;
	}
	else
	{
		cout << "识别错误" << endl;
	}
}