#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "D:\CPP\projekt-2-lukasz-rybakowski\include\tinyxml2.h" // Biblioteka tinyxml2

using namespace tinyxml2;

class Drink {
private:
    std::string name;
    double price;
    int quantity;

public:
    
    Drink(const std::string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    
    std::string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    
    void setQuantity(int newQuantity) {
        if (newQuantity < 0) {
            throw std::invalid_argument("Ilość nie może być ujemna!");
        }
        quantity = newQuantity;
    }
};

class VendingMachine {
private:
    std::vector<Drink> drinks;
    double balance = 0.0;

    void loadDrinksFromXML(const std::string& fileName) {
        XMLDocument doc;
        if (doc.LoadFile(fileName.c_str()) != XML_SUCCESS) {
            throw std::runtime_error("Failed to load XML file.");
        }

        XMLElement* root = doc.FirstChildElement("VendingMachine");
        if (!root) {
            throw std::runtime_error("Invalid XML format: Missing root element.");
        }

        XMLElement* drinkElement = root->FirstChildElement("Drink");
        while (drinkElement) {
            const char* name = drinkElement->Attribute("name");
            double price = drinkElement->DoubleAttribute("price");
            int quantity = drinkElement->IntAttribute("quantity");

            if (name) {
                drinks.emplace_back(name, price, quantity);
            }
            drinkElement = drinkElement->NextSiblingElement("Drink");
        }
    }

public:
   
    VendingMachine(const std::string& configFile) {
        loadDrinksFromXML(configFile);
    }

    
    void displayDrinks() const {
        std::cout << "Dostępne napoje:\n";
        for (size_t i = 0; i < drinks.size(); ++i) {
            std::cout << i + 1 << ". " << drinks[i].getName()
                      << " - $" << drinks[i].getPrice()
                      << " (" << drinks[i].getQuantity() << " dostępnych)\n";
        }
    }

    
    void insertCoin(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Wpłacona wartość musi być dodatnia!");
        }
        balance += amount;
        std::cout << "Aktualnie wpłacone pieniądze: $" << balance << "\n";
    }

    
    void selectDrink(int index) {
        if (index < 1 || index > static_cast<int>(drinks.size())) {
            throw std::out_of_range("Taki napój nie istnieje!");
        }

        Drink& selectedDrink = drinks[index - 1];
        if (selectedDrink.getQuantity() == 0) {
            throw std::runtime_error("Brak tego napoju!");
        }

        if (balance < selectedDrink.getPrice()) {
            throw std::runtime_error("Musisz wrzucić więcej monet!");
        }

        // Zmniejsz ilość napojów i odejmij cenę od balansu
        selectedDrink.setQuantity(selectedDrink.getQuantity() - 1);
        balance -= selectedDrink.getPrice();

        std::cout << "Wydaje napój: " << selectedDrink.getName() << ".\n";
        giveChange();
    }

    
    void giveChange() {
        if (balance > 0) {
            std::cout << "Reszta: $" << balance << "\n";
            balance = 0.0;
        }
    }
};

int main() {
    try {
        VendingMachine machine("D:\\CPP\\projekt-2-lukasz-rybakowski\\xml\\vending_machine_config.xml");

        std::cout << "Witamy w automacie z napojami!\n";
        while (true) {
            std::cout << "\nNa co masz ochotę?\n";
            std::cout << "1. Wrzuć monetę\n";
            std::cout << "2. Wybierz napój\n";
            std::cout << "3. Exit\n";
            std::cout << "Wybierz opcję od 1 do 3: ";

            int choice;
            std::cin >> choice;

            if (choice == 1) {
                double amount;
                std::cout << "Wpisz jaką kwotę chciałbyś wpłacić: $";
                std::cin >> amount;
                try {
                    machine.insertCoin(amount);
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            } else if (choice == 2) {
                machine.displayDrinks();
                std::cout << "Wbierz numer napoju, który chciałbyś zakupić: ";
                int drinkChoice;
                std::cin >> drinkChoice;

                try {
                    machine.selectDrink(drinkChoice);
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            } else if (choice == 3) {
                std::cout << "Do widzenia\n";
                break;
            } else {
                std::cout << "Taka opcja nie istnieje. Proszę spróbowac ponownie\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
