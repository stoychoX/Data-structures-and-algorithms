#include<iostream>
#include<unordered_map>

int main() {
    std::string example = "abcbabc";
    std::unordered_map<char, int> mp;
    int cnt = 1;

    for(char c : example) {
        if(mp[c] > 0) {
            ++cnt;
            mp.clear();
        }
        mp[c]++;
    }

    std::cout << cnt;
}