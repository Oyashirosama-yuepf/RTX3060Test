#include <holo/common/holo_memory.hpp>

#include <deque>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

struct C
{
    int data;
};

class TestObject
{
public:
    TestObject()
    {
        p = new C;
    }
    ~TestObject()
    {
        delete p;
        p = nullptr;
    }
    bool operator<(const TestObject& other)
    {
        if (p->data < other.p->data)
        {
            return true;
        }

        if (w < other.w)
        {
            return true;
        }
        return false;
    }
    C*  p = nullptr;
    int w = 0;
};

TEST(TestMemory, Shared_ptr)
{
    // custom structure and shared_ptr
    ::std::cout << "shared_ptr with custom structure begin." << ::std::endl;
    std::shared_ptr<TestObject> p1 = nullptr;
    std::shared_ptr<TestObject> p2(nullptr);
    std::shared_ptr<TestObject> p3(new TestObject);
    std::shared_ptr<TestObject> p4(new TestObject, std::default_delete<TestObject>());
    std::shared_ptr<TestObject> p5(new TestObject, [](TestObject* p) { delete p; }, std::allocator<TestObject>());
    std::shared_ptr<TestObject> p6(p5);
    std::shared_ptr<TestObject> p7(std::move(p4));
    std::shared_ptr<TestObject> p8(std::unique_ptr<TestObject>(new TestObject));
    std::shared_ptr<TestObject> obj(new TestObject);
    std::shared_ptr<C>          p9(obj, obj->p);
    std::shared_ptr<TestObject> p10 = ::std::make_shared<TestObject>();
    ::std::cout << "shared_ptr with custom structure done." << ::std::endl;
}

TEST(TestMemory, Unique_ptr)
{
    // custom structure and unique_ptr
    ::std::cout << "Unique_ptr with custom structure begin." << ::std::endl;
    std::default_delete<TestObject> d;
    std::unique_ptr<TestObject>     u1;
    std::unique_ptr<TestObject>     u2(nullptr);
    std::unique_ptr<TestObject>     u3(new TestObject);
    std::unique_ptr<TestObject>     u4(new TestObject, d);
    std::unique_ptr<TestObject>     u5(new TestObject, std::default_delete<TestObject>());
    std::unique_ptr<TestObject>     u6(std::move(u5));
    std::unique_ptr<TestObject>     u7(std::move(u6));
    // std::unique_ptr<TestObject>     u8 = std::make_unique<TestObject>();
    // std::unique_ptr<TestObject> u8(std::auto_ptr<TestObject>(new
    // TestObject));
    ::std::cout << "Unique_ptr with custom structure done." << ::std::endl;
}
TEST(TestMemory, Normal_New_Delete)
{
    // normal new and delete
    ::std::cout << "Normal new and delete begin." << ::std::endl;
    TestObject* t = new TestObject;
    delete t;

    TestObject* t_array = new TestObject[2];
    delete[] t_array;
    ::std::cout << "Normal new and delete done." << ::std::endl;
}
TEST(TestMemory, STL_Vector)
{
    // constructors used in the same order as described above:
    ::std::cout << "STL vector begin." << ::std::endl;
    ::std::vector<int> first;           // empty vector of ints
    ::std::vector<int> second(4, 100);  // four ints with value 100
    ::std::vector<int> third(second.begin(),
                             second.end());  // iterating through second
    ::std::vector<int> fourth(third);        // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int                myints[] = {16, 2, 77, 29};
    ::std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    ::std::vector<int> sixth(::std::move(fifth));

    ::std::cout << "STL vector done." << ::std::endl;
}

TEST(TestMemory, STL_List)
{
    ::std::cout << "STL list begin." << ::std::endl;

    ::std::list<int> first;                                // empty list of ints
    ::std::list<int> second(4, 100);                       // four ints with value 100
    ::std::list<int> third(second.begin(), second.end());  //
    // iterating through second
    ::std::list<int> fourth(third);  // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int              myints[] = {16, 2, 77, 29};
    ::std::list<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    ::std::cout << "STL list done." << ::std::endl;
}
bool fncomp(char lhs, char rhs)
{
    return lhs < rhs;
}

