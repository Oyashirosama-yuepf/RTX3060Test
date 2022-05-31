#include "iostream"

using namespace std;

class ExternFunction {
public:
	ExternFunction() {};
	~ExternFunction() {};
public:
	void ExternOutput() {
		cout << "output from extern" << output_value << endl;
	}
private:
	static const uint16_t output_value = 100;
};