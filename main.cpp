#include "config.h"
#include "world.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>  //STDIN_FILENO

constexpr int ticktime = 1000.0 / TICKRATE;
static struct termios oldt, newt;

enum gamestatus { RUNNING, PAUSED, STOPPED } game;

void initTerminal() {
    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr(STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);

    /*ECHO - don't print user input */
    newt.c_lflag &= ~(ECHO);

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restoreTerminal() {
    /*restore the old settings*/
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void input(Object &o) {
    while (game != STOPPED) {
        char c = getchar();
        if (game == PAUSED) {
            if (c == 'p')
                game = RUNNING;
            continue;
        }
        bool ok = 1;
        switch (c) {
        case 'w':
            o.changePosition(0, -1);
            break;
        case 's':
            o.changePosition(0, 1);
            break;
        case 'd':
            o.changePosition(1, 0);
            break;
        case 'a':
            o.changePosition(-1, 0);
            break;
        case 'p':
            game = PAUSED;
            break;
        case 'e':
            ok = 0;
            break;
        default:
            break;
        }

        if (!ok)
            break;
    }
}

void botAI(Object &o) {
    while (game != STOPPED) {
        if (game == PAUSED)
            continue;
        o.changePosition(rand() % 3 - 1, rand() % 3 - 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void gameloop(World &world) {
    while (game != STOPPED) {
        if (game == RUNNING)
        world.update();
        world.print(std::cout);

        switch (game) {
            case RUNNING:
                std::cout << "GAME RUNNING!\n";
                break;
            case PAUSED:
                std::cout << "GAME PAUSED\n";
                break;
            default:
                std::cout << "GAME UNDEFINED\n";
                break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(ticktime));
        
        std::cout << "\x1B[2J\x1B[H";
    }
}

int main() {
    initTerminal();
    srand(time(NULL));

    game = RUNNING;
    World world;
    Object &objtest =
        world.createObject(Object(Object::Position(3, 3), 3, '*'));
    Object &objtestAI =
        world.createObject(Object(Object::Position(20, 20), 4, '='));

    std::thread m(gameloop, std::ref(world));
    std::thread bot(botAI, std::ref(objtestAI));
    std::thread in(input, std::ref(objtest));
    in.join();
    game = STOPPED;
    bot.join();
    m.join();
    restoreTerminal();
}

