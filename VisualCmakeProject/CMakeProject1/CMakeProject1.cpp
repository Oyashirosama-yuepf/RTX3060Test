// AStarMath.cpp : 定义控制台应用程序的入口点。
//

#include "iostream"
#include <vector>

#include "MultiFunction/MultiFunction.h"
#include "AstarLib/AStarBase.h"
#include "SingleTon/SingleTon.h"
#include "ExternFunction.h"

using namespace std;

ExternFunction externFunction;
ExternFunction* externFunctionPoint;

SingleTon* SingleTon::instance = NULL;
int main(int argc, char* argv[])
{
	externFunction.ExternOutput();
	externFunctionPoint->ExternOutput();
	//TakeBus* take_bus = new TakeBus();

	//Bus* subway = new Subway();
	//Bus* station = new Station();

	//cout << "test initial" << endl;
	//subway->TakeBusToSomewhere(*take_bus);
	//station->TakeBusToSomewhere(*take_bus);

	//SingleTon::GetSingleTonInstance()->testSingleTonOutput();


	//char pBuff[5][7] = {
	//	'0','0','0','1','0','0','0',
	//	'0','1','1','0','0','1','1',
	//	'0','S','1','0','1','E','0',
	//	'0','1','0','0','0','1','0',
	//	'0','0','0','1','0','0','0'
	//};
	//Astarbase.Create(&pBuff[0][0], 7, 5);
	//Astarbase.PrintCharArr();
	//PAPoint pPoint = Astarbase.CalcNextPoint(NULL);
	//if (pPoint == NULL)
	//{                 
	//	cout  <<  "no path can arrive!" <<  endl ;
	//}
	//else {
	//	printf("success arrived!\r\n");
	//}
	//return 0;
}

