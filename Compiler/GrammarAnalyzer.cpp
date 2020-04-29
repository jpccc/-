#include"GrammarSource.h"
void GrammarAnalyzer::initialize() {
	//初始化产生式右部,内部数组从大往小用
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
	int count;//个数
	int rol = 0;//行数，即表达式个数
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

	//初始化非终结符
	nCharacters[0] = "E";
	nCharacters[1] = "E0";
	nCharacters[2] = "T";
	nCharacters[3] = "T0";
	nCharacters[4] = "F";
	//初始化终结符
	tCharacters[0] = "i";
	tCharacters[1] = "+";
	tCharacters[2] = "*";
	tCharacters[3] = "(";
	tCharacters[4] = ")";
	tCharacters[5] = "EOF";
	//初始化分析表
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
		cout << "入栈操作::" << node.value[i] << endl;
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
	return -1;//-1即没找到
}
bool GrammarAnalyzer::isNCharacter(string st) {//是否是非终极符
	bool judge = false;
	for (int i = 0; i < nCount; i++) {
		if (nCharacters[i].compare(st) == 0)
			judge = true;
	}
	return judge;;
}
bool GrammarAnalyzer::match(string sc, string tc)//判断分析站和输入流中的终极符是否匹配
{
	bool matched = false;
	if (sc.compare(tc) == 0) {
		matched = true;
	}
	return matched;;
}
bool GrammarAnalyzer::GrammarAnalyzers() {
	string sCharacter;//栈中符
	string tCharacter;//当前指针指向的终极符
	int xx, yy;//xx是非终极符在分析表中的坐标
	int expressNumber;
	while (currentToken != NULL) {
		cout << "进入while循环**************************************************************" << endl;
		if (!Stack.empty() && currentToken != NULL)
		{
			sCharacter = Stack.top();
			Stack.pop();
			cout << "栈1：" << sCharacter<<" ";

			tCharacter = currentToken->value;
			cout << tCharacter << endl;

			if (!isNCharacter(sCharacter)) //是终极符
			{
				cout << "进入终极符" << endl;
				if (sCharacter.compare("ID") == 0)
				{//是终极符ID
					if (currentToken->type != ID) {
						cout << sCharacter << "与" << tCharacter << "不匹配" << endl;
						return false;
					}
				}
				else
				{
					if (!match(sCharacter, tCharacter))
					{
						cout << sCharacter << "与" << tCharacter << "不匹配" << endl;
						return false;
					}
				}
				currentToken = currentToken->next;
				if (currentToken == NULL)
					cout << "空" << endl;
				else
					cout << "toooooooooooooooooooooooooooooooooooooooooo"<<currentToken->value << endl;
			}
			else
			{
				cout << "进入非终极符" << endl;
				xx = nLocation(sCharacter);
				yy = tLocation(tCharacter);
				if (yy == -1) {	//没找到终极符
					cout << "没找到终极符" << endl;
					return false;
				}
				expressNumber = AnalysisTable[xx][yy];
				cout << "表达式编号:" << expressNumber << endl;
				if (expressNumber == 0)
				{
					cout << sCharacter << ",,," << tCharacter << endl;
					cout << xx << ",," << yy << endl;;
					cout << "ss_error" << endl;
					return false;
				}
				else
				{
					popnCharacter(expressNumber);	//压栈
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