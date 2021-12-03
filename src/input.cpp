#include "input.hpp"

#include <iostream>
#include <fstream>

namespace xmlgrep {
Input::Input(const std::vector<std::string> &files) {
    for (const auto &file: files) {
        files_.emplace_back(file);
    }
}

Input::StreamIterator Input::begin() {
    if (files_.empty()) {
        return Input::StreamIterator{std::cin};
    }
    return Input::StreamIterator{files_};
}

Input::StreamIterator Input::end() {
    return Input::StreamIterator{files_};
}

Input::StreamIterator::StreamIterator(const std::vector<std::filesystem::path> &paths) : paths_{
        std::deque<std::filesystem::path>(paths.begin(), paths.end())} {
    this->operator++();
}

std::istream &Input::StreamIterator::operator*() {
    return *current_;
}

Input::StreamIterator &Input::StreamIterator::operator++() {
    if (!paths_.empty()) {
        current_ = std::make_unique<std::fstream>(paths_.back().string());
        paths_.pop();
    } else {
        current_->clear();
    }

    return *this;
}

bool operator==(const Input::StreamIterator &lhs, const Input::StreamIterator &rhs) {
    return lhs.paths_ == rhs.paths_;
}

Input::StreamIterator::StreamIterator(std::istream &in) : current_{&in} {

}

Input::StreamIterator::~StreamIterator() = default;
}