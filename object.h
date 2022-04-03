#pragma once

class Object {
public:
    struct Position {
        double X, Y;

        Position(): X(0), Y(0) {

        }

        Position(double x, double y): X(x), Y(y) {

        }

        void setPos(double x, double y) {
            X = x, Y = y;
        }

        const Position& operator=(const Position &p) {
            this->X = p.X, this->Y = p.Y;
            return *this;
        }
    };

    Object();
    Object(Position pos, int size, char symbol);
    virtual char getSymbol();
    Position getPosition();
    int getSize();
    void setPosition(Position p);
    void changePosition(double dx, double dy);

protected:
    char m_symbol;
    int m_size;
    Position m_pos;
};
