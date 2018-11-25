#include "SystemManager.h"

int main() {

    std::string path = "sys.ini";

    SystemManager* sys = SystemManager::Instance(path);
    sys->Run();
    SystemManager::Release();

    sys = nullptr;

    return 0;
}
