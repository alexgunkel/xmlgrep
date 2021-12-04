#ifndef XMLGREP_INPUT_HPP
#define XMLGREP_INPUT_HPP

#include <vector>
#include <istream>
#include <filesystem>

namespace xmlgrep {
class Input {
public:
    explicit Input(const std::string &file);
    explicit Input(const std::vector<std::string> &files);

    class StreamIterator {
    public:
        ~StreamIterator();

        StreamIterator &operator++();

        std::istream &operator*();

        friend bool operator==(const StreamIterator &lhs, const StreamIterator &rhs);

        friend bool operator!=(const StreamIterator &lhs, const StreamIterator &rhs);

    private:
        friend class Input;

        StreamIterator(const std::vector<std::filesystem::path> &paths, size_t position);

        explicit StreamIterator(std::istream &);

        size_t next_;
        size_t total_;
        const std::vector<std::filesystem::path> *paths_;
        std::istream *current_;
    };

    StreamIterator begin();

    StreamIterator end();

private:
    size_t next_{0};
    std::vector<std::filesystem::path> files_{};
};
}

#endif //XMLGREP_INPUT_HPP
