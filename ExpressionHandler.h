#include "Expression.h"
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include <regex>
// UnaryExpression declaration
class UnaryExpression : public Expression
{
protected:
    Expression* innerExpression;
};
// BinaryExpression declaration
class BinaryExpression : public Expression
{
protected:
    Expression* right;
    Expression* left;
};
// Value declaration
class Value : public Expression
{
private:
    double val;
public:
    Value(double value);
    virtual ~Value();
    double calculate();
};
// Variable declaration
class Variable : public Expression
{
private:
    string name;
    double value;
public:
    Variable(string name, double value);
    virtual ~Variable();
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double num);
    Variable& operator-=(double num);
    Variable& operator++(int);
    Variable& operator--(int);
    double calculate();
};
// UPlus declaration
class UPlus : public UnaryExpression
{
public:
    UPlus(Expression* expression);
    virtual ~UPlus();
    double calculate();
};
// UMinus declaration
class UMinus : public UnaryExpression
{
public:
    UMinus(Expression* expression);
    virtual ~UMinus();
    double calculate();
};
// Plus declaration
class Plus : public BinaryExpression
{
public:
    Plus(Expression * left, Expression * right);
    virtual ~Plus();
    double calculate();
};
// Minus declaration
class Minus : public BinaryExpression
{
public:
    Minus(Expression * left, Expression * right);
    virtual ~Minus();
    double calculate();
};
// Mul declaration
class Mul : public BinaryExpression
{
public:
    Mul(Expression * left, Expression * right);
    virtual ~Mul();
    double calculate();
};
// Div declaration
class Div : public BinaryExpression
{
public:
    Div(Expression * left, Expression * right);
    virtual ~Div();
    double calculate();
};
// Interpreter declaration
class Interpreter
{
private:
    map<string, double> variables;
    int isVarValid(string s);
    int isNumValid(string s);
    int isOperator(char c);
    Interpreter(){}
    static Interpreter *singleInter;
public:
    static Interpreter *instance();
    virtual ~Interpreter();
    Expression* interpret(string e);
    Expression* convertor(string s);
    void setVariables(string vars);
};