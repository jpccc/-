// Compiler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "LexicalAnalyzerByJPC.h"
#include"LexicalAnalyzerByTS.h"
using namespace std;
int main()
{
    //测试
    //LexicalAnalyzerByJPC lexicalAnalyzer;
    //lexicalAnalyzer.makeTokenList("asd2 fi := . char .. '123#");
    //Token* t = lexicalAnalyzer.getToken();
    //cout << "Token序列如下" << endl;
    //while (t != NULL) {
    //    cout << t->value << "  " << t->type << endl;
    //    t = t->next;
    //}
    LexicalAnalyzerByTS::debugging();
}

