#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

vector<int> transf(string hex){
    vector<int> bits;
    for (auto character: hex){
        bitset<4> data = character <= '9' ? character - '0' : character - 'A' + 10;
        for (int i = 3; i >= 0; i--){
            bits.push_back(data[i]);
        }
    }
    return bits;
}

int process(vector <int>& bits, int start, int& versions, long long& ans){
    int state = 0;
    int version = 0;
    int type = 0;
    long long literal = 0;
    int lengthType = 0;
    int length = 0;
    int bit = 0;
    long long pValue = 0;
    vector<long long> values;
    //cout << ans << '\n';
    while (state != 7){
       switch (state){
            case 0:
                for (int i = 0; i < 3; i++){
                    version = version << 1;
                    version += bits[start++];
                }
                state = 1;
                break;

            case 1:
                for (int i = 0; i < 3; i++){
                    type = type << 1;
                    type += bits[start++];
                }
                state = type == 4 ? 2 : 3;
                break;
            
            case 3:
                lengthType = bits[start++];
                state = 4;
                break;

            case 4:
                bit = lengthType == 0 ? 15 : 11;
                for (int i = 0; i < bit; i++){
                    length <<= 1;
                    length += bits[start++];
                }
                state = 5;
                break;
            
            case 5:{
                int end = start;
                long long subpacketValue;
                if (lengthType == 0){
                    while (end - start != length){
                        end = process(bits, end, version, subpacketValue);
                        values.push_back(subpacketValue);
                    }
                }
                else{
                    for (int i = 0; i < length; i++){
                        end = process(bits, end, version, subpacketValue);
                        values.push_back(subpacketValue);
                    }
                }
                start = end;
                state = 6;
                break;
            }

            case 2:{
                bool lastPacket = bits[start++] == 0;
                for (int i = 0; i < 4; i++) {
                    literal <<= 1;
                    literal += bits[start++];
                }
                state = lastPacket ? 6 : 2;
                break;
            }
            case 6:
                if (type == 0){
                    for (auto subpacketValue: values)
                        pValue += subpacketValue;
                } else if (type == 1){
                    pValue = 1;
                    for (auto subpacketValue: values) 
                        pValue *= subpacketValue;
                }
                else if (type == 2){
                    pValue = *min_element(values.begin(), values.end());
                }
                else if (type == 3){
                    pValue = *max_element(values.begin(), values.end());
                }
                else if (type == 4){
                    pValue = literal;
                }
                else if (type == 5){
                    pValue = values[0] > values[1];
                }
                else if (type == 6){
                    pValue = values[0] < values[1];
                }
                else{
                    pValue = values[0] == values[1];
                }
                state = 7;
                break;
        }
    }

    versions += version;
    ans = pValue;
    return start;
}

int main() {
    ifstream fin("Day16.txt");
    string line;
    fin >> line;

    auto bits = transf(line);
    int versions = 0;
    long long ans = 0;

    process(bits, 0, versions, ans);

    cout << versions << endl;
    cout << ans << endl;
}