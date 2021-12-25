#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;
int dice[1000000];
pair<long long, long long> dp[12][12][22][22];

pair<long long, long long> solve(long long p_first, long long fir_score, long long p_second, long long sec_score){
    if(sec_score >= 21)
        return make_pair(0, 1);
    if(dp[p_first][p_second][fir_score][sec_score].second || dp[p_first][p_second][fir_score][sec_score].first)
        return dp[p_first][p_second][fir_score][sec_score];
    long long s1 = 0, s2 = 0, sum;
    for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
            for(int k = 1; k <= 3; ++k){              
                sum = i + j + k;
                long long p_fir = (p_first + sum - 1) % 10 + 1;
                pair<long long, long long> h = solve(p_second, sec_score, p_fir, fir_score + p_fir);
                s1 += h.second;
                s2 += h.first;
            }
    pair<long long, long long> test;
    dp[p_first][p_second][fir_score][sec_score].first = s1;
    dp[p_first][p_second][fir_score][sec_score].second = s2;
    test.first = s1;
    test.second = s2;
    return test;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("Day21.txt");
    int first_player = 4, second_player = 8;
    int first_score = 0, second_score = 0, d = 0;
    long long ans;
    dice[1] = 1;
    dice[2] = 2;
    dice[3] = 3;
    int i = 1;
    while(first_score < 1000 && second_score < 1000){
        first_player += dice[i] + dice[i+1] + dice[i+2];
        i += 3;
        dice[i] = dice[i-1] + 1;
        if(dice[i] == 101)
            dice[i] = 1;
        dice[i+1] = dice[i] + 1;
        dice[i+2] = dice[i+1] + 1;
        if(first_player % 10 == 0){
            first_score += 10;
            first_player = 10;
        }
        else{
            first_score += first_player % 10;
            first_player = first_player  % 10;
        }
        if(first_score >= 1000 || second_score >= 1000)
            break;
        second_player += dice[i] + dice[i+1] + dice[i+2];
        if(second_player % 10 == 0){
            second_score += 10;
            second_player = 10;
        }
        else{
            second_score += second_player % 10;
            second_player = second_player  % 10;
        }
        i += 3;
        if(first_score >= 1000 || second_score >= 1000)
            break;
        dice[i] = dice[i-1] + 1;
        if(dice[i] == 101)
            dice[i] = 1;
        dice[i+1] = dice[i] + 1;
        dice[i+2] = dice[i+1] + 1;
    }
    cout << min(first_score, second_score) * (i-1) << '\n';
    fin.close();
    fin.open("Day21.txt");
    pair<long long, long long> answear = solve(5, 0, 8, 0);
    cout << answear.first << ' ' << answear.second << '\n';
    cout << max(answear.first, answear.second);
    return 0;
}
