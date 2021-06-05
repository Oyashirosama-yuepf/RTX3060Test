// AStarMath.cpp : 定义控制台应用程序的入口点。
//

#include "iostream"

#include "AstarLib/AStarBase.h"

using namespace std;

CAStarBase Astarbase;

int main(int argc, char* argv[])
{
	char pBuff[5][7] = {
		'0','0','0','1','0','0','0',
		'0','1','1','0','0','1','1',
		'0','S','1','0','1','E','0',
		'0','1','0','0','0','1','0',
		'0','0','0','1','0','0','0'
	};
	Astarbase.Create(&pBuff[0][0], 7, 5);
	Astarbase.PrintCharArr();
	PAPoint pPoint = Astarbase.CalcNextPoint(NULL);
	if (pPoint == NULL)
	{
		cout  <<  "no path can arrive!" <<  endl ;
	}
	else {
		printf("success arrived!\r\n");
	}
	return 0;
}
