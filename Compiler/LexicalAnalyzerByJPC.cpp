#include"LexicalAnalyzerByJPC.h"
char  LexicalAnalyzerByJPC::readOne(int& count) {
	char letter=input[count];		//���ڼ����жϣ���ֹԽ��
	count++;		//���봮ָ���ƶ�
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
	int count = 0;	//���봮����ָ��
	int iSize = input.size();

	string word = "";//����Ҫ����TokenList�ĵ���
	char NextChar;//�ϴζ�ȡ���ַ�
	char CurrentChar;//��ǰ��ȡ���ַ�

	State judge = S0;//ѡ��ִ����һ����֧
	bool finded = false;//�Ѿ�ʶ����һ������

	TokenType tokenType;//���ʵ�����
	CurrentChar = readOne(count);
	NextChar = CurrentChar;
	while (count <= iSize) {
		switch (judge) {
		case S0:		//��ʼ״̬
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
		case S1:		//��ĸ
			word = word + CurrentChar;		//��ʱCurrentChar�϶�����ĸ
			CurrentChar = readOne(count);
			if (isLetter(CurrentChar)||isNumber(CurrentChar))
			{
				NextChar = CurrentChar;
				break;
			}
			backOne(count, CurrentChar, NextChar);
			if (!isReservedWord(word))				//������? ������0�������Ҳ�������Ϊ��ʶ����
			{
				tokenType = ID;
				insert_List(new Token(tokenType,word));
			}
			else
			{
				tokenType = ReservedWord;
				insert_List(new Token(tokenType, word));
			}
			finded = true;//�ҵ�һ������
			break;
		case S2:		//����
			word = word + CurrentChar;		//��ʱCurrentChar�϶�����ĸ
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
		case S3: //���ַ��ֽ�
			word = word + CurrentChar;
			CurrentChar = readOne(count);
			if (NextChar == '.' && CurrentChar == '.')
			{//����ֽڷ�
				NextChar = CurrentChar;
				word = word + CurrentChar;
				tokenType = ArraySubscript;
				insert_List(new Token(tokenType, word));
				finded = true;
				break;
			}
			backOne(count, CurrentChar, NextChar);
			tokenType = OneCharDelimiter;
			if (CurrentChar == EOF)//������־,countָ����һ��Ҫ����λ��,����������ֵ�ϵ���iSize
			{
				insert_List(new Token(tokenType, "EOF"));
				return;//������
			}
			insert_List(new Token(tokenType,word));
			finded = true;
			break;
		case S4:	//˫�ַ��ֽ�
			word = word + CurrentChar;		//��ʱCurrentChar�϶�����ĸ
			CurrentChar = readOne(count);
			if (CurrentChar == '=') {
				word = word + CurrentChar;
				tokenType = TwoCharDelimiter;
				insert_List(new Token(tokenType, word));
				finded = true;
			}
			else {
				cout << "error,�е��ʴ���" << endl;
				exit(1);
			}
			break;
		case S5:			//ע����ʼ
			while (count < iSize) {
				CurrentChar = readOne(count);
				if (CurrentChar == '}')
				{
					finded = true;
					break;
				}
			}
			break;
		case S6:		//�ַ���ʼ��
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
			judge = S0;	//�ص���ʼ
			word = "";
			finded = false;
		}
	}
}
Token* LexicalAnalyzerByJPC::getToken()
{
	return TokenHead;
}