#ifndef PROGRAMMING_LABS_CELL_CONTENTS_H
#define PROGRAMMING_LABS_CELL_CONTENTS_H
#include <string>
#include <vector>

class CellContents {
public:
    virtual ~CellContents() = default;

    virtual int minHeight() = 0;
    virtual int minWidth() = 0;
    virtual std::vector<std::string> render(int maxHeight, int maxWidth) const = 0;
};

#endif // PROGRAMMING_LABS_CELL_CONTENTS_H