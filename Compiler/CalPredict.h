#pragma once
#include<string>
#include<iostream>
#include<fstream>

#include"PublicSource.h"
using namespace std;
class CalPredict//计算产生式
{
private:
	static const string ProductionPath;//保存产生式文件的路径
	static const string ExpressionPath;//保存预测集文件的路径
	int CountProduction;//产生式数目
	Production* Productions;//所有产生式集合
	Symbol** Predict;//每条产生式的Predict集，链表形式
	Symbol** PredictRear;//Predict链表尾指针
	bool isBlank = true;
public:
	CalPredict();
	static void debugging();//调试程序
	void readProductions();//从文件中读入产生式集合
	void calPredict();//根据产生式集合计算Predict集
	void writePredict();//将预测集写入文件
	Production string_to_Production( string str_Prod,char sep);//将读取的一行字符串转为产生式类型
	void getTerminalInfo();//将产生式中的所有symbol类型对象的isTerminal成员变量（判断是否为终极符）修改为正确的，刚读入产生式时全部默认为终极符
	void printProductions();//打印全部产生式
	void insertPredict(int orderNum,Symbol* symbol);//往对应产生式的Predict集里插入符号
	int getCountProduction(ifstream &inFile);//根据文件的行数确定产生式个数
};
