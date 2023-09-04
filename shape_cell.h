#pragma once

#include "cell_contents.h"
#include "geometric_figure.h"

#include <iostream>
#include <typeinfo>

class ShapeCell : public CellContents {
public:
    ShapeCell(const Shape* shape, char fill) {
        std::vector<std::string> result;

        const Shape2D* childPtr = dynamic_cast<const Shape2D*>(shape);
        if (childPtr != nullptr) {
            const Circle* childPtr2DCirc = dynamic_cast<const Circle*>(childPtr);
            std::vector<std::vector<bool>> shapeBool;
            if (childPtr2DCirc != nullptr) {
                shapeBool = childPtr2DCirc->display();
            }
            const Square* childPtr2dSquarre = dynamic_cast<const Square*>(childPtr);
            if (childPtr2dSquarre != nullptr) {
                shapeBool = childPtr2dSquarre->display();
            }

            result.resize(shapeBool.size());
            for (int i = 0; i < shapeBool.size(); ++i) {
                result[i].resize(shapeBool[i].size());
                for (int j = 0; j < shapeBool[i].size(); ++j) {
                    if (shapeBool[i][j]) {
                        result[i][j] = fill;
                    } else {
                        result[i][j] = ' ';
                    }
                }
            }
        }

        else {
            const Shape3D* childPtr1 = dynamic_cast<const Shape3D*>(shape);

            if (childPtr1 != nullptr) {
                std::vector<std::vector<bool>> shapeBool;

                const Sphere* childPtr3dSphere = dynamic_cast<const Sphere*>(childPtr1);
                if (childPtr3dSphere != nullptr) {
                    shapeBool = childPtr3dSphere->projection();
                }

                const Cube* childPtr3dCube = dynamic_cast<const Cube*>(childPtr1);
                if (childPtr3dCube != nullptr) {
                    shapeBool = childPtr3dCube->projection();
                }

                result.resize(shapeBool.size());
                for (int i = 0; i < shapeBool.size(); ++i) {
                    result[i].resize(shapeBool[i].size());
                    for (int j = 0; j < shapeBool[i].size(); ++j) {
                        if (shapeBool[i][j]) {
                            result[i][j] = fill;
                        } else {
                            result[i][j] = ' ';
                        }
                    }
                }
            } else {
                result[0] = shape->description();
            }
        }
        shapeCell = result;
    }

    std::vector<std::string> shapeCell;

    virtual std::vector<std::string> render(int, int) const override { return shapeCell; }

    int minHeight() override { return shapeCell.size(); }

    int minWidth() override {
        if (!shapeCell.empty()) {
            return shapeCell[0].size();
        }
        return 0;
    }
};