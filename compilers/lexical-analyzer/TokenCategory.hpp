#ifndef TOKENCATEGORY_HPP
#define TOKENCATEGORY_HPP

#include <cstdint>

enum TokenCategory : uint8_t {
    GeneralEof,
    GeneralInit,
    GeneralNothing,
    GeneralReturn,
    GeneralId,
    GeneralComment,
    GeneralTerminator,
    GeneralAssignment,
    GeneralConcatenation,
    // Type
    TypeInt,
    TypeFloat,
    TypeChar,
    TypeBool,
    TypeStr,
    TypeArray,
    // Type Constants
    ConstantsInt,
    ConstantsFloat,
    ConstantsChar,
    ConstantsBool,
    ConstantsStr,
    ConstantsArray,
    // Boolean
    BooleanTrue,
    BooleanFalse,
    // IO
    IoWrite,
    IoRead,
    // Instructions
    InstructionsIf,
    InstructionsElse,
    InstructionsElif,
    InstructionsWhile,
    InstructionsFor,
    // Arithmetic
    ArithmeticAddition,
    ArithmeticSubtraction,
    ArithmeticMultiplication,
    ArithmeticDivision,
    ArithmeticExponentiation,
    ArithmeticUnaryNegative,
    // Relational
    RelationalEquality,
    RelationalDifference,
    RelationalGreater,
    RelationalLess,
    RelationalGreaterOrEqual,
    RelationalLessOrEqual,
    // Logic
    LogicConjunction,
    LogicDisjunction,
    LogicNegation,
    // Scope
    ScopeBegin,
    ScopeEnd,
    // Parameter
    ParameterBegin,
    ParameterEnd,
    // Separator
    SeparatorParameter,
    SeparatorFor
};

#endif // TOKENCATEGORY_HPP
