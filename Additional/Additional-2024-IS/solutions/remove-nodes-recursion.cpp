#include <climits>
#include <iostream>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x, ListNode* next = nullptr)
		: val(x)
		, next(next)
	{}
};

class Solution
{
  public:
	ListNode* removeNodes(ListNode* head)
	{
		int maxVal = INT_MIN;
		return removeNodesRecursive(head, maxVal);
	}

  private:
	ListNode* removeNodesRecursive(ListNode* node, int& maxVal)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		ListNode* filteredNext = removeNodesRecursive(node->next, maxVal);

		if (node->val >= maxVal)
		{
			maxVal = node->val;
			node->next = filteredNext;
			return node;
		}
		else
		{
			delete node;
			return filteredNext;
		}
	}
};

void printList(ListNode* node)
{
	while (node)
	{
		std::cout << node->val << " ";
		node = node->next;
	}
	std::cout << std::endl;
}

int main()
{
	Solution s;

	ListNode* result =
		s.removeNodes(new ListNode(5, new ListNode(2, new ListNode(13, new ListNode(3, new ListNode(8))))));

	printList(result);

	ListNode* current = result;
	while (current)
	{
		ListNode* temp = current;
		current = current->next;
		delete temp;
	}

	return 0;
}
