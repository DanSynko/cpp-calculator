#include <iostream>
#include <stack>
#include <queue>
#include <string>
void safe_input(std::string& expr) {
    std::getline(std::cin, expr);

    // this list will change
    // TODO: add ^, (), %, ., ",".
    std::string correct_input_list = "0123456789+-*/ ";
    bool correct_expr = true;
    do {
        correct_expr = true;
        for (auto it = expr.begin(); it != expr.end(); it++) {
            if (correct_input_list.find(*it) == std::string::npos) {
                correct_expr = false;
                break;
            }
        }

        if (!correct_expr) {
            std::cout << "Error: invalid math expression. Try again." << std::endl;
            std::getline(std::cin, expr);
        }

    } while (!correct_expr);
}

int main()
{
    std::string math_e;
    std::cout << "Enter a math problem: " << std::endl;
    safe_input(math_e);

    std::vector<std::string> output_arr;
    std::stack<char> operators_stack;

    for (auto it = math_e.begin(); it != math_e.end(); it++) {
        if (*it == ' ') continue;

        std::string operators_list = "+-*/";

        if (operators_list.find(*it) != std::string::npos) {
            if (*it == '/' || *it == '*') {
                while (!operators_stack.empty() && (operators_stack.top() == '*' || operators_stack.top() == '/')) {
                    output_arr.push_back(std::string(1, operators_stack.top()));
                    operators_stack.pop();
                }
            }
            else if (*it == '+' || *it == '-') {
                while (!operators_stack.empty()) {
                    output_arr.push_back(std::string(1, operators_stack.top()));
                    operators_stack.pop();
                }
            }
            operators_stack.push(*it);
            continue;
        }
        else {
            std::string number;
            while (it != math_e.end() && isdigit(*it)) {
                number.push_back(*it);
                it++;
            }
            output_arr.push_back(number);
            it--;
        }
    }
    std::cout << '\n';
   
    while (!operators_stack.empty()) {
        output_arr.push_back(std::string(1, operators_stack.top()));
        operators_stack.pop();
    }





    std::stack<char> stack_temp = operators_stack;

    std::cout << "reverse polish notation: ";
    for (auto it = output_arr.begin(); it != output_arr.end(); it++) {
        std::cout << *it << ". ";
    }
    while (!stack_temp.empty()) {
        std::cout << stack_temp.top() << ". " << std::endl;
        stack_temp.pop();
    }
    std::cout << '\n' << std::endl;




    std::stack<double> result;

    for (auto it = output_arr.begin(); it != output_arr.end(); it++) {
        if (*it == "+" || *it == "-" || *it == "*" || *it == "/") {
            double a = result.top();
            result.pop();
            double b = result.top();
            result.pop();
            if (*it == "+") {
                result.push(a + b);
            }
            else if (*it == "-") {
                result.push(b - a);
            }
            else if (*it == "*") {
                result.push(a * b);
            }
            else if (*it == "/") {
                result.push(b / a);
            }
        }
        else {
            result.push(std::stod(*it));
        }
    }


    std::cout << "result: " << result.top() << std::endl;

    return 0;
}