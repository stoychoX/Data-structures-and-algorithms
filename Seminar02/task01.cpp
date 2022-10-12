#include<string>
#include<stack>
#include<iostream>

std::string removeStars(const std::string& s) {
        std::stack<char> st;
        
        for(char c : s) {
            if(c == '*')
                st.pop();
            else
                st.push(c);
        }
        
        std::string res(st.size(), '\0');
        size_t idx = st.size() - 1;

        while(!st.empty()) {
            res[idx--] = st.top();
            st.pop();
        }
        
        return res;
}

int main() {

}