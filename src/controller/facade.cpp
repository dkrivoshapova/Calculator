#include "facade.h"

namespace s21 {

Facade::Facade(Model *model, CreditModel *credit, DepositModel *deposit)
    : model_(model), credit_(credit), deposit_(deposit) {}

double Facade::get_answer(std::string expression) {
  return model_->calc(expression);
}

double Facade::get_answer(std::string expression, double value) {
  return model_->calc(expression, value);
}

std::pair<vector<double>, vector<double>> Facade::get_coordinates(
    std::string expression, Plot plot_features) {
  return model_->get_coordinates(expression, plot_features);
}

void Facade::get_answer(double amount, int term, int term_type,
                        double interest_rate, int payment_type) {
  credit_->credit(amount, term, term_type, interest_rate, payment_type);
}

std::string Facade::get_monthly_payment() {
  return credit_->get_monthly_payment();
}

std::string Facade::get_overpayment() { return credit_->get_overpayment(); }

std::string Facade::get_total_payment() { return credit_->get_total_payment(); }

void Facade::get_answer(double amount, int term, double interest_rate,
                        int payment_type, bool capitalizacion) {
  deposit_->calculate(amount, term, interest_rate, payment_type,
                      capitalizacion);
}
std::string Facade::get_income() { return deposit_->get_income(); }
std::string Facade::get_tax() { return deposit_->get_tax(); }
std::string Facade::get_total() { return deposit_->get_total(); }

}  // namespace s21
