#include<list>
#include<iostream>
#include<queue>
#include<stack>

bool isSymethric(const std::list<int>& ll) {
    auto start = ll.begin();
    auto end = --(ll.end());

    while(start != end) {
        if(*start != *end)
            return false;
        
        ++start;
        if(start == end)
            break;
        --end;
    }

    return true;
}

int evaluateExpr(char op, int fst, int snd) {
    // assert(isOperator(op));
    
    switch (op) {
        case '+':
            return (fst + snd);
        break;
         case '-':
            return (fst - snd);
        break;
         case '*':
            return (fst * snd);
        break;
         case '/':
            return (snd / fst);
        break;
    }
}

size_t evaluateQueue(std::queue<char> q) {
    std::stack<int> nums;

    while(!q.empty()) {
        if(isdigit(q.front())) {
            int cDigit = q.front() - '0';
            q.pop();
            nums.push(cDigit);
        }
        else {
            int fst = nums.top();
            nums.pop();
            int snd = nums.top();
            nums.pop();
            char op = q.front();
            q.pop();

            nums.push(evaluateExpr(op, fst, snd));
        }
    }
    return nums.top();
}

bool solution(const std::list<std::queue<char>>& ll) {
    std::list<int> l;

    for(auto elem : ll)
        l.push_back(evaluateQueue(elem));
    
    return isSymethric(l);
}

int main() {
    std::list<std::queue<char>> test(5);

    auto it = test.begin();
    (*it).push('4');
    (*it).push('5');
    (*it).push('+');

    ++it;

    (*it).push('1');
    (*it).push('6');
    (*it).push('+');
    (*it).push('7');
    (*it).push('*');
    ++it;

    (*it).push('8');
    ++it;

    (*it).push('1');
    (*it).push('7');
    (*it).push('7');
    (*it).push('*');
    (*it).push('*');

    ++it;

    (*it).push('2');
    (*it).push('3');
    (*it).push('*');
    (*it).push('3');
    (*it).push('+');


    std::cout << solution(test);
}