#include "StateMachineManager.h"

int main(int argc, char *argv[])
{
    StateMachineManager game({ 1920, 1080 }, statesList::InGame);
    game.run();
    return 0;
}
