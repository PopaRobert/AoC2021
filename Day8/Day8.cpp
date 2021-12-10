#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

char pattern[10];

int main(){
    int nr;
    char ch;
    vector <string> input;
    vector <string> output;
    string in;
    ifstream fin("Day8.txt");
    long long ans = 0;
    while(!fin.eof()){
        input.clear();
        output.clear();
        for(int i = 0; i < 10; ++i){
            fin >> in;
            input.push_back(in); 
        }
        fin >> ch;
        for(int i = 0; i < 4; ++i){
            fin >> in;
            output.push_back(in); 
        }
        for(auto i : output){
            if(i.size() == 7)
                ++ans;
            else if(i.size() == 2){
                ++ans;
            }
            else if(i.size() == 4)
                ++ans;
            else if(i.size() == 3)
                ++ans;
        }
    }
    cout << ans << '\n';
    fin.close();
    fin.open("Day8.txt");
    ans = 0;
    while(!fin.eof()){
        input.clear();
        output.clear();
        for(int i = 0; i < 10; ++i){
            fin >> in;
            input.push_back(in); 
        }
        fin >> ch;
        for(int i = 0; i < 4; ++i){
            fin >> in;
            output.push_back(in); 
        }
        string one, two, three, four, five, six, seven, eight, nine, zero;
        for(auto i : input){
            if(i.size() == 3)
                seven = i;
            else if(i.size() == 2)
                one = i;
            else if(i.size() == 4)
                four = i;
            else if(i.size() == 7)
                eight = i;
        }
        for(auto i : input){
            if(i.size() == 6){
                int cnt = 0;
                for(int j = 0; j < i.size(); ++j)
                    if(i[j] == one[0] || i[j] == one[1])
                        ++cnt;
                if(cnt == 1)
                    six = i;
            }
        }
        // 1, 4, 6, 7, 8, 9, 0
        for(auto i : input){
            if(i.size() == 6){
                int cnt = 0;
                for(int j = 0; j < i.size(); ++j)
                    if(i[j] == one[0] || i[j] == one[1])
                        ++cnt;
                if(cnt == 2){
                    cnt = 0;
                    for(int j = 0; j < i.size(); ++j)
                        for(int k = 0; k < four.size(); ++k)
                            if(i[j] == four[k]){
                                ++cnt;
                                continue;
                            }
                    if(cnt == 4)
                        nine = i;
                    else
                        zero = i;
                }
            }
        }
        for(auto i : input){
            if(i.size() == 5){
                int onecnt = 0;
                for(int k = 0; k < i.size(); ++k){
                    if(i[k] == one[0] || i[k] == one[1])
                       ++onecnt;
                }
                if(onecnt == 2){
                    three = i;
                    break;
                }
            }
        }
        for(auto i : input){
            if(i.size() == 5 && i != three){
                int cnt = 0;
                for(int j = 0; j < nine.size(); ++j)
                    for(int k = 0; k < i.size(); ++k)
                        if(nine[j] == i[k]){
                            ++cnt;
                            k = i.size();
                        }
                if(cnt == 5)
                    five = i;
            }
        }
        for(auto i : input)
            if(i.size() == 5 && i != three && i != five)
                two = i;
        //cout << one << ' ' << two << ' ' << three << ' ' << four << ' ' << five << ' ' << six << ' ' << seven << ' ' << eight << ' ' << nine << ' ' << zero;
        //cout << '\n';
        int nr = 0;
        for(auto i : output){
            nr *= 10;
            int cnt = 0;
            if(i.size() == 2){
                nr += 1;         
                continue;
            }
            if(i.size() == 3){
                nr += 7;
                continue;
            }
            if(i.size() == 4){
                nr += 4;
                continue;
            }
            if(i.size() == 7){
                nr += 8;
                continue;
            }
            for(int k = 0; k < two.size(); ++k){
                for(int j = 0; j < i.size(); ++j)
                    if(two[k] == i[j]){
                        ++cnt;
                        j = i.size();
                    }
            }
            if(cnt == 5 && i.size() == two.size()){
                nr += 2;
                continue;
            }
            cnt = 0;
            for(int k = 0; k < three.size(); ++k){
                for(int j = 0; j < i.size(); ++j)
                    if(three[k] == i[j]){
                        ++cnt;
                        j = i.size();
                    }
            }
            if(cnt == 5 && i.size() == three.size()){
                nr += 3;
                continue;
            }
            cnt = 0;
            for(int k = 0; k < five.size(); ++k){
                for(int j = 0; j < i.size(); ++j)
                    if(five[k] == i[j])
                        ++cnt;
            }
            if(cnt == 5 && i.size() == five.size()){
                nr += 5;
                continue;
            }
            cnt = 0;
            for(int k = 0; k < six.size(); ++k){
                for(int j = 0; j < i.size(); ++j)
                    if(six[k] == i[j]){
                        ++cnt;
                        j = i.size();
                    }
            }
            if(cnt == 6 && i.size() == six.size()){
                nr += 6;
                continue;
            }
            cnt = 0;
            for(int k = 0; k < nine.size(); ++k){
                for(int j = 0; j < i.size(); ++j)
                    if(nine[k] == i[j]){
                        ++cnt;
                        j = i.size();
                    }
            }
            if(cnt == 6 && i.size() == nine.size()){
                nr += 9;
                continue;
            }
        }
        cout << nr << '\n';
        cout << ans << '\n';
        ans += nr;
        /**
         *    1
         * 6     2
         *    7
         * 5     3
         *    4  
        */

    }
    cout << ans << '\n';
    return 0;
}