#include "model.h"

using s21::Model;

double Model::calc(const string &expression) {
  vector<Lexem> lexems = string_to_lexems(expression);
  return polish_notation(lexems);
}

double Model::calc(const string &expression, double value) {
  vector<Lexem> lexems = string_to_lexems(expression);
  replace_x(lexems, value);
  return polish_notation(lexems);
}

vector<Model::Lexem> Model::string_to_lexems(string expression) {
  if (expression.empty()) {
    throw std::invalid_argument("ERROR");
  }
  if (!correct_brackets(expression)) {
    throw std::invalid_argument("ERROR");
  }
  if (expression[0] == '.') {
    throw std::invalid_argument("ERROR");
  }

  _math_expression = expression;
  simplify(_math_expression);
  return strip();
}

bool Model::correct_brackets(string expression) {
  int count_open = 0;
  int count_close = 0;
  for (size_t i = 0; i < expression.length(); i++) {
    if (expression[i] == ')') {
      count_open++;
    }
    if (expression[i] == '(') {
      count_close++;
    }
  }
  return count_close == count_open;
}

double Model::polish_notation(vector<Model::Lexem> &lexems) {
  if (lexems.size() == 1 && lexems[0].get_type() != NUMBER)
    throw std::invalid_argument("ERROR");
  if (check_operators(lexems)) {
    throw std::invalid_argument("ERROR");
  }
  stack<Lexem> polish_notation = marshalling_station(lexems);
  return get_result(polish_notation);
}

void Model::replace_x(vector<Lexem> &expression, double value) {
  for (size_t i = 0; i < expression.size(); i++) {
    if (expression[i].get_type() == X) {
      expression[i].set_value(value);
      expression[i].set_type(NUMBER);
    }
  }
}

stack<Model::Lexem> Model::marshalling_station(vector<Lexem> expression) {
  stack<Lexem> out;
  stack<Lexem> operation;
  for (size_t i = 0; i < expression.size(); i++) {
    int type = expression[i].get_type();
    int preor = expression[i].get_preoritet();
    if (type == NUMBER) {
      out.push(expression[i]);
    } else if (preor == 5 || type == OPEN) {
      operation.push(expression[i]);
    } else if (type == CLOSE) {
      find_open_brackets(out, operation);
    } else {
      transport_operations(out, operation, preor);
      operation.push(expression[i]);
    }
  }
  transfer(out, operation);
  transfer(operation, out);
  return operation;
}

void Model::find_open_brackets(stack<Lexem> &out, stack<Lexem> &operation) {
  if (operation.size() < 1) {
    throw std::invalid_argument("ERROR");
  }
  Lexem temp = operation.top();
  operation.pop();
  while (temp.get_type() != OPEN && operation.size() > 0) {
    out.push(temp);
    temp = operation.top();
    operation.pop();
  }
}

void Model::transport_operations(stack<Lexem> &out, stack<Lexem> &operation,
                                 int preor) {
  if (operation.size() > 0) {
    Lexem temp = operation.top();
    while (temp.get_preoritet() > preor ||
           (temp.get_preoritet() == preor && preor != 3)) {
      operation.pop();
      out.push(temp);
      if (operation.size() > 0) {
        temp = operation.top();
      } else {
        break;
      }
    }
  }
}

void Model::transfer(stack<Lexem> &to, stack<Lexem> &from) {
  while (from.size()) {
    Lexem temp = from.top();
    from.pop();
    to.push(temp);
  }
}

stack<Model::Lexem> Model::calculation(stack<Lexem> polish_notation) {
  stack<Lexem> result;
  while (polish_notation.size() > 0) {
    Lexem temp = polish_notation.top();
    polish_notation.pop();
    result.push(temp);
    if (temp.get_preoritet() > 3) {
      unary(result);
    } else if (temp.get_preoritet() > 0) {
      binary(result);
    }
  }
  return result;
}

double Model::get_result(const stack<Lexem> &polish_notation) {
  stack<Lexem> result = calculation(polish_notation);
  if (result.size() != 1) {
    throw std::invalid_argument("ERROR");
  }
  return result.top().get_value();
}

void Model::unary(stack<Lexem> &result) {
  double (*operations[11])(double) = {log10, sqrt, cos,  sin, tan,
                                      acos,  asin, atan, log};
  if (result.size() < 2) {
    throw std::invalid_argument("ERROR");
  }
  Lexem operation = result.top();
  result.pop();
  Lexem number = result.top();
  result.pop();
  double num = number.get_value();
  if (operation.get_type() == MINUS) {
    num *= (-1);
  } else if (operation.get_type() == PLUS) {
    num *= (1);
  } else {
    num = operations[operation.get_type() - 6](number.get_value());
  }
  number.set_value(num);
  result.push(number);
}
double sum(double one, double two) { return one + two; }

double sub(double one, double two) { return one - two; }

double mult(double one, double two) { return one * two; }

double div(double one, double two) { return one / two; }

double mod(double one, double two) {
  int div_ = one / two;
  return one - (two * div_);
}

