#pragma once

#include <QtWidgets/QDialog>

#include "facade.h"

namespace Ui {
class Credit;
}

namespace s21 {

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(s21::Facade *facade, QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
  s21::Facade *facade_;
};

}  // namespace s21
