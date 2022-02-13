//
// Created by 46762 on 2022-02-10.
//

#include "board.h"

Board::Board() {
    this->texture.loadFromFile(std::filesystem::current_path().string() + "\\assets\\board.jpg");
    this->sprite.setTexture(this->texture);
}

void Board::initialize_board() {
    int iter = 0;
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int id = board[i][j];
            int x = std::abs(id) - 1;
            int y = id > 0 ? 1 : 0;

            this->pieces[iter] = Piece(j * 100, i * 100, id);
            this->pieces[iter].texture_manager(x * 100, y * 100);

            iter++;
        }
    }
}

Piece *Board::get_pieces() {
    return this->pieces;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}

