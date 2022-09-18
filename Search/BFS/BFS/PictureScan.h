#pragma once
#include "Common.h"
class picture_search {
public:
    picture_search() {};
    ~picture_search() {};
    vector<pair<int, int>>::iterator getMinCostNode(vector<std::pair<int, int>>& open) {
        auto itMinCost = open.begin();
        for (auto it = open.begin(); it != open.end(); ++it) {
            if ((*it).second < (*itMinCost).second) {
                itMinCost = it;
            }
        }
        return itMinCost;
    }

    int minimumStep(vector<vector<int>> &myMap) {
        for (int k = 0; k < myMap.size(); k++)   // ˢ��������ܵ�������������־���
         for (int i = 0; i < myMap.size(); i++)
            for (int j = 0; j < myMap.size(); j++)     // ����ÿһ����
                    if (myMap[i][j] > myMap[i][k] + myMap[k][j]) {
                        myMap[i][j] = myMap[i][k] + myMap[k][j];
                    }
        return 0;
    }

};