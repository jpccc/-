#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>

#include"PublicSource.h"
using namespace std;
struct LinkListPoints {//链表首尾指针
	Symbol* head;
	Symbol* rear;
	LinkListPoints(Symbol* head, Symbol* rear) {
		this->head = head;
		this->rear = rear;
	}
};
struct OrderNum {
	int num;
	OrderNum* next;
};
class CalPredict//计算产生式
{
private:
	static const string ProductionPath;//保存产生式文件的路径
	static const string ExpressionPath;//保存预测集文件的路径
	int CountProduction;//产生式数目
	Production* Productions;//所有产生式集合
	Symbol** Predict;//每条产生式的Predict集，链表形式
	bool* TruePredict;//标记predict集是否已经不包含非终极符
	Symbol** PredictRear;//Predict链表尾指针	
	Symbol** history;//每个产生式创建一个链表用于保存操作记录，防止多次对同一个产生式插入同个符号的后续符号(insertFollowSymbol函数专用)
public:
	CalPredict();
	static void debugging();//调试程序
	void readProductions();//从文件中读入产生式集合
	void calPredict();//根据产生式集合计算Predict集
	void calFakePredict();//求出带有非终极符的predict集
	void writePredict();//将预测集写入文件
	Production string_to_Production( string str_Prod,char sep);//将读取的一行字符串转为产生式类型
	void getTerminalInfo();//将产生式中的所有symbol类型对象的isTerminal成员变量（判断是否为终极符）修改为正确的，刚读入产生式时全部默认为终极符
	
	void printProductions();//打印全部产生式
	void printPredict(int orderNum);//打印单条产生式的predict集
	void printPredicts();//打印全部predict集
	
	void insertPredict(int orderNum,Symbol* symbol);//往对应产生式的Predict集里插入符号
	void insertPredict(int orderNum, LinkListPoints llp);//往对应产生式的Predict集里插入符号链表,参数llp为首尾指针
	int getCountProduction(ifstream &inFile);//根据文件的行数确定产生式个数
	void insertFollowSymbol(int i,Symbol symbol);//将该符号的后续符号加入对应产生式的predict集，包括非终极符
	bool inHistory(Symbol** history, int orderNum, Symbol symbol);//判断是否在操作记录中(insertFollowSymbol函数专用)
	void insertHistory(Symbol** history, int orderNum, Symbol symbol);//插入操作记录链表(insertFollowSymbol函数专用)
	Symbol* findInPredict(int orderNum, Symbol symbol);//判断符号是否在对应predict集里
	bool calFinish();//判断predict集中是否还有非终极符
	void killNTsymbol();//将predict集中的非终极符替换为对应终极符，也可视作替换为该非终极符的predict集
	bool isTruePredict(int orderNum);//判断是否为不包含非终极符的predict集
	void setTruePredict();//判断所有predict集是否不包含非终极符的信息，结果存入数组
	vector<int>* isTruePredict(Symbol symbol);//该符号为左部的产生式的predict集是否不包含非终极符，是则返回产生式序号的vector，否则返回空
	void replaceNT(Symbol symbol, vector<int>* v);//在所有产生式的predict集中替换掉该非终极符
	void removePredict(int orderNum, Symbol* symbol);//删除predict集中符号
};
