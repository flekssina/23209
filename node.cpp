#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс для узлов дерева
class Node {
public:
  virtual ~Node() {}
};

// Класс для операций (+, -, *, /)
class Op : public Node {
public:
  enum Type { Plus, Minus, Multiply, Divide };
  Op(Type type) : type(type), left(nullptr), right(nullptr) {}
  Type getType() const { return type; }

  Node* left;
  Node* right;

  ~Op() { delete left; delete right; }
  
private:
  Type type;
};

// Класс для числовых значений
class Value : public Node {
public:
  Value(int value) : value(value) {}
  int getValue() const { return value; }

private:
  int value;
};

// Класс парсера
class Parser {
public:
  Parser(const std::string& text) : text(text), pos(0) {}

  // Метод для построения дерева разбора
  Node* parse() {
    skipSpaces();
    return S();
  }

private:
  const std::string text;
  int pos;

  // Вспомогательные функции для парсинга
  Node* S() {
    skipSpaces();
    Node* left = M();

    skipSpaces();
    if (match('+')) {
      Op* op = new Op(Op::Plus);
      op->left = left;
      op->right = S();
      return op;
    } else if (match('-')) {
      Op* op = new Op(Op::Minus);
      op->left = left;
      op->right = S();
      return op;
    }
    return left;
  }

  Node* M() {
    skipSpaces();
    Node* left = P();

    skipSpaces();
    if (match('*')) {
      Op* op = new Op(Op::Multiply);
      op->left = left;
      op->right = M();
      return op;
    } else if (match('/')) {
      Op* op = new Op(Op::Divide);
      op->left = left;
      op->right = M();
      return op;
    }
    return left;
  }

  Node* P() {
    skipSpaces();
    if (isDigit(text[pos])) {
      return new Value(readInt());
    } else if (match('(')) {
      Node* expr = S();
      if (!match(')')) {
        throw std::runtime_error("Отсутсвует закрывающая скобка");
      }
      return expr;
    }
    throw std::runtime_error("Непредвиденный символ");
  }

  // Пропускает пробелы
  void skipSpaces() {
    while (pos < text.length() && text[pos] == ' ') {
      pos++;
    }
  }

  // Проверяет, совпадает ли текущий символ с ожидаемым
  bool match(char c) {
    skipSpaces();
    if (pos < text.length() && text[pos] == c) {
      pos++;
      skipSpaces(); 
      return true;
    }
    return false;
  }

  bool isDigit(char c) {
    return c >= '0' && c <= '9';
  }

  int readInt() {
    skipSpaces();
    int value = 0;
    while (pos < text.length() && isDigit(text[pos])) {
      value = value * 10 + (text[pos] - '0');
      pos++;
    }
    skipSpaces(); 
    return value;
  }
};

// Функция для вывода дерева разбора
void printTree(Node* node, int level) {
  if (node == nullptr) {
    return;
  }
  for (int i = 0; i < level; i++) {
    std::cout << "  ";
  }
  if (auto valNode = dynamic_cast<Value*>(node)) {
    std::cout << "Value: " << valNode->getValue() << std::endl;
  } else if (auto opNode = dynamic_cast<Op*>(node)) {
    switch (opNode->getType()) {
      case Op::Plus:
        std::cout << "Op: +" << std::endl;
        break;
      case Op::Minus:
        std::cout << "Op: -" << std::endl;
        break;
      case Op::Multiply:
        std::cout << "Op: *" << std::endl;
        break;
      case Op::Divide:
        std::cout << "Op: /" << std::endl;
        break;
    }
    printTree(opNode->left, level + 1);
    printTree(opNode->right, level + 1);
  }
}

int main() {
  std::string input;
  std::cout << "Введите арифметическое выражение: ";
  std::getline(std::cin, input);

  Parser parser(input);
  try {
    Node* root = parser.parse();
    std::cout << "Дерево разбора:" << std::endl;
    printTree(root, 0);
    delete root;
  } catch (const std::runtime_error& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}
