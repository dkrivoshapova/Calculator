#pragma once

#include <QDialog>
#include <QVector>

#include "facade.h"

namespace Ui {
class plotwindow;
}

namespace s21 {

class plotwindow : public QDialog {
  Q_OBJECT

 public:
  explicit plotwindow(s21::Facade *facade, QString math_expression,
                      QWidget *parent = nullptr);
  ~plotwindow();

 private slots:
  void on_get_btn_clicked();

 private:
  Ui::plotwindow *ui;
  s21::Facade *facade_;
  QString math_expression_;
  QVector<double> x, y;
  void plot_expression();
  QVector<double> convert_std_vector(std::vector<double> &vec);
};

}  // namespace s21
