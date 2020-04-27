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

	int count = 0;	//���봮����ָ��
	int iSize = input.size();

	string word = "";//����Ҫ����TokenList�ĵ���
	char NextChar;//�ϴζ�ȡ���ַ�
	char CurrentChar;//��ǰ��ȡ���ַ�

	int judge = 0;//ѡ��ִ����һ����֧
	int reserved_Location;//�������ڱ��е�λ��

	bool finded = false;//�Ѿ�ʶ����һ������

	Token* reserved_word = NULL;
	TokenType tokenType = ID;
	CurrentChar = input[count];
	NextChar = CurrentChar;
	count++;		//���봮ָ���ƶ�
	while (count < iSize) {
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
			if (CurrentChar == '#')//������־
			{
				judge = 9;	//	��ʱ�趨
				break;
			}
			break;
		case 1:		//��ĸ
			word = word + CurrentChar;		//��ʱCurrentChar�϶�����ĸ

			CurrentChar = input[count];		//���ڼ����жϣ���ֹԽ��
			count++;		//���봮ָ���ƶ�
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z') || ('0' <= CurrentChar && CurrentChar <= '9'))
			{
				NextChar = CurrentChar;
				break;
			}
			count--;			//���Ǳ�ʶ����Back
			CurrentChar = NextChar;
			reserved_Location = srearch_ReservedWord(word);
			if (reserved_Location == 0)				//������? ������0�������Ҳ�������Ϊ��ʶ����
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
		case 2:		//����
			word = word + CurrentChar;		//��ʱCurrentChar�϶�����ĸ
			CurrentChar = input[count];		//���ڼ����жϣ���ֹԽ��
			count++;		//���봮ָ���ƶ�
			if ('0' <= CurrentChar && CurrentChar <= '9')
			{
				NextChar = CurrentChar;
				break;
			}
			count--;			//���Ǳ�ʶ����Back
			CurrentChar = NextChar;
			reserved_word = new Token();
			tokenType = INTC;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		case 3: //���ַ��ֽ�
			word = word + CurrentChar;

			CurrentChar = input[count];		//���ڼ����жϣ���ֹԽ��
			count++;		//���봮ָ���ƶ�
			if (NextChar == '.' && CurrentChar == '.')
			{
				NextChar = CurrentChar;
				judge = 8;
				break;
			}
			count--;			//���Ǳ�ʶ����Back
			CurrentChar = NextChar;
			reserved_word = new Token();
			tokenType = OneCharDelimiter;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		case 4:	//˫�ַ��ֽ�
			word = word + CurrentChar;		//��ʱCurrentChar�϶�����ĸ
			CurrentChar = input[count];		//���ڼ����жϣ���ֹԽ��
			count++;		//���봮ָ���ƶ�
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
		case 5:			//ע����ʼ
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = CommentHeader;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;

		case 6:		//ע�ͽ���
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = CommentTerminator;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;

		case 7:		//�ַ���ʼ��
			word = word + CurrentChar;
			reserved_word = new Token();
			tokenType = Character;
			reserved_word->type = tokenType;
			reserved_word->value = word;
			reserved_word->next = NULL;
			insert_List(reserved_word);
			finded = true;
			break;
		case 8://�����±���޷�
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
			CurrentChar = input[count];		//���ڼ����жϣ���ֹԽ��
			NextChar = CurrentChar;
			count++;		//���봮ָ���ƶ�
			judge = 0;	//�ص���ʼ
			word = "";
			finded = false;
		}
		if (judge == 9)	//����whileѭ��	
			break;
	}
}
Token* LexicalAnalyzerByJPC::getToken()
{
	return TokenList;
}