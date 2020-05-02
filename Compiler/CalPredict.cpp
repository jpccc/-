#include "CalPredict.h"
const string CalPredict::ProductionPath = "Debug/file/production.txt";
const string CalPredict::ExpressionPath = "Debug/file/expression.txt";
void CalPredict::readProductions()
{
	ifstream inFile;
    inFile.open(ProductionPath);
    if (!inFile.is_open()) {
        cout << "Could not find the file\n";
        cout << "Program terminating\n";
        exit(EXIT_FAILURE);
    }
    CountProduction = getCountProduction(inFile);
    Productions = new Production[CountProduction];
    Predict = new Symbol * [CountProduction];
    PredictRear = new Symbol * [CountProduction];
    int orderNum = 0;
    while (!inFile.eof()) {
        string str_prod;
		getline(inFile,str_prod);//读取一行产生式字符串
        Productions[orderNum++]=string_to_Production(str_prod,' ');//转为类对象存入数组
    }
    
}

void CalPredict::calPredict()
{
   // if (isblank) {
   //     calFakePredict();//求出带有非终极符的predict集
   // }
   // else {
   //     while (!calFinish()) {//calFinish判断predict集中是否还有非终极符，有则视为计算还未结束
			//killNTsymbol()//将predict集中的非终极符替换为对应终极符，也可视作替换为该非终极符的predict集
   //     }     
   // }
    //  calFakePredict()

	//for (int i = 0; i < CountProduction; i++) {
	//	Production prod = Productions[i];
	//	Symbol* right_first = new Symbol(*prod.Right);//取得右部第一个符号
	//	if (right_first->value != "epsilon") {
	//		insertPredict(i, right_first);
	//	}
	//	else {
	//		Symbol* follow = findFollowSymbol(*prod.Left);//找到该产生式左部符号在其他产生式右部中出现时，在它后续出现的符号，返回链表
	//		insertPredict(i, follow);//将含所有后续符号的链表加入predict集，包括非终极符
	//	}
	//}    
}

void CalPredict::writePredict()
{
}

Production CalPredict::string_to_Production(string str_Prod, char sep)
{
    Production prod;
    int i = 0;
    //获取产生式左部
    for (i = 0; str_Prod[i] !=sep; i++){}
    string str_symbol = str_Prod.substr(0, i);
    str_Prod = str_Prod.substr(i + 1);
    prod.Left = Symbol(str_symbol);
    //丢弃符号“->”
    for (i = 0; str_Prod[i] != sep; i++) {}
    str_Prod = str_Prod.substr(i + 1);
    //获取产生式右部
    for(i=0;i!=str_Prod.length();i++){
        if (str_Prod[i] == sep) {
            str_symbol = str_Prod.substr(0, i);
            str_Prod = str_Prod.substr(i + 1);
            prod.insertRight(new Symbol(str_symbol));
            i = 0;
        }
    }
    //处理最后一个符号
    str_symbol = str_Prod;
    prod.insertRight(new Symbol(str_symbol));
    return prod;
}

void CalPredict::getTerminalInfo()
{
    for (int i = 0; i < CountProduction; i++) {
        Symbol* symbol = &Productions[i].Left;//在左部出现的是非终极符
        symbol->isTerminal = false;
        //该非终极符在右部出现时，也应设置为非终极符
        for (int j = 0; j < CountProduction; j++) {
            Symbol* p=Productions[j].findSymbolInRight(*symbol);
            if (p != nullptr)
                p->isTerminal = false;
        }
    }
}

void CalPredict::printProductions()
{
    for (int i = 0; i < CountProduction; i++) {
        Productions[i].printProduction();        
    }
}

void CalPredict::insertPredict(int orderNum, Symbol* symbol)
{   
    Symbol* rear = PredictRear[orderNum];
    if (rear == nullptr) {
        Symbol* head = Predict[orderNum];
        head = symbol;
        rear = symbol;
        symbol->next = nullptr;
    }
    else {
        rear->next = symbol;
        rear = symbol;
        symbol->next = nullptr;
    }
}

int CalPredict::getCountProduction(ifstream &inFile)
{
    if (!inFile.is_open()) {
        cout << "Could not find the file\n";
        cout << "Program terminating\n";
        exit(EXIT_FAILURE);
    }
    inFile.clear();
    inFile.seekg(0);
    char ch;
    int count=0;
    while (!inFile.eof()) {
        ch = inFile.get();
        if (ch == '\n')
            count++;
    }
    inFile.clear();
    inFile.seekg(0); 
    return ++count;
}

CalPredict::CalPredict()
{
    for (int i = 0; i < CountProduction; i++) {
        Predict[i] = nullptr;
        PredictRear[i] = nullptr;
    }
}

void CalPredict::debugging()
{
    CalPredict* CP = new CalPredict();
    CP->readProductions();
    CP->getTerminalInfo();
    CP->printProductions();
    
}
