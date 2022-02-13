//
// Created by 46762 on 2022-02-10.
//

#ifndef HOLYCHESS_PIECE_H
#define HOLYCHESS_PIECE_H

#include <string>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Piece : public sf::Sprite {
public:
    Piece() = default;
    Piece(int x, int y, int id);

    void set_id(int id);
    int get_id();
    bool king(sf::Vector2f& from, sf::Vector2f& to);

    bool pawn(sf::Vector2f& from, sf::Vector2f& to);
    bool rook(sf::Vector2f& from, sf::Vector2f& to);
    bool queen(sf::Vector2f& from, sf::Vector2f& to);
    bool knight(sf::Vector2f& from, sf::Vector2f& to);
    bool bishop(sf::Vector2f& from, sf::Vector2f& to);
    bool is_valid_move(sf::Vector2f& from, sf::Vector2f& to);

    void make_move(sf::Vector2f& from, sf::Vector2f& to);
    void texture_manager(int x, int y);

    bool is_out_of_bounds(sf::Vector2f& to);

    void set_legal_moves(std::vector<sf::Vector2f>& legal_moves);
    std::vector<sf::Vector2f> get_legal_moves();

private:
    int id;
    sf::Texture texture;
    std::vector<sf::Vector2f> legal_moves;
};


#endif //HOLYCHESS_PIECE_H
