#include<iostream>
#include<stack>

void sort(std::stack<int> & inputSt ){
    std::stack<int> tempSt;
    int poped;
    
    while( !inputSt.empty() ){
        poped = inputSt.top();
        inputSt.pop();
    
        if( tempSt.empty() || tempSt.top() <= poped ){
            tempSt.push(poped);
        }else{
            while( !tempSt.empty() ){
                inputSt.push(tempSt.top());
                tempSt.pop();
                if(tempSt.top() <= poped || tempSt.empty() ){
                    tempSt.push(poped);
                    break;
                }
            }
        }
    }
    
    while( !tempSt.empty() ){
        inputSt.push(tempSt.top());
        tempSt.pop();
    }
    

    return;
}

template<typename T>
void printStack(std::stack<T> stack){
    while( !stack.empty() ){
        std::cout<<stack.top()<<std::endl;
        stack.pop();
    }
}


int main(){
    std::stack<int> A;
    A.push(19);
    A.push(10);
    A.push(4);
    A.push(18);
    A.push(999);
    A.push(0);
    sort(A);
    printStack(A);
}
