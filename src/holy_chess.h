//
// Created by 46762 on 2022-02-12.
//

#ifndef HOLYCHESS_HOLY_CHESS_H
#define HOLYCHESS_HOLY_CHESS_H

#include "piece.h"
#include "board.h"
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace holy {
    class Chess {
    public:
        Chess();
        ~Chess();

        void init();
        void update();
        void render();
        void handle_events();
        void run(std::string title, int width, int height, int flags);

    protected:
        sf::Event *event;
        sf::Vector2i mouse;
        sf::RenderWindow *window;

        void generate_legal_moves();
    private:
        Board board;
        Piece* pieces;
        Piece current_piece;

        struct states {
            static int n;
            static float dx, dy;
            static bool turn, is_move;
            static sf::Vector2f old_pos, new_pos;
        };
    };
}


#endif //HOLYCHESS_HOLY_CHESS_H
