#include "plotwindow.h"

#include <iostream>

#include "ui_plotwindow.h"

namespace s21 {

plotwindow::plotwindow(s21::Facade *facade, QString math_expression,
                       QWidget *parent)
    : QDialog(parent),
      ui(new Ui::plotwindow),
      facade_(facade),
      math_expression_(math_expression) {
  ui->setupUi(this);
  plot_expression();
}

plotwindow::~plotwindow() { delete ui; }

void plotwindow::plot_expression() {
  double x_max = ui->x_max->text().toDouble();
  double x_min = ui->x_min->text().toDouble();
  double y_max = ui->y_max->text().toDouble();
  double y_min = ui->y_min->text().toDouble();
  double scale = ui->scale->text().toDouble();
  s21::Plot plot(x_min, x_max, y_min, y_max, scale);
  auto pair = facade_->get_coordinates(math_expression_.toStdString(), plot);
  ui->widget->xAxis->setRange(x_min - 1, x_max + 1);
  ui->widget->yAxis->setRange(y_min - 1, y_max + 1);
  ui->widget->addGraph();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      (QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(188, 143, 143),
                       QColor(188, 143, 143), 5)));
  ui->widget->graph(0)->addData(convert_std_vector(pair.first),
                                convert_std_vector(pair.second));
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->replot();
}

QVector<double> plotwindow::convert_std_vector(std::vector<double> &vec) {
  QVector<double> result;
  for (auto &i : vec) {
    result.push_back(i);
  }
  return result;
}

void plotwindow::on_get_btn_clicked() {
  try {
    plot_expression();
  } catch (std::invalid_argument &e) {
    QMessageBox::warning(this, "Werror", "ERROR");
  }
}

}  // namespace s21
