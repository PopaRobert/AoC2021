#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <string.h>
#include <limits.h>

using namespace std;

char cypher[515] =
"##.####..##...##..##.##.###....#..##..#.####.#####..##.#.##.#..#.#####.#.#.....#.####.##.......#.###.#.#..#.##.#.#....####.###..#.####.....##.##.#.#.#.###..#.#..##.####..####...####.#......#...####.#.....##.##.#.#####.#.##...###.#.##.#.#.###.#.####...#####..#.#....######.##.#.###....##...##.#####..##.#.###....#...#...#.#.###.#...##..##........###.#####.###.##....#.##.##..###..#.####....##...###.#####.##..#...###.######.#..#.#...##..#.#####.###.#...#....#.##.#.#.#..#...#####.#..###..#.#...#.#.###.#.#..###.#.";
char grid[1000][1000], newGrid[1000][1000];
int rows, cols;

void transform(){
    for(int r = 0; r < 1000; ++r){
        for(int c = 0; c < 1000; ++c){
            int binNum = 0;
            for (int dR = -1; dR <= 1; ++dR){
                for (int dC = -1; dC <= 1; ++dC){
                    int newR = r + dR;
                    int newC = c + dC;
                    binNum <<= 1;
                    if (newR < 0 || newR >= 1000 || newC < 0 || newC >= 1000){
                        if (grid[r][c] == '#')
                            binNum = 2;
                        else
                            binNum = 0;
                        goto out;
                    }
                    else if (grid[newR][newC] == '#')
                        binNum += 1;
                }
            }
            out:
            newGrid[r][c] = cypher[binNum];
        }
    }
    for(int r = 0; r < 1000; ++r) 
        for(int c = 0; c < 1000; ++c)
            grid[r][c] = newGrid[r][c];
}

int countLit(){
    int cnt = 0;
    for(int r = 0; r < 1000; ++r)
        for(int c = 0; c < 1000; ++c)
            if(grid[r][c] == '#')
                ++cnt;
    return cnt;
}

void testcase(){
    for (int i = 0; i < 50; ++i)
        transform();
    cout << countLit() << '\n';
}

int main() {
    ifstream fin("Day20.txt");
    string str;
    rows = 500;
    while(fin >> str){
        for(int i = 0; i < str.size(); ++i)
            grid[rows][400+i] = str[i];
        ++rows;
    }
    for(int r = 0; r < 1000; ++r){
        for(int c = 0; c < 1000; ++c){
            if (grid[r][c] != '#') 
                grid[r][c] = '.';
        }
    }
    testcase();
    return 0;
}