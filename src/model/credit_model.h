#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

constexpr long double kMAX = 10000000000;

enum TypeCredit { ANNUITY, DIFFERENTIATED };
enum TypeDate { YEAR, MONTH };

namespace s21 {

class CreditModel {
 private:
  long double _amount = 0;
  int _term = 0;
  int _term_type = YEAR;
  double _interest_rate = 10;
  int _payment_type = ANNUITY;
  std::string _monthly_payment;
  double _overpayment = 0.0;
  double _total_payment = 0.0;

 private:
  void annuity_credit();
  void differentiated_credit();
  void set_amount(double amount);
  void set_term(int term);
  void set_interest_rate(int interest_rate);
  void calc();

 public:
  CreditModel() = default;
  ~CreditModel() = default;
  void credit(double amount, int term, int term_type, double interest_rate,
              int payment_type);
  std::string get_monthly_payment();
  std::string get_overpayment();
  std::string get_total_payment();
  std::string to_string(double number);
};

}  // namespace s21
