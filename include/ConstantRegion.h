//
// Created by Liming on 2023/6/18.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_CONSTANTREGION_H
#define MATHEMATICAL_EXPRESSION_CPP_CONSTANTREGION_H

#include "string"
#include "regex"

const std::string STRING_NULL = "null";
const char LEFT_BRACKET = '(';
const char RIGHT_BRACKET = ')';
const char DECIMAL_POINT = '.';
const char EMPTY = ' ';
const std::string NO_CHAR;
const short BA_ASCII = 0b1000001;
const short BZ_ASCII = 0b1011010;
const short SA_ASCII = 0b1100001;
const short SZ_ASCII = 0b1111010;
const char PLUS_SIGN = '+';
const char MINUS_SIGN = '-';
const char MULTIPLICATION_SIGN = '*';
const char DIVISION_SIGN = '/';
const char REMAINDER_SIGN = '%';
const char COMMA = ',';
const std::string GREATER_THAN_SIGN = ">";
const std::string LESS_THAN_SIGN = "<";
const std::string EQUAL_SIGN1 = "=";
const std::string EQUAL_SIGN2 = EQUAL_SIGN1 + EQUAL_SIGN1;
const std::string NEGATE_SIGN = "!";
const std::string MINUS_SIGN_STR = std::string(&MINUS_SIGN);
const std::string NOT_EQUAL_SIGN1 = NEGATE_SIGN + EQUAL_SIGN1;
const std::string NOT_EQUAL_SIGN2 = LESS_THAN_SIGN + GREATER_THAN_SIGN;
const std::string GREATER_THAN_OR_EQUAL_TO_SIGN = GREATER_THAN_SIGN + EQUAL_SIGN1;
const std::string LESS_THAN_OR_EQUAL_TO_SIGN = LESS_THAN_SIGN + EQUAL_SIGN1;
const std::string REGULAR_COMPARISON_OPERATOR = LESS_THAN_OR_EQUAL_TO_SIGN + "|" +
                                                GREATER_THAN_OR_EQUAL_TO_SIGN + "|" + NOT_EQUAL_SIGN1 + "|" +
                                                NOT_EQUAL_SIGN2 + "|" + EQUAL_SIGN2 +
                                                "|[" + LESS_THAN_SIGN + EQUAL_SIGN1 + GREATER_THAN_SIGN + "]";
const std::string REGULAR_PURE_LETTER = "[a-zA-Z]+";
const std::string REGULAR_ADDITION_SUBTRACTION_AMBIGUITY = &"\\"[PLUS_SIGN] + MINUS_SIGN;
const std::string LOG_INFO_GET_FUNCTION = "Get a function component from the manager. => ";
const std::string LOG_INFO_GET_COMPONENT = "Get a computing component from the manager. => ";
const std::string LOG_INFO_FIND_FUNCTION = "Find and prepare the startup function: ";
const std::string LOG_INFO_REGISTER_COMPONENT = "A computing component is registered ";
const std::string LOG_INFO_register_FUNCTION = "A function is registered ";
const std::string LOG_INFO_UNREGISTER_COMPONENT = "Preparing to unregister the compute component. Component name:";
const std::string LOG_INFO_UNREGISTER_FUNCTION = "Prepare the logoff of a function. FunctionManager name:";
const std::string LOG_INFO_SHARED_POOL = "Use shared pool data. The identity of the data is: ";

namespace ME {
    static const std::regex ALL_INVISIBLE_CHARACTERS_PATTERN("\\s+");
    static const std::regex REGULAR_COMPARISON_OPERATOR_PATTERN(REGULAR_COMPARISON_OPERATOR);
    static const std::regex INTERVAL_EXTRACTION_PATTERN("[\\[\\]]");
}
#endif //MATHEMATICAL_EXPRESSION_CPP_CONSTANTREGION_H
