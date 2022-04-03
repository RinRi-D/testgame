#pragma once

#include "config.h"
#include "object.h"

#include <iostream>
#include <list>
#include <vector>

class World {
    size_t m_height, m_width;
    std::vector<std::vector<char>> m_c;
    std::list<Object> m_objects;

  public:
    World();
    void init();
    Object &createObject(Object &&);
    void draw(Object &o);
    void update();
    void print(std::ostream &out);
    void destroy();
    ~World();
};
