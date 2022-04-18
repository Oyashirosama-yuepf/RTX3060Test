#include "vector"
#include "iostream"

// ��������������ڼ����������
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
	// �쳣����
	uint16_t leftAbnormalCount;
	uint16_t rightAbnormalCount;
};
// �������������
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

// ��������
class BasicTask {

};

// ��������Ļ�������
class TaskAndMonitor {

};

// �߽�����1, ��ǽ�˶�
class WallFollowingTask : public TaskAndMonitor{
	
};