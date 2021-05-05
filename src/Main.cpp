#include "StateMachineManager.h"

int main(int argc, char *argv[])
{
    StateMachineManager game({ 1920, 1080 });
    game.runSynchronous();
    return 0;
}
