#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

int freq[100];

int main(){
    ifstream fin("Day10.txt");
    vector <char> braces;
    vector <long long> values;
    string s;
    long long ans = 0;
    char ch;
    while(fin >> s){
        long long localsum = 0;
        if(!braces.empty())
            braces.clear();
        int i;
        for(i = 0; i < s.size(); ++i){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<'){
                braces.push_back(s[i]);
            }
            else{
                char ch = braces.back();
                if(s[i] == ')' && ch != '('){
                    localsum += 3;
                    break;
                }
                if(s[i] == ']' && ch != '['){
                    localsum += 57;
                    break;
                }
                if(s[i] == '}' && ch != '{'){
                    localsum += 1197;
                    break;
                }
                if(s[i] == '>' && ch != '<'){
                    localsum += 25137;
                    break;
                }
                braces.pop_back(); 
            }
        }
        ans += localsum;
        if(localsum == 0 && i == s.size()){
            while(!braces.empty()){
                ch = braces.back();
                if(ch == '('){
                    localsum *= 5;
                    localsum += 1;
                }
                if(ch == '['){
                    localsum *= 5;
                    localsum += 2;
                }
                if(ch == '{'){
                    localsum *= 5;
                    localsum += 3;
                }
                if(ch == '<'){
                    localsum *= 5;
                    localsum += 4;
                }
                braces.pop_back();
            }
            //cout << localsum << '\n';
            values.push_back(localsum);
        }
    }
    cout << ans << '\n';
    sort(values.begin(), values.end());
    cout << values[values.size() / 2];
    return 0;
}
