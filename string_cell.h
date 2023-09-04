#pragma once

#include "cell_contents.h"

class StringCell : public CellContents {
public:
    StringCell(std::vector<std::string> matrix) : information(matrix) { }

    StringCell(std::string string) {
        information.resize(1);
        information[0] = string;
    }

    std::vector<std::string> information;

    int minHeight() override { return information.size(); }

    int minWidth() override {
        uint64_t tmp = 1;
        for (int i = 0; i < information.size(); ++i) {
            tmp = std::max(tmp, information[i].size());
        }
        return tmp;
    }

    std::vector<std::string> render(int, int) const override { return information; }
};