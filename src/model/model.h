#pragma once

#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <stack>
#include <string>

#include "../temp/temp.h"
using std::regex;
using std::regex_iterator;
using std::stack;
using std::string;
using std::vector;

namespace s21 {

enum lexem_type {
  PLUS,
  MINUS,
  MULT,
  DIV,
  MOD,
  POW,
  LOG,
  SQRT,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  LN,
  OPEN,
  X,
  CLOSE,
  NUMBER
};

class Model {
  class Lexem {
    int _type;
    long double _value;
    int _preority;

   public:
    Lexem(string simbol, int previous_type);
    int get_type();
    long double get_value();
    int get_preoritet();

    friend std::ostream &operator<<(std::ostream &os, Lexem &date) {
      return os << date.get_type() << " " << date.get_value() << " "
                << date.get_preoritet();
    }

    int ident_type(string lexem);
    void ident_preority();
    long double convert_to_number(string number);
    void set_type(int type);
    void set_value(long double value);
    void set_preoritet(int preoritet);
  };
  string _math_expression;

 public:
  double calc(const string &expression);
  double calc(const string &expression, double value);
  std::pair<vector<double>, vector<double>> get_coordinates(
      const string &expression, Plot plot_features);
  bool chec_plot_features(Plot plot_features);

  vector<Lexem> strip();
  void simplify(string &math_expression);
  vector<Lexem> string_to_lexems(string expression);
  void replace_x(vector<Lexem> &expression, double value);
  vector<Lexem> prepare_expression(string &math_expression);
  bool correct_brackets(string expression);
  bool check_operators(vector<Lexem> &lexems);
  stack<Lexem> marshalling_station(vector<Lexem> expression);
  double polish_notation(vector<Lexem> &lexems);
  void find_open_brackets(stack<Lexem> &out, stack<Lexem> &operation);
  void transport_operations(stack<Lexem> &out, stack<Lexem> &operation,
                            int preor);
  void transfer(stack<Lexem> &out, stack<Lexem> &operation);

  double get_result(const stack<Lexem> &polish_notation);
  stack<Lexem> calculation(stack<Lexem> polish_notation);
  void unary(stack<Lexem> &result);
  void binary(stack<Lexem> &result);

  void print(stack<Lexem> operation);
};

}  //  namespace s21
