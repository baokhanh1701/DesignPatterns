#include <iostream>
#include <unordered_map>
using namespace std;

// enum Type
// {
//     PROTOTYPE_1 = 0,
//     PROTOTYPE_2
// };
enum ShapeType
{
    RECTANGLE = 0,
    CIRCLE
};

// class Prototype
// {
// protected:
//     string prototype_name_;
//     float prototype_field_;

// public:
//     Prototype(){};
//     Prototype(string prototype_name_) : prototype_name_(prototype_name_){};
//     virtual ~Prototype(){};
//     virtual Prototype *Clone() const = 0;
//     virtual void Method(float prototype_field)
//     {
//         this->prototype_field_ = prototype_field;
//         cout << "Call method from" << prototype_name_ << "with field" << prototype_field << endl;
//     }
// };

class Shape
{
protected:
    string shape_name_;
    float shape_field_x_;
    float shape_field_y_;

public:
    Shape(){};
    Shape(string shape_name_) : shape_name_(shape_name_){};
    virtual ~Shape(){};
    virtual Shape *clone() const = 0;
    virtual void Method(float shape_field_x, float shape_field_y)
    {
        this->shape_field_x_ = shape_field_x;
        this->shape_field_y_ = shape_field_y;
        cout << "Call method from" << shape_name_ << "with field" << shape_field_x << ", " << shape_field_y << endl;
    }
};

// class ConcretePrototype1 : public Prototype
// {
// private:
//     float concrete_prototype_field1_;

// public:
//     ConcretePrototype1(string prototype_name, float concrete_prototype_field) : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field){};
//     Prototype *Clone() const override
//     {
//         return new ConcretePrototype1(*this);
//     }
// };

class Rectangle : public Shape
{
private:
    float width_;
    float height_;

public:
    Rectangle(string rectangle_name, float width, float height) : Shape(rectangle_name), width_(width), height_(height) {};
    Shape *clone() const override
    {
        return new Rectangle(*this);
    }
};

// class ConcretePrototype2 : public Prototype
// {
// private:
//     float concrete_prototype_field2_;

// public:
//     ConcretePrototype2(string prototype_name, float concrete_prototype_field) : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field){};
//     Prototype *Clone() const override
//     {
//         return new ConcretePrototype2(*this);
//     }
// };
class Circle : public Shape
{
private:
    float radius_;
public: 
    Circle(string circle_name, float radius) : Shape(circle_name), radius_(radius){};
    Shape *clone() const override
    {
        return new Circle(*this);
    }
};

class PrototypeFactory
{
private:
    unordered_map<ShapeType, Shape *, hash<int>> prototypes_;

public:
    PrototypeFactory()
    {
        prototypes_[ShapeType::RECTANGLE] = new Rectangle("Prototype_Rectangle", 50.f, 20.f);
        prototypes_[ShapeType::CIRCLE] = new Circle("PROTOTYPE_CIRCLE", 60.f);
    };
    ~PrototypeFactory()
    {
        delete prototypes_[ShapeType::RECTANGLE];
        delete prototypes_[ShapeType::CIRCLE];
    }
    Shape *CreatePrototype(ShapeType type)
    {
        return prototypes_[type]->clone();
    }
};



void Client(PrototypeFactory &prototype_factory)
{
    cout << "Let's create a Prototype 1\n";
    Shape *prototype = prototype_factory.CreatePrototype(ShapeType::RECTANGLE);
    prototype->Method(90, 20);
    delete prototype;

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";
    prototype = prototype_factory.CreatePrototype(ShapeType::CIRCLE);
    prototype->Method(10, 20);
    delete prototype;
}

int main()
{
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;
    return 0;
}