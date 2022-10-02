#include "credit_model.h"
using s21::CreditModel;

void CreditModel::credit(double amount, int term, int term_type,
                         double interest_rate, int payment_type) {
  _payment_type = payment_type;
  _term_type = term_type;
  set_term(term);
  set_interest_rate(interest_rate);
  set_amount(amount);
  calc();
}

void CreditModel::calc() {
  if (_payment_type == ANNUITY) {
    annuity_credit();
  } else {
    differentiated_credit();
  }
}

void CreditModel::annuity_credit() {
  _total_payment = 0;
  _overpayment = 0;
  long double monthly_payment =
      _amount * _interest_rate *
      (1 + (1 / (pow((1 + _interest_rate), _term) - 1)));
  _total_payment = monthly_payment * _term;
  _overpayment = _total_payment - _amount;
  _monthly_payment = to_string(monthly_payment);
}

void CreditModel::differentiated_credit() {
  _total_payment = 0;
  _overpayment = 0;
  double fix_payment = _amount / _term;
  double max_payment = fix_payment + _amount * _interest_rate;
  double min_payment = fix_payment * (1 + _interest_rate);

  for (auto i = _term; i > 0; i--) {
    _overpayment += fix_payment * _interest_rate * i;
  }
  _total_payment = _overpayment + _amount;
  _monthly_payment = to_string(max_payment) + "..." + to_string(min_payment);
}

void CreditModel::set_amount(double amount) {
  if (amount < 0 || amount > kMAX) {
    throw std::invalid_argument("ERROR");
  }
  _amount = amount;
}

void CreditModel::set_term(int term) {
  if (_term_type == YEAR) {
    term *= 12;
  }
  if (term > 720 || term < 0) {
    throw std::invalid_argument("ERROR");
  }
  _term = term;
}

void CreditModel::set_interest_rate(int interest_rate) {
  if (interest_rate < 0 || interest_rate > 50)
    throw std::invalid_argument("ERROR");
  _interest_rate = interest_rate / (100.0 * 12);
}

std::string CreditModel::get_monthly_payment() { return _monthly_payment; }

std::string CreditModel::get_overpayment() { return to_string(_overpayment); }

std::string CreditModel::get_total_payment() {
  return to_string(_total_payment);
}

std::string CreditModel::to_string(double number) {
  std::string result;
  std::stringstream ss;
  ss << result << std::fixed << std::setprecision(2) << number;
  result = ss.str();
  return result;
}
