// Caleb Atchison
// Programming Languages Exam 2

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Question 1 ----------------

class Profession {
public:
    virtual void description() = 0;
    virtual void salary() = 0;
    virtual void regrets() = 0;
    virtual ~Profession() {}
};

class Barista : public Profession {
public:
    void description() override {
        std::cout << "I am a barista and I serve coffee to happy customers" << std::endl;
    }
    void salary() override {
        std::cout << "I make $25,000 per year" << std::endl;
    }
    void regrets() override {
        std::cout << "I wish I had gone to UCF to become a software engineer" << std::endl;
    }
};

class PsychologyMajor : public Profession {
public:
    void description() override {
        std::cout << "I am a psychology major at USF and hope to learning something some day" << std::endl;
    }
    void salary() override {
        std::cout << "I will make $45,000 per year" << std::endl;
    }
    void regrets() override {
        std::cout << "I wish I could pay my student loans when I graduate" << std::endl;
    }
};

class SoftwareEngineer : public Profession {
public:
    void description() override {
        std::cout << "I am a software engineer and I solve problems" << std::endl;
    }
    void salary() override {
        std::cout << "I make $125,000 per year" << std::endl;
    }
    void regrets() override {
        std::cout << "I am glad I went to UCF and majored in computer science" << std::endl;
    }
};

// Question 2 -------------

class Observer {
    public:
        virtual ~Observer() {}
        virtual void update(const std::string& itemName, double price, int quantity) = 0;
    };
    
    class Subject {
    public:
        virtual ~Subject() {}
        virtual void attach(Observer* observer) = 0;
        virtual void detach(Observer* observer) = 0;
        virtual void notify() = 0;
    };
    
    class GroceryItem : public Subject {
    private:
        std::string name;
        double price;
        int quantity;
        std::vector<Observer*> observers;
    
    public:
        GroceryItem(const std::string& name, double price, int quantity)
            : name(name), price(price), quantity(quantity) {}
    
        void attach(Observer* observer) override {
            observers.push_back(observer);
        }
    
        void detach(Observer* observer) override {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }
    
        void notify() override {
            for (Observer* obs : observers) {
                obs->update(name, price, quantity);
            }
        }
    
        void setPrice(double newPrice) {
            price = newPrice;
            notify();
        }
    
        void setQuantity(int newQuantity) {
            quantity = newQuantity;
            notify();
        }
};
    
class Customer : public Observer {
private:
    std::string name;

public:
    Customer(const std::string& name) : name(name) {}

    void update(const std::string& itemName, double price, int quantity) override {
        std::cout << "Hello, " << name << "! "
                    << "The item '" << itemName << "' has been updated.\n"
                    << "  New Price: $" << price << "\n"
                    << "  Quantity: " << quantity << "\n"
                    << std::endl;
    }
};

int main() {

    // Question 1

    Barista barista;
    barista.description();
    barista.salary();
    barista.regrets();

    PsychologyMajor psych;
    psych.description();
    psych.salary();
    psych.regrets();

    SoftwareEngineer se;
    se.description();
    se.salary();
    se.regrets();

    // Question 2

    std::cout << "\n\n";

    GroceryItem milk("Milk", 2.99, 10);
    GroceryItem eggs("Eggs", 3.49, 30);

    Customer alice("Alice");
    Customer bob("Bob");

    milk.attach(&alice);
    milk.attach(&bob);

    eggs.attach(&bob);

    milk.setPrice(2.79);
    eggs.setQuantity(0);

    return 0;
}