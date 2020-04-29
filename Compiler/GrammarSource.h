#include<stack>
#include<string>
#include<fstream>
#include"PublicSource.h"
#include<iostream>
using namespace std;
const int nCount = 5;//非终极符的数目
const int tCount = 5 + 1;//终极符的数目
const int expressionNumber = 8;//产生式数量
const int maxValue = 4;//预测集中最大几个元素
struct Node {//节点，代表终结符或非终结符
	int count;	
	string value[maxValue];	
public:
	void out(){
		for (int i = count - 1; i >= 0; i--)
			cout << value[i] << " ";
		cout << endl;
	}		//链表和数组哪个好？？
};
class GrammarAnalyzer {
private:
	stack<string> Stack;//分析栈
	Token* currentToken;
	int AnalysisTable[nCount][tCount] = {0};

	Node expressionLeft[expressionNumber];//产生式左部,,,,,用不到
	Node expressionRight[expressionNumber];		//从大往小用Node
	Node Predicts[expressionNumber];
	string nCharacters[nCount];//非终极符集合
	string tCharacters[tCount];
public:
	GrammarAnalyzer(Token* TokenStart) {
		currentToken = TokenStart;
		Stack.push("#");
		Stack.push("E");
		cout << "初始化" << endl;
	}
	bool GrammarAnalyzers();
	bool match(string sc, string tc);
	bool isNCharacter(string st);
	int nLocation(string st);//非终结符在数组中的位置
	int tLocation(string st);
	void popnCharacter(int expressNumber);
	void initialize();
	void test();
};
