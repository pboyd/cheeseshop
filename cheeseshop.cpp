#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

#include <toml.hpp>

class CheeseShop {
    public:
        CheeseShop(){}
        CheeseShop(std::string configPath) {
            auto cfg = toml::parse(configPath);

            auto cheeses = toml::find<std::vector<std::string>>(cfg, "cheeses");
            for (auto name : cheeses)
                inventory.insert(name);
        }

        std::string gotAny(std::string cheeseName) const {
            return inventory.count(cheeseName) == 1 ? "Yes" : "No";
        }

    private:
        std::unordered_set<std::string> inventory;
};

int main() {
    CheeseShop shop;

    try {
        shop = CheeseShop{"config.toml"};
    } catch(std::exception &e) {
        // Silently continue anyway..
    }

    std::cout << "Red Leicester? " << shop.gotAny("Red Leicester") << std::endl;
    std::cout << "Tilsit? " << shop.gotAny("Tilsit") << std::endl;
    std::cout << "Wenslydale? " << shop.gotAny("Wenslydale") << std::endl;
    std::cout << "Cheddar? " << shop.gotAny("Cheddar") << std::endl;
}
