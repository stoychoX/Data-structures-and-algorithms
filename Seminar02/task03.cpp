#include<iostream>
#include<stack>
#include<string>
#include<cassert>

bool isOperation(char c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int eval(int fst, int snd, char op) {
    assert(isOperation(c));
    
    switch (op) {
    case '+':
        return fst + snd;  
    case '-':
        return fst - snd;
    case '*':
        return fst * snd;
    case '/':
        return fst / snd;
    }
}

int RPN(const std::string& str) {
    std::stack<int> numbers;

    for (size_t i = 0; i < str.size(); i++) {
        if(isOperation(str[i])) {
            int snd = numbers.top();
            numbers.pop();

            int fst = numbers.top();
            numbers.pop();

            numbers.push(eval(fst, snd, str[i]));
        }
        else if(str[i] != ' ') {
            int number = 0;
            while(i < str.size() && isDigit(str[i])) {
                number *= 10;
                number += str[i] - '0';
                i++;
            }
            i--;
            numbers.push(number);
        }
    }
    
    return numbers.top();
}

int main() {
    std::cout << RPN("9 3 4 * - 2 5 * -");
}