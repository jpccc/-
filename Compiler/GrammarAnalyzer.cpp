#include"GrammarSource.h"
void GrammarAnalyzer::initialize() {
	//��ʼ������ʽ�Ҳ�,�ڲ�����Ӵ���С��
	string fileName ="file/expression.txt";
	fstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Could not find the file\n";
		cout << "Program terminating\n";
		exit(EXIT_FAILURE);
	}
	string temp;
	string left;
	string right;
	int location;
	int count;//����
	int rol = 0;//�����������ʽ����
	while (getline(inFile, temp))
	{
		count = 0;
		location = temp.find(":");
		left = temp.substr(0, location);
		right = temp.substr(location + 1);
		while (right.size() != 0) {
			location = right.find(",");
			expressionRight[rol].value[count] = right.substr(0, location);
			count++;
			if (location == string::npos)
				break;
			right = right.substr(location + 1);
		}
		expressionRight[rol].count = count;
		rol++;
	}

	//��ʼ�����ս��
	nCharacters[0] = "E";
	nCharacters[1] = "E0";
	nCharacters[2] = "T";
	nCharacters[3] = "T0";
	nCharacters[4] = "F";
	//��ʼ���ս��
	tCharacters[0] = "i";
	tCharacters[1] = "+";
	tCharacters[2] = "*";
	tCharacters[3] = "(";
	tCharacters[4] = ")";
	tCharacters[5] = "EOF";
	//��ʼ��������
	AnalysisTable[0][0] = 1;
	AnalysisTable[0][3] = 1;
	AnalysisTable[1][1] = 2;
	AnalysisTable[1][4] = 3;
	AnalysisTable[1][5] = 3;
	AnalysisTable[2][0] = 4;
	AnalysisTable[2][3] = 4;
	AnalysisTable[3][1] = 6;
	AnalysisTable[3][2] = 5;
	AnalysisTable[3][4] = 6;
	AnalysisTable[3][5] = 6;
	AnalysisTable[4][0] = 8;
	AnalysisTable[4][3] = 7;
}
void GrammarAnalyzer::popnCharacter(int expressNumber) {
	Node node = expressionRight[expressNumber-1];
	for (int i = node.count - 1; i >= 0; i--)
	{
		cout << "��ջ����::" << node.value[i] << endl;
		Stack.push(node.value[i]);
	}
}
int GrammarAnalyzer::nLocation(string st) {
	for (int i = 0; i < nCount; i++)
		if (nCharacters[i].compare(st) == 0)
			return i;
}
int GrammarAnalyzer::tLocation(string st) {
	for (int i = 0; i < tCount; i++)
		if (tCharacters[i].compare(st) == 0)
			return i;
	return -1;//-1��û�ҵ�
}
bool GrammarAnalyzer::isNCharacter(string st) {//�Ƿ��Ƿ��ռ���
	bool judge = false;
	for (int i = 0; i < nCount; i++) {
		if (nCharacters[i].compare(st) == 0)
			judge = true;
	}
	return judge;;
}
bool GrammarAnalyzer::match(string sc, string tc)//�жϷ���վ���������е��ռ����Ƿ�ƥ��
{
	bool matched = false;
	if (sc.compare(tc) == 0) {
		matched = true;
	}
	return matched;;
}
bool GrammarAnalyzer::GrammarAnalyzers() {
	string sCharacter;//ջ�з�
	string tCharacter;//��ǰָ��ָ����ռ���
	int xx, yy;//xx�Ƿ��ռ����ڷ������е�����
	int expressNumber;
	while (currentToken != NULL) {
		cout << "����whileѭ��**************************************************************" << endl;
		if (!Stack.empty() && currentToken != NULL)
		{
			sCharacter = Stack.top();
			Stack.pop();
			cout << "ջ1��" << sCharacter<<" ";

			tCharacter = currentToken->value;
			cout << tCharacter << endl;

			if (!isNCharacter(sCharacter)) //���ռ���
			{
				cout << "�����ռ���" << endl;
				if (sCharacter.compare("ID") == 0)
				{//���ռ���ID
					if (currentToken->type != ID) {
						cout << sCharacter << "��" << tCharacter << "��ƥ��" << endl;
						return false;
					}
				}
				else
				{
					if (!match(sCharacter, tCharacter))
					{
						cout << sCharacter << "��" << tCharacter << "��ƥ��" << endl;
						return false;
					}
				}
				currentToken = currentToken->next;
				if (currentToken == NULL)
					cout << "��" << endl;
				else
					cout << "toooooooooooooooooooooooooooooooooooooooooo"<<currentToken->value << endl;
			}
			else
			{
				cout << "������ռ���" << endl;
				xx = nLocation(sCharacter);
				yy = tLocation(tCharacter);
				if (yy == -1) {	//û�ҵ��ռ���
					cout << "û�ҵ��ռ���" << endl;
					return false;
				}
				expressNumber = AnalysisTable[xx][yy];
				cout << "���ʽ���:" << expressNumber << endl;
				if (expressNumber == 0)
				{
					cout << sCharacter << ",,," << tCharacter << endl;
					cout << xx << ",," << yy << endl;;
					cout << "ss_error" << endl;
					return false;
				}
				else
				{
					popnCharacter(expressNumber);	//ѹջ
				}
			}



		}
	}
	return true;
}
void GrammarAnalyzer::test() {
	int i, j;
	for (i = 0; i < nCount; i++)
	{
		for (j = 0; j < tCount; j++)
			cout << AnalysisTable[i][j] << " ";
		cout << endl;
	}

	for (i = 0; i < nCount; i++)
		cout << nCharacters[i] << endl;

	for (i = 0; i < tCount; i++)
		cout << tCharacters[i] << endl;

	for (i = 0; i < expressionNumber; i++)
		expressionRight[i].out();
}