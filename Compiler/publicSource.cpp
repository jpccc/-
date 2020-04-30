#include"PublicSource.h"

bool isLetter(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}

bool isNumber(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool isNumberExcpZero(char ch)
{
	if (ch >= '1' && ch <= '9')
		return true;
	else
		return false;
}

bool isOneCharDelimiter(char ch)
{
	for (int i = 0; i < OneCharDelimiter_count; i++) {
		if (ch==oneChar_delimiter[i])
			return true;
	}
	return false;
}

bool isReservedWord(string st)
{
	for (int i = 0; i < reserved_count; i++) {
		if (!st.compare(reserved_word[i]))
			return true;
	}
	return false;
}

Token::Token()
{
	next = nullptr;
}

Token::Token(TokenType type,string value)
{
	this->type = type;
	this->value = value;
	this->next = nullptr;
}

Symbol::Symbol(string value)
{
	this->value = value;
	isTerminal = true;
	next = nullptr;
}

Symbol::Symbol()
{
	isTerminal = true;
	value = "null";
	next = nullptr;
}

void Production::insertRight(Symbol* symbol)
{
	if (RightRear == nullptr) {
		Right = symbol;
		RightRear = symbol;
	}
	else {
		RightRear->next = symbol;
		RightRear = symbol;
		symbol->next = nullptr;
	}
}

void Production::printProduction()
{
	cout << Left.value <<"("<<Left.isTerminal <<")"<< "->";
	Symbol* p = Right;
	while (p != nullptr) {
		cout << p->value <<"("<<p->isTerminal <<")"<< ' ';
		p = p->next;
	}
	cout << endl;
}

Symbol* Production::findSymbolInRight(Symbol symbol)
{
	Symbol* p=Right;
	while (p != nullptr) {
		if (!p->value.compare(symbol.value)) {
			return p;
		}
		p = p->next;
	}
	return nullptr;
}

Production::Production()
{
	Right = nullptr;
	RightRear = nullptr;
}
