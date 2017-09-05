#include "LexicalAnalyzer.hpp"

#include <iostream>

#include "LexicalTable.hpp"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(CodeReader *codeReader) : m_currentLine(-1), m_currentColumn(-1),
    m_line(""), m_codeReader(codeReader)
{
}

bool LexicalAnalyzer::hasNextToken()
{
    if (hasAnyCharacter()) {
        return true;
    } else {
        while (m_codeReader->hasNextLine()) {
            goToNextLine();
            if (hasAnyCharacter()) {
                return true;
            }
        }
        m_codeReader->close();
        return false;
    }
}

Token LexicalAnalyzer::nextToken()
{
    LexicalTable *lexicalTable = LexicalTable::getInstance();
    string tokenValue = "";
    char c = m_line.at(m_currentColumn);
    if (c == '#') {
        do {
            goToNextLine();
            if (hasAnyCharacter()) {
                c = m_line.at(m_currentColumn);
                if (c != '#') {
                    break;
                }
            } else if (!m_codeReader->hasNextLine()) {
                tokenValue = "";
                break;
            }
        } while (true);
    }

    if (c == '\"') {
        while (true) {
            m_currentColumn += 1;
            tokenValue.append(1u, c);
            c = m_line.at(m_currentColumn);
            if (c == '\"') {
                tokenValue.append(1u, c);
                m_currentColumn += 1;
                break;
            } else if (m_currentColumn + 1 == m_line.length()) {
                tokenValue = "";
                break;
            }
        }
    } else if (c == '\'') {
        tokenValue.append(1u, c);
        tokenValue.append(1u, m_line.at(++m_currentColumn));
        tokenValue.append(1u, m_line.at(++m_currentColumn));
    } else if (c != '#') {
        while (true) {
            m_currentColumn += 1;
            tokenValue.append(1u, c);
            if (m_currentColumn == m_line.length()) {
                goToNextLine();
                break;
            } else {
                c = m_line.at(m_currentColumn);
            }
            if (lexicalTable->isSymbol(c)) {
                if (tokenValue.at(0) == '\"') {
                    if (c == '\"') {
                        tokenValue.append(1u, c);
                        m_currentColumn += 1;
                    } else {
                        continue;
                    }
                }
                break;
            }
        }
    }

    TokenCategory category = lexicalTable->getInstance()->getCategoryFromValue(tokenValue);
    if (category == TokenCategory::GeneralEof
            && (m_currentColumn < m_line.size() || m_codeReader->hasNextLine())) {
        cerr << "Lexical error at l" << m_currentLine << "c" << m_currentColumn << endl;
        exit(-1);
    }
    return Token(m_currentLine, m_currentColumn, category, tokenValue);
}

bool LexicalAnalyzer::hasAnyCharacter()
{
    for (int i = m_currentColumn; i < m_line.length(); ++i) {
        m_currentColumn = i;
        if (!isspace(m_line.at(i))) {
            return true;
        }
    }
    return false;
}

char LexicalAnalyzer::getNextChar()
{
    char c;
    do {
        if (m_currentColumn == m_line.length()) {
            return '\n';
        }
        c = m_line.at(m_currentColumn);
        m_currentColumn += 1;
    } while (c == ' ' || c == '\t');
    return c;
}

void LexicalAnalyzer::goToNextLine()
{
    m_line = m_codeReader->getNextLine();
    m_currentColumn = 0;
    m_currentLine += 1;
}
