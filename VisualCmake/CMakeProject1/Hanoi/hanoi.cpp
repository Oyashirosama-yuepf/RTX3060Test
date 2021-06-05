#include <iostream>

using namespace std;
class Hanoilmpl {
public:
    static void hanoi(int n, char A, char B, char C) {
        if (n == 1) {
            move(A, C);
        }
        else {
            hanoi(n - 1, A, C, B);
            move(A, C);
            hanoi(n - 1, B, A, C);
        }
    }
private:
    static void move(char A, char C) {
        std::cout << "move:" << A << "----->" << C << std::endl;
    }

public:
    static void main() {
        std::cout << "move hanoi step:" << std::endl;
        hanoi(3, 'a', 'b', 'c');
    }
};

