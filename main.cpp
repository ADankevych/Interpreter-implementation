#include <iostream>
#include <queue>
#include <stack>
#include <string>
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
                buffer.emplace(1, element);
            } else if (element == '(' || element == ')' || element == ',') {
                if (!buffer.empty()) {
                    string number;
                    while (!buffer.empty()) {
                        number = buffer.top() + number;
                        buffer.pop();
                    }
                    queueTokens.push(number);
                }
                queueTokens.emplace(1, element);
            } else if (operators.find(element) != string::npos) {
                if (i == 0 || (i > 0 && operators.find(numExpression[i - 1]) != string::npos)) {
                    buffer.emplace(1, element);
                } else {
                    if (!buffer.empty()) {
                        string number;
                        while (!buffer.empty()) {
                            number = buffer.top() + number;
                            buffer.pop();
                        }
                        queueTokens.push(number);
                    }
                    queueTokens.emplace(1, element);
                }
            } else if ((numExpression.substr(i, 3) == "min") ||
                       (numExpression.substr(i, 3) == "max") ||
                       (numExpression.substr(i, 3) == "pow")) {
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


int main() {
    cout << "Hello, World!" << endl << "Enter something " << endl;
    string input;
    getline(cin, input);
    queue<string> tokens = Token::QueueToken(input);
    while (!tokens.empty()) {
        cout << tokens.front() << " ";
        tokens.pop();
    }

    return 0;
}
