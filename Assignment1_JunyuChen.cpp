#include <iostream>
#include <string>
using namespace std;

class Vehicle{
private:
    int age;
public:
    Vehicle(int age);
    int getAge() const;
    int repeats() const;
    int ageInMonths() const;
    void print() const;
    virtual string complianceLabel() const;
    virtual ~Vehicle();
};
Vehicle::Vehicle(int age) : age(age){}
int Vehicle::getAge() const{return this->age;}
string Vehicle::complianceLabel() const{
    return "GENERAL";
}
int Vehicle::repeats() const{    //Recognizing subclass by getting label by complianceLabel function
    string label = complianceLabel();
    if (label == "CAR") return 2;
    if (label == "BIKE") return 3;
    if (label == "BUS") return 4;
    if (label == "TRUCK") return 5;

    return 1; // 1 is for father class Vehicle
}
int Vehicle::ageInMonths() const{
    return getAge();
}
void Vehicle::print() const{
    cout << ageInMonths();
    for (int i = 0; i < repeats(); ++i) {  //reusing repeats function to print amount of according time output
        cout << " " << complianceLabel();
    }
    cout << endl;
}
Vehicle::~Vehicle() {}

class Car : public Vehicle{
public:
    Car(int age);
    int repeats() const;
    virtual string complianceLabel() const;
    virtual ~Car();
};
Car::Car(int age) : Vehicle(age){}
Car::~Car() {}

int Car::repeats() const {
    return 2;
}
string Car::complianceLabel() const {
    return "CAR";
}

class Bike : public Vehicle{
public:
    Bike(int age);
    int repeats() const;
    virtual string complianceLabel() const;
    virtual ~Bike();
};
Bike::Bike(int age) : Vehicle(age) {}
int Bike::repeats() const {
    return 3;
}
string Bike::complianceLabel() const {
    return "BIKE";
}
Bike::~Bike() {}

class Bus : public Vehicle{
public:
    Bus(int age);
    int repeats() const;
    virtual string complianceLabel() const;
    virtual ~Bus();
};
Bus::Bus(int age) : Vehicle(age) {}
int Bus::repeats() const {
    return 4;
}
string Bus::complianceLabel() const {
    return "BUS";
}
Bus::~Bus() {}

class Truck : public Vehicle{
public:
    Truck(int age);
    int repeats() const;
    virtual string complianceLabel() const;
    virtual ~Truck();
};
Truck::Truck(int age) : Vehicle(age) {}
int Truck::repeats() const {
    return 4;
}
string Truck::complianceLabel() const {
    return "TRUCK";
}
Truck::~Truck() {}

int main() {
    Vehicle v0(12);
    Car c0(24);
    Bike b0(6);
    Bus bus0(111);
    Truck t0(60);

    v0.print();
    c0.print();
    b0.print();
    t0.print();
    bus0.print();
    cout << endl;

    Vehicle* vehicles[10];

    vehicles[0] = new Car(10);
    vehicles[1] = new Bike(5);
    vehicles[2] = new Bus(48);
    vehicles[3] = new Vehicle(7);
    vehicles[4] = new Bike(20);
    vehicles[5] = new Car(36);
    vehicles[6] = new Vehicle(2);
    vehicles[7] = new Bus(120);
    vehicles[8] = new Bike(9);
    vehicles[9] = new Bike(3);

    for (int i = 0; i < 10; ++i) {
        vehicles[i]->print();
    }
    for (int i = 0; i < 10; ++i) {
        delete vehicles[i];
        vehicles[i] = 0;
    }
    return 0;
}
