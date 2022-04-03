#include "config.h"
#include "object.h"

Object::Object() : m_symbol('*'), m_size(1), m_pos(0, 0) {}

Object::Object(Position pos, int size, char symbol)
    : m_symbol(symbol), m_size(size), m_pos(pos) {}

char Object::getSymbol() { return m_symbol; }

Object::Position Object::getPosition() { return m_pos; }

int Object::getSize() { return m_size; }

void Object::setPosition(Object::Position p) { m_pos = p; }

void Object::changePosition(double dx, double dy) {
    if (m_pos.X + dx + (-(m_size + 1) / 2 + 1) < 0)
        dx = -(m_pos.X + (-(m_size + 1) / 2 + 1));
    if (m_pos.Y + dy + (-(m_size + 1) / 2 + 1) < 0)
        dy = -(m_pos.Y + (-(m_size + 1) / 2 + 1));
    if (m_pos.X + dx + m_size / 2 >= WORLD_WIDTH)
        dx = (WORLD_WIDTH-1) - (m_pos.X + m_size / 2);
    if (m_pos.Y + dy + m_size / 2 >= WORLD_HEIGHT)
        dy = (WORLD_HEIGHT-1) - (m_pos.Y + m_size / 2);

    m_pos.X += dx, m_pos.Y += dy;
}

