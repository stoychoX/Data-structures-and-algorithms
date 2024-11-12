bool has_cycle(SinglyLinkedListNode* head) {
    if(!head)
        return false;
        
    SinglyLinkedListNode* slow = head;
    SinglyLinkedListNode* fast = head;
    
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        
        if(slow == fast)
            return true;
    }
    
    return false;
}
