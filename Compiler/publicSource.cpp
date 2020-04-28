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
