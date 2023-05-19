#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class Database
{
private:
    static Database *pinstance_;
    static mutex mutex_;

protected:
    Database(const string value) : value_(value){};
    ~Database(){};
    string value_;

public:
    Database(Database &other) = delete;
    void operator=(const Database &) = delete;

    static Database *GetInstance(const string &value);
    void SomeBusinessLogic()
    {
        cout << "this is some business logic \n";
    }
    string value() const
    {
        return value_;
    }
};

Database *Database::pinstance_{nullptr};
mutex Database::mutex_;

Database *Database::GetInstance(const string &value)
{
    lock_guard<mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Database(value);
    }
    return pinstance_;
}

void ThreadFoo()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Database *singleton = Database::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Database *singleton = Database::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{
    cout << "If you see the same value, then singleton was reused. (right since this is thread-safe)\n";
    cout << "If you see different values, then 2 singletons were created. (wrong, since you implemented thread-safe) \n";
    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();
    return 0;
}