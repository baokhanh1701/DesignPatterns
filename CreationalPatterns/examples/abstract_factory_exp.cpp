#include <iostream>
using namespace std;

class Chair
{
public:
    virtual ~Chair(){};
    virtual string hasLegs() const = 0;
    virtual string sitOn() const = 0;
};

class VictorianChair : public Chair
{
public:
    string hasLegs() const override
    {
        return "This Victorian Chair has legs.";
    }
    string sitOn() const override
    {
        return "This Victorian Chair can be sit on.";
    }
};
class ModernChair : public Chair
{
public:
    string hasLegs() const override
    {
        return "This Modern Chair has legs.";
    }
    string sitOn() const override
    {
        return "This Modern Chair can be sit on.";
    }
};

class Sofa
{
public:
    virtual ~Sofa(){};
    virtual string hasLegs() const = 0;
    virtual string sitOn() const = 0;
};

class VictorianSofa : public Sofa
{
public:
    string hasLegs() const override
    {
        return "This Victorian Sofa has legs.";
    }
    string sitOn() const override
    {
        return "This Victorian Sofa can be sit on.";
    }
};
class ModernSofa : public Sofa
{
public:
    string hasLegs() const override
    {
        return "This Modern Sofa has legs.";
    }
    string sitOn() const override
    {
        return "This Modern Sofa can be sit on.";
    }
};

class CoffeeTable
{
public:
    virtual ~CoffeeTable(){};
    virtual string hasLegs() const = 0;
    virtual string coffeeSet(const Chair &collaborator) const = 0;
};
class VictorianCoffeeTable : public CoffeeTable
{
public:
    string hasLegs() const override
    {
        return "This Victorian Coffee Table has legs";
    }
    string coffeeSet(const Chair &collaborator) const override
    {
        const string result = collaborator.hasLegs();
        return "The result of the VictorianCoffeeTable collaborating with ( " + result + " )";
    }
};
class ModernCoffeeTable : public CoffeeTable
{
public:
    string hasLegs() const override
    {
        return "This Modern Coffee Table has legs";
    }
    string coffeeSet(const Chair &collaborator) const override
    {
        const string result = collaborator.hasLegs();
        return "The result of the ModernCoffeeTable collaborating with ( " + result + " )";
    }
};

class FunitureFactory
{
public:
    virtual Chair *CreateChair() const = 0;
    virtual CoffeeTable *CreateCoffeeTable() const = 0;
    virtual Sofa *CreateSofa() const = 0;
};

class VictorianFunitureFactory : public FunitureFactory
{
public:
    Chair *CreateChair() const override
    {
        return new VictorianChair();
    }
    CoffeeTable *CreateCoffeeTable() const override
    {
        return new VictorianCoffeeTable();
    }
    Sofa *CreateSofa() const override
    {
        return new VictorianSofa();
    }
};

class ModernFunitureFactory : public FunitureFactory
{
public:
    Chair *CreateChair() const override
    {
        return new ModernChair();
    }
    CoffeeTable *CreateCoffeeTable() const override
    {
        return new ModernCoffeeTable();
    }
    Sofa *CreateSofa() const override
    {
        return new ModernSofa();
    }
};
void ClientCode(const FunitureFactory &factory)
{
    const Chair *chair = factory.CreateChair();
    const CoffeeTable *coffee_table = factory.CreateCoffeeTable();
    const Sofa *sofa = factory.CreateSofa();
    std::cout << chair->hasLegs() << "\n";
    std::cout << sofa->sitOn() << "\n";
    std::cout << coffee_table->coffeeSet(*chair) << "\n";
    delete chair;
    delete coffee_table;
}

int main()
{
    cout << "Client: Testing client code with the victorian factory type: \n";
    VictorianFunitureFactory *victorian_factory = new VictorianFunitureFactory();
    ClientCode(*victorian_factory);
    delete victorian_factory;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the modern factory type:\n";
    ModernFunitureFactory *modern_factory = new ModernFunitureFactory();
    ClientCode(*modern_factory);
    delete modern_factory;
    return 0;
}