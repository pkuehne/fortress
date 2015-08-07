#ifndef LOCATION_COMPONENT_H
#define LOCATION_COMPONENT_H

struct LocationComponent {
    size_t x;
    size_t y;
    size_t z;
    LocationComponent(): x(0), y(0), z(0) { }
};

#endif
