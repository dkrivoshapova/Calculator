#include "gtest/gtest.h"
#include "model/credit_model.h"
#include "model/deposit_model.h"
#include "model/model.h"

using s21::CreditModel;
using s21::DepositModel;
using s21::Model;

TEST(StripMathExp, Pow) {
  string s = "2^3^2";
  Model a;
  double result = a.calc(s);
  double expected = pow(2, pow(3, 2));
  EXPECT_EQ(result, expected);
}

TEST(StripMathExp, Pow1) {
  string s = "-3^-2";
  Model a;
  double result = a.calc(s);
  double expected = pow(-3, -2);
  EXPECT_EQ(result, expected);
}

TEST(StripMathExp, Pow2) {
  string s = "3^-2";
  Model a;
  double result = a.calc(s);
  double expected = pow(3, -2);
  EXPECT_EQ(result, expected);
}

TEST(StripMathExp, Pow3) {
  string s = "-3^2";
  Model a;
  double result = a.calc(s);
  double expected = pow(-3, 2);
  EXPECT_EQ(result, expected);
}
TEST(StripMathExp, expression) {
  string s = "cos(-3^(-2))+4%5*ln(e)+log(e)";
  Model a;
  double result = a.calc(s);
  double expected = cos(pow(-3, -2)) + 4 % 5 * log(M_E) + log10(M_E);
  EXPECT_EQ(result, expected);
}
TEST(StripMathExp, expression1) {
  string s = "sin(π÷2)*2.231^3-asin(+0.123)";
  Model a;
  double result = a.calc(s);
  double expected = sin(M_PI / 2) * pow(2.231, 3) - asin(0.123);
  EXPECT_EQ(result, expected);
}
TEST(StripMathExp, expression2) {
  string s = "cos(π-2)÷(2.231^3)-acos(0.123)";
  Model a;
  double result = a.calc(s);
  double expected = cos(M_PI - 2) / pow(2.231, 3) - acos(0.123);
  ASSERT_DOUBLE_EQ(result, expected);
}
TEST(StripMathExp, expression3) {
  string s = "tan(π+2)÷-(2.231^3)*-atan(-0.123)";
  Model a;
  double result = a.calc(s);
  double expected = tan(M_PI + 2) / (-pow(2.231, 3)) * (-atan(-0.123));
  ASSERT_DOUBLE_EQ(result, expected);
}

TEST(StripMathExp, Unary_end) {
  string s = "√2-+-+-3";
  Model a;
  double result = a.calc(s);
  double expected = sqrt(2) - 3;
  EXPECT_EQ(result, expected);
}

TEST(StripMathExp, Unary_start) {
  string s = "-+-+-3+√2";
  Model a;
  double result = a.calc(s);
  double expected = -3 + sqrt(2);
  EXPECT_EQ(result, expected);
}

// TEST(InvalidMathExp, Brackets_1) {
//   string s = "()-+-+-3+√2";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Brackets_2) {
//   string s = "-+-+-3+√2)(";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Brackets_3) {
//   string s = ")(";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Plus) {
//   string s = "+";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Minus) {
//   string s = "-";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Div) {
//   string s = "÷";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Mod) {
//   string s = "%";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Mult) {
//   string s = "*";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Pow) {
//   string s = "^";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Plus2) {
//   string s = "+*";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Minus2) {
//   string s = "-*";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Div2) {
//   string s = "÷÷";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Mod2) {
//   string s = "%%";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Mult2) {
//   string s = "**";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Pow2) {
//   string s = "^^";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, MultDiv) {
//   string s = "*÷";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, DivMult) {
//   string s = "÷*";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Dot) {
//   string s = ".";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Dot2) {
//   string s = "...";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Dot3) {
//   string s = ".()";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression1) {
//   string s = "2+*3";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Expression2) {
//   string s = "4-*5";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Expression3) {
//   string s = "6÷÷7";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression4) {
//   string s = "2%%2";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression5) {
//   string s = "1^^1";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression6) {
//   string s = "tan(";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression7) {
//   string s = "2+";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression8) {
//   string s = "2*";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }
// TEST(InvalidMathExp, Expression9) {
//   string s = "((*)(*))";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

// TEST(InvalidMathExp, Expression10) {
//   string s = "(((÷)2+3+4+5+5))";
//   Model a;
//   ASSERT_ANY_THROW(a.calc(s));
// }

