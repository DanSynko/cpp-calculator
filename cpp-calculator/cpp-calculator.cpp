#include <iostream>
#include <stack>
#include <queue>
#include <string>
void safe_input(std::string& expr) {
    std::getline(std::cin, expr);

    // this list in string_view will change
    // TODO: add (), %, ^.
    
    bool correct_expr;
    do {
        correct_expr = true;
        if (expr.empty()) {
            correct_expr = false;
        }
        else {
            for (auto it = expr.begin(); it != expr.end(); it++) {
                if (std::string_view("0123456789+-*/., ").find(*it) == std::string_view::npos) {
                    correct_expr = false;
                    break;
                }
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


    
    // Shunting-yard algorithm

    std::vector<std::string> output_arr;
    std::stack<char> operators_stack;

    for (auto it = math_e.begin(); it != math_e.end(); it++) {
        if (*it == ' ') continue;

        if (std::string_view("+-*/").find(*it) != std::string_view::npos) {
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
            bool has_point = false;
            while (it != math_e.end() && (isdigit(*it) || *it == ' ' || *it == '.' || *it == ',')) {
                if (*it != ' ') {
                    if ((*it == '.' || *it == ',')) {
                        if (!has_point) {
                            number.push_back('.');
                            has_point = true;
                        }
                    }
                    else {
                        number.push_back(*it);
                    }
                }
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




    // reverse polish notation output

    std::cout << "reverse polish notation: ";
    for (auto it = output_arr.begin(); it != output_arr.end(); it++) {
        std::cout << *it << ". ";
    }
    std::cout << '\n' << std::endl;




    // stack machine

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