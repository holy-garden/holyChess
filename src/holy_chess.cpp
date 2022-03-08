//
// Created by 46762 on 2022-02-12.
//

#include "holy_chess.h"

using namespace holy;

/* Defining initial states */
int n = 0;
float dx, dy = 0;
bool turn = true;
bool is_move = false;
sf::Vector2f old_pos;
sf::Vector2f new_pos;

Chess::Chess(): event{nullptr}, window{nullptr}  {

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
    if (is_move) {
        this->pieces[n].setPosition(this->mouse.x - dx, this->mouse.y - dy);
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
                            is_move = true;

                            dx = this->mouse.x - this->pieces[i].getPosition().x;
                            dy = this->mouse.y - this->pieces[i].getPosition().y;
                            n = i;
                            old_pos = this->pieces[i].getPosition();
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (this->event->mouseButton.button == sf::Mouse::Left) {
                    is_move = false;

                    auto pos = this->pieces[n].getPosition() + sf::Vector2f(100 / 2, 100 / 2);
                    new_pos = sf::Vector2f(100 * int(pos.x / 100), 100 * int(pos.y / 100));

                    int index = new_pos.y / 100 *  8 + new_pos.x / 100;
                    if (this->pieces[n].is_valid_move(old_pos, new_pos)) {
                        this->pieces[n].setPosition(new_pos);
                        this->pieces[n].set_is_empty(false);
                        this->pieces[index].set_is_empty(true);
                        std::cout << "old index: " << n << std::endl;
                        std::cout << "index: " << index << std::endl;

                    } else {
                        this->pieces[n].setPosition(old_pos);
                    }

                    for(int i = 0; i < 8; i++){
                        for(int j = 0; j < 8; j++){
                            std::cout << this->pieces[i * 8 + j].is_empty() << " ";
                        }
                        std::cout << std::endl;
                    }
                    std::cout << std::endl;
                }
                break;
        }
    }
}

void Chess::init() {
    this->board.initialize_board();
    this->pieces = this->board.get_pieces();
    turn = true; // first move to white
}

void Chess::generate_legal_moves() {
    std::vector<sf::Vector2f> moves;
}