TEST(Credit_calc, Annuity1) {
  CreditModel a;
  a.credit(1000000, 5, YEAR, 12, ANNUITY);
  string result = a.get_monthly_payment();
  string expected = "22244.45";
  EXPECT_EQ(result, expected);
  result = a.get_overpayment();
  expected = "334666.86";
  EXPECT_EQ(result, expected);
  result = a.get_total_payment();
  expected = "1334666.86";
  EXPECT_EQ(result, expected);
}
TEST(Credit_calc, Annuity2) {
  CreditModel a;
  a.credit(100000, 5, MONTH, 12, ANNUITY);
  string result = a.get_monthly_payment();
  string expected = "20603.98";
  EXPECT_EQ(result, expected);
  result = a.get_overpayment();
  expected = "3019.90";
  EXPECT_EQ(result, expected);
  result = a.get_total_payment();
  expected = "103019.90";
  EXPECT_EQ(result, expected);
}

TEST(Credit_calc, Differentiated1) {
  CreditModel a;
  a.credit(1000000, 5, YEAR, 12, DIFFERENTIATED);

  string result = a.get_monthly_payment();
  string expected = "26666.67...16833.33";
  EXPECT_EQ(result, expected);
  result = a.get_overpayment();
  expected = "305000.00";
  EXPECT_EQ(result, expected);
  result = a.get_total_payment();
  expected = "1305000.00";
  EXPECT_EQ(result, expected);
}
TEST(Credit_calc, Differentiated2) {
  CreditModel a;
  a.credit(5000000, 24, MONTH, 20, DIFFERENTIATED);

  string result = a.get_monthly_payment();
  string expected = "291666.67...211805.56";
  EXPECT_EQ(result, expected);
  result = a.get_overpayment();
  expected = "1041666.67";
  EXPECT_EQ(result, expected);
  result = a.get_total_payment();
  expected = "6041666.67";
  EXPECT_EQ(result, expected);
}

TEST(Deposit_calc, Capitalizacion1) {
  DepositModel a;
  a.calculate(50000, 36, 4.6, 1, true);
  EXPECT_EQ(a.get_income(), "7222.27");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "57222.27");
}

TEST(Deposit_calc, Capitalizacion365) {
  DepositModel a;
  a.calculate(5000000, 60, 9.8, 365, true);
  EXPECT_EQ(a.get_income(), "3161044.34");
  EXPECT_EQ(a.get_tax(), "401185.76");
  EXPECT_EQ(a.get_total(), "8161044.34");
}

TEST(Deposit_calc, Capitalizacion2) {
  DepositModel a;
  a.calculate(10000, 12, 1, 2, true);
  EXPECT_EQ(a.get_income(), "100.25");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "10100.25");
}

TEST(Deposit_calc, Capitalizacion4) {
  DepositModel a;
  a.calculate(10000, 12, 1, 4, true);
  EXPECT_EQ(a.get_income(), "100.38");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "10100.38");
}

TEST(Deposit_calc, No_capitalizacion1) {
  DepositModel a;
  a.calculate(50000, 36, 4.6, 1, false);
  EXPECT_EQ(a.get_income(), "6900.00");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "50000.00");
}

TEST(Deposit_calc, No_capitalizacion2) {
  DepositModel a;
  a.calculate(50000, 6, 2.6, 2, false);
  EXPECT_EQ(a.get_income(), "650.00");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "50000.00");
}
TEST(Deposit_calc, No_capitalizacion4) {
  DepositModel a;
  a.calculate(50000, 4, 7, 4, false);
  EXPECT_EQ(a.get_income(), "1166.67");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "50000.00");
}
TEST(Deposit_calc, No_capitalizacion12) {
  DepositModel a;
  a.calculate(10000, 36, 1, 12, false);
  EXPECT_EQ(a.get_income(), "300.00");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "10000.00");
}

TEST(Deposit_calc, No_capitalizacion52) {
  DepositModel a;
  a.calculate(500, 60, 10, 52, false);
  EXPECT_EQ(a.get_income(), "250.00");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "500.00");
}

TEST(Deposit_calc, No_capitalizacion365) {
  DepositModel a;
  a.calculate(500000, 6, 4.6, 365, false);
  EXPECT_EQ(a.get_income(), "11500.00");
  EXPECT_EQ(a.get_tax(), "0.00");
  EXPECT_EQ(a.get_total(), "500000.00");
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
