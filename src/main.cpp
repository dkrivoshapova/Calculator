#include <QApplication>

#include "controller/facade.h"
#include "controller/mainwindow.h"
#include "model/model.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::CreditModel credit;
  s21::DepositModel deposit;
  s21::Facade facade(&model, &credit, &deposit);
  s21::MainWindow w(&facade);
  w.setWindowTitle("SmartCalc");
  w.show();
  return a.exec();
}
