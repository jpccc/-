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
		cout << "�����ַ���" << endl;
		getline(cin,input);
		input.append(1, EOF);
		while (input[0]!= EOF) {
			if (la->testIDandReservedWord(input)) {//ʶ���ʶ��������������
				cout << "ʶ���ʶ�������������֣��ɹ�" << endl;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//ȥ����ʶ��ɹ��ĵ���
				continue;
			}
			if (la->testINTC(input)) {//ʶ���޷�������
				cout << "ʶ���޷��������ɹ�" << endl;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//ȥ����ʶ��ɹ��ĵ���
				continue;
			}
			if (la->testOtherChar(input)) {//ʶ����������
				cout << "ʶ���������ųɹ�" << endl;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//ȥ����ʶ��ɹ��ĵ���
				continue;
			}
			break;
		}	
		if (input[0] == EOF) {
			cout << "�ʷ������ɹ�" << endl;
			
		}else {
			cout << "�ʷ�����ʧ�ܣ����޷�ʶ�𵥴�" << endl;
		}
		cout << "token��������" << endl;
		cout << "���� ����" << endl;
		for (Token* ptr = la->TokenList; ptr != nullptr; ptr = ptr->next) {
			cout << ptr->type << " " << ptr->value << endl;
		}
	}
}
bool LexicalAnalyzerByTS::testIDandReservedWord(string input) {
	State state = S0;
	int index = 0;//�����ַ���������
	char curChar = input[index];
	State matrix[3][2] = { S1,error,S2,S2,S2,S2 };//״̬ת������
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
		string word = input.substr(0, index);//��ȡʶ��ĵ���
		if(isReservedWord(word))
			insert_List(new Token(ReservedWord, word));//���ʷ���token����
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
	int index = 0;//�����ַ���������
	char curChar = input[index];
	State matrix[3][2] = { S1,error,S2,S2,S2,S2 };//״̬ת������
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
		string word = input.substr(0, index);//��ȡʶ��ĵ���
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
	int index = 0;//�����ַ���������
	char curChar = input[index];
	if (curChar == '.') {//ʶ�������±���޷���ͬʱʶ���ַ��ֽ����.��
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
	if (isOneCharDelimiter(curChar)) {//ʶ���ַ��ֽ��
		string word = input.substr(0, 1);//��ȡʶ��ĵ���
		insert_List(new Token(TokenType::OneCharDelimiter, word));
		return true;
	}
	if (curChar == ':') {//ʶ��˫�ַ��ֽ��
		curChar = input[++index];
		if (curChar == '=') {
			insert_List(new Token(TokenType::TwoCharDelimiter, ":="));
			return true;
		}
		else {
			return false;
		}
	}
	if (curChar == '{') {//ʶ��ע��ͷ��
		insert_List(new Token(TokenType::CommentHeader, "{"));
		return true;
	}
	if (curChar == '}') {//ʶ��ע�ͽ�����
		insert_List(new Token(TokenType::CommentTerminator, "}"));
		return true;
	}
	if (curChar == '\'') {//ʶ���ַ���ʼ���ͽ�����
		insert_List(new Token(TokenType::Character, "\'"));
		return true;
	}
}
