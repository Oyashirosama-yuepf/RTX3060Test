#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double factorial(double num) {
  if (num == 0) {
    return 1.0;
  } else {
    return num * factorial(num - 1);
  }
}

int main()
{
    double pi = 3.141592;
    double Rmin = 4.0;
    double angle = pi/2;
    double s = 2*Rmin*angle;
    double heading =0.0;
    int loopN = 50;
    int segNum = 100;
    double segS = s / segNum;
    double si{0};
    double dc = 1 / Rmin / s;
    vector<double> coor_x(101);
    vector<double> coor_y(101);
    vector<double> coor_k(101);
    vector<double> coor_heading(101);
    double x = 0.0;
    double y = 0.0;
    double k = 0;
    double start_x = 0.0;
    double start_y = 0.0;
    double start_k = 0.0;

    double end_x = 10.0;
    double end_y = 5.0;

    std::ofstream out_debuger("./clothoid.txt");

    for (int j = 0; j < segNum + 1; j++) {
      x = 0;
      y = 0;
      si = segS * j;
      for (int i = 0; i < loopN; i++) {
        x += (std::pow(-1, i) * std::pow(dc, 2 * i) * std::pow(si, 4 * i + 1)) /
             ((4 * i + 1) * std::pow(2, 2 * i) * factorial(double(2 * i)));
        y += (std::pow(-1, i) * std::pow(dc, 2 * i + 1) *
             std::pow(si, 4 * i + 3)) /
             ((4 * i + 3) * std::pow(2, 2 * i + 1) * factorial(double(2 * i + 1)));
      }
      k = dc * si;
      heading = dc*std::pow(si,2)/2;
      coor_x[j] = x;
      coor_y[j] = y;
      coor_k[j] = k;
      coor_heading[j] = heading;
      cout<<x<<","<<y<<","<<k<<","<<heading<<endl;
    }

    cout << "======"<<endl;

    double pro_x = end_x/coor_x[100];
    double pro_y = end_y/coor_y[100];

    for(int j = 0; j < segNum + 1; j++){
        coor_x[j] *= pro_x;
        coor_y[j] *= pro_y;
        cout<<coor_x[j]<<","<<coor_y[j]<<","<<coor_k[j]<<","<<coor_heading[j]<<endl;
        out_debuger<<coor_x[j]<<","<<coor_y[j]<<","<<coor_k[j]<<","<<coor_heading[j]<<endl;
    }
    out_debuger.close();
    return 0;
}
