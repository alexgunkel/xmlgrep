#include "output_formatter.hpp"

#include <iostream>

Printer::Printer(std::ostream &ostream): ostream_{ostream}, cache_{} {

}

void Printer::addLine(const std::string &line) {
    cache_.push_back(line);
}

void Printer::addEntry() {
    for (const auto &line: cache_) {
        ostream_ << line << "\n";
    }
    cache_.clear();
}

void Printer::reset() {
    cache_.clear();
}

Counter::~Counter() {
    std::cout << entries_ << " " << lines_ << std::endl;
}

void Counter::addLine(const std::string &line) {
    lineCache_++;
}

void Counter::addEntry() {
    entries_++;
    lines_ += lineCache_;
    reset();
}

void Counter::reset() {
    lineCache_ = 0;
}
