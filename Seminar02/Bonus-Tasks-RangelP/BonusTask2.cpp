#include<iostream>
#include<stack>
#include<string>

bool isBalanced(const  std::string& str){
    std::stack<char> s;
    bool oneDeletedSymbol = false;
    for (size_t i = 0 ; i < str.size() ; i++){

        if(str[i] == ')'){
            if(s.empty() ){
                if( !oneDeletedSymbol){
                    oneDeletedSymbol = true;
                }else{  
                    return false;
                }
            }else{
                s.pop();
            }
        }else {
            s.push(str[i]);
        }
    }


    if( !(s.empty() || oneDeletedSymbol) ){
        s.pop();
    }
    return s.empty();
}

int main(){
    std::cout << isBalanced("((()))(");
}
