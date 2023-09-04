// Tests added to this file won't run on GitHub

#include "shape_cell.h"
#include "string_cell.h"
#include "table.h"
#include "testing.h"
#include <assert.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

void print(const std::vector<std::string>& rows) {
    for (const auto& row : rows) {
        std::cout << row << "\n";
    }
    std::cout.flush();
}

TEST(Public, Nested) {
    Table* nested = new Table(2, 1);
    nested->setBorder(false);
    nested->setCell(0, 0, new StringCell("First line"));
    nested->setCell(1, 0, new StringCell("Second line"));
    Table table(3, 2);
    table.setCell(0, 0, new StringCell("Alice"));
    table.setCell(0, 1, new StringCell("Bob"));
    table.setCell(1, 0, new StringCell("123456"));
    table.setCell(1, 1, new StringCell(""));
    table.setCell(2, 0, new StringCell(std::vector<std::string>{"Multi", "line"}));
    table.setCell(2, 1, nested);
    EXPECT_EQ(table.minHeight(), 9);
    EXPECT_EQ(table.minWidth(), 20);
    EXPECT_THAT(
        table.renderCompact(),
        ::testing::ElementsAre(
            // clang-format off
            "+------+-----------+",
            "|Alice |Bob        |",
            "+------+-----------+",
            "|123456|           |",
            "+------+-----------+",
            "|Multi |First line |",
            "|line  |-----------|",
            "|      |Second line|",
            "+------+-----------+"
            // clang-format on
        )
    );
}

TEST(Public, Shapes) {
    Circle circle(2.5);
    Sphere sphere(4);
    Table table(3, 2);
    table.setCell(0, 0, new StringCell("Shape"));
    table.setCell(0, 1, new StringCell("Display"));
    table.setCell(1, 0, new StringCell(circle.description()));
    table.setCell(1, 1, new ShapeCell(&circle, '#'));
    table.setCell(2, 0, new StringCell(sphere.description()));
    table.setCell(2, 1, new ShapeCell(&sphere, '#'));
    print(table.renderCompact());
}
