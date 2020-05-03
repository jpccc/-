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
		getline(inFile,str_prod);//��ȡһ�в���ʽ�ַ���
        Productions[orderNum++]=string_to_Production(str_prod,' ');//תΪ������������
    }
    getTerminalInfo();
}

void CalPredict::calPredict()
{
    //��ʼ����ȫ�����
    for (int i = 0; i < CountProduction; i++) {
        Predict[i] = nullptr;
        PredictRear[i] = nullptr;
        history[i] = nullptr;
        TruePredict[i] = false;
    }
	calFakePredict();//������з��ռ�����predict��
    setTruePredict();
	while (!calFinish()) {//��unFinishNum��ʼ����predict�����Ƿ��з��ռ���������unFinishNum��ֵΪ��һ���������з��ռ����Ĳ���ʽ
        killNTsymbol();//��predict���еķ��ռ����滻Ϊ��Ӧ�ռ�����Ҳ�������滻Ϊ�÷��ռ�����predict�� 		
	}
}

void CalPredict::calFakePredict()
{
    for (int i = 0; i < CountProduction; i++) {
    	Production prod = Productions[i];
    	Symbol* right_first = new Symbol(*prod.Right);//ȡ���Ҳ���һ������
    	if (right_first->value != "epsilon") {            
    		insertPredict(i, right_first);
    	}
    	else {
            insertFollowSymbol(i,prod.Left);//�������󲿷��ŵĺ������ż���predict�����������ռ���
    	}
        cout << "FakePredict" << i << "=";
        printPredict(i);
        cout << endl;
    }    
}

void CalPredict::writePredict()
{
}

Production CalPredict::string_to_Production(string str_Prod, char sep)
{
    Production prod;
    int i = 0;
    //��ȡ����ʽ��
    for (i = 0; str_Prod[i] !=sep; i++){}
    string str_symbol = str_Prod.substr(0, i);
    str_Prod = str_Prod.substr(i + 1);
    prod.Left = Symbol(str_symbol);
    //�������š�->��
    for (i = 0; str_Prod[i] != sep; i++) {}
    str_Prod = str_Prod.substr(i + 1);
    //��ȡ����ʽ�Ҳ�
    for(i=0;i!=str_Prod.length();i++){
        if (str_Prod[i] == sep) {
            str_symbol = str_Prod.substr(0, i);
            str_Prod = str_Prod.substr(i + 1);
            prod.insertRight(new Symbol(str_symbol));
            i = 0;
        }
    }
    //�������һ������
    str_symbol = str_Prod;
    prod.insertRight(new Symbol(str_symbol));
    return prod;
}

void CalPredict::getTerminalInfo()
{
    for (int i = 0; i < CountProduction; i++) {
        Symbol* symbol = &Productions[i].Left;//���󲿳��ֵ��Ƿ��ռ���
        symbol->isTerminal = false;
        //�÷��ռ������Ҳ�����ʱ��ҲӦ����Ϊ���ռ���
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

void CalPredict::insertPredict(int orderNum, LinkListPoints llp)
{
 /*   Symbol* addHead = llp.head;
    Symbol* addRear = llp.rear;
    Symbol* rear = PredictRear[orderNum];
    if (rear == nullptr) {
        Symbol* head = Predict[orderNum];
        head = addHead;
        rear = addRear;
        addRear->next = nullptr;
    }
    else {
        rear->next = addHead;
        rear = addRear;
        addRear->next = nullptr;
    }*/
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
    cout << "insertFollow " << orderNum << "," << symbol.value<<endl;
	for (int i = 0; i < CountProduction; i++) {        
		Symbol* p = Productions[i].findSymbolInRight(symbol);//�ڲ���ʽ�Ҳ��ҵ��÷���
        if (p == nullptr)
            continue;
        if (p->next != nullptr) {
            if (findInPredict(orderNum, *p->next)==nullptr) {
				insertPredict(orderNum, new Symbol(*p->next));//�к�̷���ֱ�Ӳ���
            }            
        }
        else {
            if (!Productions[i].Left.value.compare(Productions[orderNum].Left.value))
                continue;
            insertFollowSymbol(orderNum, Productions[i].Left);//�Ѿ����Ҳ����һ�����ţ�����ò���ʽ�󲿵ĺ�������
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
        vector<Symbol*>* NTsymbols=new vector<Symbol*>();
		while (p != nullptr) {
			if (!p->isTerminal) {
                NTsymbols->push_back(p);
			}
			p = p->next;
		}
        if (NTsymbols->size() > 0) {
            for (int j = 0; j < NTsymbols->size(); j++) {
				vector<int>* v = isTruePredict(*(NTsymbols->at(j)));//�÷���Ϊ�󲿵Ĳ���ʽ��predict���Ƿ񲻰������ռ��������򷵻ز���ʽ��ŵ��������򷵻ؿ�
				if (v != nullptr) {
					replaceNT(*(NTsymbols->at(j)), v);//�����в���ʽ��predict�����滻���÷��ռ���					
				}
            }			
        }
    }  
    setTruePredict();//����TruePredict
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
    vector<int>* v=new vector<int>();
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
            removePredict(i,NTsymbol);//ɾ��predict���з���
            for (int j = 0; j < v->size(); j++) {
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
    cout << Predict[orderNum] << " " << PredictRear[orderNum] << endl;
	delete(symbol);
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
}
