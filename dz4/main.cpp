#include <iostream>
#include <array>

const size_t Dimension = 3;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

class State {
private:
    array<char, Dimension> field;
    char emptyPos;
public:
    bool CanMoveLeft() const;
    State MoveLeft() const;
};

bool State::CanMoveLeft() const {
    return emptyPos % Dimension != Dimension - 1;
}

State State::MoveLeft() const {
    
}