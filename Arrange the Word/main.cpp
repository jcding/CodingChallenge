#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool compare (string &s1, string &s2){
    return s1.size() < s2.size();
}


string arrange(string sentence){
    string res = "";
    vector <string> words;
    // convert string to vector
    string word = "";
    for(auto s : sentence){
        if(s == ' ' || s == '.'){
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            words.push_back(word);
            word = "";
        }
        else{
            word = word + s;
        }
    }

    sort(words.begin(), words.end(), compare);

    for(int i = 0; i < words.size(); i++){
        res = res + words[i] + " ";
    }


    return res;
}




int main(){

    string word = "The lines are printed in reverse order.";

    cout << arrange(word) ;






    return 0;
}