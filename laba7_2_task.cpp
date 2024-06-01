#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ParkingGarage {
public:
    virtual void arrive(const string& car) = 0;
    virtual void depart(const string& car) = 0;
    virtual bool contains(const string& car) const = 0;
    virtual void display() const = 0;
    virtual ~ParkingGarage() = default;
};

class Garage : public ParkingGarage {
private:
    vector<string> parkingLine;

public:
    void arrive(const string& car) override {
        parkingLine.push_back(car);
        cout << "Автомобіль " << car << " приїхав." << endl;
    }

    void depart(const string& car) override {
        auto it = find(parkingLine.rbegin(), parkingLine.rend(), car);
        if (it != parkingLine.rend()) {
            cout << "Автомобіль " << car << " виїхав." << endl;
            parkingLine.erase((it + 1).base());
        } else {
            cout << "Автомобіль " << car << " не в гаражі." << endl;
        }
    }

    bool contains(const string& car) const override {
        return find(parkingLine.begin(), parkingLine.end(), car) != parkingLine.end();
    }

    void display() const override {
        cout << "Поточна лінія паркування: ";
        for (const auto& car : parkingLine) {
            cout << car << " ";
        }
        cout << endl;
    }
};

int main() {
    Garage garage;

    garage.arrive("Toyota");
    garage.arrive("BMW");
    garage.arrive("Audi");
    garage.display();

    garage.depart("BMW");
    garage.display();

    garage.depart("Mercedes");
    garage.display();

    if (garage.contains("Toyota")) {
        cout << "Toyota в гаражі." << endl;
    } else {
        cout << "Toyota не в гаражі." << endl;
    }

    return 0;
}
