#include "vector"
#include "iostream"

// 基本监控器，用于监控设置轮速
class Monitor {
public:
	Monitor(float timer_div):timerDivision(timer_div) {
		leftAbnormalCount = 0;
		rightAbnormalCount = 0;
	};
	~Monitor() {};
	void CheckLeftWheelSpeed() {
		leftAbnormalCount++;
	}	
	void CheckRightWheelSpeed() {
		rightAbnormalCount++;
	}
private:
	float timerDivision;
	float setWheelLeftSpeed;
	float setWheelRightSpeed;
	float feedWheelLeftSpeed;
	float feedWheelRightSpeed;
	// 异常计数
	uint16_t leftAbnormalCount;
	uint16_t rightAbnormalCount;
};
// 物理受困监控器
class PhysicialStuck : public Monitor {
public:
	PhysicialStuck() {};
	~PhysicialStuck() {};
private:
	float setRobotLinearSpeed;
	float setRobotAngularSpeed;
	float robotLinearSpeedByEncoder;
	float robotAngularSpeedByEncoder;
	float robotLinearSpeedBySlam;
	float robotAngularSpeedBySlam;
	float robotLinearSpeedByGyro;
	float robotAngularSpeedByGyro;
};

// 基本任务
class BasicTask {

};

// 带监控器的基本任务
class TaskAndMonitor {

};

// 高阶任务1, 沿墙运动
class WallFollowingTask : public TaskAndMonitor{
	
};