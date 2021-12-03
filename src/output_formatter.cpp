#include "output_formatter.hpp"

#include <cassert>
#include <iostream>
#include <utility>

Printer::Printer(std::ostream &ostream, std::string delimiter) : ostream_{ostream},
                                                                 delimiter_{std::move(delimiter)} {

}

void Printer::addLine(const std::string &line) {
    cache_.push_back(line);
}

void Printer::addEntry() {
    for (const auto &line: cache_) {
        ostream_ << line << "\n";
    }
    if (!delimiter_.empty()) {
        ostream_ << delimiter_ << "\n";
    }
    cache_.clear();
}

void Printer::reset() {
    cache_.clear();
}

Counter::~Counter() {
    assert(!lineCache_);
    out_ << entries_ << " " << lines_ << std::endl;
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

Counter::Counter(std::ostream &ostream) : out_{ostream} {

}

std::unique_ptr<OutputFormatter> createOutputFormatter(std::ostream &out, bool count, const std::string &delimiter) {
    if (count)
        return std::make_unique<Counter>(out);

    return std::make_unique<Printer>(out, delimiter);
}