void Model::binary(stack<Lexem> &result) {
  double (*operations[11])(double, double) = {sum, sub, mult, div, mod, pow};
  if (result.size() < 3) {
    throw std::invalid_argument("ERROR");
  }
  Lexem operation = result.top();
  result.pop();
  Lexem number1 = result.top();
  result.pop();
  double num1 = number1.get_value();
  Lexem number2 = result.top();
  result.pop();
  double num2 = number2.get_value();
  double num = operations[operation.get_type()](num2, num1);
  number1.set_value(num);
  result.push(number1);
}

int Model::Lexem::ident_type(const string lexem) {
  vector<string> operations = {"+",    "-",    "*",   "÷",   "%",   "^",
                               "log",  "√",    "cos", "sin", "tan", "acos",
                               "asin", "atan", "ln",  "(",   "x",   ")"};
  for (size_t i = 0; i < operations.size(); i++) {
    if (operations[i] == lexem) {
      return i;
    }
  }
  set_value(convert_to_number(lexem));
  return operations.size();
}

void Model::Lexem::ident_preority() {
  vector<int> oper_preor = {1, 1, 2, 2, 2, 3, 5, 5, 5, 5,
                            5, 5, 5, 5, 5, 0, 0, 0, 0};
  int type = get_type();
  if (type < MULT) {
    if (get_preoritet() > 15) {
      set_preoritet(1);
    } else {
      set_preoritet(4);
    }
  } else {
    set_preoritet(oper_preor[type]);
  }
}

Model::Lexem::Lexem(string lexem, int previous_type = 0) {
  set_value(0);
  set_preoritet(previous_type);
  set_type(ident_type(lexem));
  ident_preority();
}

vector<Model::Lexem> Model::strip() {
  regex e(
      "x|cos|sin|tan|acos|asin|atan|ln|log|√|e|π|\\(|\\)|\\+|-|\\*|\\÷|%|"
      "\\^|[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?");
  regex_iterator<string::iterator> rit(_math_expression.begin(),
                                       _math_expression.end(), e);
  regex_iterator<string::iterator> rend;
  vector<Lexem> valixan;
  int previous = 0;
  for (; rit != rend; ++rit) {
    Lexem a(rit->str(), previous);
    previous = a.get_type();
    valixan.push_back(a);
  }

  return valixan;
}

bool Model::check_operators(vector<Model::Lexem> &lexems) {
  for (size_t i = 0; i < lexems.size() - 1; i++) {
    int type = lexems[i].get_type();
    int next_type = lexems[i + 1].get_type();
    if (type == next_type && type < OPEN) {
      return true;
    }
    if ((type == PLUS or type == MINUS) || (type < LOG && type > MINUS)) {
      if (next_type < LOG && next_type > MINUS) {
        return true;
      }
    }
  }
  return false;
}

void Model::simplify(string &math_expression) {
  for (size_t i = 0; i < math_expression.length() - 1; i++) {
    if (math_expression[i] == '+') {
      if (math_expression[i + 1] == '+') {
        math_expression.erase(i, 1);
        i--;
      } else if (math_expression[i + 1] == '-') {
        math_expression.replace(i, 2, "-");
        i--;
      }
    }
    if (math_expression[i] == '-') {
      if (math_expression[i + 1] == '+') {
        math_expression.replace(i, 2, "-");
        i--;
      } else if (math_expression[i + 1] == '-') {
        math_expression.replace(i, 2, "+");
        i--;
      }
    }
  }
}

long double Model::Lexem::convert_to_number(string number) {
  if (number == "π") {
    return M_PI;
  }
  if (number == "e") {
    return M_E;
  }
  if (number == ".") {
    throw std::invalid_argument("ERROR");
  }
  std::string::size_type sz;
  long double num = std::stod(number, &sz);
  return num;
}

std::pair<vector<double>, vector<double>> Model::get_coordinates(
    const string &expression, Plot plot_features) {
  vector<double> x;
  vector<double> y;
  if (!chec_plot_features(plot_features)) {
    throw std::invalid_argument("ERROR");
  }
  for (auto temp = plot_features.x_min; temp < plot_features.x_max;
       temp += plot_features.scale) {
    x.push_back(temp);
    y.push_back(calc(expression, temp));
  }
  return {x, y};
}

bool Model::chec_plot_features(Plot plot_features) {
  double n = (plot_features.x_max - plot_features.x_min) / plot_features.scale;
  if (plot_features.scale < 0) {
    return false;
  }
  if (plot_features.x_min > plot_features.x_max) {
    return false;
  }
  if (plot_features.y_min > plot_features.y_max) {
    return false;
  }
  if (n > 1000000) {
    return false;
  }
  return true;
}

int Model::Lexem::get_type() { return _type; }
long double Model::Lexem::get_value() { return _value; }
int Model::Lexem::get_preoritet() { return _preority; }
void Model::Lexem::set_type(int type) { _type = type; }
void Model::Lexem::set_value(long double value) { _value = value; }
void Model::Lexem::set_preoritet(int preoritet) { _preority = preoritet; }
