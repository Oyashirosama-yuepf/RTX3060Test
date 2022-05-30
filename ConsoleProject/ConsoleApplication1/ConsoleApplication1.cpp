// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "DeepFieldSearch.h"
#include "PictureScan.h"

class Status;

class FsmManager {
    friend class Status;
public:
    FsmManager() {};
public:
    ~FsmManager() = default;
private:
    int FsmTestValue1;
    int FsmTestValue2;
};

class Status {
public:
    Status() {};
public:
    ~Status() = default;
public:
    int16_t reviseFsmManagerValue(FsmManager &fsm_manager) {
        fsm_manager.FsmTestValue1 = 1;
        fsm_manager.FsmTestValue2 = fsm_manager.FsmTestValue1 + 1;
        return fsm_manager.FsmTestValue2;
    }

    int16_t reviseFsmManagerValue(FsmManager* fsm_manager) {
        fsm_manager->FsmTestValue1 = 1;
        fsm_manager->FsmTestValue2 = fsm_manager->FsmTestValue1 + 1;
        return fsm_manager->FsmTestValue2;
    }
};

int main()
{

    //vector<vector<int>> inputValue = { 
    //    {1, 0, 1, 1, 0, 1, 0, 1},
    //    {1, 0, 1, 1, 0, 1, 1, 1},
    //    {0, 0, 0, 0, 0, 0, 0, 1}
    //};
    //cout << "maximum island:" << inputValue[0].size() << "  "<< inputValue.size() << endl;

    //deep_field_search* dfs = new deep_field_search();

    FsmManager fsm_manager_ ;
    std::shared_ptr<Status> status_ = std::shared_ptr<Status>();

    std::cout << status_->reviseFsmManagerValue(&fsm_manager_) << std::endl;

    picture_search* ps = new picture_search();

    //unordered_map<int, vector<pair<int, int>>> myMap;
    //myMap[0] = { make_pair(1, 2), make_pair(3, 4), make_pair(4, 7) };
    //myMap[1] = { make_pair(2, 4), make_pair(4, 5) };
    //myMap[2] = { make_pair(5, 3) };
    //myMap[3] = { make_pair(4, 4) };
    //myMap[4] = { make_pair(5, 1), make_pair(2, 3) };
    //myMap[5] = {};

    //vector<pair<int, int>> current_node = myMap[0];   // 当前节点
    //cout << "myMap:" << myMap[0][0].second << myMap[2].size() << endl;

    //vector<vector<int>> inputValue1= { 
    //    {0,2,6,4},
    //    {9999, 0, 3, 9999},
    //    {7,9999,0,1},
    //    {5,9999,12,0}
    //};

    //ps->minimumStep(inputValue1);
    //cout << "inputValue1 unit:" << inputValue1[0][2] << endl;
    //delete dfs;
    return 0;
}

