#include "deposit.h"

#include <map>

#include "ui_deposit.h"

namespace s21 {

Deposit::Deposit(s21::Facade *facade, QWidget *parent)
    : QDialog(parent), ui(new Ui::Deposit), facade_(facade) {
  ui->setupUi(this);
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_Calc_clicked() {
  double amount = ui->amount_lineEdit->text().toDouble();
  double term = ui->term_lineEdit->text().toDouble();
  if (ui->years->isChecked()) {
    term *= 12.0;
  }
  double interest = ui->interest_lineEdit->text().toDouble();
  QString type = ui->payment_type->currentText();
  int payment_type = convert_type(type);
  bool capitalizacion = ui->capitalization->checkState();

  facade_->get_answer(amount, term, interest, payment_type, capitalizacion);
  ui->incom->setText(QString::fromStdString(facade_->get_income()));
  ui->tax->setText(QString::fromStdString(facade_->get_tax()));
  ui->total->setText(QString::fromStdString(facade_->get_total()));
}

int Deposit::convert_type(QString type) {
  std::string payment_type = type.toStdString();
  std::map<std::string, int> translate{
      {"Every day", 365},    {"Every week", 52},      {"Once a month", 12},
      {"Once a quarter", 4}, {"Every six months", 2}, {"Once a year", 1}};
  return translate[payment_type];
}

}  // namespace s21
