//
// Created by 46762 on 2022-02-10.
//

#include "piece.h"


Piece::Piece(int x, int y, int id): id(id) {
    this->setPosition(float(x), float(y));
}

void Piece::texture_manager(int x, int y) {
    auto piece_path = std::filesystem::current_path().string() + "\\assets\\pieces.png";
    this->texture.loadFromFile(piece_path);
    if(this->id) {
        this->setTexture(this->texture);
        this->setTextureRect(sf::IntRect(x, y, 100, 100));
    }
}

void Piece::set_id(int id) {
    this->id = id;
}

int Piece::get_id() {
    return this->id;
}

bool Piece::rook(sf::Vector2f& from, sf::Vector2f& to) {
    auto [from_x, from_y] = from;
    auto [to_x, to_y] = to;


    if((from_x != to_x && from_y != to_y) || (from_y != to_y && from_x != to_x))
        return false;

    if(from_x > to_x && from_y == to_y)
        for(int i = 0; i < (int)std::abs(from_x - to_x); i += 100)
            if(from_x - i < 0)
                return false;
    else if(from_x < to_x && from_y == to_y)
        for(int i = 0; i < (int)std::abs(from_x - to_x); i += 100)
            if(from_x + i > 700)
                return false;

    else if(from_x == to_x && from_y > to_y)
        for(int i = 0; i < (int)std::abs(from_y - to_y); i += 100)
            if(from_y - i < 0)
                return false;

    else if(from_x == to_x && from_y < to_y)
        for(int i = 0; i < (int)std::abs(from_y - to_y); i += 100)
            if(from_y + i > 700)
                return false;

    return true;
}

bool Piece::knight(sf::Vector2f& from, sf::Vector2f& to) {
    auto [from_x, from_y] = from;
    auto [to_x, to_y] = to;

    if( (std::abs(from_x - to_x) == 200 && std::abs(from_y - to_y) == 100) \
            || (std::abs(from_y - to_y) == 200 && std::abs(from_x - to_x) == 100) )
        return true;

    return false;
}

bool Piece::bishop(sf::Vector2f& from, sf::Vector2f& to) {
    auto [from_x, from_y] = from;
    auto [to_x, to_y] = to;

    if (std::abs(from_x - to_x) != std::abs(from_y - to_y))
        return false;

    if (from_x > to_x && from_y > to_y)
        for (int i = 0; i < (int) std::abs(from_x - to_x); i += 100)
            if (from_x - i < 0 && from_y - i < 0)
                return false;
    else if (from_x > to_x && from_y < to_y)
        for (int i = 0; i < (int) std::abs(from_x - to_x); i += 100)
            if (from_x - i < 0 && from_y + i > 700)
                return false;
    else if (from_x < to_x && from_y > to_y)
        for (int i = 0; i < (int) std::abs(from_x - to_x); i += 100)
            if (from_x + i > 700 && from_y - i < 0)
                return false;
    else if (from_x < to_x && from_y < to_y)
        for (int i = 0; i < (int) std::abs(from_x - to_x); i += 100)
            if (from_x + i > 700 && from_y + i > 700)
                return false;

    return true;
}

bool Piece::queen(sf::Vector2f& from, sf::Vector2f& to) {
    if (this->rook(from, to) or this->bishop(from, to)) return true;
    return false;
}

bool Piece::king(sf::Vector2f& from, sf::Vector2f& to) {
    auto [from_x, from_y] = from;
    auto [to_x, to_y] = to;

    if (std::abs(from_x - to_x) <= 100 and std::abs(from_y - to_y) <= 100) return true;

    return false;
}

bool Piece::pawn(sf::Vector2f& from, sf::Vector2f& to) {
    auto [from_x, from_y] = from;
    auto [to_x, to_y] = to;

    if (this->id == 6) {
        if (to_y > from_y and to_y - from_y == 100 and from_x == to_x) return true;
        // can move two squares down from start position
        if (from_y == 100 and to_y - from_y == 200 and from_x == to_x) return true;
    }
    if (this->id == -6) {
        if (to_y < from_y and from_y - to_y == 100 and from_x == to_x) return true;
        // can move two squares up from start position
        if (from_y == 600 and from_y - to_y == 200 and from_x == to_x) return true;
    }
    return false;
}

bool Piece::is_valid_move(sf::Vector2f& from, sf::Vector2f& to) {
    if (!this->is_out_of_bounds(to)) {
        switch (std::abs(this->id)) {
            case 1:
                return this->king(from, to);
            case 2:
                return this->queen(from, to);
            case 3:
                return this->bishop(from, to);
            case 4:
                return this->knight(from, to);
            case 5:
                return this->rook(from, to);
            case 6:
                return this->pawn(from, to);
        }
    }
    return false;
}

void Piece::make_move(sf::Vector2f& from, sf::Vector2f& to) {
    if (!this->is_valid_move(from, to)) {
        this->setPosition(from.x, from.y);
    }
    else {
        this->setPosition(to.x, to.y);
    }
}

bool Piece::is_out_of_bounds(sf::Vector2f& to) {
    auto [to_x, to_y] = to;
    if ((to_x < 0 or to_x > 700) or (to_y < 0 or to_y > 700)) return true;
    return false;
}

void Piece::set_legal_moves(std::vector<sf::Vector2f>& legal_moves) {
    this->legal_moves = legal_moves;
}

std::vector<sf::Vector2f> Piece::get_legal_moves() {
    return this->legal_moves;
}

bool Piece::is_empty() {
    return this->empty;
}

void Piece::set_is_empty(bool is_empty) {
    this->empty = is_empty;
}
