#include <bits/stdc++.h>
using namespace std;

// class Target
// {
// public:
//     virtual ~Target() = default;
//     virtual string Request() const
//     {
//         return "Target: default target's behavior.";
//     }
// };

class RoundPeg
{
private:
    float radius;

public:
    RoundPeg() {};
    RoundPeg(const float radius)
    {
        this->radius = radius;
    }
    float getRadius()
    {
        return this->radius;
    }
};
class RoundHole
{
private:
    float radius;

public:
    RoundHole(){};
    RoundHole(const float radius)
    {
        this->radius = radius;
    };
    virtual ~RoundHole() = default;
    virtual float getRadius()
    {
        return this->radius;
    }
    virtual bool fits(RoundPeg *peg)
    {
        return this->getRadius() >= peg->getRadius();
    }
};

// class Adaptee
// {
// public:
//     string SpecificRequest() const
//     {
//         return ".eetpadA eht fo roivaheb laicepS";
//     }
// };



class SquarePeg
{
private:
    float width;

public:
    SquarePeg() {};
    SquarePeg(const float width)
    {
        this->width = width;
    }
    float getWidth()
    {
        return this->width;
    }
};
// class Adapter : public Target
// {
// private:
//     Adaptee *adaptee_;

// public:
//     Adapter(Adaptee *adaptee) : adaptee_(adaptee){};
//     string Request() const override
//     {
//         string to_reverse = this->adaptee_->SpecificRequest();
//         std::reverse(to_reverse.begin(), to_reverse.end());
//         return "Adapter: (Translated)" + to_reverse;
//     }
// };

class SquarePegAdapter : public RoundPeg
{
private:
    SquarePeg *peg_;

public:
    SquarePegAdapter(SquarePeg *peg)
    {
        this->peg_ = peg;
    }
    float getRadius()
    {
        return peg_->getWidth() * sqrt(2) / 2;
    }
};

void ClientCode(RoundHole *target, RoundPeg *peg)
{
    cout << target->fits(peg);
};

// int main()
// {
//     cout << "Client: I can work just fine with the Target objects: ";
//     Target *target = new Target;
//     ClientCode(target);
//     cout << "\n\n";
//     Adaptee *adaptee = new Adaptee;
//     cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
//     cout << "Adaptee: " << adaptee->SpecificRequest();
//     cout << "\n\n";
//     cout << "Client: But I can work with it via the Adapter: \n";
//     Adapter *adapter = new Adapter(adaptee);
//     ClientCode(adapter);
//     cout << "\n";

//     delete target;
//     delete adaptee;
//     delete adapter;

//     return 0;
// }

int main()
{
    RoundHole *round_hole = new RoundHole(5);
    RoundPeg *rpeg = new RoundPeg(5);
    cout << round_hole->fits(rpeg) << "\n";

    SquarePeg *small_square_peg = new SquarePeg(5);
    SquarePeg *large_square_peg = new SquarePeg(10);
    // round_hole.fits(small_square_peg); Wont compile
    // round_hole.fits(large_square_peg); Wont compile

    RoundPeg *small_square_adapter = new SquarePegAdapter(small_square_peg);
    RoundPeg *large_square_adapter = new SquarePegAdapter(large_square_peg);

    cout << round_hole->fits(small_square_adapter) << "\n";
    cout << round_hole->fits(large_square_adapter) << "\n";
    return 0;
}