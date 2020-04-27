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

Token::Token()
{
	next = nullptr;
}

Token::Token(TokenType type,string value)
{
	this->type = type;
	this->value = value;
}
