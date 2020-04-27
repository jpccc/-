#include"LexicalAnalyzerByJPC.h"
void LexicalAnalyzerByJPC::insert_List(Token* token) {
	Token* start = TokenList;
	if (start == NULL) {
		TokenList = token;
	}
	else
	{
		while (start->next != NULL)
			start = start->next;
		start->next = token;
	}
}
int LexicalAnalyzerByJPC::srearch_ReservedWord(string st) {
	int exist = 0;
	for (int i = 0; i < reserved_count; i++) {
		if (st.compare(reserved_word[i]) == 0)
		{
			exist = i + 1;
			break;
		}
	}
	return exist;
}
void LexicalAnalyzerByJPC::makeTokenList(string input) {

	int count = 0;	//输入串遍历指针
	int iSize = input.size();

	string word = "";//即将要加入TokenList的单词
	char NextChar;//上次读取的字符
	char CurrentChar;//当前读取的字符

	int judge = 0;//选择执行哪一个分支
	int reserved_Location;//保留字在表中的位置

	bool finded = false;//已经识别了一个单词

	Token* reserved_word = NULL;
	TokenType tokenType = ID;
	CurrentChar = input[count];
	NextChar = CurrentChar;
	count++;		//输入串指针移动
	while (count < iSize) {
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
			if (CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/' || CurrentChar == '<' || CurrentChar == '=' || CurrentChar == '(' || CurrentChar == ')' || CurrentChar == '['
				|| CurrentChar == ']' || CurrentChar == '.' || CurrentChar == ';' || CurrentChar == 'EOF' || CurrentChar == ' ')
			{
				judge = 3;
				break;
			}
			if (CurrentChar == ':')
			{
				judge = 4;
				break;
			}
			if (CurrentChar == ':')
			{
				judge = 5;
				break;
			}
			if (CurrentChar == ':')
			{
				judge = 6;
				break;
			}
			if (CurrentChar == '\'')
			{
				judge = 7;
				break;
			}
			if (CurrentChar == '#')//结束标志
			{
				judge = 9;	//	暂时设定
				break;
			}
			break;
		case 1:		//字母
			word = word + CurrentChar;		//这时CurrentChar肯定是字母

			CurrentChar = input[count];		//后期加上判断，防止越界
			count++;		//输入串指针移动
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z') || ('0' <= CurrentChar && CurrentChar <= '9'))
			{
				NextChar = CurrentChar;
				break;
			}
			count--;			//不是标识符，Back
			CurrentChar = NextChar;
			reserved_Location = srearch_ReservedWord(word);
			if (reserved_Location == 0)				//保留字? 若返回0，表里找不到，则为标识符，
			{
				reserved_word = new Token();
				tokenType = ID;
				reserved_word->type = tokenType;
				reserved_word->value = word;
				reserved_word->next = NULL;
				insert_List(reserved_word);
			}
			else
			{
				reserved_word = new Token();
				tokenType = ReservedWord;
				reserved_word->type = tokenType;
				reserved_word->value = word;
				reserved_word->next = NULL;
				insert_List(reserved_word);
			}
			finded = true;
			break;
		case 2:		//数字
			word = word + CurrentChar;		//这时CurrentChar肯定是字母
			CurrentChar = input[count];		//后期加上判断，防止越界
			count++;		//输入串指针移动
			if ('0' <= CurrentChar && CurrentChar <= '9')
			{
				NextChar = CurrentChar;
				break;
			}
			count--;			//不是标识符，Back
			CurrentChar = NextChar;
			reserved_word = new Token();
			tokenType = INTC;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		case 3: //单字符分界
			word = word + CurrentChar;

			CurrentChar = input[count];		//后期加上判断，防止越界
			count++;		//输入串指针移动
			if (NextChar == '.' && CurrentChar == '.')
			{
				NextChar = CurrentChar;
				judge = 8;
				break;
			}
			count--;			//不是标识符，Back
			CurrentChar = NextChar;
			reserved_word = new Token();
			tokenType = OneCharDelimiter;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		case 4:	//双字符分界
			word = word + CurrentChar;		//这时CurrentChar肯定是字母
			CurrentChar = input[count];		//后期加上判断，防止越界
			count++;		//输入串指针移动
			if (CurrentChar == '=') {
				word = word + CurrentChar;
				reserved_word = new Token();
				tokenType = TwoCharDelimiter;
				reserved_word->type = tokenType;
				reserved_word->value = word;
				reserved_word->next = NULL;
				insert_List(reserved_word);
				finded = true;
			}
			else {
				cout << "error" << endl;
				exit(1);
			}
			break;
		case 5:			//注释起始
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = CommentHeader;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;

		case 6:		//注释结束
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = CommentTerminator;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;

		case 7:		//字符起始符
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = Character;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		case 8://数组下标界限符
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = ArraySubscript;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		default:
			break;
		}
		if (finded)
		{
			CurrentChar = input[count];		//后期加上判断，防止越界
			NextChar = CurrentChar;
			count++;		//输入串指针移动
			judge = 0;	//回到起始
			word = "";
			finded = false;
		}
		if (judge == 9)	//跳出while循环	
			break;
	}
}
Token* LexicalAnalyzerByJPC::getToken()
{
	return TokenList;
}