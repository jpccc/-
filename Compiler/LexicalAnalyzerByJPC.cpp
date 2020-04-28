#include"LexicalAnalyzerByJPC.h"
char  LexicalAnalyzerByJPC::readOne(int& count) {
	char letter=input[count];		//后期加上判断，防止越界
	count++;		//输入串指针移动
	return letter;
}
void  LexicalAnalyzerByJPC::backOne(int& count,char&CurrentChar,char& NextChar) {
	count--;
	CurrentChar = NextChar;
}
void LexicalAnalyzerByJPC::insert_List(Token* token) {
	if (TokenHead == NULL)
		TokenHead = token;
	else
		TokenTail->next = token;
	token->next = NULL;
	TokenTail = token;
}
void LexicalAnalyzerByJPC::makeTokenList() {
	int count = 0;	//输入串遍历指针
	int iSize = input.size();

	string word = "";//即将要加入TokenList的单词
	char NextChar;//上次读取的字符
	char CurrentChar;//当前读取的字符

	State judge = S0;//选择执行哪一个分支
	bool finded = false;//已经识别了一个单词

	TokenType tokenType;//单词的种类
	CurrentChar = readOne(count);
	NextChar = CurrentChar;
	while (count <= iSize) {
		switch (judge) {
		case S0:		//起始状态
			if (isLetter(CurrentChar))
			{
				judge = S1;
				break;
			}
			if (isNumber(CurrentChar))
			{
				judge = S2;
				break;
			}
			if (isOneCharDelimiter(CurrentChar))
			{
				judge = S3;
				break;
			}
			if (CurrentChar == ':')
			{
				judge = S4;
				break;
			}
			if (CurrentChar == '{')
			{
				judge = S5;
				break;
			}
			if (CurrentChar == '\'')
			{
				judge = S6;
				break;
			}
			finded = true;
			break;
		case S1:		//字母
			word = word + CurrentChar;		//这时CurrentChar肯定是字母
			CurrentChar = readOne(count);
			if (isLetter(CurrentChar)||isNumber(CurrentChar))
			{
				NextChar = CurrentChar;
				break;
			}
			backOne(count, CurrentChar, NextChar);
			if (!isReservedWord(word))				//保留字? 若返回0，表里找不到，则为标识符，
			{
				tokenType = ID;
				insert_List(new Token(tokenType,word));
			}
			else
			{
				tokenType = ReservedWord;
				insert_List(new Token(tokenType, word));
			}
			finded = true;//找到一个单词
			break;
		case S2:		//数字
			word = word + CurrentChar;		//这时CurrentChar肯定是字母
			CurrentChar = readOne(count);
			if (isNumber(CurrentChar))
			{
				NextChar = CurrentChar;
				break;
			}
			backOne(count, CurrentChar, NextChar);
			tokenType = INTC;
			insert_List(new Token(tokenType, word));
			finded = true;
			break;
		case S3: //单字符分界
			word = word + CurrentChar;
			CurrentChar = readOne(count);
			if (NextChar == '.' && CurrentChar == '.')
			{//数组分节符
				NextChar = CurrentChar;
				word = word + CurrentChar;
				tokenType = ArraySubscript;
				insert_List(new Token(tokenType, word));
				finded = true;
				break;
			}
			backOne(count, CurrentChar, NextChar);
			tokenType = OneCharDelimiter;
			if (CurrentChar == EOF)//结束标志,count指向下一个要读的位置,结束后在数值上等于iSize
			{
				insert_List(new Token(tokenType, "EOF"));
				return;//结束了
			}
			insert_List(new Token(tokenType,word));
			finded = true;
			break;
		case S4:	//双字符分界
			word = word + CurrentChar;		//这时CurrentChar肯定是字母
			CurrentChar = readOne(count);
			if (CurrentChar == '=') {
				word = word + CurrentChar;
				tokenType = TwoCharDelimiter;
				insert_List(new Token(tokenType, word));
				finded = true;
			}
			else {
				cout << "error,有单词错误" << endl;
				exit(1);
			}
			break;
		case S5:			//注释起始
			while (count < iSize) {
				CurrentChar = readOne(count);
				if (CurrentChar == '}')
				{
					finded = true;
					break;
				}
			}
			break;
		case S6:		//字符起始符
			word = word + CurrentChar;
			tokenType = Character;
			insert_List(new Token(tokenType, word));
			finded = true;
			break;
		default:
			cout << "error" << endl;
			break;
		}
		if (finded)
		{
			CurrentChar = readOne(count);
			NextChar = CurrentChar;
			judge = S0;	//回到起始
			word = "";
			finded = false;
		}
	}
}
Token* LexicalAnalyzerByJPC::getToken()
{
	return TokenHead;
}