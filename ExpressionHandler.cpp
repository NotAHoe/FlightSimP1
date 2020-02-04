#include "ExpressionHandler.h"

// Value functions
// Constructor
Value::Value(double value)
{
    this->val = value;
}
// Destructor
Value::~Value() {
}
// Calculate - returns variable value
double Value::calculate()
{
    return this->val;
}

// Variable functions
// Constructor
Variable::Variable(string varName, double val)
{
    this->name = varName;
    this->value = val;
}
// Destructor
Variable::~Variable() {
}
// Calculate - returns the value itself
double Variable::calculate()
{
    return this->value;
}
// Operations on variable
Variable& Variable::operator++()
{
    ++this->value;
    return *this;
}
Variable& Variable::operator--()
{
    --this->value;
    return *this;
}
Variable& Variable::operator+=(double num)
{
    this->value += num;
    return *this;
}
Variable& Variable::operator-=(double num)
{
    this->value -= num;
    return *this;
}
Variable& Variable::operator++(int)
{
    this->value++;
    return *this;
}
Variable& Variable::operator--(int)
{
    this->value--;
    return *this;
}

// UPlus functions
// Constructor
UPlus::UPlus(Expression* expression)
{
    this->innerExpression = expression;
}
// Destructor
UPlus::~UPlus() {
    if (this->innerExpression != NULL)
    {
        delete this->innerExpression;
    }
}
// Calculate - return the value of the inner expression
double UPlus::calculate()
{
    return this->innerExpression->calculate();
}

// UMinus functions
// Constructor
UMinus::UMinus(Expression* expression)
{
    this->innerExpression = expression;
}
// Destructor
UMinus::~UMinus() {
    if (this->innerExpression != NULL)
    {
        delete this->innerExpression;
    }
}
// Calculate - return the negative value of the inner expression
double UMinus::calculate()
{
    return -1 * this->innerExpression->calculate();
}

// Plus functions
// Constructor
Plus::Plus(Expression* l, Expression* r)
{
    this->left = l;
    this->right = r;
}
// Destructor
Plus::~Plus() {
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}
// Calculate - returns the sum of the inner expressions
double Plus::calculate()
{
    return (this->left)->calculate() + (this->right)->calculate();
}

// Minus functions
// Constructor
Minus::Minus(Expression* l, Expression* r)
{
    this->left = l;
    this->right = r;
}
// Destructor
Minus::~Minus() {
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}
// Calculate - returns the difference between the inner expressions
double Minus::calculate()
{
    return (this->left)->calculate() - (this->right)->calculate();
}

// Mul functions
// Constructor
Mul::Mul(Expression* l, Expression* r)
{
    this->left = l;
    this->right = r;
}
// Destructor
Mul::~Mul() {
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}
// Calculate - returns the multipication of the inner expressions
double Mul::calculate()
{
    return (this->left)->calculate() * (this->right)->calculate();
}

// Div functions
// Constructor
Div::Div(Expression* l, Expression* r)
{
    this->left = l;
    this->right = r;
}
// Destructor
Div::~Div() {
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}
// Calculate - returns the division between the inner expressions
double Div::calculate()
{
    double divide = (this->right)->calculate();
    if (divide == 0)
    {
        throw "Division by 0 is not allowed!";
    }
    return (this->left)->calculate() / divide;
}

