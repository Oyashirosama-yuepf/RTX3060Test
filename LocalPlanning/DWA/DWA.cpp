#include <math.h>
#include <iostream>
#include <vector>
//vector sun
#include <numeric>
using namespace std;


#define pi 3.1415926
double dt = 0.1;



class State
{
public:
    State()
    {
        x = 0;
        y = 0;
        yaw = 0;
        v = 0;
        w = 0;
    }
    double x;
    double y;
    double yaw;
    double v;
    double w;
};
class GTreturn
{
public:
    std::vector<State> traj;
    State state;
};
class UU
{
public:
    UU()
    {
        vt = 0;
        ot = 0;
    }
    double vt;
    double ot;
};

class KModel
{
public:
    KModel()
    {
        MD_MAX_V = 1;//最大速度
        MD_MAX_W = 0.349;//最大角速度
        MD_ACC = 0.2;//加速度
        MD_VW = 0.8727;//角加速度
        MD_V_RESOLUTION = 0.01;//速度分辨率
        MD_W_RESOLUTION = 0.01745;//角速度分辨率
    }
    double MD_MAX_V;//最大速度
    double MD_MAX_W;//最大角速度
    double MD_ACC;//加速度
    double MD_VW;//角加速度
    double MD_V_RESOLUTION;//速度分辨率
    double MD_W_RESOLUTION;//角速度分辨率
};






class VR
{
 
public:
    VR()
    {
        min_v = 0;
        max_v = 0;
        min_w = 0;
        max_w = 0;
    }
    double min_v;
    double max_v;
    double min_w;
    double max_w;


};

class OB
{
public:
    OB()
    {
        x = 0;
        y = 0;
    }
    double x;
    double y;
};


class EvalDB_cell
{
public:
    EvalDB_cell()
    {
        vt = 0;
        ot = 0;
        heading = 0;
        dist = 0;
        vel = 0;

    }
    double vt;
    double ot;
    double heading;
    double dist;
    double vel;
};

class SumDB
{
public:

    std::vector<EvalDB_cell> EvalDB;
    std::vector<State> trajDB;

};

class DWAreturn
{
public:
    std::vector<State> trajDB;
    UU u;

};


double toDegree(double radian);
double toRadian(double degree);
State f(State state, UU u);
VR CalcDynamicWindow(State state, KModel model);
double CalcHeadingEval(State state, double goal[2]);
double CalcDistEval(State state, std::vector<OB> &obs, double R);
double CalcBreakingDist(double vel, KModel model);
GTreturn GenerateTrajectory(State state, UU u, double evaldt, KModel model);
void NormalizeEval(std::vector<EvalDB_cell> &EvalDB);
SumDB Evaluation(State state, VR vr, double goal[2], std::vector<OB> &obs, double R, KModel model, double evalParam[4]);
DWAreturn DynamicWindowApproach(State state, KModel model, double goal[2], double evalParam[4], std::vector<OB> &obs, double R);
double max(double a, double b);
double min(double a, double b);


int main()
{

    cout << "Dynamic Window Approach sample program start!!" << endl;
    double evalParam[4] = { 0.05,0.01,0.9,3.0 };
    State state;
    state.yaw = pi /4;
    double goal[2] = { 5,5 };
    std::vector<OB> obs(2);
    obs[0].x = 0;
    obs[0].y = 2;
    obs[1].x = 2;
    obs[1].y = 0;
    double obstacleR = 0.5;
    KModel model;
    std::vector<State> result;
    UU u1;
    for (int iii = 0;iii < 5000;iii++)
    {
        DWAreturn dwareturn = DynamicWindowApproach(state, model, goal, evalParam, obs, obstacleR);
        u1 = dwareturn.u;
        state = f(state, u1);
        result.push_back(state);

        if (sqrt(pow(state.x - goal[0], 2) + pow(state.y - goal[1], 2)) < 0.1)
        {
            cout << "Arrive Goal" << endl;
            break;
        }

        cout << "第"<<iii<<"s到达的位置为" << "x = " << state.x << " y = " << state.y << endl;





    }
}




//////////////////////////////////////////////////////

DWAreturn DynamicWindowApproach(State state, KModel model, double goal[2], double evalParam[4], std::vector<OB> &obs, double R)
{
    DWAreturn dwareturn;
    VR vr = CalcDynamicWindow(state, model);
    SumDB DB = Evaluation(state, vr, goal, obs, R, model, evalParam);
    if (DB.EvalDB.empty())
    {
        cout << "no path to goal!" << endl;
            dwareturn.u.vt = 0;
            dwareturn.u.ot= 0;
            return dwareturn;

    }
   NormalizeEval(DB.EvalDB);

        double result1;
        std::vector<double> feval;
    for (int id = 0; id < DB.EvalDB.size(); id++)
    {
        result1 = evalParam[0] * DB.EvalDB[id].heading + evalParam[1] * DB.EvalDB[id].dist + evalParam[2] * DB.EvalDB[id].vel;
        feval.push_back(result1);
    }
    int k = 0;
    for (int ii = 1;ii < feval.size();ii++)
    {
        if (feval[ii]>feval[ii-1])
        {
            k = ii;
        }
    }


    dwareturn.u.vt = DB.EvalDB[k].vt;
    dwareturn.u.ot = DB.EvalDB[k].ot;
    dwareturn.trajDB = DB.trajDB;
    return dwareturn;

}




