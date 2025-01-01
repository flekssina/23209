#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>

// Объявление шаблонного класса CSVParser
template <typename... Args>
class CSVParser {
public:
    class Iterator {
    public:
        using value_type = std::tuple<Args...>;

        Iterator(std::ifstream* file, char delimiter, char escape_char, size_t line_number);
        Iterator();

        Iterator& operator++();
        value_type operator*() const;
        bool operator!=(const Iterator& other) const;

    private:
        std::ifstream* file;
        char delimiter;
        char escape_char;
        size_t line_number;
        value_type current_row;

        void parse_line(const std::string& line);

        template <std::size_t Index, typename Tuple>
        void parse_helper(const std::vector<std::string>& cells, Tuple& tuple, size_t column);

        template <typename T>
        T convert(const std::string& str);
    };

    CSVParser(std::ifstream& file, size_t skip_lines, char delimiter = ',', char escape_char = '\"');

    Iterator begin();
    Iterator end();

private:
    std::ifstream& file;
    char delimiter;
    char escape_char;
};

#include "CSVParser.cpp"

#endif
