#include "LexicalTable.hpp"

#include <algorithm>
#include <iostream>
#include <regex>

using namespace std;

LexicalTable::LexicalTable()
{
    populateSymbols();
    populateLexeme();
}

bool LexicalTable::isSymbol(char c)
{
    if (find(m_symbols.begin(), m_symbols.end(), c) != m_symbols.end()) {
        return true;
    } else {
        return false;
    }
}

TokenCategory LexicalTable::getCategoryFromValue(string value)
{
    map<string, TokenCategory>::iterator it = m_lexemes.find(value);
    if (it != m_lexemes.end()) {
        return it->second;
    } else {
        for (it = m_lexemesRegex.begin(); it != m_lexemesRegex.end(); ++it) {
            regex e(it->first);
            if (regex_match(value, e)) {
                return it->second;
            }
        }
        return TokenCategory::GeneralEof;
    }
}

void LexicalTable::populateSymbols()
{
    m_symbols.push_back(' ');
    m_symbols.push_back(',');
    m_symbols.push_back(';');
    m_symbols.push_back('+');
    m_symbols.push_back('-');
    m_symbols.push_back('*');
    m_symbols.push_back('/');
    m_symbols.push_back('^');
    m_symbols.push_back('~');
    m_symbols.push_back('%');
    m_symbols.push_back('#');
    m_symbols.push_back('>');
    m_symbols.push_back('<');
    m_symbols.push_back('=');
    m_symbols.push_back('(');
    m_symbols.push_back(')');
    m_symbols.push_back('[');
    m_symbols.push_back(']');
    m_symbols.push_back('{');
    m_symbols.push_back('}');
    m_symbols.push_back('\'');
    m_symbols.push_back('"');
}

void LexicalTable::populateLexeme()
{
    putLexemeRegex("[a-zA-Z][_a-zA-Z0-9]*\\w*", TokenCategory::GeneralId);
    // Type Constants
    putLexemeRegex("[0-9]+", TokenCategory::ConstantsInt);
    putLexemeRegex("[+|-]?([0-9]*\\.[0-9]+)", TokenCategory::ConstantsFloat);
    // TODO: Verify this case
    putLexeme("", TokenCategory::ConstantsChar);
    putLexemeRegex("true|false", TokenCategory::ConstantsBool);
    putLexemeRegex("[a-zA-Z_]?\"(\\.|[^\"])*\"", TokenCategory::ConstantsStr);
    // TODO: Verify this case
    putLexeme("", TokenCategory::ConstantsArray);

    // TODO: Verify this case
    putLexeme("", TokenCategory::GeneralEof);
    putLexeme("init", TokenCategory::GeneralInit);
    putLexeme("nothing", TokenCategory::GeneralNothing);
    putLexeme("return", TokenCategory::GeneralReturn);
    putLexeme("#", TokenCategory::GeneralComment);
    putLexeme(";", TokenCategory::GeneralTerminator);
    putLexeme("=", TokenCategory::GeneralAssignment);
    putLexeme("%", TokenCategory::GeneralConcatenation);
    // Type
    putLexeme("int", TokenCategory::TypeInt);
    putLexeme("float", TokenCategory::TypeFloat);
    putLexeme("char", TokenCategory::TypeChar);
    putLexeme("bool", TokenCategory::TypeBool);
    putLexeme("str", TokenCategory::TypeStr);
    putLexeme("array", TokenCategory::TypeArray);
    // Boolean
    putLexeme("true", TokenCategory::BooleanTrue);
    putLexeme("false", TokenCategory::BooleanFalse);
    // IO
    putLexeme("read", TokenCategory::IoRead);
    putLexeme("write", TokenCategory::IoWrite);
    // Instructions
    putLexeme("if", TokenCategory::InstructionsIf);
    putLexeme("else", TokenCategory::InstructionsElse);
    putLexeme("elif", TokenCategory::InstructionsElif);
    putLexeme("while", TokenCategory::InstructionsWhile);
    putLexeme("for", TokenCategory::InstructionsFor);
    // Arithmetic
    putLexeme("+", TokenCategory::ArithmeticAddition);
    putLexeme("-", TokenCategory::ArithmeticSubtraction);
    putLexeme("*", TokenCategory::ArithmeticMultiplication);
    putLexeme("/", TokenCategory::ArithmeticDivision);
    putLexeme("^", TokenCategory::ArithmeticExponentiation);
    putLexeme("~", TokenCategory::ArithmeticUnaryNegative);
    // Relational
    putLexeme("==", TokenCategory::RelationalEquality);
    putLexeme("!=", TokenCategory::RelationalDifference);
    putLexeme(">", TokenCategory::RelationalGreater);
    putLexeme("<", TokenCategory::RelationalLess);
    putLexeme(">=", TokenCategory::RelationalGreaterOrEqual);
    putLexeme("<=", TokenCategory::RelationalLessOrEqual);
    // Logic
    putLexeme("&", TokenCategory::LogicConjunction);
    putLexeme("|", TokenCategory::LogicDisjunction);
    putLexeme("!", TokenCategory::LogicNegation);
    // Scope
    putLexeme("{", TokenCategory::ScopeBegin);
    putLexeme("}", TokenCategory::ScopeEnd);
    // Parameter
    putLexeme("(", TokenCategory::ParameterBegin);
    putLexeme(")", TokenCategory::ParameterEnd);
    // Separator
    putLexeme(",", TokenCategory::SeparatorParameter);
    putLexeme(";", TokenCategory::SeparatorFor);
}

void LexicalTable::putLexeme(string key, TokenCategory value)
{
    m_lexemes.insert(pair<string, TokenCategory>(key, value));
}

void LexicalTable::putLexemeRegex(string key, TokenCategory value)
{
    m_lexemesRegex.insert(pair<string, TokenCategory>(key, value));
}
