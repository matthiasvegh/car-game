
#include <boost/test/unit_test.hpp>

#include "MathExpression.hpp"

#include <sstream>

using namespace car;

BOOST_AUTO_TEST_SUITE(MathExpressionTest)

BOOST_AUTO_TEST_CASE(test_float_parse_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2"), FormulaValue(2), 0.001);
}

BOOST_AUTO_TEST_CASE(test_float_parse_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2.0"), FormulaValue(2), 0.001);
}

BOOST_AUTO_TEST_CASE(test_add_mul_precedence) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2+3*4"), FormulaValue(14), 0.001);
}

BOOST_AUTO_TEST_CASE(test_sub_add_precedence_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2+3-4"), FormulaValue(1), 0.001);
}

BOOST_AUTO_TEST_CASE(test_sub_add_precedence_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2-3+4"), FormulaValue(3), 0.001);
}

BOOST_AUTO_TEST_CASE(test_div_mul_precedence_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("8*3/4"), FormulaValue(6), 0.001);
}

BOOST_AUTO_TEST_CASE(test_div_mul_precedence_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2/3*6"), FormulaValue(4), 0.001);
}

BOOST_AUTO_TEST_CASE(test_less_mul_precedence_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("3*1>2"), FormulaValue(1), 0.001);
}

BOOST_AUTO_TEST_CASE(test_less_mul_precedence_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("3*(1>2)"), FormulaValue(0), 0.001);
}

BOOST_AUTO_TEST_CASE(test_less_mul_precedence_3) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("3*(1<2)"), FormulaValue(3), 0.001);
}

BOOST_AUTO_TEST_CASE(test_greatereq_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2>=2"), FormulaValue(1), 0.001);
}

BOOST_AUTO_TEST_CASE(test_lesseq_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2<=2"), FormulaValue(1), 0.001);
}

BOOST_AUTO_TEST_CASE(test_juxtaposition_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2 2"), FormulaValue(4), 0.001);
}

BOOST_AUTO_TEST_CASE(test_juxtaposition_2) {
	SymbolTable table = {{"s", FormulaValue(3.0)}};
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2s", table), FormulaValue(6), 0.001);
}

BOOST_AUTO_TEST_CASE(test_juxtaposition_3) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("(3)(4)"), FormulaValue(12), 0.001);
}

BOOST_AUTO_TEST_CASE(test_symbol_parsing_1) {
	SymbolTable table = {{"s", FormulaValue(3.0)}};
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("s", table), FormulaValue(3.0), 0.001);
}

BOOST_AUTO_TEST_CASE(test_symbol_parsing_2) {
	SymbolTable table = {{"s", FormulaValue(3.0)}};
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("s+1", table), FormulaValue(4.0), 0.001);
}

BOOST_AUTO_TEST_CASE(test_minus_parsing_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2+-1"), FormulaValue(1), 0.001);
}

BOOST_AUTO_TEST_CASE(test_minus_parsing_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("-1"), FormulaValue(-1), 0.001);
}

BOOST_AUTO_TEST_CASE(test_minus_parsing_3) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("-1+3"), FormulaValue(2), 0.001);
}

BOOST_AUTO_TEST_CASE(test_minus_parsing_4) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("-2*3"), FormulaValue(-6), 0.001);
}

BOOST_AUTO_TEST_CASE(test_minus_parsing_5) {
	SymbolTable table = {{"s", FormulaValue(3.0)}};
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("-s", table), FormulaValue(-3.0), 0.001);
}

BOOST_AUTO_TEST_CASE(test_minus_parsing_6) {
	SymbolTable table = {{"s", FormulaValue(3.0)}};
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("--s", table), FormulaValue(3.0), 0.001);
}

BOOST_AUTO_TEST_CASE(test_plus_parsing_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("+3"), FormulaValue(3), 0.001);
}

BOOST_AUTO_TEST_CASE(test_plus_parsing_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("++3"), FormulaValue(3), 0.001);
}

BOOST_AUTO_TEST_CASE(test_parentheses_1) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("2*(3+4)"), FormulaValue(14), 0.001);
}

BOOST_AUTO_TEST_CASE(test_parentheses_2) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("-(3+4)"), FormulaValue(-7), 0.001);
}

BOOST_AUTO_TEST_CASE(test_parentheses_3) {
	BOOST_CHECK_CLOSE(evaluateMathExpressionFromString("((((3))))"), FormulaValue(3), 0.001);
}

BOOST_AUTO_TEST_CASE(test_output_1) {
	std::stringstream ss; ss << parseMathExpression("3+4");
	BOOST_CHECK_EQUAL(ss.str(), "3+4");
}

BOOST_AUTO_TEST_CASE(test_output_2) {
	std::stringstream ss; ss << parseMathExpression("3*4");
	BOOST_CHECK_EQUAL(ss.str(), "3*4");
}

BOOST_AUTO_TEST_CASE(test_output_3) {
	std::stringstream ss; ss << parseMathExpression("3-4");
	BOOST_CHECK_EQUAL(ss.str(), "3-4");
}

BOOST_AUTO_TEST_CASE(test_output_4) {
	std::stringstream ss; ss << parseMathExpression("3/4");
	BOOST_CHECK_EQUAL(ss.str(), "3/4");
}

BOOST_AUTO_TEST_CASE(test_output_5) {
	std::stringstream ss; ss << parseMathExpression("3+3*4");
	BOOST_CHECK_EQUAL(ss.str(), "3+3*4");
}

BOOST_AUTO_TEST_CASE(test_output_6) {
	std::stringstream ss; ss << parseMathExpression("(3+3)*4");
	BOOST_CHECK_EQUAL(ss.str(), "(3+3)*4");
}

BOOST_AUTO_TEST_CASE(test_output_7) {
	std::stringstream ss; ss << parseMathExpression("3+3+4");
	BOOST_CHECK_EQUAL(ss.str(), "3+3+4");
}



BOOST_AUTO_TEST_SUITE_END()

