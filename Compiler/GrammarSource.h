#include"PublicSource.h"
using namespace std;
const int expressionNumber = 104;
struct Node {//�ڵ㣬�����ս������ս��
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
	stack<string> Stack;//����ջ
	Token* currentToken;
	int** AnalysisTable;//������
	Nodes* expressionLeft[expressionNumber];		//����ʽ��
	Nodes* expressionRight[expressionNumber];		//����ʽ�ұ�
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
		cout << "��ʼ���﷨����****************************************************************" << endl;
	}
	bool GrammarAnalyzers();
	bool match(string sc, string tc);
	bool isNCharacter(string st);
	int nLocation(string st);//���ս���������е�λ��
	int tLocation(string st);
	void popnCharacter(int expressNumber);
	void initialize();
	void test();
};
