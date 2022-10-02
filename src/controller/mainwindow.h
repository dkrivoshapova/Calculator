#pragma once

#include <QtWidgets/QMainWindow>

#include "credit.h"
#include "deposit.h"
#include "facade.h"
#include "plotwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(s21::Facade *facade, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::Facade *facade_;
  void print_error();
  void print_result(double result);
  void expression_with_x(QString entered_text, double x);
  void check_expression_with_x(QString entered_text);
  void expression_without_x(QString entered_text);

 private slots:
  void number_pressed();
  void expression_pressed();
  void ac_pressed();
  void del_pressed();
  void eq_pressed();

  void on_plot_btn_clicked();
  void on_actionCredit_triggered();
  void on_actionDeposit_triggered();
};

}  // namespace s21
