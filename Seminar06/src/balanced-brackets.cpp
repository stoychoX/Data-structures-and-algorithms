#include <stack>
#include <string>

bool is_opening_bracket(char ch)
{
	return ch == '(' || ch == '{' || ch == '[';
}

bool is_closing_bracket(char ch)
{
	return ch == ')' || ch == ']' || ch == '}';
}

bool is_corresponding_brackets(char left, char right)
{
	return left == '(' && right == ')' || left == '{' && right == '}' || left == '[' && right == ']';
}

bool balanced_brackets(const std::string& str)
{
	std::stack<char> s;

	for (char c : str)
	{
		if (is_opening_bracket(c))
		{
			s.push(c);
		}
		else if (is_closing_bracket(c))
		{
			if (s.empty())
				return false;

			char top = s.top();
			s.pop();

			if (!is_corresponding_brackets(top, c))
				return false;
		}
	}

	return s.empty();
}