#include<stack>
#include<string>
#include<fstream>
#include"PublicSource.h"
#include<iostream>
using namespace std;
const int nCount = 5;//���ռ�������Ŀ
const int tCount = 5 + 1;//�ռ�������Ŀ
const int expressionNumber = 8;//����ʽ����
const int maxValue = 4;//Ԥ�⼯����󼸸�Ԫ��
struct Node {//�ڵ㣬�����ս������ս��
	int count;	
	string value[maxValue];	
public:
	void out(){
		for (int i = count - 1; i >= 0; i--)
			cout << value[i] << " ";
		cout << endl;
	}		//����������ĸ��ã���
};
class GrammarAnalyzer {
private:
	stack<string> Stack;//����ջ
	Token* currentToken;
	int AnalysisTable[nCount][tCount] = {0};

	Node expressionLeft[expressionNumber];//����ʽ��,,,,,�ò���
	Node expressionRight[expressionNumber];		//�Ӵ���С��Node
	Node Predicts[expressionNumber];
	string nCharacters[nCount];//���ռ�������
	string tCharacters[tCount];
public:
	GrammarAnalyzer(Token* TokenStart) {
		currentToken = TokenStart;
		Stack.push("#");
		Stack.push("E");
		cout << "��ʼ��" << endl;
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
