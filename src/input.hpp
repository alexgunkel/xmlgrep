#ifndef XMLGREP_INPUT_HPP
#define XMLGREP_INPUT_HPP

#include <vector>
#include <istream>
#include <filesystem>
#include <queue>

namespace xmlgrep {
class Input {
public:
    explicit Input(const std::vector<std::string> &files);

    class StreamIterator {
    public:
        ~StreamIterator();

        StreamIterator &operator++();

        std::istream &operator*();

        friend bool operator==(const StreamIterator &lhs, const StreamIterator &rhs);

    private:
        friend class Input;

        explicit StreamIterator(const std::vector<std::filesystem::path> &paths);

        explicit StreamIterator(std::istream &);

        std::queue<std::filesystem::path> paths_;
        std::unique_ptr<std::istream> current_;
    };

    StreamIterator begin();

    StreamIterator end();

private:
    std::vector<std::filesystem::path> files_{};
};
}

#endif //XMLGREP_INPUT_HPP
