//
// Created by 46762 on 2022-02-12.
//

#include "holy_chess.h"

using namespace holy;

/* Defining initial states */
int Chess::states::n = 0;
float Chess::states::dx = 0;
float Chess::states::dy = 0;
bool Chess::states::turn = true;
bool Chess::states::is_move = false;
sf::Vector2f Chess::states::old_pos = {0.f, 0.f};
sf::Vector2f Chess::states::new_pos = {0.f, 0.f};

Chess::Chess(): event{nullptr}, window{nullptr}, pieces{nullptr}  {

}

Chess::~Chess() {
}

void Chess::run(std::string title, int width, int height, int flags) {
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, flags);
    while (this->window->isOpen()) {
        this->handle_events();
        this->update();
        this->render();
    }
}

void Chess::update() {
    if (states::is_move) {
        this->pieces[states::n].setPosition(this->mouse.x - states::dx, this->mouse.y - states::dy);
    }
}

void Chess::render() {
    this->window->clear();
    this->window->draw(this->board);
    for(int i = 0; i < 64; i++)
        this->window->draw(this->pieces[i]);
    this->window->display();
}

void Chess::handle_events() {
    this->event = new sf::Event();
    this->mouse = sf::Mouse::getPosition(*this->window);

    while (this->window->pollEvent(*this->event))
    {
        switch (this->event->type) {
            case sf::Event::Closed:
                this->window->close();

            case sf::Event::MouseButtonPressed:
                if (this->event->mouseButton.button == sf::Mouse::Left) {
                    for(int i = 0; i < 64; i++) {
                        if (pieces[i].getGlobalBounds().contains(this->mouse.x, this->mouse.y)) {
                            states::is_move = true;

                            states::dx = this->mouse.x - this->pieces[i].getPosition().x;
                            states::dy = this->mouse.y - this->pieces[i].getPosition().y;
                            states::n = i;
                            states::old_pos = this->pieces[i].getPosition();
                            this->current_piece = pieces[i];
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (this->event->mouseButton.button == sf::Mouse::Left) {
                    states::is_move = false;

                    auto pos = this->pieces[states::n].getPosition() + sf::Vector2f(100 / 2, 100 / 2);
                    states::new_pos = sf::Vector2f(100 * int(pos.x / 100), 100 * int(pos.y / 100));

                    this->pieces[states::n].make_move(states::old_pos, states::new_pos);
                }
                break;
        }
    }
}

void Chess::init() {
    this->board.initialize_board();
    this->pieces = this->board.get_pieces();
    states::turn = true; // first move to white
}

void Chess::generate_legal_moves() {
    std::vector<sf::Vector2f> moves;

    Piece curr_piece = this->pieces[states::n];
    switch (std::abs(curr_piece.get_id())) {
        case 4: // white and black pawn
            int Xmoves[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
            int Ymoves[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

            /*int count = 0;
            for (int i = 0; i < 8; i++) {
                int x = states::new_pos.x + Xmoves[i] * 100;
                int y = states::new_pos.y + Ymoves[i] * 100;
                if (x>=0 && y>=0 && x<8 && y<8 && !this->_board[x/100][y/100])
                    count++;
            }*/
            int it = 0;
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    std::cout << this->pieces[it].get_id() << " ";
                it++;
                }
                std::cout << std::endl;
            }
            //std::cout << "Available moves: " << count << std::endl;
            break;
    }
}
