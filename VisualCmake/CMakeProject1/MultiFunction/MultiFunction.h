#include "vector"
#include "iostream"

using namespace std;

class TakeBus {
public:
	TakeBus() {
		cout << "Take Bus Initial" << endl;
	}

	~TakeBus() {
		cout << "Take Bus Stop" << endl;
	}

public:
	void TakeBusToSubway() {
		cout << "Take Bus To Subway" << endl;
	}

	void TakeBusToStation() {
		cout << "Take Bus To Station" << endl;
	}
};

class Bus {
public:
	void TakeBusToSomewhere(TakeBus& take_bus) {
		cout << "Take Bus To Unknow Place" << endl;
	}
};

class Subway : public Bus {
public:
	virtual void TakeBusToSomewhere(TakeBus& take_bus) {
		take_bus.TakeBusToSubway();
	}
};

class Station :public Bus {
public:
	void TakeBusToSomewhere(TakeBus& take_bus) {
		take_bus.TakeBusToStation();
	}
};