#ifndef XMLGREP_OUTPUT_FORMATTER_HPP
#define XMLGREP_OUTPUT_FORMATTER_HPP

#include <string>
#include <vector>
#include <memory>

class OutputFormatter {
public:
    virtual void addLine(const std::string& line) = 0;
    virtual void addEntry() = 0;
    virtual void reset() = 0;
    virtual ~OutputFormatter() = default;
};

class Printer final : public OutputFormatter
{
public:
    explicit Printer(std::ostream& ostream, std::string  delimiter);

    void addLine(const std::string &line) override;

    void addEntry() override;

    void reset() override;

private:
    std::vector<std::string> cache_;
    std::ostream &ostream_;
    std::string delimiter_;
};

class Counter final : public OutputFormatter
{
public:
    explicit Counter(std::ostream& ostream);
    ~Counter() override;

    void addLine(const std::string &line) override;

    void addEntry() override;

    void reset() override;

private:
    std::ostream &out_;
    uint64_t entries_{0};
    uint64_t lines_{0};
    uint64_t lineCache_{0};
};

std::unique_ptr<OutputFormatter> createOutputFormatter(std::ostream& out, bool count, const std::string& delimiter);

#endif //XMLGREP_OUTPUT_FORMATTER_HPP
