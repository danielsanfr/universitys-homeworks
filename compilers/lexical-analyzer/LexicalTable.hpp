#ifndef LEXICALTABLE_HPP
#define LEXICALTABLE_HPP

#include <map>
#include <vector>
#include <string>

#include "TokenCategory.hpp"

class LexicalTable
{
public:
    static LexicalTable *getInstance() {
        static LexicalTable *s_instance = nullptr;
        if (s_instance == nullptr) {
            s_instance = new LexicalTable();
        }
        return s_instance;
    }
    bool isSymbol(char c);
    TokenCategory getCategoryFromValue(std::string value);
private:
    std::vector<char> m_symbols;
    std::map<std::string, TokenCategory> m_lexemes;
    std::map<std::string, TokenCategory> m_lexemesRegex;
    LexicalTable();
    void populateSymbols();
    void populateLexeme();
    void putLexeme(std::string key, TokenCategory value);
    void putLexemeRegex(std::string key, TokenCategory value);
};

#endif // LEXICALTABLE_HPP
