#pragma once

#include "../model/credit_model.h"
#include "../model/deposit_model.h"
#include "../model/model.h"

namespace s21 {

class Facade {
 public:
  Facade(Model *model, CreditModel *credit, DepositModel *deposit);
  double get_answer(std::string expression);
  double get_answer(std::string expression, double value);
  std::pair<vector<double>, vector<double>> get_coordinates(string expression,
                                                            Plot plot_features);
  void get_answer(double amount, int term, int term_type, double interest_rate,
                  int payment_type);
  std::string get_monthly_payment();
  std::string get_overpayment();
  std::string get_total_payment();

  void get_answer(double amount, int term, double interest_rate,
                  int payment_type, bool capitalizacion);
  void send_replenishments(string replenishments);
  void send_withdrawals(string withdrawals);
  std::string get_income();
  std::string get_tax();
  std::string get_total();

 private:
  s21::Model *model_;
  s21::CreditModel *credit_;
  s21::DepositModel *deposit_;
};

}  // namespace s21
