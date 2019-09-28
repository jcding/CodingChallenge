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

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> arr) {
    int max = INT_MIN;
    
    for(int row = 0; row < arr.size()-2 ; row++){
        for(int col = 1 ; col < arr[0].size() -1 ; col++){
            int calcVal = arr[row][col-1] +
                          arr[row][col] + 
                          arr[row][col + 1] + 
                          arr[row+1][col] + 
                          arr[row+2][col-1] + 
                          arr[row+2][col] +
                          arr[row+2][col+1];
                          
            if(calcVal > max){
                max = calcVal;
            }
        }
    }
    return max;
}


int main(){



 ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}