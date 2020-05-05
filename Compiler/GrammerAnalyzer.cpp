#include"GrammarSource.h"
void GrammarAnalyzer::initialize() {
	//初始化产生式右部,内部数组从大往小用
	string fileName = "file/expression.txt";
	fstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Could not find the file\n";
		cout << "Program terminating\n";
		exit(EXIT_FAILURE);
	}
	cout << "文件已经打开" << endl;	
	string temp;
	string left;//表达式左部
	string right;//表达式右部
	string predict;//预测集
	int location;//记录:的位置
	int count;//记录表达式左边、右边、预测集分别有多少个符号
	int rol = 0;//行数，即在104个产生式中的位置
	while (getline(inFile, temp))
	{
		location = temp.find(":");	//第一个冒号
		left = temp.substr(0, location);//产生式左部*****这样做是SNL因为产生式左部都是一个符号
		expressionLeft[rol].value[0] = left.substr(0, location);
		expressionLeft[rol].count = 1;
		sets_L.insert(left);
		temp = temp.substr(location + 1);//删除产生式左部

		location = temp.find(":");//第二个冒号
		right = temp.substr(0, location);//产生式右边
		predict = temp.substr(location + 1);//预测集

		count = 0;
		while (right.size() != 0) {	//产生式右部
			location = right.find(",");
			expressionRight[rol].value[count] = right.substr(0, location);
			sets_B.insert(right.substr(0, location));
			count++;
			if (location == string::npos)//已经没有逗号了，说明处理完了
				break;
			right = right.substr(location + 1);
		}
		expressionRight[rol].count = count;

		count = 0;	//预测集
		while (predict.size() != 0) {
			location = predict.find(",");
			Predicts->value[count] = predict.substr(0, location);
			count++;
			if (location == string::npos)//已经没有逗号了，说明处理完了
				break;
			predict = predict.substr(location + 1);
		}
		Predicts[rol].count = count;
		rol++;//处理下一个产生式
	}

	for (set<string>::iterator it = sets_B.begin(); it != sets_B.end(); it++)
		if (!sets_L.count(*it))
			sets_R.insert(*it);

	//初始化分析表
	int nCount = sets_L.size();
	int tCount = sets_R.size()+1;//1是#
	AnalysisTable = new int* [nCount];
	for (int i = 0; i < nCount; i++)
		AnalysisTable[i] = new int[tCount] {0};

	location = 0;//记录产生式左部在sets中的位置
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
		cout << "入栈操作::" << node.value[i] << endl;
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
	return -1;//-1即没找到
}
int GrammarAnalyzer::tLocation(string st) {
	int location = 0;
	for (set<string>::iterator it = sets_R.begin(); it != sets_R.end(); it++)
		if (st.compare(*it) == 0)
			return location;
		else
			location++;
	return -1;//-1即没找到
}
/*
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
	return matched;
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
			cout << "栈1：" << sCharacter << " ";

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
					cout << "toooooooooooooooooooooooooooooooooooooooooo" << currentToken->value << endl;
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
*/