//
// Created by 46762 on 2022-02-10.
//

#ifndef HOLYCHESS_BOARD_H
#define HOLYCHESS_BOARD_H

#include "piece.h"
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class Board: public sf::Drawable {
public:
    Board();

    void initialize_board();
    Piece* get_pieces();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    Piece pieces[64];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    int board[8][8] = {
            {5, 4, 3, 1, 2, 3, 4, 5 },
            {6, 6, 6, 6, 6, 6, 6, 6 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {-6, -6, -6, -6, -6, -6, -6, -6 },
            {-5, -4, -3, -1, -2, -3, -4, -5 }
    };
};


#endif //HOLYCHESS_BOARD_H
