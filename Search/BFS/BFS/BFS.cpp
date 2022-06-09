// BFS.cpp: 定义应用程序的入口点。
//

#include "BFS.h"
using namespace std;

int Map[5][5];  //定义地图大小
int dir[4][2] = { 1,0,-1,0,0,-1,0,1 };  //定义方向
int n, m, ans;

int visitedDFS[5] = { 0 };
int visitedBFS[5] = { 0 };
int count_DFS = 0;
int count_dfs = 0;
int count_BFS = 0;
int count_bfs = 0;
struct node
{
    int x, y, step;

} now, nextt;  //保存走步
int BFS(int x, int y)
{
    queue<node>q;
    int xx, yy, zz;
    Map[x][y] = 2;  //走过初始点
    now.x = x;
    now.y = y;
    now.step = 0;
    q.push(now);  //从当前点开始
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)  //遍历四个方向
        {
            xx = now.x + dir[i][0];
            yy = now.y + dir[i][1];  //走一步
            if (xx >= 0 && xx < 5 && yy >= 0 && yy < 5 && Map[xx][yy] != 1 && Map[xx][yy] != 2)  //可以走
            {
                nextt.x = xx;
                nextt.y = yy;
                nextt.step = now.step + 1;  //步数加一
                Map[now.x][now.y] = 2;   //走过一个点
                if (Map[xx][yy] == 3)  //到达终点
                    return nextt.step;
                q.push(nextt);
            }
            for (int i = 0; i < 5; i++) {      //打印地图
                for (int j = 0; j < 5; j++)
                    cout << Map[i][j];
                cout << endl;
            }
            cout << endl;
        }

    }
    return -1;   //走不过去
}

/*深度优先遍历的非递归实现,利用栈来实现*/
void DFS(int startNum, int mat[][5]) {

	stack<int> s; //初始化一个栈用来存储序号
	s.push(startNum); //初始序号入栈
	int flag[5] = { 0 }; //设置一个数组用来判断序号是否已被遍历
	flag[startNum - 1] = 1;
	//cout << "深度优先遍历：" << endl;
	cout << startNum << " ";

	while (!s.empty()) //当栈不为空时循环执行
	{
		int currentNum = s.top(); //读取栈顶元素
		int i; //设置遍历序号

		//循环遍历当前序号的相邻序号，如果未被访问则插入栈中
		for (i = 0; i < 5; i++) {
			count_DFS++;
			if (mat[currentNum - 1][i] == 1 && flag[i] == 0) {
				s.push(i + 1);
				flag[i] = 1;
				cout << i + 1 << " ";
				break;
			}
		}

		//用来判断当前序号是否有相邻未被访问的结点，如有则跳过，若无则栈顶元素出栈
		if (i == 5) s.pop();
	}

	return;
}

/*深度优先遍历的递归实现*/
void dfs(int startNum, int mat[][5]) {
	int i;
	visitedDFS[startNum - 1] = 1;
	cout << startNum << " ";
	for (i = 0; i < 5; i++) {
		count_dfs++;
		if (visitedDFS[i] == 0 && mat[startNum - 1][i] == 1) dfs(i + 1, mat);
	}
}

/*宽度优先遍历的非递归实现,利用队列来实现*/
void BFS(int startNum, int mat[][5]) {

	queue<int> q; //初始化一个队列
	q.push(startNum); //初始值入队
	int flag[5] = { 0 }; //设置一个数组用来判断序号是否已被遍历
	if (flag[startNum - 1] == 0) {
		flag[startNum - 1] = 1;
		cout << startNum << " ";
	}
	//cout << "宽度优先遍历：" << endl;

	while (!q.empty()) //当队列不为空时循环执行
	{
		int currentNum = q.front(); //当前序号为队首元素
		q.pop(); //队首元素出队
		for (int i = 0; i < 5; i++) { //循环遍历当前序号的相邻序号，如果未被访问则插入队列中
			count_BFS++;
			if (mat[currentNum - 1][i] == 1 && flag[i] == 0) {
				q.push(i + 1);
				flag[i] = 1;
				cout << i + 1 << " ";
			}
		}
	}

	return;
}

/*宽度优先遍历的递归实现*/
void bfs(int startNum, int mat[][5]) {

	if (visitedBFS[startNum - 1] == 0) {
		visitedBFS[startNum - 1] = 1;
		cout << startNum << " ";
	}

	int i;
	int flag = 0;

	for (i = 0; i < 5; i++) {
		count_bfs++;
		if (visitedBFS[i] == 0 && mat[startNum - 1][i] == 1) {
			cout << i + 1 << " ";
			visitedBFS[i] = 1;
			flag = 1;
		}
	}

	if (flag)
		for (int j = 0; j < 5; j++) {
			if (mat[startNum - 1][j] == 1) bfs(j + 1, mat);
		}
}


int main() {

	int matrix[5][5] = { {0,1,0,1,1},
						{1,0,1,1,0},
						{0,1,0,1,0},
						{1,1,1,0,0},
						{1,0,0,0,0} };

	cout << "设置输入矩阵如下：" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}

	cout << "宽度优先遍历非递归实现：" << endl;
	BFS(1, matrix);
	cout << "循环次数：" << count_BFS << endl;

	cout << "宽度优先遍历递归实现：" << endl;
	bfs(1, matrix);
	cout << "循环次数：" << count_bfs << endl;

	cout << "深度优先遍历非递归实现：" << endl;
	DFS(1, matrix);
	cout << "循环次数：" << count_DFS << endl;

	cout << "深度优先遍历递归实现：" << endl;
	dfs(1, matrix);
	cout << "循环次数：" << count_dfs << endl;

	return 0;
}
