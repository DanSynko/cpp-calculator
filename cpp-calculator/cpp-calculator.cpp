#include <iostream>
#include <stack>
#include <queue>
#include <string>

int main()
{
    std::string math_e;
    std::cout << "Enter a math problem: " << std::endl;
    std::cin >> math_e;

    std::vector<char> output_arr;
    std::stack<char> operators_stack;

    for (auto it = math_e.begin(); it != math_e.end(); it++) {
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

    return 0;
}