SumDB Evaluation(State state, VR vr, double goal[2], std::vector<OB> &obs, double R, KModel model, double evalParam[4])
{
    SumDB DB;
    GTreturn GT;
    double heading, dist, vel, stopDist;
    EvalDB_cell evaldb;
    UU u;
    for (double vt = vr.min_v;vt < vr.max_v;vt = vt + model.MD_V_RESOLUTION)
    {
        for (double ot = vr.min_w;ot < vr.max_w;ot = ot + model.MD_W_RESOLUTION)
        {
            u.vt = vt;
            u.ot = ot;

            GT = GenerateTrajectory(state, u, evalParam[3], model);
         
            heading = CalcHeadingEval(GT.state, goal);
            dist = CalcDistEval(GT.state, obs, R);
            vel = abs(vt);
            stopDist = CalcBreakingDist(vel, model);

            if (dist > stopDist)
            {
                evaldb.vt = vt;
                evaldb.ot = ot;
                evaldb.heading = heading;
                evaldb.dist = dist;
                evaldb.vel = vel;
                DB.EvalDB.push_back(evaldb);
                
             /*   DB.trajDB.push_back(traj);*/

            }
        }
    }

    return DB;

}


void NormalizeEval(std::vector<EvalDB_cell> &EvalDB)
{
    int n = EvalDB.size();
    double sum1 = 0, sum2 = 0, sum3 = 0;
    int i;
 
    for (i = 0;i < n;i++) { sum1 = sum1 + EvalDB[i].heading; }
    for (i = 0;i < n;i++) { EvalDB[i].heading = EvalDB[i].heading / sum1; }

    for (i = 0;i < n;i++) { sum2 = sum2 + EvalDB[i].dist; }
    for (i = 0;i < n;i++) { EvalDB[i].dist = EvalDB[i].dist / sum2; }

    for (i = 0;i < n;i++) { sum3 = sum3 + EvalDB[i].vel; }
    for (i = 0;i < n;i++) { EvalDB[i].vel = EvalDB[i].vel / sum3; }

}

GTreturn GenerateTrajectory(State state, UU u, double evaldt, KModel model)
{
    GTreturn GT;
    double time = 0;
    GT.traj.push_back(state);
    while (time <= evaldt)
    {
        time = time + dt;
        state = f(state, u);
        GT.traj.push_back(state);
    }
    GT.state = state;
    return GT;

}


double CalcBreakingDist(double vel, KModel model)
{
    double stopDist = 0;
    while (vel > 0)
    {
        stopDist = stopDist + vel * dt;
        vel = vel - model.MD_ACC * dt;

    }
    return stopDist;

}



double CalcDistEval(State state, std::vector<OB>& obs, double R)
{
    //Define an upper distance limit
    double dist = 100;
    for (int io = 0;io < obs.size();io++)
    {
        double disttmp = sqrt(pow(obs[io].x - state.x, 2) + pow(obs[io].y - state.y, 2)) - R;
        if (dist > disttmp)
        {
            dist = disttmp;
        }

    }
    if (dist >= 2 * R)
    {
        dist = 2 * R;
    }
    return dist;
}
double CalcHeadingEval(State state, double goal[2])
{
    double theta = toDegree(state.yaw);
    double goalTheta = toDegree(atan2(goal[1] - state.y, goal[0] - state.x));
    double targetTheta;
    if (goalTheta > theta)
    {
        targetTheta = goalTheta - theta;
    }
    else
    {
        targetTheta = theta - goalTheta;
    }
    double heading = 90 - targetTheta;
    return heading;



}

VR CalcDynamicWindow(State state, KModel model)
{
    VR vr;
    vr.min_v = max(0, state.v - model.MD_ACC * dt);
    vr.max_v = min(model.MD_MAX_V, state.v + model.MD_ACC * dt);
    vr.min_w = max(-model.MD_MAX_W, state.w - model.MD_VW * dt);
    vr.max_w = min(model.MD_MAX_W, state.w + model.MD_VW * dt);

    return vr;

}

State f(State state, UU u)
{
    State state2;

    state2.x = state.x + u.vt * dt * cos(state.yaw);
    state2.y = state.y + u.vt * dt * sin(state.yaw);
    state2.yaw = state.yaw + dt * u.ot;
    state2.v = u.vt;
    state2.w = u.ot;

    return state2;
}



double toRadian(double degree)
{
    double radian = degree / 180 * pi;
    return radian;

}

double toDegree(double radian)
{

    double degree = radian / pi * 180;
    return degree;

}
double max(double a, double b)
{
    if (a < b) { a = b; };
    return a;

}
double min(double a, double b)
{
    if (a > b) { a=b; };
    return a;

}

