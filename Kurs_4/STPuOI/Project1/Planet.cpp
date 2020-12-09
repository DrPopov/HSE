//
// Created by drpopov on 11/25/20.
//

#include "Planet.h"

Planet::Planet(int id, string name, Colors color, int portals) {
    Planet::set_id(id);
    Planet::set_name(name);
    Planet::set_color(color);
    Planet::set_portals(portals);
}

Planet::Planet() {
    Planet::set_id(1);
    Planet::set_name("Test");
    Planet::set_color(red);
    Planet::set_portals(3);
}
