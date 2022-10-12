#include<iostream>
#include<stack>

int fib(unsigned x) {
    if(x == 0 || x == 1)
        return 1;

    return fib(x - 1) + fib(x - 2);
}

// Малък пример как можем да симулираме рекурсия чрез стек.
int fibStack(unsigned x) {
    std::stack<unsigned> s;
    s.push(x);
    int result = 0;

    while(!s.empty()) {
        int currArg = s.top(); 
        s.pop();

        if(currArg == 1 || currArg == 0)
            ++result;                          // Еквивалентно на return 1;
        else{
            s.push(currArg - 1);            // Еквивалентно на fib(x - 1);
            s.push(currArg - 2);            // Еквивалентно на fib(x - 2);
        }
    }
    return result;
}

int main() {
    std::cout << fib(10) << " " << fibStack(10);
}
