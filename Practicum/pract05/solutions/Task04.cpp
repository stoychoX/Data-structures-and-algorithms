/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    size_t getLen(ListNode* head)
    {
        size_t cnt = 0;
        while(head)
        {
            head = head->next;
            cnt++;
        }

        return cnt;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB)
            return nullptr;

        size_t sizeA = getLen(headA);
        size_t sizeB = getLen(headB);

        while(sizeA > sizeB)
        {
            headA = headA->next;
            sizeA--;
        }

        while(sizeB > sizeA)
        {
            headB = headB->next;
            sizeB--;
        }

        while(headA && headB)
        {
            if(headA == headB)
                return headA;

            headA = headA->next;
            headB = headB->next;
        }
        
        return nullptr;
    }
};
