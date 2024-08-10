#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::endl;

// Get user input for items
std::vector<std::string> GetInputList(const std::string& Prompt){
    std::vector<std::string> Items;
    std::string TempItem;
    cout << Prompt << "\nHit enter on a new line to continue:\n" << endl;
    while(true){
        std::getline(cin, TempItem);
        if (TempItem.empty())
            break;
        Items.push_back(TempItem);
    }
    return Items;
}

int main(){
    fs::path BasePath = fs::current_path();

    std::string AddonName;
    cout << "Addon Name: ";
    std::getline(cin, AddonName);

    cout << endl;

    // Get the list of weapons and entities from the user
    std::vector<std::string> Weapons = GetInputList("Give the names of all the weapons you want to create");
    std::vector<std::string> Entities = GetInputList("Give the names of all the entities you want to create");

    // Create necessary directories
    fs::create_directory(BasePath / AddonName);
    fs::create_directory(BasePath / AddonName / "lua");
    fs::create_directory(BasePath / AddonName / "lua" / "autorun");

    if(!Weapons.empty()){
        fs::path WeaponsPath = BasePath / AddonName / "lua" / "weapons";
        fs::create_directory(WeaponsPath);
        for(std::string& Weapon : Weapons){
            fs::create_directory(WeaponsPath / Weapon);
        }
    }

    if(!Entities.empty()){
        fs::path EntitiesPath = BasePath / AddonName / "lua" / "entities";
        fs::create_directory(EntitiesPath);
        for(std::string& Entity : Entities){
            fs::create_directory(EntitiesPath / Entity);
        }
    }

    return 0;
}
