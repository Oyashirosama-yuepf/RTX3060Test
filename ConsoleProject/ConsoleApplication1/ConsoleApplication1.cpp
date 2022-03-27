// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "DeepFieldSearch.h"
#include "PictureScan.h"

int main()
{
    //vector<vector<int>> inputValue = { 
    //    {1, 0, 1, 1, 0, 1, 0, 1},
    //    {1, 0, 1, 1, 0, 1, 1, 1},
    //    {0, 0, 0, 0, 0, 0, 0, 1}
    //};
    //cout << "maximum island:" << inputValue[0].size() << "  "<< inputValue.size() << endl;

    //deep_field_search* dfs = new deep_field_search();

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

    vector<vector<int>> inputValue1= { 
        {0,2,6,4},
        {9999, 0, 3, 9999},
        {7,9999,0,1},
        {5,9999,12,0}
    };

    ps->minimumStep(inputValue1);
    cout << "inputValue1 unit:" << inputValue1[0][2] << endl;
    //delete dfs;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