// Interpreter functions
// Constructor
//Interpreter::Interpreter()
//{
//
//}
// Destructor
Interpreter::~Interpreter()
{
}
// Interpret - recieves a string and translating it to an expression
Expression * Interpreter::interpret(string e)
{
    // Defining helpful data structures for the Shunting Yard algorithm

    // Stores the Reverse Polish Notation form of the expression
    queue <string> rpnQueue;
    // Stores the operators in the expression
    stack <string> operators;
    // Stores each math function precedence
    map<string, int> precedences;
    // Will be used as a string-builder for variable names and numbers
    string currString = "";
    // Stores the last character that the algorithm checked
    char last;

    // Defining the functions' precedences
    precedences["+"] = 2;
    precedences["-"] = 2;
    precedences["*"] = 3;
    precedences["/"] = 3;
    precedences[")"] = 4;

    // Check if the string contains any '-|+x', an unary operation before a variable with no bracket
    regex varPattern("([^a - zA - Z | \\_ | 1 - 9 | ][-| +][a - zA - Z | \\_] | ^[-| +][a - zA - Z | \\_])");
    if (regex_match(e, varPattern))
    {
        throw "Invalid expression string";
    }
    regex operatorPattern("([\\+|\\-|\\*|\\/])([\\+|\\-|\\*|\\/])");
    if (regex_match(e, operatorPattern))
    {
        throw "Invalid expression string";
    }

    // Going over the string, character by character
    for (string::size_type i = 0; i < e.size(); i++)
    {
        // If the character isn't an operator, add the char to the string builder
        if (!isOperator(e[i]) && e[i] != ' ')
        {
            currString += e[i];
            if (i == e.size() - 1)
            {
                // Checking if the string builder contains a variable or a number
                if (!isVarValid(currString) && !isNumValid(currString))
                {
                    throw "The string is invalid!";
                }
                // Push into the elements queue
                rpnQueue.push(currString);
            }
        }
        else if (e[i] != ' ')
        {
            // If the character is an operator, check if the string builder isn't empty
            if (!currString.empty())
            {
                // Checking if the string builder contains a variable or a number
                if (!isVarValid(currString) && !isNumValid(currString))
                {
                    throw "The string is invalid!";
                }
                // Push into the elements queue
                rpnQueue.push(currString);
            }
            // Since the queue and stack are string type, convert the current character to string
            currString = e[i];
            // Check if this is the first operator found
            if (!operators.empty())
            {
                // Opening bracket always enters the queue
                if (e[i] == '(')
                {
                    operators.push(currString);
                }
                    // If a closing bracket was found
                else if (e[i] == ')')
                {
                    // Pass every value from the stack to the queue until an opening bracket is found
                    while (operators.top() != "(")
                    {
                        rpnQueue.push(operators.top());
                        operators.pop();

                        if (operators.empty())
                        {
                            throw "There's a closing bracket with no opening bracket!";
                            break;
                        }
                    }
                    // Pop out the opening bracket
                    operators.pop();
                }
                    // If the current char is + and it came after an opening bracket, it's a unary plus
                else if (e[i] == '+' && last == '(')
                {
                    operators.push("P");
                }
                    // If the current char is - and it came after an opening bracket, it's a unary minus
                else if (e[i] == '-' && last == '(')
                {
                    operators.push("N");
                }
                    // If the the current operator has lesser or equal precedence to the operator in the top of the stack
                else if (precedences[operators.top()] >= precedences[currString])
                {
                    // Replace the operators and put the one from the stack in the queue
                    rpnQueue.push(operators.top());
                    operators.pop();
                    operators.push(currString);
                }
                else
                {
                    operators.push(currString);
                }
            }
            else
            {
                // If the first char is +, it's a unary plus
                if (e[i] == '+' && rpnQueue.empty())
                {
                    operators.push("P");
                }
                // If the first char is -, it's a unary minus
                if (e[i] == '-' && rpnQueue.empty())
                {
                    operators.push("N");
                }
                else
                {
                    operators.push(currString);
                }
            }
            currString = "";
        }

        if (e[i] != ' ')
            last = e[i];
    }

    // Put the leftovers from the stack in the queue as well
    while (!operators.empty())
    {
        if (operators.top() != "(")
        {
            rpnQueue.push(operators.top());
            operators.pop();
        }
        else
        {
            throw "There's an opening bracket without a closing bracket!";
        }
    }

    // RPN arrangement finished. Defining helpful data structures for the conversion

    // Used as a temp expression for saving data while inserting and popping values
    Expression* ex = nullptr;
    // An expression stack to store the expressions converted from rpn
    stack <Expression*> expressions;

    // Go over the elements in the rpn
    while (!rpnQueue.empty())
    {
        // Getting the current element
        currString = rpnQueue.front();
        rpnQueue.pop();

        // Checking if it's an operator
        if (currString != "+" &&
            currString != "-" &&
            currString != "*" &&
            currString != "/" &&
            currString != "P" &&
            currString != "N")
        {
            expressions.push(convertor(currString));
        }
        else
        {
            // If the operator is unary, at least one expression is needed
            if (expressions.size() < 1)
            {
                throw "Error in logical expression";
            }

            // If it's a unary plus, replace the current expression with a unary plus on the expression
            if (currString == "P")
            {
                ex = new UPlus(expressions.top());
                expressions.pop();
                expressions.push(ex);
            }
                // If it's a unary minus, replace the current expression with its negative
            else if (currString == "N")
            {
                ex = new UMinus(expressions.top());
                expressions.pop();
                expressions.push(ex);
            }
            else
            {
                // If the operator is binary, at least two expression is needed
                if (expressions.size() < 2)
                {
                    throw "Error in logical expression";
                }

                Expression* a = expressions.top();
                expressions.pop();
                Expression* b = expressions.top();
                expressions.pop();

                // If it's +, replace the last two expressions with their sum
                if (currString == "+")
                {
                    expressions.push(new Plus(b, a));
                }
                    // If it's -, replace the last two expressions with their difference
                else if (currString == "-")
                {
                    expressions.push(new Minus(b, a));
                }
                    // If it's *, replace the last two expressions with their multipication
                else if (currString == "*")
                {
                    ex = new Mul(b, a);
                    expressions.push(ex);
                }
                    // If it's /, replace the last two expressions with their division
                else if (currString == "/")
                {
                    ex = new Div(b, a);
                    expressions.push(ex);
                }
            }
        }
    }
    // If there are more than one expression, something went wrong
    if (expressions.size() > 1)
    {
        throw "Error in logical expression";
    }

    return expressions.top();
}
// Convertor - recieves a string and converting it to a variable or a number
Expression * Interpreter::convertor(string s)
{
    // If the string is a number
    if (isNumValid(s))
    {
        return new Value(stod(s));
    }
        // If the string is a variable
    else if (isVarValid(s))
    {
        // If the variable exists and has a value, create it
        if (this->variables.find(s) != this->variables.end())
        {
            return new Variable(s, this->variables[s]);
        }

        throw "There's a variable with no value";
    }
    throw "Error in string";
    return nullptr;
}
// Set Variables - recieves a string, reading it and with the info given, creating variables
void Interpreter::setVariables(string vars)
{
    // Checking if the string is of the form 'variable=number;'
    regex pattern("^(([a-z]|[A-Z]|\\_)(\\_|[a-z]|[A-Z]|[0-9])*=-?(0|([1-9][0-9]*))(\\.[0-9]+)?;?)*$");
    if (!regex_match(vars, pattern))
    {
        throw "Invalid variables string";
    }

    // Flags for reading variables or numbers
    int isVar = 1;
    int isNum = 0;
    // Strings for current data
    string currVar = "";
    string currNum = "";
    // Going over the data string
    for (char &c : vars)
    {
        // If = was found, it means the variable name has ended
        if (c == '=')
        {
            isNum = 1;
            isVar = 0;
        }
            // If = was found, it means the number has ended
        else if (c == ';')
        {
            isNum = 0;
            isVar = 1;
            this->variables[currVar] = stod(currNum);
            currVar = "";
            currNum = "";
        }
            // Check what flag is up and read accordingly
        else if (isVar)
        {
            currVar += c;
        }
        else if (isNum)
        {
            currNum += c;
        }
    }

    // In case the string doesn't end with ;
    if (!currNum.empty() && isNumValid(currNum))
    {
        this->variables[currVar] = stod(currNum);
    }
}
// Is Variable Valid - recieves a string and checking if it's a valid variable name
int Interpreter::isVarValid(string s)
{
    regex ex("^([a-z]|[A-Z]|\\_)(\\_|[a-z]|[A-Z]|[0-9])*$");
    if (regex_match(s, ex))
    {
        return 1;
    }
    return 0;
}
// Is Number Valid - recieves a string and checking if it's a valid number
int Interpreter::isNumValid(string s)
{
    regex ex("^-?(0|([1-9][0-9]*))(\\.[0-9]+)?$");
    if (regex_match(s, ex))
    {
        return 1;
    }
    return 0;
}
// Is Operator - recieves a string and checking if it's a valid operator
int Interpreter::isOperator(char c)
{
    if (c != '+' &&
        c != '-' &&
        c != '*' &&
        c != '/' &&
        c != '(' &&
        c != ')')
    {
        return 0;
    }
    return 1;
}

Interpreter* Interpreter::singleInter = 0;

Interpreter *Interpreter::instance() {
    if (singleInter == 0)
    {
        singleInter = new Interpreter();
    }

    return singleInter;
}