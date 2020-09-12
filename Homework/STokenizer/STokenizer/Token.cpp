/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Functions to implement Token
 *
 * Notes: None.
 */

#include "Token.h"
#include "SMConstants.h"

Token::Token() :
	_type(0)
{

}

Token::Token(const std::string& str, int type) :
	_token(str),
	_type(type)
{

}

int Token::type() const
{
	return _type;
}

std::string Token::type_string() const
{
	switch (_type)
	{
	case ALPHA:
		return "ALPHA";
	case DIGIT:
	case SUB_DIGIT:
		return "DIGIT";
	case PUNCT:
		return "PUNCT";
	case SPACE:
		return "SPACE";
	default:
		break;
	}

	return "UNKNOWN";
}

const std::string &Token::token_str() const
{
	return _token;
}

std::ostream& operator<<(std::ostream& outs, const Token& t)
{
	outs << "|" << t._token << "|";

	return outs;
}
