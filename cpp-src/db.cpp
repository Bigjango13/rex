#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <format>
#include <cmath>

#include "db.h"

// Table
void Table::addCol(std::string name) {
    columns.push_back(Column(name));
}

void Table::addRow(std::vector<Record> rowvals) {
    // TODO: Proper error handling
    assert(rowvals.size() == columns.size());
    for (size_t i = 0; i < columns.size(); i++) {
        // TODO: Type checking?
        //assert(columns[i].is_str == rowvals[i].is_str);
        columns[i].records.push_back(rowvals[i]);
        columns[i].max_align = std::max(
            columns[i].max_align,
            rowvals[i].getStringValue().size()
        );
    }
}

// Imports a table from a CSV file
void Table::addFromCSV(std::istream &stream) {
    // Headers
    std::string cell, line;
    getline(stream, line);
    std::stringstream ss(line);
    while (std::getline(ss, cell, ',')) {
        addCol(cell);
    }

    // Values
    while (std::getline(stream, line)) {
        std::stringstream ss(line);
        int i = 0;
        while (std::getline(ss, cell, ',')) {
            columns[i].records.push_back(Record(cell));
            i++;
        }
    }
}

void Table::print() {
    // Print headers
    for (auto &col : columns) {
        col.update_max_align();
        std::cout << std::left << std::setw(col.max_align + 2);
        std::cout << col.name;
    }
    std::cout << std::endl;
    if (columns.size() == 0) return;
    // Print the data
    size_t size = columns[0].records.size();
    for (size_t i = 0; i < size; i++) {
        for (auto &col : columns) {
            std::cout << std::left << std::setw(col.max_align + 2);
            std::cout << col.records[i].getStringValue();
       }
       std::cout << std::endl;
    }
}

// Column
Column::Column(std::string title)
    : name(title)
{}

// Used for printing the db all pretty
void Column::update_max_align() {
    max_align = 0;
    for (auto &r : records) {
        max_align = std::max(
            max_align,
            r.getStringValue().size()
        );
    }
}

// Record
Record::Record(std::string data) : sdata(data), is_str(true) {
    char *end = NULL;
    double val = strtod(this->sdata.c_str(), &end);
    if (end != this->sdata.c_str() && *end == '\0' && val != HUGE_VAL) {
        this->is_str = false;
        this->fdata = val;
    }
}

Record::Record(double data) : fdata(data), is_str(false) {
}

Record::Record(bool str) : sdata(""), fdata(0.0), is_str(str) {
}

// TODO: Where do we handle type errors?
// Do we even handle type errors or do
// some gross JS-like type coercion?
double Record::getDoubleValue() {
    if (!is_str) return fdata;
    return 0;
}

void Record::setDoubleValue(double val) {
    // TODO: See prev todo
    if (!is_str) fdata = val;
}

std::string Record::getStringValue() {
    if (is_str) return sdata;
    // Convert the double to a string
    return std::format("{}", fdata);
}

void Record::setStringValue(std::string val) {
    // TODO: See prev todo
    if (is_str) sdata = val;
}
