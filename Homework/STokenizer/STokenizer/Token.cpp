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
	std::string res;

	switch (_type)
	{
	case ALPHA:
		res = "ALPHA";
		break;
	case DIGIT:
	case SUB_DIGIT:
		res = "DIGIT";
		break;
	case PUNCT:
		res = "PUNCT";
		break;
	case SPACE:
		res = "SPACE";
		break;
	case UNKNOWN:
		res = "UNKNOWN";
		break;
	default:
		break;
	}

	return res;
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
