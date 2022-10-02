#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>

#include "facade.h"

namespace Ui {
class Deposit;
}

namespace s21 {

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(s21::Facade *facade, QWidget *parent = nullptr);
  ~Deposit();
  int convert_type(QString type);

 private slots:
  void on_Calc_clicked();

 private:
  Ui::Deposit *ui;
  s21::Facade *facade_;
};

}  // namespace s21
