#include <iostream>
using namespace std;

class Transport
{
public:
    virtual ~Transport(){};
    virtual string deliver() const = 0;
};

class Truck : public Transport
{
    string deliver() const override
    {
        return "Deliver by land in a box";
    }
};

class Ship : public Transport
{
    string deliver() const override
    {
        return "Deliver by sea in a container";
    }
};

class Logistic
{
public:
    virtual ~Logistic(){};
    virtual Transport *FactoryMethod() const = 0;
    string SomeOperation() const
    {
        Transport *transport = this->FactoryMethod();
        string result = "Logistic: the same logistic's code has just worked with: " + transport->deliver();
        delete transport;
        return result;
    }
};

class RoadLogistics : public Logistic
{
public:
    Transport *FactoryMethod() const override
    {
        return new Truck();
    }
};

class SeaLogistics : public Logistic
{
public:
    Transport *FactoryMethod() const override
    {
        return new Ship();
    }
};

void ClientCode(const Logistic &logistic)
{
    cout << "Client: I'm not aware of the logistic's class, but it still works.\n"
         << logistic.SomeOperation() << std::endl;
}

int main()
{
    std::cout << "App: Launched with the RoadLogistics.\n";
    Logistic *logistic = new RoadLogistics();
    ClientCode(*logistic);

    std::cout << std::endl;
    std::cout << "App: Launched with the SeaLogistics.\n";
    Logistic *logistic2 = new SeaLogistics();
    ClientCode(*logistic2);

    delete logistic;
    delete logistic2;
    return 0;
}
