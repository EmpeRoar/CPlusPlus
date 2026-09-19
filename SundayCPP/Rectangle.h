#pragma once

class Rectangle {
private:
    float length;
    float width;

public:
    Rectangle(float l, float w);
    float area() const;
};
