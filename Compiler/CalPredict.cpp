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
    history = new Symbol * [CountProduction];
    TruePredict = new bool[CountProduction];
    for (int i = 0; i < CountProduction; i++) {
        Predict[i] = nullptr;
        PredictRear[i] = nullptr;
        history[i] = nullptr;
        TruePredict[i] = false;
    }
    int orderNum = 0;
    while (!inFile.eof()) {
        string str_prod;
		getline(inFile,str_prod);//读取一行产生式字符串
        Productions[orderNum++]=string_to_Production(str_prod,' ');//转为类对象存入数组
    }
    getTerminalInfo();
}

void CalPredict::calPredict()
{
    //初始化，全部清空
    for (int i = 0; i < CountProduction; i++) {
        Predict[i] = nullptr;
        PredictRear[i] = nullptr;
        history[i] = nullptr;
        TruePredict[i] = false;
    }
	calFakePredict();//求出带有非终极符的predict集
    setTruePredict();
	while (!calFinish()) {//从unFinishNum开始查找predict集中是否还有非终极符，有则unFinishNum赋值为第一条被发现有非终极符的产生式
        killNTsymbol();//将predict集中的非终极符替换为对应终极符，也可视作替换为该非终极符的predict集 		
	}
}

void CalPredict::calFakePredict()
{
    for (int i = 0; i < CountProduction; i++) {
    	Production prod = Productions[i];
    	Symbol* right_first = prod.Right;//取得右部第一个符号
    	if (right_first->value != "epsilon") {            
    		insertPredict(i,new Symbol(*right_first));
            while (canBeEpsilon(*right_first)&&(right_first->next!=nullptr)) {
                insertPredict(i, new Symbol(*right_first->next));
                right_first = right_first->next;
            }
            if (canBeEpsilon(*right_first)&&(right_first->next == nullptr)) {
                insertFollowSymbol(i, prod.Left);//将所有左部符号的后续符号加入predict集，包括非终极符
            }
    	}
    	else {
            insertFollowSymbol(i,prod.Left);//将所有左部符号的后续符号加入predict集，包括非终极符
    	}
        cout << "FakePredict" << i << "=";
        printPredict(i);
        cout << endl;
    }    
}

void CalPredict::writePredict()
{
    ofstream outFile;
    outFile.open(ExpressionPath);
    if (!outFile.is_open()) {
        cout << "Could not find the file\n";
        cout << "Program terminating\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < CountProduction; i++) {
        outFile << Productions[i].Left.value;
        outFile << ":";
        Symbol* p = Productions[i].Right;
        outFile << p->value;
        p = p->next;
        while (p != nullptr) {
            outFile <<","<< p->value;
            p = p->next;
        }
        outFile<< ":";
        p = Predict[i];
        outFile << p->value;
        p = p->next;
        while (p != nullptr) {
            outFile << "," << p->value;
            p = p->next;
        }
        outFile << endl;
    }
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
            vector<Symbol*>* v=Productions[j].findSymbolInRight(*symbol);
            if (v == nullptr)
                continue;
            for (int i = 0; i < v->size(); i++) {
                v->at(i)->isTerminal = false;
            }
        }
    }
}

void CalPredict::printProductions()
{
    for (int i = 0; i < CountProduction; i++) {
        Productions[i].printProduction();        
    }
}

void CalPredict::printPredict(int orderNum)
{
    Symbol* p = Predict[orderNum];
    if (p == nullptr) {
        cout << "null";
        return;
    }      
    while (p->next != nullptr) {
        cout << p->value << ",";
        p = p->next;
    }
    cout << p->value;

}

void CalPredict::printPredicts()
{
    for (int i = 0; i < CountProduction; i++) {
        cout << i << " ";
        Productions[i].printProduction();
        cout << ":";
        printPredict(i);
        cout << endl;
    }
}

