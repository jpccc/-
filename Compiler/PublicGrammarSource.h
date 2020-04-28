#pragma once
//标识符采用大小写，在表中加一下
#include<iostream>
#include<string>
using namespace std;
//语法树节点设计
const int child_Count = 5;
const int Identifier_Count = 5;
/******语法树节点类型***********/
enum NodeKind {
	ProK,PheadK,TypeK,VarK,ProcDeck,StmLK,DecK,StmtK,ExpK
};
//声明类型,NodeKind取DecK时有效
enum Dec {
	ArrayK,CharK,IntegerK,RecordK,IdK
};
//语句类型,NodeKind取StmtK时有效
enum Stmt {
	IfK,WhileK,AssignK,ReadK,WriteK,CallK,ReturnK
};
//表达式类型,NodeKind取ExpK时有效
enum Exp {
	OpK,ConstK,IdK
};
/********语法树节点的具体类型*******/
union Kind
{
	Dec  dec;
	Stmt stmt;
	Exp  exp;
};
struct TreeNode {
	TreeNode* child[child_Count];	//指向子语法树节点指针
	TreeNode* sibling;//指向兄弟语法树节点指针
	int lineno;//记录源程序行号
	NodeKind nodeKind;//记录语法树节点类型
	Kind kind;//记录语法树的具体类型
	int idnum;//记录一个节点中标识符的个数
	string name[Identifier_Count];//节点中标识符名字
	void setnodeKind(NodeKind kind) {
		nodeKind = kind;
	}
};
