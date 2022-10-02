#include "credit.h"

#include <QMessageBox>

#include "ui_credit.h"

namespace s21 {

Credit::Credit(s21::Facade *facade, QWidget *parent)
    : QDialog(parent), ui(new Ui::Credit), facade_(facade) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  double amount = ui->amount_line->text().toDouble();
  int term = ui->term_line->text().toInt();
  double interest_rate = ui->rate_line->text().toDouble();
  int type_date = MONTH;
  if (ui->yearButton->isChecked()) {
    type_date = YEAR;
  }
  int payment_type = DIFFERENTIATED;
  QString credit_type = ui->credit_type->currentText();
  if (credit_type == "annuity") {
    payment_type = ANNUITY;
  }
  try {
    facade_->get_answer(amount, term, type_date, interest_rate, payment_type);
    ui->overp_line->setText(QString::fromStdString(facade_->get_overpayment()));
    ui->payment_line->setText(
        QString::fromStdString(facade_->get_monthly_payment()));
    ui->totalp_line->setText(
        QString::fromStdString(facade_->get_total_payment()));
  } catch (std::invalid_argument &e) {
    QMessageBox::warning(this, "Werror", "ERROR");
  }
}

}  // namespace s21
