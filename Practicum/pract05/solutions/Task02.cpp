class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if(!head)
            return nullptr;
      
        ListNode* middle = head;
        ListNode* end = head;

        while(end != nullptr && end->next != nullptr) {
            middle = middle->next;
            end = end->next->next;
        }
        return middle;        
    }
};
