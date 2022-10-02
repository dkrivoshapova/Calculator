#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

enum Frequency {
  DAYS = 365,
  WEEKS = 52,
  MONTHS = 12,
  QUARTE = 4,
  HALFYEAR = 2,
  YEARS = 1,
  END = 0
};

namespace s21 {

class DepositModel {
 private:
  double _amount;
  double _term;
  double _interest_rate;
  double _income;
  double _tax = 0;
  double _total;
  double _effective_rate;

 private:
  void calc(int payment_type);
  void calc();
  void set_tax();
  std::string to_string(double number);

 public:
  DepositModel() = default;
  ~DepositModel() = default;
  void calculate(double amount, int term, double interest_rate,
                 int payment_type, bool capitalizacion);
  std::string get_income();
  std::string get_tax();
  std::string get_total();
};

}  // namespace s21
