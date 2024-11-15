#include <iostream>
#include <stack>
#include <string>

std::string parse(const std::string& str) {
    std::stack<char> result; 

    for (char ch : str) { 
        if (ch >= 'a' && ch <= 'z') {
            result.push(ch);
        } else if (ch == '*' && !result.empty()) {
            result.pop(); 
        } else if (ch == '$' && !result.empty()) {
            result.push(result.top()); 
        }
    }

    std::string finalResult; 
    while (!result.empty()) {
        finalResult = result.top() + finalResult; 
        result.pop();
    }

    return finalResult; 
}

int main() {
    std::string input = "abc*$$*d$a$$zz*";
    std::cout << "Result: " << parse(input) << std::endl; 

    return 0;
}
