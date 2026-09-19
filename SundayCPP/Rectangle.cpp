#include "Rectangle.h"

Rectangle::Rectangle(float l, float w) : length(l), width(w) {}

float Rectangle::area() const {
    return length * width;
}
