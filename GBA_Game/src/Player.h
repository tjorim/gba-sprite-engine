//
// Created by Wout Briels on 03/01/2019.
//


class Player {
private:
    int health = 3;     // Set to 3 in StartScene!!

public:
    void setHealth(int health) {
            this->health = health;
    }

    int getHealth() {
            return  health;
    }
};