#ifndef LOCATION_COMPONENT_H
#define LOCATION_COMPONENT_H

struct LocationComponent {
    unsigned int x;
    unsigned int y;
    unsigned int z;
    LocationComponent(): x(0), y(0), z(0) { }
};

#endif
