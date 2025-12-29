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

    std::vector<char> output_arr;
    std::stack<char> operators_stack;

    for (auto it = math_e.begin(); it != math_e.end(); it++) {
        if (*it == ' ') continue;

        if (*it == '+' || *it == '-' || *it == '/' || *it == '*') {
            while (!operators_stack.empty() && (operators_stack.top() == '*' || operators_stack.top() == '/')) {
                output_arr.push_back(operators_stack.top());
                operators_stack.pop();
            }
            operators_stack.push(*it);
            continue;
        }
        output_arr.push_back(*it);
    }
    std::cout << '\n';
   
    while (!operators_stack.empty()) {
        output_arr.push_back(operators_stack.top());
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




    std::stack<int> result;

    for (auto it = output_arr.begin(); it != output_arr.end(); it++) {
        if (*it == '+' || *it == '-' || *it == '*' || *it == '/') {
            int a = result.top();
            result.pop();
            int b = result.top();
            result.pop();
            switch (*it) {
                case '+':
                    result.push(a + b);
                    break;
                case '-':
                    result.push(b - a);
                    break;
                case '*':
                    result.push(a * b);
                    break;
                case '/':
                    result.push(b / a);
                    break;
            }
        }
        else if (isdigit(*it)) {
            result.push(*it - '0');
        }
    }


    std::cout << "result: " << result.top() << std::endl;

    return 0;
}