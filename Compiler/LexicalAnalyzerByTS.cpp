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

	int count = 0;	//���봮����ָ��
	unsigned int iSize = input.size();

	string word = "";//����Ҫ����TokenList�ĵ���
	char NextChar;//�ϴζ�ȡ���ַ�
	char CurrentChar;//��ǰ��ȡ���ַ�

	int judge = 0;//ѡ��ִ����һ����֧
	int reserved_Location;//�������ڱ��е�λ��

	while (count < iSize) {
		CurrentChar = input[count];
		NextChar = CurrentChar;
		count++;		//���봮ָ���ƶ�

		switch (judge) {
		case 0:		//��ʼ״̬
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
			judge = 3;//��������ʱ����
			if (CurrentChar = '#')//������־
			{
				judge = 10;	//	��ʱ�趨
				break;
			}
			break;
		case 1:		//��ĸ
			CurrentChar = input[count];		//���ڼ����жϣ���ֹԽ��
			count++;		//���봮ָ���ƶ�
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z') || ('0' <= CurrentChar && CurrentChar <= '9'))
			{
				word = word + CurrentChar;//ƴ��
				NextChar = CurrentChar;
				break;
			}
			count--;			//���Ǳ�ʶ����Back
			CurrentChar = NextChar;
			reserved_Location = srearch_ReservedWord(word);
			if (reserved_Location == 0)				//������? ������0�������Ҳ�������Ϊ��ʶ����
			{
				Token* reserved_word = new Token();
				reserved_word->type = 2;
				reserved_word->value = word;
				reserved_word->next = NULL;
			}

			break;
		case 2:		//����

			break;
		}

		if (judge == 10)	//����whileѭ��	
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
	 cout << "�����ַ���" << endl;
	 cin >> input;
	 input.append("#");
	 cout << "��������" << input << endl;
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
		cout << "ʶ��ɹ�" << endl;
	}
	else
	{
		cout << "ʶ�����" << endl;
	}
}