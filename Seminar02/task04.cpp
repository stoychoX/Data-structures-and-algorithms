#include<iostream>
#include<stack>
#include<vector>

class firstLeftGreaterElement {
private:
    std::vector<int> data;

    void init(const std::vector<int>& v) {
        std::stack<int> monotonicStack;

        data.resize(v.size());

        for (size_t i = 0; i < v.size(); i++) {
            while(!monotonicStack.empty() && monotonicStack.top() < v[i]) {
                monotonicStack.pop();
            }

            data[i] = monotonicStack.empty() ? -1 : monotonicStack.top();
            monotonicStack.push(v[i]);
        }
    }

public:
    firstLeftGreaterElement(const std::vector<int>& v) {
        init(v);
    }

    int getFirstLeftGreaterElement(size_t idx) const {
        return data[idx];
    }
};

int main() {
    std::vector<int> example {4, 7, 2, 3, 12, 6, 4, 13};
    std::vector<int> example2 {1, 4, 3, 8, 12, 7};

    firstLeftGreaterElement f(example);
    firstLeftGreaterElement s(example2);

    for (size_t i = 0; i < example.size(); i++)
        std::cout << f.getFirstLeftGreaterElement(i) << " ";

    std::cout << std::endl;

    std::cout << s.getFirstLeftGreaterElement(0) << " " << s.getFirstLeftGreaterElement(2) << " " << s.getFirstLeftGreaterElement(5);
}