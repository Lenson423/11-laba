#ifndef PROGRAMMING_LABS_GEOMETRIC_FIGURE_H
#define PROGRAMMING_LABS_GEOMETRIC_FIGURE_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <string>
#include <vector>

class Shape {
public:
    virtual std::string description() const = 0;
    virtual double measure() const = 0;
};

class Shape2D : public Shape {
public:
    virtual std::vector<std::vector<bool>> display() const = 0;
};

class Circle : public Shape2D {
public:
    Circle(double rad) : radius(rad) { }

    Circle(const Circle& tmp) { radius = tmp.radius; }

    double radius;

    std::string description() const override {
        return "circle with radius " + std::to_string(radius);
    }

    double measure() const override { return M_PI * radius * radius; }

    std::vector<std::vector<bool>> display() const override {
        std::vector<std::vector<bool>> result(radius * 2, std::vector<bool>(radius * 2));
        for (int i = 0; i < result.size(); ++i) {
            for (int j = 0; j < result[i].size(); ++j) {
                if ((radius - i - 0.5) * (radius - i - 0.5)
                        + (radius - j - 0.5) * (radius - j - 0.5)
                    <= (radius - 0.5) * (radius - 0.5) + 0.5) {
                    result[i][j] = true;
                } else {
                    result[i][j] = false;
                }
            }
        }
        return result;
    }
};

class Square : public Shape2D {
public:
    Square(double sizeNew) : size(sizeNew) { }

    Square(const Square& tmp) { size = tmp.size; }

    double size;

    std::string description() const override { return "square with size " + std::to_string(size); }

    double measure() const override { return size * size; }

    std::vector<std::vector<bool>> display() const override {
        std::vector<std::vector<bool>> result(size, std::vector<bool>(size));
        for (int i = 0; i < result.size(); ++i) {
            for (int j = 0; j < result[i].size(); ++j) {
                result[i][j] = true;
            }
        }
        return result;
    }
};

class Shape3D : public Shape {
public:
    virtual std::vector<std::vector<bool>> projection() const = 0;
};

class Sphere : public Shape3D {
public:
    Sphere(double rad) : radius(rad) { }

    double radius;

    std::string description() const override {
        return "sphere with radius " + std::to_string(radius);
    }

    double measure() const override { return 4 / 3 * M_PI * radius * radius * radius; }

    std::vector<std::vector<bool>> projection() const override {
        Circle result(radius);
        return result.display();
    }
};

class Cube : public Shape3D {
public:
    Cube(double rad) : side(rad) { }

    double side;

    std::string description() const override { return "cube with size " + std::to_string(side); }

    double measure() const override { return side * side * side; }

    std::vector<std::vector<bool>> projection() const override {
        Square result(side);
        return result.display();
    }
};

#endif // PROGRAMMING_LABS_GEOMETRIC_FIGURE_H