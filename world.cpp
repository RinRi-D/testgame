#include "world.h"

World::World()
    : m_height(WORLD_HEIGHT), m_width(WORLD_WIDTH),
      m_c(WORLD_HEIGHT, std::vector<char>(WORLD_WIDTH, DEFAULT_CHAR)) {
    init();
}

void World::init() {}

Object &World::createObject(Object &&o) {
    m_objects.push_front(o);
    return m_objects.front();
}

void World::draw(Object &o) {
    double x = o.getPosition().X, y = o.getPosition().Y;
    int sz = o.getSize();
    char c = o.getSymbol();
    for (int i = -(sz + 1) / 2 + 1; i <= sz / 2; ++i)
        for (int j = -(sz + 1) / 2 + 1; j <= sz / 2; ++j)
            m_c[y + i][x + j] = c;
}

void World::update() {
    for (auto &i : m_c)
        for (auto &j : i)
            j = DEFAULT_CHAR;

    for (auto &it : m_objects) {
        draw(it);
    }
}

void World::print(std::ostream &out) {
    for (const auto &i : m_c) {
        for (const auto &j : i)
            out << j;
        out << '\n';
    }
}

void World::destroy() {}

World::~World() { destroy(); }
