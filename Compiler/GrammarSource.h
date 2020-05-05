#include<stack>
#include<string>
#include<fstream>
#include"PublicSource.h"
#include<iostream>
#include <set>
using namespace std;
const int expressionNumber = 104;

struct Node {//节点，代表终结符或非终结符
	string value;			
	Node next*;
};
class GrammarAnalyzer {
private:
	stack<string> Stack;//分析栈
	Token* currentToken;
	int** AnalysisTable;//分析表
	Node expressionLeft[expressionNumber];		//产生式左部
	Node expressionRight[expressionNumber];		//产生式右边，从大往小用Node
	Node Predicts[expressionNumber];
	set<string> sets_L;
	set<string> sets_R;
	set<string> sets_B;
public:
	GrammarAnalyzer(Token* TokenStart) {
		currentToken = TokenStart;
		Stack.push("EOF");
		Stack.push("Program");
		cout << "初始化" << endl;
	}
	//bool GrammarAnalyzers();
	//bool match(string sc, string tc);
	//bool isNCharacter(string st);
	int nLocation(string st);//非终结符在数组中的位置
	int tLocation(string st);
	//void popnCharacter(int expressNumber);
	void initialize();
	//void test();
};
