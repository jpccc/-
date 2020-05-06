#include"PublicSource.h"
using namespace std;
const int expressionNumber = 104;
struct Node {//节点，代表终结符或非终结符
	string value;			
	Node* next;	
	Node* last;
	Node(string st) {
		value = st;
		next = NULL;
		last = NULL;
	}
};
struct Nodes {
	Node* head;
	Node* rear;
	Nodes() {
		head = NULL;
		rear = NULL;
	}
	void insert(Node*p) {
		if (head==NULL)
		{
			head = p;
			rear = p;
		}
		else 
		{
			p->last = rear;
			rear->next = p;
			rear = p;
		}
	}
	Node* getHead() {
		return head;
	}
	Node* getRear() {
		return rear;
	}
};
class GrammarAnalyzer {
private:
	stack<string> Stack;//分析栈
	Token* currentToken;
	int** AnalysisTable;//分析表
	Nodes* expressionLeft[expressionNumber];		//产生式左部
	Nodes* expressionRight[expressionNumber];		//产生式右边
	Nodes* Predicts[expressionNumber];
	set<string> sets_N;
	set<string> sets_T;
	set<string> sets_B;
public:
	GrammarAnalyzer(Token* TokenStart) {
		currentToken = TokenStart;
		for (int i = 0; i < expressionNumber; i++) {
			expressionLeft[i] = new Nodes();
			expressionRight[i] = new Nodes();
			Predicts[i] = new Nodes();
		}
		Stack.push(".");
		Stack.push("Program");
		initialize();
		cout << "初始化语法分析****************************************************************" << endl;
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
