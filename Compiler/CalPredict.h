#pragma once
#include<string>
#include"PublicSource.h"
using namespace std;
const string CalPredict::ProductionPath = "Debug / file / production.txt";
const string CalPredict::ExpressionPath = "Debug / file / expression.txt";
class CalPredict//计算产生式
{
private:
	static const string ProductionPath;//保存产生式文件的路径
	static const string ExpressionPath;//保存预测集文件的路径
	static const int CountProduction=104;//产生式数目
	Production Productions[CountProduction];//所有产生式集合
	Symbol* Predict[CountProduction];//每条产生式的Predict集，链表形式
public:
	void readProductions();//从文件中读入产生式集合
	void calPredict();//根据产生式集合计算Predict集
	void writePredict();//将预测集写入文件
};

