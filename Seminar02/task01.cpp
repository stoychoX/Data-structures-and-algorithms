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

int main() {

}