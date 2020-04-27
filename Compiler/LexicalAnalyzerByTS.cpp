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
		cout << "�����ַ���" << endl;
		getline(cin,input);
		input.append("#");
		while (input[0]!= '#') {
			bool getWord=false;//��ǵ���ʶ���Ƿ�ɹ�
			if (la->testId(input)) {//ʶ���ʶ��
				cout << "ʶ���ʶ���ɹ�" << endl;
				getWord = true;
				string word = la->getLastToken().value;
				input = input.substr(word.length());//ȥ����ʶ��ɹ��ĵ���
			}
			if (!getWord)
				break;
		}	
		if (input[0] == '#') {
			cout << "�ʷ������ɹ�" << endl;
			
		}else {
			cout << "�ʷ�����ʧ�ܣ����޷�ʶ�𵥴�" << endl;
		}
		cout << "token��������" << endl;
		cout << "���� ����" << endl;
		for (Token* ptr = la->TokenList; ptr != nullptr; ptr = ptr->next) {
			cout << ptr->value << " " << ptr->type << endl;
		}
	}
}
bool LexicalAnalyzerByTS::testId(string input) {
	State state = S0;
	int index = 0;//�����ַ���������
	char curChar = input[index];
	State matrix[3][2] = { S1,error,S2,S2,S2,S2 };//״̬ת������
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
		string word = input.substr(0, index);//��ȡʶ��ĵ���
		insert_List(new Token(ID, word));//���ʷ���token����
		return true;
	}
	else
	{
		return false;
	}
}