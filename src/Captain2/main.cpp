#include "manager.hpp"

int main(int argc, char** argv)
{
    manager.setParams(argc, argv);
    return (manager.run());
}
