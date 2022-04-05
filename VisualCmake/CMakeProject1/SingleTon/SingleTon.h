using namespace std;

class SingleTon {
public:
	void testSingleTonOutput() {
		cout << "output from singleTon" << endl;
	}
private:
	SingleTon() {
		cout << "singleTon test initial" << endl;
	}
	~SingleTon() {
		cout << "singleTon test stop" << endl;
	}
	SingleTon(SingleTon& s) {
		cout << "singleTon copy intial" << endl;
	};
private:
	static SingleTon* instance;
public:
	static SingleTon* GetSingleTonInstance() {
		if (instance != NULL) {
			instance = new SingleTon();
		}
		cout << "singleTon is being used" << endl;
		return instance;
	}
};