void CalPredict::insertPredict(int orderNum, Symbol* symbol)
{   
    Symbol*& rear = PredictRear[orderNum];
    if (rear == nullptr) {
        Predict[orderNum]= symbol;
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

void CalPredict::insertFollowSymbol(int orderNum,Symbol symbol)
{
    if (inHistory(history,orderNum,symbol)) {
        return;
    }
    else {
        insertHistory(history, orderNum, symbol);
    }
	for (int i = 0; i < CountProduction; i++) {        
        vector<Symbol*>* v = Productions[i].findSymbolInRight(symbol);//在产生式右部找到该符号
        if (v ==nullptr)
            continue;
        for (int j = 0; j < v->size(); j++) {
            Symbol* p = v->at(j);
            if (p->next != nullptr) {
				if (findInPredict(orderNum, *(p->next)) == nullptr) {
					insertPredict(orderNum, new Symbol(*(p->next)));//有后继符号直接插入
                    
				}
			}
			else {
				if (!Productions[i].Left.value.compare(Productions[orderNum].Left.value))
					continue;
				insertFollowSymbol(orderNum, Productions[i].Left);//已经是右部最后一个符号，插入该产生式左部的后续符号
                continue;
			}
            p = p->next; 
			while (canBeEpsilon(*p) && (p->next != nullptr)) {
				insertPredict(orderNum, new Symbol(*(p->next)));
				p = p->next;
			}
			if (canBeEpsilon(*p) && (p->next == nullptr)) {
				insertFollowSymbol(orderNum, Productions[i].Left);//将所有左部符号的后续符号加入predict集，包括非终极符
			}
			
        }      
	}
}

bool CalPredict::inHistory(Symbol** history, int orderNum, Symbol symbol)
{
    Symbol* p = history[orderNum];
    bool result = false;
    while (p != nullptr) {
        if (!p->value.compare(symbol.value)) {
            result = true;
            break;
        }
        p = p->next;
    }
    return result;
}

void CalPredict::insertHistory(Symbol** history, int orderNum, Symbol symbol)
{
    Symbol*& head = history[orderNum];
    Symbol* p = head;
    if (head == nullptr) {
        head = new Symbol(symbol);
        head->next = nullptr;
    }
    else {
        while (p->next != nullptr) { p = p->next; }
        p->next = new Symbol(symbol);
        p->next->next = nullptr;
    }

}

Symbol* CalPredict::findInPredict(int orderNum, Symbol symbol)
{
    Symbol* p = Predict[orderNum];
    while (p != nullptr) {
        if (!p->value.compare(symbol.value)) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

bool CalPredict::calFinish()
{
    for (int i = 0; i < CountProduction; i++) {
        if (!TruePredict[i]) {
            return false;
        }
    }
    return true;
}

void CalPredict::killNTsymbol()
{
    for (int i = 0; i < CountProduction; i++) {
		Symbol* p = Predict[i];
        vector<Symbol*>* NTsymbols=new vector<Symbol*>(0);
		while (p != nullptr) {
			if (!p->isTerminal) {
                NTsymbols->push_back(p);
			}
			p = p->next;
		}
        if (NTsymbols->size() > 0) {
            for (int j = 0; j < NTsymbols->size(); j++) {
				vector<int>* v = isTruePredict(*(NTsymbols->at(j)));//该符号为左部的产生式的predict集是否不包含非终极符，是则返回产生式序号的链表，否则返回空
				if (v != nullptr) {
					replaceNT(*(NTsymbols->at(j)), v);//在所有产生式的predict集中替换掉该非终极符					
				}
            }			
        }
    }  
    setTruePredict();//更新TruePredict
}

bool CalPredict::isTruePredict(int orderNum)
{
    Symbol* p = Predict[orderNum];
    while (p != nullptr) {
        if (!p->isTerminal) {
            return false;
        }
        p = p->next;
    }
    return true;
}

void CalPredict::setTruePredict()
{
    for (int i = 0; i < CountProduction; i++) {
        if (isTruePredict(i)) {
            TruePredict[i] = true;
        }
    }
}

vector<int>* CalPredict::isTruePredict(Symbol symbol)
{ 
    vector<int>* v=new vector<int>(0);
    int* head = nullptr;
	for (int i = 0; i < CountProduction; i++) {
		if (!Productions[i].Left.value.compare(symbol.value)) {
			if (!TruePredict[i]) {
                return nullptr;
            }
            else {
                v->push_back(i);
            }
		}
	}
    return v;
}

void CalPredict::replaceNT(Symbol symbol, vector<int>* v)
{
    for (int i = 0; i < CountProduction; i++) {
        Symbol* NTsymbol =findInPredict(i,symbol) ;
        if (NTsymbol!=nullptr) {
            removePredict(i,NTsymbol);//删除predict集中符号
            for (int j = 0; j < v->size(); j++) {
                if (!Productions[(*v)[j]].Right->value.compare("epsilon")) {
                    continue;
                }
                Symbol* p = Predict[(*v)[j]];
                while (p != nullptr) {
                    if(findInPredict(i,*p)==nullptr)
                        insertPredict(i, new Symbol(*p));
                    p = p->next;
                }
            }
        }
    }
}

void CalPredict::removePredict(int orderNum, Symbol* symbol)
{
    Symbol* last = Predict[orderNum];
    if (symbol == Predict[orderNum]) {
        Predict[orderNum] = Predict[orderNum]->next;
        last = nullptr;
    }
    else {
		while (last->next != symbol && last != nullptr) {
			last = last->next;
		}
        last->next = symbol->next;
    }	
    if (symbol == PredictRear[orderNum]) {
            PredictRear[orderNum] = last;
    }	
	delete(symbol);
}

bool CalPredict::canBeEpsilon(Symbol symbol)
{
    for (int i = 0; i < CountProduction; i++) {
        if (!Productions[i].Left.value.compare(symbol.value)) {
            if (!Productions[i].Right->value.compare("epsilon")) {
                return true;
            }
        }
    }
    return false;
}

CalPredict::CalPredict()
{

}

void CalPredict::debugging()
{
    CalPredict* CP = new CalPredict();
    CP->readProductions();
    CP->calPredict();
    CP->printPredicts();
    CP->writePredict();
}
