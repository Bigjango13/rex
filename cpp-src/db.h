#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Record {
public:
    std::string sdata = "";
    double fdata = 0.0;

    bool is_str = false;

    Record(std::string data);
    Record(double data);
    Record(bool str);

    double getDoubleValue();
    void setDoubleValue(double val);
    std::string getStringValue();
    void setStringValue(std::string val);
};

class Column {
public:
    size_t max_align = 2;
    std::string name;
    std::vector<Record> records = {};

    Column(std::string title);

    void update_max_align();
};

class Table {
public:
    std::vector<Column> columns = {};

    void addCol(std::string name);
    void addRow(std::vector<Record> rowvals);

    void addFromCSV(std::istream &stream);

    void print();

    Table() {}
};
