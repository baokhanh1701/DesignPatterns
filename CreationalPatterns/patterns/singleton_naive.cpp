#include <iostream>
#include <thread>
using namespace std;

class Singleton
{
protected:
    string value_;
    Singleton(const string value) : value_(value){};
    static Singleton *singleton_;

public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;
    static Singleton *GetInstance(const string &value);
    void SomeBusinessLogic()
    {
        cout << "Business Logic" << endl;
    }
    string value() const
    {
        return value_;
    }
};

Singleton *Singleton::singleton_ = nullptr;

Singleton *Singleton::GetInstance(const string &value)
{
    if (singleton_ == nullptr)
    {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadOne()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("thread 1");
    cout << singleton->value() << "\n";
}

void ThreadTwo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("thread 2");
    cout << singleton->value() << "\n";
}

int main()
{
    cout << "If you see the same value, then singleton was reused. (1 thread, yay!!!)\n";
    cout << "If you see different values, then 2 singletons were created. (multithread) \n";
    thread t1(ThreadOne);
    thread t2(ThreadTwo);
    t1.join();
    t2.join();
    return 0;
}