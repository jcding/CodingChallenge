class Solution {
public:
    
    struct BuildingPoints{
        int x;
        int y;
        bool isStart;
        
        BuildingPoints(int input_x, int input_y, bool input_isStart) {
            x = input_x;
            y = input_y;
            isStart = input_isStart;
        }
    };
    
    // ERROR comparator could be more efficient!
    struct customComp{
        bool operator()(const BuildingPoints & building1, const BuildingPoints &building2){
            if(building1.x == building2.x){
                // if buildings are the same height
                if(building1.y == building2.y){
                    if(building1.isStart){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                // both points are starting points
                else if(building1.isStart && building2.isStart){
                    return building1.y > building2.y;
                }
                // both points are ending points
                else if(!building1.isStart && !building2.isStart){
                    return building1.y < building2.y;
                }
                else if (building1.isStart && !building2.isStart){
                    return building1.y > building2.y;
                }
                else{
                    return building1.y < building2.y;
                }
            }
            else{
                return building1.x < building2.x;
            }
        }
    };
    
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> res;
        if(buildings.size() == 0){
            return res;
        }
        
        vector<BuildingPoints> buildingPointsVec;
        
        //construct vector of BuildingPoints
        for(int i = 0; i < buildings.size() ; i++){
            
            int xstart = buildings[i][0];
            int xend = buildings[i][1];
            int height = buildings[i][2];
            
            // push back start coordinates
            buildingPointsVec.push_back(BuildingPoints(xstart, height, true));
            // push back end coordinates
            buildingPointsVec.push_back(BuildingPoints(xend, height, false));
        }
        
        sort(buildingPointsVec.begin(), buildingPointsVec.end(), customComp());
        
        
        
        
        // print out mp to verify
        map<int,int> mp;
        
        int max_val = 0;
        // initalizing the map with 0
        mp[0]++;
        
        for(int i = 0 ; i < buildingPointsVec.size(); i++){
            // if start
            BuildingPoints currBld = buildingPointsVec[i];
            
            if(currBld.isStart){
                //potiental error //value might be undefined
                mp[currBld.y]++;
                // change max val
                if(currBld.y > max_val){
                    max_val = currBld.y;
                    vector<int> push_this;
                    // push x first
                    push_this.push_back(currBld.x);
                    // push y second
                    push_this.push_back(currBld.y);
                    
                    
                    // FIX "ERROR": shouldnt need this step, fix the comparator
                    if(res.size() >0){
                        if(res.back()[0] == currBld.x && res.back()[1] < currBld.y){
                            res.back()[1] = currBld.y;
                        }
                        else{
                            res.push_back(push_this);
                        }
                    }
                    else{
                        res.push_back(push_this);
                    }
                    
                    
                    
                }
            }
            // if end
            else{
                if(mp.find(currBld.y) != mp.end()){
                    // remove it from the map
                    if(mp.find(currBld.y)->second == 1){
                        mp.erase(mp.find(currBld.y));
                    }
                    else{
                        mp[currBld.y]--;
                    }
                    
                    // if the max changes then it needs to be in the final result
                    if(mp.rbegin()->first != max_val){
                        max_val = mp.rbegin()->first;
                        vector<int> push_this;
                        // push x first
                        push_this.push_back(currBld.x);
                        // push y second
                        push_this.push_back(max_val);
                        
                        res.push_back(push_this);
                    }
                    
                }
            }
        }
        
        
        return res;
    }
};