struct classcomp
{
    bool operator()(const char& lhs, const char& rhs) const
    {
        return lhs < rhs;
    }
};

TEST(TestMemory, STL_Map)
{
    ::std::cout << "STL map begin." << ::std::endl;
    ::std::map<char, int> first;

    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    ::std::map<char, int> second(first.begin(), first.end());

    ::std::map<char, int> third(second);

    ::std::map<char, int, classcomp> fourth;  // class as Compare

    bool (*fn_pt)(char, char) = fncomp;
    // std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer Compare
    ::std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer Compare
    ::std::map<TestObject, int>                 sixth;
    ::std::cout << "STL map done." << ::std::endl;
}
TEST(TestMemory, STL_deque)
{
    ::std::cout << "STL deque begin." << ::std::endl;

    // constructors used in the same order as described above:
    ::std::deque<int> first;                                // empty deque of ints
    ::std::deque<int> second(4, 100);                       // four ints with value 100
    ::std::deque<int> third(second.begin(), second.end());  // iterating through second
    ::std::deque<int> fourth(third);                        // a copy of third

    // the iterator constructor can be used to copy arrays:
    int               myints[] = {16, 2, 77, 29};
    ::std::deque<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    ::std::cout << "STL deque done." << ::std::endl;
}
TEST(TestMemory, STL_set)
{
    ::std::cout << "STL set begin." << ::std::endl;
    ::std::set<int> first;  // empty set of ints

    int             myints[] = {10, 20, 30, 40, 50};
    ::std::set<int> second(myints, myints + 5);  // range

    ::std::set<int> third(second);  // a copy of second

    ::std::set<int> fourth(second.begin(), second.end());  // iterator ctor.

    ::std::set<int, classcomp> fifth;  // class as Compare

    bool (*fn_pt)(char, char) = fncomp;
    ::std::set<char, bool (*)(char, char)> sixth(fn_pt);  // function pointer as Compare
    ::std::cout << "STL set done." << ::std::endl;
}

typedef ::std::unordered_map<std::string, std::string> stringmap;

stringmap merge(stringmap a, stringmap b)
{
    stringmap temp(a);
    temp.insert(b.begin(), b.end());
    return temp;
}
TEST(TestMemory, STL_unordered_map)
{
    ::std::cout << "STL unordered_map begin." << ::std::endl;
    stringmap first;                                                 // empty
    stringmap second({{"apple", "red"}, {"lemon", "yellow"}});       // init list
    stringmap third({{"orange", "orange"}, {"strawberry", "red"}});  // init list
    stringmap fourth(second);                                        // copy
    stringmap fifth(merge(third, fourth));                           // move
    stringmap sixth(fifth.begin(), fifth.end());                     // range

    ::std::cout << "STL unordered_map done." << ::std::endl;
}
TEST(TestMemory, STL_string)
{
    ::std::cout << "STL string begin." << ::std::endl;
    ::std::string s0("Initial string");

    // constructors used in the same order as described above:
    ::std::string s1;
    ::std::string s2(s0);
    ::std::string s3(s0, 8, 3);
    ::std::string s4("A character sequence");
    ::std::string s5("Another character sequence", 12);
    ::std::string s6a(10, 'x');
    ::std::string s6b(10, 42);  // 42 is the ASCII code for '*'
    ::std::string s7(s0.begin(), s0.begin() + 7);

    ::std::cout << "STL string done." << ::std::endl;
}

TEST(TestMemory, Basic_type)
{
    ::std::cout << "basic new begin." << ::std::endl;
    std::shared_ptr<char> p0(new char);
    ::std::cout << "basic new done." << ::std::endl;
}

TEST(TestMemory, Test_memory)
{
    const unsigned int memory_pool_size = ::holo::holo_memory_default_value;
    {
        bool ok = ::holo::HoloMemoryInit(memory_pool_size);
        ASSERT_TRUE(ok);

        ok &= ::holo::HoloMemoryDestroy();
        ASSERT_TRUE(ok);
    }
    {
        bool ok = ::holo::HoloMemoryInit(::holo::holo_memory_limit + 1);
        ASSERT_FALSE(ok);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
