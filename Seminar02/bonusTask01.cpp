#include <iostream>
#include <stack>

void sortStack(std::stack<int> &first)
{
    std::stack<int> second;
    int currentElement = 0;
    while (!first.empty())
    {
        currentElement = first.top();
        first.pop();

        while (!second.empty() && second.top() > currentElement)
        {
            first.push(second.top());
            second.pop();
        }
        second.push(currentElement);
    }

    while (!second.empty())
    {
        first.push(second.top());
        second.pop();
    }
}

void stackPrint(std::stack<int> st)
{
    while (!st.empty())
    {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
}

int main()
{
    std::stack<int> st;
    st.push(8);
    st.push(2);
    st.push(4);
    st.push(1);
    st.push(5);
    st.push(3);

    stackPrint(st);
    sortStack(st);
    stackPrint(st);
}