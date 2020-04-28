#pragma once
//��ʶ�����ô�Сд���ڱ��м�һ��
#include<iostream>
#include<string>
using namespace std;
//�﷨���ڵ����
const int child_Count = 5;
const int Identifier_Count = 5;
/******�﷨���ڵ�����***********/
enum NodeKind {
	ProK,PheadK,TypeK,VarK,ProcDeck,StmLK,DecK,StmtK,ExpK
};
//��������,NodeKindȡDecKʱ��Ч
enum Dec {
	ArrayK,CharK,IntegerK,RecordK,IdK
};
//�������,NodeKindȡStmtKʱ��Ч
enum Stmt {
	IfK,WhileK,AssignK,ReadK,WriteK,CallK,ReturnK
};
//���ʽ����,NodeKindȡExpKʱ��Ч
enum Exp {
	OpK,ConstK,IdK
};
/********�﷨���ڵ�ľ�������*******/
union Kind
{
	Dec  dec;
	Stmt stmt;
	Exp  exp;
};
struct TreeNode {
	TreeNode* child[child_Count];	//ָ�����﷨���ڵ�ָ��
	TreeNode* sibling;//ָ���ֵ��﷨���ڵ�ָ��
	int lineno;//��¼Դ�����к�
	NodeKind nodeKind;//��¼�﷨���ڵ�����
	Kind kind;//��¼�﷨���ľ�������
	int idnum;//��¼һ���ڵ��б�ʶ���ĸ���
	string name[Identifier_Count];//�ڵ��б�ʶ������
	void setnodeKind(NodeKind kind) {
		nodeKind = kind;
	}
};
