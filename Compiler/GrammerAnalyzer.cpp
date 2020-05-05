#include"GrammarSource.h"
void GrammarAnalyzer::initialize() {
	//��ʼ������ʽ�Ҳ�,�ڲ�����Ӵ���С��
	string fileName = "file/expression.txt";
	fstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Could not find the file\n";
		cout << "Program terminating\n";
		exit(EXIT_FAILURE);
	}
	cout << "�ļ��Ѿ���" << endl;	
	string temp;
	string left;//���ʽ��
	string right;//���ʽ�Ҳ�
	string predict;//Ԥ�⼯
	int location;//��¼:��λ��
	int count;//��¼���ʽ��ߡ��ұߡ�Ԥ�⼯�ֱ��ж��ٸ�����
	int rol = 0;//����������104������ʽ�е�λ��
	while (getline(inFile, temp))
	{
		location = temp.find(":");	//��һ��ð��
		left = temp.substr(0, location);//����ʽ��*****��������SNL��Ϊ����ʽ�󲿶���һ������
		expressionLeft[rol].value[0] = left.substr(0, location);
		expressionLeft[rol].count = 1;
		sets_L.insert(left);
		temp = temp.substr(location + 1);//ɾ������ʽ��

		location = temp.find(":");//�ڶ���ð��
		right = temp.substr(0, location);//����ʽ�ұ�
		predict = temp.substr(location + 1);//Ԥ�⼯

		count = 0;
		while (right.size() != 0) {	//����ʽ�Ҳ�
			location = right.find(",");
			expressionRight[rol].value[count] = right.substr(0, location);
			sets_B.insert(right.substr(0, location));
			count++;
			if (location == string::npos)//�Ѿ�û�ж����ˣ�˵����������
				break;
			right = right.substr(location + 1);
		}
		expressionRight[rol].count = count;

		count = 0;	//Ԥ�⼯
		while (predict.size() != 0) {
			location = predict.find(",");
			Predicts->value[count] = predict.substr(0, location);
			count++;
			if (location == string::npos)//�Ѿ�û�ж����ˣ�˵����������
				break;
			predict = predict.substr(location + 1);
		}
		Predicts[rol].count = count;
		rol++;//������һ������ʽ
	}

	for (set<string>::iterator it = sets_B.begin(); it != sets_B.end(); it++)
		if (!sets_L.count(*it))
			sets_R.insert(*it);

	//��ʼ��������
	int nCount = sets_L.size();
	int tCount = sets_R.size()+1;//1��#
	AnalysisTable = new int* [nCount];
	for (int i = 0; i < nCount; i++)
		AnalysisTable[i] = new int[tCount] {0};

	location = 0;//��¼����ʽ����sets�е�λ��
	for (int i = 0; i < expressionNumber; i++)
	{
		location = nLocation(expressionLeft->value[0]);
		if (location == -1) {
			cout << "error" << endl;
			return -1;
		}
		
	}
}


/*
void GrammarAnalyzer::popnCharacter(int expressNumber) {
	Node node = expressionRight[expressNumber - 1];
	for (int i = node.count - 1; i >= 0; i--)
	{
		cout << "��ջ����::" << node.value[i] << endl;
		Stack.push(node.value[i]);
	}
}
*/
int GrammarAnalyzer::nLocation(string st) {
	int location = 0;
	for (set<string>::iterator it = sets_L.begin(); it != sets_L.end(); it++)
		if (st.compare(*it) == 0)
			return location;
		else
			location++;
	return -1;//-1��û�ҵ�
}
int GrammarAnalyzer::tLocation(string st) {
	int location = 0;
	for (set<string>::iterator it = sets_R.begin(); it != sets_R.end(); it++)
		if (st.compare(*it) == 0)
			return location;
		else
			location++;
	return -1;//-1��û�ҵ�
}
/*
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
	return matched;
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
			cout << "ջ1��" << sCharacter << " ";

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
					cout << "toooooooooooooooooooooooooooooooooooooooooo" << currentToken->value << endl;
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
*/