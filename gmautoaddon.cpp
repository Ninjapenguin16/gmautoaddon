#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::endl;

// Get the path to the executable file itself
fs::path GetExecutablePath() {

    char path[1024];

    #if defined(_WIN32)
        GetModuleFileNameA(nullptr, path, sizeof(path));
    #elif defined(__linux__)
        ssize_t count = readlink("/proc/self/exe", path, sizeof(path));
        if (count != -1) {
            path[count] = '\0';
        }
    #elif defined(__APPLE__)
        uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) == 0) {
            return std::string(path);
        }
    #endif
    
    return fs::path(path);
}

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

    fs::path WorkingPath = fs::current_path();
    fs::path ExecutablePath = GetExecutablePath();

    std::string AddonName;
    cout << "Addon Name: ";
    std::getline(cin, AddonName);

    cout << endl;

    // Get the list of weapons and entities from the user
    std::vector<std::string> Weapons = GetInputList("Give the class names of all the weapons you want to create");
    std::vector<std::string> Entities = GetInputList("Give the class names of all the entities you want to create");

    // Create necessary directories
    fs::create_directory(WorkingPath / AddonName);
    fs::create_directory(WorkingPath / AddonName / "lua");
    fs::create_directory(WorkingPath / AddonName / "lua" / "autorun");

    if(!Weapons.empty()){
        fs::path WeaponsPath = WorkingPath / AddonName / "lua" / "weapons";
        fs::create_directory(WeaponsPath);
        for(std::string& Weapon : Weapons){
            fs::create_directory(WeaponsPath / Weapon);
            fs::copy(ExecutablePath / "Templates" / "Weapons", WeaponsPath / Weapon);
        }
    }

    if(!Entities.empty()){
        fs::path EntitiesPath = WorkingPath / AddonName / "lua" / "entities";
        fs::create_directory(EntitiesPath);
        for(std::string& Entity : Entities){
            fs::create_directory(EntitiesPath / Entity);
            fs::copy(ExecutablePath / "Templates" / "Entities", EntitiesPath / Entity);
        }
    }

    return 0;
}
