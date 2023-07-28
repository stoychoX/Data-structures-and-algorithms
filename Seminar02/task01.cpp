#include<string>
#include<stack>
#include<iostream>

std::string removeStars(const std::string& s) {
	std::stack<char> st;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '*') {
			if (st.empty())
				throw "invalid expr";
			else
				st.pop();
		}
		else
			st.push(s[i]);
	}

	std::string res(st.size(), '\0');
	size_t idx = st.size() - 1;

	while (!st.empty()) {
		res[idx--] = st.top();
		st.pop();
	}

	return res;
}

std::string removeStarsTwo(const std::string& str) {
    // As we are using only push_back and pop_back here
    // the std::string is equivalent to a stack
    // and we save up some time and memory.
    std::string result;

    for(char c : str) {
        if(c == '*') {
            result.pop_back();
        }
        else {
            result.push_back(c);
        }
    }

    return result;
}


int main() {

}
