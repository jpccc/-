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
		getline(inFile,str_prod);//��ȡһ�в���ʽ�ַ���
        Productions[orderNum++]=string_to_Production(str_prod,' ');//תΪ������������
    }
    
}

void CalPredict::calPredict()
{
   // if (isblank) {
   //     calFakePredict();//������з��ռ�����predict��
   // }
   // else {
   //     while (!calFinish()) {//calFinish�ж�predict�����Ƿ��з��ռ�����������Ϊ���㻹δ����
			//killNTsymbol()//��predict���еķ��ռ����滻Ϊ��Ӧ�ռ�����Ҳ�������滻Ϊ�÷��ռ�����predict��
   //     }     
   // }
    //  calFakePredict()

	//for (int i = 0; i < CountProduction; i++) {
	//	Production prod = Productions[i];
	//	Symbol* right_first = new Symbol(*prod.Right);//ȡ���Ҳ���һ������
	//	if (right_first->value != "epsilon") {
	//		insertPredict(i, right_first);
	//	}
	//	else {
	//		Symbol* follow = findFollowSymbol(*prod.Left);//�ҵ��ò���ʽ�󲿷�������������ʽ�Ҳ��г���ʱ�������������ֵķ��ţ���������
	//		insertPredict(i, follow);//�������к������ŵ��������predict�����������ռ���
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
