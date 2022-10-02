#include "mainwindow.h"

#include <QMessageBox>

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(s21::Facade *facade, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), facade_(facade) {
  ui->setupUi(this);
  connect(ui->zero_btn, SIGNAL(pressed()), this, SLOT(number_pressed()));
  connect(ui->one_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->two_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->three_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->four_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->five_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->six_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->seven_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->eight_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->nine_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->dot_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->sin_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->cos_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->tan_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->asin_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->acos_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->atan_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->plus_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->minus_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->mul_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->mod_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->div_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->pow_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->sqr_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->log_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->ln_btn, SIGNAL(released()), this, SLOT(expression_pressed()));
  connect(ui->e_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->pi_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->x_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->ob_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->cb_btn, SIGNAL(released()), this, SLOT(number_pressed()));
  connect(ui->del_btn, SIGNAL(released()), this, SLOT(del_pressed()));
  connect(ui->ac_btn, SIGNAL(released()), this, SLOT(ac_pressed()));
  connect(ui->eq_btn, SIGNAL(released()), this, SLOT(eq_pressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::number_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString entered_text = ui->math_expression_line_edit->text();
  ui->math_expression_line_edit->setText(entered_text + button_text);
}
void MainWindow::expression_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString entered_text = ui->math_expression_line_edit->text();
  ui->math_expression_line_edit->setText(entered_text + button_text + "(");
}

void MainWindow::ac_pressed() {
  ui->math_expression_line_edit->clear();
  ui->get_x_line_edit->setText("0");
}

void MainWindow::del_pressed() {
  QString entered_text = ui->math_expression_line_edit->text();
  entered_text.resize(entered_text.length() - 1);
  ui->math_expression_line_edit->setText(entered_text);
}

void MainWindow::eq_pressed() {
  QString entered_text = ui->math_expression_line_edit->text();
  if (entered_text.contains("x")) {
    check_expression_with_x(entered_text);
  } else {
    expression_without_x(entered_text);
  }
}

void MainWindow::check_expression_with_x(QString entered_text) {
  QString x_str = ui->get_x_line_edit->text();
  bool check;
  double x = x_str.toDouble(&check);
  if (x_str.isEmpty() || !check) {
    print_error();
    return;
  } else {
    expression_with_x(entered_text, x);
  }
}

void MainWindow::expression_with_x(QString entered_text, double x) {
  try {
    double result = facade_->get_answer(entered_text.toStdString(), x);
    print_result(result);
  } catch (std::invalid_argument &e) {
    QMessageBox::warning(this, "Werror", "Text label incorrect");
  }
}

void MainWindow::expression_without_x(QString entered_text) {
  try {
    double result = facade_->get_answer(entered_text.toStdString());
    print_result(result);
  } catch (std::invalid_argument &e) {
    QMessageBox::warning(this, "Werror", "Text label incorrect");
  }
}

void MainWindow::print_result(double result) {
  QString valueAsString = QString::number(result);
  ui->math_expression_line_edit->setText(valueAsString);
}

void MainWindow::print_error() {
  ui->math_expression_line_edit->setText("Error");
}

void MainWindow::on_plot_btn_clicked() {
  try {
    QString entered_text = ui->math_expression_line_edit->text();
    plotwindow plot(facade_, entered_text);
    plot.setModal(true);
    plot.setWindowTitle("Plot");
    plot.exec();
  } catch (std::invalid_argument &e) {
    QMessageBox::warning(this, "Werror", "ERROR");
  }
}

void MainWindow::on_actionCredit_triggered() {
  Credit credit_window(facade_);
  credit_window.setModal(true);
  credit_window.setWindowTitle("Credit");
  credit_window.exec();
}

void MainWindow::on_actionDeposit_triggered() {
  Deposit deposit_window(facade_);
  deposit_window.setModal(true);
  deposit_window.setWindowTitle("Deposit");
  deposit_window.exec();
}

}  // namespace s21
