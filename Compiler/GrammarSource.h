#include<stack>
#include<string>
#include<fstream>
#include"PublicSource.h"
#include<iostream>
#include <set>
using namespace std;
const int expressionNumber = 104;

struct Node {//�ڵ㣬�����ս������ս��
	string value;			
	Node next*;
};
class GrammarAnalyzer {
private:
	stack<string> Stack;//����ջ
	Token* currentToken;
	int** AnalysisTable;//������
	Node expressionLeft[expressionNumber];		//����ʽ��
	Node expressionRight[expressionNumber];		//����ʽ�ұߣ��Ӵ���С��Node
	Node Predicts[expressionNumber];
	set<string> sets_L;
	set<string> sets_R;
	set<string> sets_B;
public:
	GrammarAnalyzer(Token* TokenStart) {
		currentToken = TokenStart;
		Stack.push("EOF");
		Stack.push("Program");
		cout << "��ʼ��" << endl;
	}
	//bool GrammarAnalyzers();
	//bool match(string sc, string tc);
	//bool isNCharacter(string st);
	int nLocation(string st);//���ս���������е�λ��
	int tLocation(string st);
	//void popnCharacter(int expressNumber);
	void initialize();
	//void test();
};
