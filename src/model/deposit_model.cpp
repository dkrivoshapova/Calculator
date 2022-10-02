#include "deposit_model.h"
using s21::DepositModel;

void DepositModel::calc(int payment_type) {
  double effectiv_rate = 1 + (_interest_rate / payment_type);
  _effective_rate = pow(effectiv_rate, (payment_type * _term / 12));
  _total = _amount * _effective_rate;
  _income = _amount * (_effective_rate - 1);
  set_tax();
}
void DepositModel::calc() {
  _effective_rate = _interest_rate * _term / 12.00;
  _total = _amount;
  _income = _amount * _effective_rate;
  set_tax();
}
void DepositModel::calculate(double amount, int term, double interest_rate,
                             int payment_type, bool capitalizacion) {
  _amount = amount;
  _term = (double)term;
  _interest_rate = interest_rate / 100.00;
  if (capitalizacion) {
    calc(payment_type);
  } else {
    calc();
  }
}

void DepositModel::set_tax() {
  if (_income > 75000) {
    _tax = (_income - 75000) * 0.13;
  }
}

std::string DepositModel::get_income() { return to_string(_income); }
std::string DepositModel::get_tax() { return to_string(_tax); }
std::string DepositModel::get_total() { return to_string(_total); }

std::string DepositModel::to_string(double number) {
  std::string result;
  std::stringstream ss;
  ss << result << std::fixed << std::setprecision(2) << number;
  result = ss.str();
  return result;
}
