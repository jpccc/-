#include"GrammarSource.h"
void GrammarAnalyzer::initialize() {
	string fileName = "file/expression.txt";
	fstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Could not find the file\n";
		cout << "Program terminating\n";
		exit(EXIT_FAILURE);
	}

	string temp;//����ʽ
	string left;//���ʽ��
	string right;//���ʽ�Ҳ�
	string predict;//Ԥ�⼯
	int location;//��¼:��λ��
	int rol = 0;//����������104������ʽ�е�λ��
	while (getline(inFile, temp))
	{
		location = temp.find(":");	//��һ��ð��
		left = temp.substr(0, location);//����ʽ��*****��������SNL��Ϊ����ʽ�󲿶���һ������
		expressionLeft[rol]->insert(new Node(left));
		sets_N.insert(left);
		temp = temp.substr(location + 1);//ɾ������ʽ��

		location = temp.find(":");//�ڶ���ð��
		right = temp.substr(0, location);//����ʽ�ұ�
		predict = temp.substr(location + 1);//Ԥ�⼯

		while (right.size() != 0) {	//����ʽ�Ҳ�
			location = right.find(",");
			expressionRight[rol]->insert(new Node(right.substr(0, location)));
			sets_B.insert(right.substr(0, location));
			if (location == string::npos)//�Ѿ�û�ж����ˣ�˵����������
				break;
			right = right.substr(location + 1);
		}	
    	//Ԥ�⼯
		while (predict.size() != 0) {
			location = predict.find(",");
			Predicts[rol]->insert(new Node(predict.substr(0, location)));
			if (location == string::npos)//�Ѿ�û�ж����ˣ�˵����������
				break;
			predict = predict.substr(location + 1);
		}
		rol++;//������һ������ʽ		
	}

	for (set<string>::iterator it = sets_B.begin(); it != sets_B.end(); it++)
		if (!sets_N.count(*it))
			sets_T.insert(*it);
	//��ʼ��������
	sets_T.insert("EOF");
	int nCount = sets_N.size();
	int tCount = sets_T.size();//1��#
	AnalysisTable = new int* [nCount];
	for (int i = 0; i < nCount; i++)
		AnalysisTable[i] = new int[tCount] {0};
	int x, y;
	for (int i = 0; i < expressionNumber; i++) {
		Node* node_N=expressionLeft[i]->getHead();
		Node* node_P = Predicts[i]->getHead();
		x = nLocation(node_N->value);
		while (node_P != NULL) {
			y = tLocation(node_P->value);
			AnalysisTable[x][y] = i+1;
			node_P = node_P->next;
		}
	}
}
void GrammarAnalyzer::popnCharacter(int expressNumber) {
	Nodes* node = expressionRight[expressNumber - 1];
	Node* nodes = node->getRear();
	while(nodes!=NULL){
		cout << "ѹջ:" << nodes->value << "	";
		Stack.push(nodes->value);
		nodes = nodes->last;
	}
	cout << endl;
}
int GrammarAnalyzer::nLocation(string st) {
	int location = 0;
	for (set<string>::iterator it = sets_N.begin(); it != sets_N.end(); it++)
		if (st.compare(*it) == 0)
			return location;
		else
			location++;
	return -1;//-1��û�ҵ�
}
int GrammarAnalyzer::tLocation(string st) {
	int location = 0;
	for (set<string>::iterator it = sets_T.begin(); it != sets_T.end(); it++)
		if (st.compare(*it) == 0)
			return location;
		else
			location++;
	return -1;//-1��û�ҵ�
}
bool GrammarAnalyzer::isNCharacter(string st) {//�Ƿ��Ƿ��ռ���
	bool judge = false;
	for (set<string>::iterator it = sets_N.begin(); it != sets_N.end(); it++)
		if (st.compare(*it) == 0)
			judge = true;
	return judge;
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
				cout << "xy" << xx << "," << yy << endl;
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
}