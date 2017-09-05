#ifndef LEXICALANALYZER_HPP
#define LEXICALANALYZER_HPP

#include <string>

#include "Token.hpp"
#include "CodeReader.hpp"

class LexicalAnalyzer
{
public:
    LexicalAnalyzer(CodeReader *codeReader);
    bool hasNextToken();
    Token nextToken();
private:
    int m_currentLine;
    int m_currentColumn;
    std::string m_line;
    CodeReader *m_codeReader;
    bool hasAnyCharacter();
    char getNextChar();
    void goToNextLine();
};

#endif // LEXICALANALYZER_HPP
