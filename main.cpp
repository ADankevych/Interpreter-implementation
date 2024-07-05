#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
#include <map>
using namespace std;

class Token {
public:
    static queue<string> QueueToken(const string &numExpression) {
        queue<string> queueTokens;
        stack<string> buffer;
        const string operators = "+-*/";

        for (size_t i = 0; i < numExpression.length(); i++) {
            char element = numExpression[i];

            if (isdigit(element) || element == '.') {
                buffer.push(string(1, element));
            } else if (element == '(' || element == ')' || element == ',') {
                if (!buffer.empty()) {
                    string number;
                    while (!buffer.empty()) {
                        number = buffer.top() + number;
                        buffer.pop();
                    }
                    queueTokens.push(number);
                }
                queueTokens.push(string(1, element));
            } else if (operators.find(element) != string::npos) {
                if (i == 0 || (i > 0 && operators.find(numExpression[i - 1]) != string::npos)) {
                    buffer.push(string(1, element));
                } else {
                    if (!buffer.empty()) {
                        string number;
                        while (!buffer.empty()) {
                            number = buffer.top() + number;
                            buffer.pop();
                        }
                        queueTokens.push(number);
                    }
                    queueTokens.push(string(1, element));
                }
            } else if (numExpression.substr(i, 3) == "min" ||
                       numExpression.substr(i, 3) == "max" ||
                       numExpression.substr(i, 3) == "pow") {
                queueTokens.push(numExpression.substr(i, 3));
                i += 2;
            }
        }

        if (!buffer.empty()) {
            string number;
            while (!buffer.empty()) {
                number = buffer.top() + number;
                buffer.pop();
            }
            queueTokens.push(number);
        }

        return queueTokens;
    }
};

class PolishNotation {
public:
    static int OperatorsPrecedence(const string &op) {
        switch (op[0]) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case 'm':
            case 'p':
                return 3;
            default:
                return 0;
        }
    }

    static queue<string> ShuntingYard(queue<string> &tokens) {
        queue<string> queueOutput;
        stack<string> notationStack;

        while (!tokens.empty()) {
            string token = tokens.front();
            tokens.pop();

            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                queueOutput.push(token);
            } else if (token == ",") {
                while (!notationStack.empty() && notationStack.top() != "(") {
                    queueOutput.push(notationStack.top());
                    notationStack.pop();
                }
            } else if (token == "(") {
                notationStack.push(token);
            } else if (token == ")") {
                while (!notationStack.empty() && notationStack.top() != "(") {
                    queueOutput.push(notationStack.top());
                    notationStack.pop();
                }
                if (!notationStack.empty() && notationStack.top() == "(") {
                    notationStack.pop();
                }
            } else if (token == "min" || token == "max" || token == "pow") {
                notationStack.push(token);
            } else {
                while (!notationStack.empty() && OperatorsPrecedence(token) <= OperatorsPrecedence(notationStack.top())) {
                    queueOutput.push(notationStack.top());
                    notationStack.pop();
                }
                notationStack.push(token);
            }
        }

        while (!notationStack.empty()) {
            queueOutput.push(notationStack.top());
            notationStack.pop();
        }

        return queueOutput;
    }
};

class Calculator {
public:
    static double ChooseOperation(const string &operation, double operand1, double operand2) {
        switch (operation[0]) {
            case '+':
                return operand1 + operand2;
            case '-':
                return operand1 - operand2;
            case '*':
                return operand1 * operand2;
            case '/':
                return operand1 / operand2;
            case 'm':
                if (operation == "min") return min(operand1, operand2);
                if (operation == "max") return max(operand1, operand2);
            case 'p':
                return pow(operand1, operand2);
            default:
                return 0;
        }
    }

    static double Calculate(queue<string> &tokens) {
        stack<double> stack;
        while (!tokens.empty()) {
            string token = tokens.front();
            tokens.pop();

            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                stack.push(stod(token));
            } else {
                double operand2 = stack.top();
                stack.pop();
                double operand1 = stack.top();
                stack.pop();
                stack.push(ChooseOperation(token, operand1, operand2));
            }
        }

        return stack.top();
    }
};

class Variable {
public:
    static void VariableValue(string input){
        int counter1 = strlen("var ");
        int counter2 = strlen("var ");
        map<string, double> variables;
        while(input[counter1] != ' ' && input[counter1] != '=') {
            counter1++;
        }
        string varName = input.substr(counter2, counter1 - counter2);
        size_t positionEquals = input.find("=");
        string varValue = input.substr(positionEquals, input.length() - positionEquals);

        queue<string> tokensVar = Token::QueueToken(varValue);
        queue<string> outputVar = PolishNotation::ShuntingYard(tokensVar);
        double resultVar = Calculator::Calculate(outputVar);
        variables[varName] = resultVar;

        getline(cin, input);
        size_t positionVar = input.find(varName);
        while (positionVar != string::npos) {
            input.replace(positionVar, varName.length(), to_string(resultVar));
            positionVar = input.find(varName, positionVar + to_string(resultVar).length());
        }

        queue<string> tokensWithVar = Token::QueueToken(input);
        queue<string> outputWithVar = PolishNotation::ShuntingYard(tokensWithVar);
        double resultWithVar = Calculator::Calculate(outputWithVar);

        cout << resultWithVar << endl;
    }

};

int main() {
    string input;
    while (true){
        getline(cin, input);

        switch (input[0]){
            case'0':
                cout << "Bye";
                return 0;
            case 'v':
                Variable::VariableValue(input);
                break;

            default:
                queue<string> tokens = Token::QueueToken(input);
                queue<string> output = PolishNotation::ShuntingYard(tokens);
                double result = Calculator::Calculate(output);
                cout << result;
                break;
        }
    }
    return 0;
}
