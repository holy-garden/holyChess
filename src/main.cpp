#include "holy_chess.h"

using namespace holy;
Chess *holy_chess = nullptr;

int main()
{
    holy_chess = new Chess();
    holy_chess->init();
    holy_chess->run("holyChess", 800, 800, sf::Style::Titlebar | sf::Style::Close);

    return 0;
}
