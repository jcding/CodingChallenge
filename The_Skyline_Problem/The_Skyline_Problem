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
    
    struct customComp{
        bool operator()(const BuildingPoints & building1, const BuildingPoints &building2){
            if(building1.x == building2.x){
                // both points are starting points
                if(building1.isStart && building2.isStart){
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
        
        
        priority_queue<int> pq;
            
        // print out pq to verify
        
        return res;
    }
};
