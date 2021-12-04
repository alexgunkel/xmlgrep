#include "input.hpp"

#include <iostream>
#include <fstream>

namespace xmlgrep {
Input::Input(const std::string &file) {
    if (!file.empty()) {
        files_.emplace_back(file);
    }
}


Input::Input(const std::vector<std::string> &files) {
    for (const auto &file: files) {
        files_.emplace_back(file);
    }
}

Input::StreamIterator Input::begin() {
    if (files_.empty()) {
        return Input::StreamIterator{std::cin};
    }
    return {files_, 0};
}

Input::StreamIterator Input::end() {
    return {files_, files_.size()};
}

Input::StreamIterator::StreamIterator(const std::vector<std::filesystem::path> &paths, size_t position) : next_{
        position}, total_{paths.size()}, paths_{&paths}, current_{nullptr} {
    this->operator++();
}

std::istream &Input::StreamIterator::operator*() {
    return *current_;
}

Input::StreamIterator &Input::StreamIterator::operator++() {
    if (next_ < total_) {
        current_ = new std::fstream(paths_->at(next_).string());
    } else if (total_) {
        delete current_;
        current_ = nullptr;
    }

    next_++;

    return *this;
}

bool operator==(const Input::StreamIterator &lhs, const Input::StreamIterator &rhs) {
    return lhs.next_ == rhs.next_;
}

bool operator!=(const Input::StreamIterator &lhs, const Input::StreamIterator &rhs) {
    return !(rhs == lhs);
}

Input::StreamIterator::StreamIterator(std::istream &in) : next_{0}, total_{0}, paths_{},
                                                          current_{&in} {

}

Input::StreamIterator::~StreamIterator() {
    if (total_) {
        delete current_;
    }
}
}