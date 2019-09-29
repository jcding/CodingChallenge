class LRUCache {
public:
    LRUCache(int i_capacity) {
        capacity = i_capacity;
    }
    
    int get(int key) {
        
        if(mp.find(key) == mp.end()){
            return -1;
        }
        
        int value = mp.find(key)->second.first;
        auto list_iter = mp.find(key)->second.second;
        // FRONT is most recently used
        // BACK is least recently used
        
        // erase the element in the LIST at "list_iter"
        // place it at the front of the LIST
        LIST.erase(list_iter);
        LIST.push_front(key);
        
        
        mp.find(key)->second.second = LIST.begin();
        
        return value;
    }
    
    void put(int key, int value) {
        // we find the key in the map already
        if(mp.find(key) != mp.end()){
            // set the value
            mp.find(key)->second.first = value;
            
            auto list_iter = mp.find(key)->second.second;
            if(list_iter != LIST.begin()){
                LIST.erase(list_iter);
                LIST.push_front(key);
                mp.find(key)->second.second = LIST.begin();
            }  
        }
        
        // if the key is not in the map already
        else{
            // if LIST size is not at capacity
            if(LIST.size() < capacity){
                // insert into the list first
                LIST.push_front(key);
                    
                pair<int, list<int>::iterator> INSERT (value, LIST.begin());
                    
                mp.insert(make_pair(key, INSERT));
            }
            else{
                // delete the last item in the LIST
                // delete it from the map
                int last_item_key = LIST.back();
                mp.erase(last_item_key);
                LIST.pop_back();
                
                
                LIST.push_front(key);
                    
                pair<int, list<int>::iterator> INSERT (value, LIST.begin());
                    
                mp.insert(make_pair(key, INSERT));
            }
        }
    }
    
private:
    int capacity;
    list <int> LIST;
    unordered_map<int, pair<int, list<int>::iterator>> mp;
    
    //list iterator of key
    // mp.find(key)->second.second
    
    //value of the key
    //mp.find(key)->second.first
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
