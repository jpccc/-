// Compiler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include<fstream>
#include "LexicalAnalyzerByJPC.h"
#include"LexicalAnalyzerByTS.h"
#include"GrammarSource.h"
using namespace std;
void ReadChar(string fileName, string& input);
int main()
{
    /********************************读入源程序********************************/
    string filename = "file/test1.txt";//debug目录下
    string input;//存储源程序
    ReadChar(filename, input);
    /***********************词法分析返回Token序列,注释直接丢弃****************/
    LexicalAnalyzerByJPC lexicalAnalyzer(input);
    lexicalAnalyzer.makeTokenList();
    Token* t = lexicalAnalyzer.getToken();
    Token* start = t;
    
    cout << "Token序列如下" << endl;
    while (t!= NULL) {
        cout << t->value << "  " << t->type << endl;
        t = t->next;
    }
    /********************************语法分析********************************/

    GrammarAnalyzer grammarAnalyzer(start);
    grammarAnalyzer.initialize();
    //grammarAnalyzer.test();
    if(grammarAnalyzer.GrammarAnalyzers())
        cout << "语法分析成功" << endl;
    else
        cout << "语法分析失败" << endl;
}
void ReadChar(string fileName,string& input) {
    fstream inFile;
    char c;
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cout << "Could not find the file\n";
        cout << "Program terminating\n";
        exit(EXIT_FAILURE);
    }
    inFile >> noskipws;
    inFile >> c;
    while (!inFile.eof()) {
        if (inFile.good()) {
            input.append(1,c);
            inFile >> c;
        }
    }
    inFile.close();
    input.append(1, EOF);
}
