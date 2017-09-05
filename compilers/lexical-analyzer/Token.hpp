#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "TokenCategory.hpp"

class Token
{
public:
    const int line;
    const int column;
    const int categoryNumber;
    const std::string categoryName;
    const std::string value;
    Token(int line, int column, TokenCategory category, std::string value);
    std::string toString();
private:
    std::string getCategoryName(TokenCategory category);
};

#endif // TOKEN_HPP
