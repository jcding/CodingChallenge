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

class LFUCache {
public:
    LFUCache(int i_capacity) {
        capacity = i_capacity;
    }
    
    int get(int key) {
        if(mp.find(key) == mp.end()){
           return -1; 
        }
        // we find the key in the mp
        else{
            
            
            // 
            // change the list_iter of "keyToListIter"

            
            int oldfreq = mp.find(key)->second.second;

            //cout << "key: " << key <<" oldfreq: " << oldfreq<< endl;
            // 1. delete it from the old freqency list
            sameFreqList.find(oldfreq)->second.erase( keyToListIter.find(key)->second );
            // delete the entry in the sameFreqlist if its list is empty
            if(sameFreqList.find(oldfreq)->second.empty()){
                sameFreqList.erase(oldfreq);
            }
            
            // 2. update the frequency of the thing in mp
            mp.find(key)->second.second++;



            int newfreq = mp.find(key)->second.second;
            // 3. put it in a different frequency list
            sameFreqList[newfreq].push_front(key);
            // 4. change it to the point to the new list_iter
            keyToListIter.find(key)->second = sameFreqList[newfreq].begin();
            
            //cout << "key: " << key <<" newfreq: " << newfreq<< endl;

            return mp.find(key)->second.first;
        }
        
       
       
    }
    
    void put(int key, int value) {
        if(capacity == 0){
            return;
        }

       // if the key is present already in mp
       // need to change the frequency
       if(mp.find(key) != mp.end()){
            // 1. set the new value
            mp[key].first = value;
            // 2. delete it from the old frequency list
            int oldfreq = mp.find(key)->second.second;
            sameFreqList.find(oldfreq)->second.erase(keyToListIter.find(key)->second);
            // delete the entry in the sameFreqlist if its list is empty
            if(sameFreqList.find(oldfreq)->second.empty()){
                sameFreqList.erase(oldfreq);
            }
            
            // 3. update the freq
            mp.find(key)->second.second++;
            int newfreq = mp.find(key)->second.second;
            // 4. push it into the new freq list
            sameFreqList[newfreq].push_front(key);
            // 5. change it to point to new list
            keyToListIter.find(key)->second = sameFreqList[newfreq].begin();

       }
       // if the key is not present in mp
       else{
           // if we are less than capacity
            if(mp.size() < capacity){
                // 1. put it in mp
                pair<int, int> value_and_freq(value, 1);

                pair <int, pair<int, int>> insert_this(key, value_and_freq);
                mp.insert(insert_this);
                
                // 2. put it in the sameFreqList (1 means that the frequency is 1)
                sameFreqList[1].push_front(key); // .back() is the LRU
                
                // 3. put it in keyToListIter
                pair<int, list<int>::iterator> insert_keyToListIter(key, sameFreqList[1].begin());
                keyToListIter.insert(insert_keyToListIter);

            }

           // if we are at capacity
           else{
               // no tie in frequency counter
               if(sameFreqList.begin()->second.size() == 1){
                   // remove this value first
                   int remove_key = sameFreqList.begin()->second.back();
                   mp.erase(remove_key);
                   keyToListIter.erase(remove_key);
                   sameFreqList.erase(sameFreqList.begin());

                

                    // insert the new key
                    // 1. put it in mp
                    pair<int, int> value_and_freq(value, 1);

                    pair <int, pair<int, int>> insert_this(key, value_and_freq);
                    mp.insert(insert_this);
                
                    // 2. put it in the sameFreqList (1 means that the frequency is 1)
                    sameFreqList[1].push_front(key); // .back() is the LRU
                
                    // 3. put it in keyToListIter
                    pair<int, list<int>::iterator> insert_keyToListIter(key, sameFreqList[1].begin());
                    keyToListIter.insert(insert_keyToListIter);
               }
               // if there is a tie in frequency
               else{
                   int remove_key = sameFreqList.begin()->second.back();
                   // 1. remove it from sameFreqList
                   sameFreqList.begin()->second.pop_back();
                   // 2. remove it from mp
                   mp.erase(remove_key);
                   // 3. remove it from keyToListIter
                   keyToListIter.erase(remove_key);


                   // insert new key
                    // 1. put it in mp
                    pair<int, int> value_and_freq(value, 1);

                    pair <int, pair<int, int>> insert_this(key, value_and_freq);
                    mp.insert(insert_this);
                
                    // 2. put it in the sameFreqList (1 means that the frequency is 1)
                    sameFreqList[1].push_front(key); // .back() is the LRU
                
                    // 3. put it in keyToListIter
                    pair<int, list<int>::iterator> insert_keyToListIter(key, sameFreqList[1].begin());
                    keyToListIter.insert(insert_keyToListIter);
               }

               // find the one with the smallest freq
               // sameFreqList.begin()
           }
       }
        
        
       
    }
    
    // mp value : mp.find(key)->second.first
    // mp freq : mp.find(key)->second.second
    
private:
    int capacity;
    
    unordered_map<int, pair<int, int>> mp; // unordered_map<key, pair<value, freq>
    unordered_map<int, list<int>::iterator > keyToListIter; // unordered_map<key, list<int>::iterator >
    map<int, list<int>> sameFreqList; // unordered_map <freq, list<int>>
    
    
    
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */