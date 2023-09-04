#pragma once

#include "cell_contents.h"
#include <iostream>

class Table : public CellContents {
public:
    Table(int rows, int columns)
        : rows_(rows),
          columns_(columns),
          data_(rows, std::vector<CellContents*>(columns, nullptr)) { }

    ~Table() {
        for (auto elem : data_) {
            for (auto subItem : elem) {
                delete subItem;
            }
        }
    }

    int rows_;
    int columns_;
    std::vector<std::vector<CellContents*>> data_;
    bool border = true;

    void setBorder(bool enabled) { border = enabled; }

    int minWidth() override {
        std::vector<int> width(columns_);

        for (int i = 0; i < data_.size(); ++i) {
            for (int j = 0; j < data_[i].size(); ++j) {
                if (data_[i][j] != nullptr) {
                    width[j] = std::max(width[j], data_[i][j]->minWidth());
                }
            }
        }

        int totalWidth = 1;

        for (int i = 0; i < width.size(); ++i) {
            totalWidth += width[i] + 1;
        }
        if (border) {
            return totalWidth;
        } else {
            return (totalWidth - 2);
        }
    }

    int minHeight() override {
        std::vector<int> height(rows_);

        for (int i = 0; i < data_.size(); ++i) {
            int maxHeight = 0;
            for (int j = 0; j < data_[i].size(); ++j) {
                if (data_[i][j] != nullptr) {
                    maxHeight = std::max(maxHeight, data_[i][j]->minHeight());
                }
            }
            height[i] = maxHeight;
        }

        int totalHeight = 1;

        for (int i = 0; i < height.size(); ++i) {
            totalHeight += height[i] + 1;
        }
        if (border) {
            return totalHeight;
        } else {
            return (totalHeight - 2);
        }
    }

    void setCell(int i, int j, CellContents* ptr) {
        auto* tmp = data_[i][j];
        data_[i][j] = ptr;
        delete tmp;
    }

    std::vector<std::string> renderCompact() const {
        std::vector<int> height(rows_);
        std::vector<int> width(columns_);

        for (int i = 0; i < data_.size(); ++i) {
            int maxHeight = 0;
            for (int j = 0; j < data_[i].size(); ++j) {
                if (data_[i][j] != nullptr) {
                    maxHeight = std::max(maxHeight, data_[i][j]->minHeight());
                }
            }
            height[i] = maxHeight;
        }

        for (int i = 0; i < data_.size(); ++i) {
            for (int j = 0; j < data_[i].size(); ++j) {
                if (data_[i][j] != nullptr) {
                    width[j] = std::max(width[j], data_[i][j]->minWidth());
                }
            }
        }

        int totalHeight = 1;
        int totalWidth = 1;

        for (int i = 0; i < width.size(); ++i) {
            totalWidth += width[i] + 1;
        }

        for (int i = 0; i < height.size(); ++i) {
            totalHeight += height[i] + 1;
        }

        std::vector<std::string> result(totalHeight);
        for (int i = 0; i < result.size(); ++i) {
            result[i].resize(totalWidth, '0');
        }

        int startY = 1;
        for (int i = 0; i < height.size(); ++i) {
            int startX = 1;
            for (int j = 0; j < width.size(); ++j) {
                if (data_[i][j] != nullptr) {
                    std::vector<std::string> data =
                        data_[i][j]->render(data_[i][j]->minHeight(), data_[i][j]->minWidth());
                    for (int row = 0; row < height[i]; ++row) {
                        for (int col = 0; col < width[j]; ++col) {
                            if (row < data.size() && col < data[row].size()) {
                                result[startY + row][startX + col] = data[row][col];
                            } else {
                                result[startY + row][startX + col] = ' ';
                            }
                        }
                    }
                } else {
                    for (int row = 0; row < height[i]; ++row) {
                        for (int col = 0; col < width[j]; ++col) {
                            result[startY + row][startX + col] = ' ';
                        }
                    }
                }
                startX += width[j] + 1;
            }
            startY += height[i] + 1;
        }

        startY = 0;
        for (int i = 0; i < height.size(); ++i) {
            for (int j = 0; j < result[0].size(); ++j) {
                result[startY][j] = '-';
            }
            startY += height[i] + 1;
            for (int j = 0; j < result[i].size(); ++j) {
                result[startY][j] = '-';
            }
        }

        int startX = 0;
        for (int i = 0; i < result.size(); ++i) {
            if (result[i][startX] != '-') {
                result[i][startX] = '|';
            } else {
                result[i][startX] = '+';
            }
            for (int j = 0; j < width.size(); ++j) {
                startX += width[j] + 1;
                if (result[i][startX] != '-') {
                    result[i][startX] = '|';
                } else {
                    result[i][startX] = '+';
                }
            }
            startX = 0;
        }

        if (!border) {
            result.erase(result.begin());
            result.pop_back();
            for (int i = 0; i < result.size(); ++i) {
                result[i].erase(result[i].begin());
                result[i].pop_back();
            }
        }

        return result;
    }

    std::vector<std::string> render(int maxHeight, int maxWidth) const override {
        std::vector<std::string> result = renderCompact();
        result.resize(maxHeight);
        for (int i = 0; i < result.size(); ++i) {
            result[i].resize(maxWidth, ' ');
        }
        return result;
    }
};