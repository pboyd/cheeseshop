#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

#include <toml.hpp>

class CheeseShop {
    public:
        CheeseShop() :
            clerkName{nullptr} {}
        CheeseShop(std::string configPath) :
            clerkName{nullptr}
        {
            auto cfg = toml::parse(configPath);

            auto cheeses = toml::find<std::vector<std::string>>(cfg, "cheeses");
            for (auto name : cheeses)
                inventory.insert(name);

            if (cfg.contains("clerk")) {
                clerkName = new std::string{toml::find<std::string>(cfg, "clerk")};
            }
        }

        ~CheeseShop() {
            if (clerkName)
                delete clerkName;
        }

        CheeseShop(CheeseShop &other) = delete;
        CheeseShop(CheeseShop &&other) = delete;
        CheeseShop &operator=(CheeseShop &other) = delete;
        CheeseShop &operator=(CheeseShop &&other) noexcept {
            inventory = std::move(other.inventory);

            if (clerkName)
                delete clerkName;
            clerkName = other.clerkName;
            other.clerkName = nullptr;

            return *this;
        }

        std::string gotAny(std::string cheeseName) const {
            if (clerkName && cheeseName == *clerkName)
                return "Sir?";

            return inventory.count(cheeseName) == 1 ? "Yes" : "No";
        }

    private:
        std::unordered_set<std::string> inventory;
        std::string *clerkName;
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
