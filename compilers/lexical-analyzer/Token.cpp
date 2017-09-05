#include "Token.hpp"

#include <sstream>
#include <iomanip>

using namespace std;

Token::Token(int line, int column, TokenCategory category, string value)
    : line(line), column(column), categoryNumber(static_cast<int>(category)),
      categoryName(getCategoryName(category)), value(value)
{
}

string Token::toString()
{
    stringstream ss;
    ss << "Token(line=" << setfill('0') << setw(5) << line
       << ", column=" << setfill('0') << setw(4) << column
       << ", categoryNumber=" << setfill('0') << setw(2) << categoryNumber
       << ", categoryName=" << categoryName
       << ", value= " << value << ")";
    return ss.str();
}

string Token::getCategoryName(TokenCategory category)
{
    switch (category) {
    case TokenCategory::GeneralEof:
        return "GeneralEof";
    case TokenCategory::GeneralInit:
        return "GeneralInit";
    case TokenCategory::GeneralNothing:
        return "GeneralNothing";
    case TokenCategory::GeneralReturn:
        return "GeneralReturn";
    case TokenCategory::GeneralId:
        return "GeneralId";
    case TokenCategory::GeneralFunction:
        return "GeneralFunction";
    case TokenCategory::GeneralComment:
        return "GeneralComment";
    case TokenCategory::GeneralTerminator:
        return "GeneralTerminator";
    case TokenCategory::GeneralAssignment:
        return "GeneralAssignment";
    case TokenCategory::GeneralConcatenation:
        return "GeneralConcatenation";
    case TokenCategory::TypeInt:
        return "TypeInt";
    case TokenCategory::TypeFloat:
        return "TypeFloat";
    case TokenCategory::TypeChar:
        return "TypeChar";
    case TokenCategory::TypeBool:
        return "TypeBool";
    case TokenCategory::TypeStr:
        return "TypeStr";
    case TokenCategory::TypeArray:
        return "TypeArray";
    case TokenCategory::ConstantsInt:
        return "ConstantsInt";
    case TokenCategory::ConstantsFloat:
        return "ConstantsFloat";
    case TokenCategory::ConstantsChar:
        return "ConstantsChar";
    case TokenCategory::ConstantsBool:
        return "ConstantsBool";
    case TokenCategory::ConstantsStr:
        return "ConstantsStr";
    case TokenCategory::ConstantsArray:
        return "ConstantsArray";
    case TokenCategory::BooleanTrue:
        return "BooleanTrue";
    case TokenCategory::BooleanFalse:
        return "BooleanFalse";
    case TokenCategory::IoWrite:
        return "IoWrite";
    case TokenCategory::IoRead:
        return "IoRead";
    case TokenCategory::InstructionsIf:
        return "InstructionsIf";
    case TokenCategory::InstructionsElse:
        return "InstructionsElse";
    case TokenCategory::InstructionsElif:
        return "InstructionsElif";
    case TokenCategory::InstructionsWhile:
        return "InstructionsWhile";
    case TokenCategory::InstructionsFor:
        return "InstructionsFor";
    case TokenCategory::ArithmeticAddition:
        return "ArithmeticAddition";
    case TokenCategory::ArithmeticSubtraction:
        return "ArithmeticSubtraction";
    case TokenCategory::ArithmeticMultiplication:
        return "ArithmeticMultiplication";
    case TokenCategory::ArithmeticDivision:
        return "ArithmeticDivision";
    case TokenCategory::ArithmeticExponentiation:
        return "ArithmeticExponentiation";
    case TokenCategory::ArithmeticUnaryNegative:
        return "ArithmeticUnaryNegative";
    case TokenCategory::RelationalEquality:
        return "RelationalEquality";
    case TokenCategory::RelationalDifference:
        return "RelationalDifference";
    case TokenCategory::RelationalGreater:
        return "RelationalGreater";
    case TokenCategory::RelationalLess:
        return "RelationalLess";
    case TokenCategory::RelationalGreaterOrEqual:
        return "RelationalGreaterOrEqual";
    case TokenCategory::RelationalLessOrEqual:
        return "RelationalLessOrEqual";
    case TokenCategory::LogicConjunction:
        return "LogicConjunction";
    case TokenCategory::LogicDisjunction:
        return "LogicDisjunction";
    case TokenCategory::LogicNegation:
        return "LogicNegation";
    case TokenCategory::ScopeBegin:
        return "ScopeBegin";
    case TokenCategory::ScopeEnd:
        return "ScopeEnd";
    case TokenCategory::ParameterBegin:
        return "ParameterBegin";
    case TokenCategory::ParameterEnd:
        return "ParameterEnd";
    case TokenCategory::SeparatorParameter:
        return "SeparatorParameter";
    case TokenCategory::SeparatorFor:
        return "SeparatorFor";
    default:
        return "UNDEFINED";
    }
}
