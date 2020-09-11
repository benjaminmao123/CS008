#pragma once

#include <string>
#include <iostream>

class Token
{
public:
    Token();
    Token(const std::string& str, int type);

    friend std::ostream& operator<<(std::ostream& outs, const Token& t);
    
    int type() const;
    std::string type_string() const;
    const std::string& token_str() const;

private:
    std::string _token;
    int _type;
};