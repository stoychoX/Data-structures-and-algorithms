#include <climits>
#include <iostream>
#include <stack>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode()
		: val(0)
		, next(nullptr)
	{}
	ListNode(int x)
		: val(x)
		, next(nullptr)
	{}
	ListNode(int x, ListNode* next)
		: val(x)
		, next(next)
	{}
};

class Solution
{
  public:
	ListNode* removeNodes(ListNode* node)
	{
		if (!node || !node->next)
			return node;

		std::stack<ListNode*> listNodes;
		int maxValue = INT_MIN;

		ListNode* iter = nullptr;

		while (node)
		{
			listNodes.push(node);
			node = node->next;
		}

		while (!listNodes.empty())
		{
			ListNode* currentNode = listNodes.top();
			listNodes.pop();

			if (currentNode->val >= maxValue)
			{
				maxValue = currentNode->val;
				currentNode->next = iter;
				iter = currentNode;
			}
			else
			{
				delete currentNode;
			}
		}

		return iter;
	}
};

void freeList(ListNode* node)
{
	while (node)
	{
		ListNode* temp = node;
		node = node->next;
		delete temp;
	}
}

int main()
{
	Solution s;

	ListNode* result =
		s.removeNodes(new ListNode(5, new ListNode(2, new ListNode(13, new ListNode(3, new ListNode(8))))));

	ListNode* toDelete = result;

	while (result)
	{
		std::cout << result->val << " ";
		result = result->next;
	}

	freeList(toDelete);
}
