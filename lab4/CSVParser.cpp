#include "CSVParser.h"
#include <sstream>
#include <iostream>

// Реализация методов класса Iterator

template <typename... Args>
CSVParser<Args...>::Iterator::Iterator(std::ifstream* file, char delimiter, char escape_char, size_t line_number)
    : file(file), delimiter(delimiter), escape_char(escape_char), line_number(line_number) {
    ++(*this); // Прочитать первую строку
}

template <typename... Args>
CSVParser<Args...>::Iterator::Iterator() : file(nullptr), line_number(0) {}

template <typename... Args>
typename CSVParser<Args...>::Iterator& CSVParser<Args...>::Iterator::operator++() {
    if (file && !file->eof()) {
        std::string line;
        std::getline(*file, line);
        if (!line.empty()) {
            parse_line(line);
            ++line_number;
        } else {
            file = nullptr; // Конец файла
        }
    } else {
        file = nullptr;
    }
    return *this;
}

template <typename... Args>
typename CSVParser<Args...>::Iterator::value_type CSVParser<Args...>::Iterator::operator*() const {
    return current_row;
}

template <typename... Args>
bool CSVParser<Args...>::Iterator::operator!=(const Iterator& other) const {
    return file != other.file;
}

template <typename... Args>
void CSVParser<Args...>::Iterator::parse_line(const std::string& line) {
    std::vector<std::string> cells;
    std::string current_cell;
    bool inside_quotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == escape_char) {
            // Если видим кавычку
            if (inside_quotes && i + 1 < line.size() && line[i + 1] == escape_char) {
                // Две подряд кавычки внутри строки, добавляем одну кавычку
                current_cell += escape_char;
                ++i; // Пропускаем следующую кавычку
            } else {
                // Меняем состояние (входим или выходим из кавычек)
                inside_quotes = !inside_quotes;
            }
        } else if (c == delimiter && !inside_quotes) {
            // Разделитель вне кавычек, завершаем ячейку
            cells.push_back(current_cell);
            current_cell.clear();
        } else {
            // Обычный символ
            current_cell += c;
        }
    }

    // Добавляем последнюю ячейку
    cells.push_back(current_cell);

    // Проверяем количество столбцов
    if (cells.size() != sizeof...(Args)) {
        throw std::runtime_error("Parsing error at line " + std::to_string(line_number) +
                                 ": expected " + std::to_string(sizeof...(Args)) + " columns, but got " +
                                 std::to_string(cells.size()));
    }

    // Преобразуем ячейки в кортеж
    parse_helper<0>(cells, current_row, 1);
}


template <typename... Args>
template <std::size_t Index, typename Tuple>
void CSVParser<Args...>::Iterator::parse_helper(const std::vector<std::string>& cells, Tuple& tuple, size_t column) {
    if constexpr (Index < std::tuple_size<Tuple>::value) {
        try {
            // Преобразование текущей ячейки в соответствующий тип
            std::get<Index>(tuple) = convert<std::tuple_element_t<Index, Tuple>>(cells[Index]);
        } catch (const std::exception& e) {
            throw std::runtime_error("Conversion error at line " + std::to_string(line_number) +
                                     ", column " + std::to_string(column) + ": " + e.what());
        }

        // Рекурсивно обрабатываем следующий элемент
        parse_helper<Index + 1>(cells, tuple, column + 1);
    }
}



template <typename... Args>
template <typename T>
T CSVParser<Args...>::Iterator::convert(const std::string& str) {
    if constexpr (std::is_same_v<T, std::string>) {
        // Если тип — строка, возвращаем её без изменений
        return str;
    } else {
        // Для числовых типов выполняем преобразование
        std::istringstream iss(str);
        T value;
        if (!(iss >> value)) {
            throw std::runtime_error("Invalid value: " + str);
        }
        return value;
    }
}

// Реализация методов класса CSVParser

template <typename... Args>
CSVParser<Args...>::CSVParser(std::ifstream& file, size_t skip_lines, char delimiter, char escape_char)
    : file(file), delimiter(delimiter), escape_char(escape_char) {
    for (size_t i = 0; i < skip_lines; ++i) {
        std::string temp;
        std::getline(file, temp); // Пропустить строки
    }
}

template <typename... Args>
typename CSVParser<Args...>::Iterator CSVParser<Args...>::begin() {
    return Iterator(&file, delimiter, escape_char, 1);
}

template <typename... Args>
typename CSVParser<Args...>::Iterator CSVParser<Args...>::end() {
    return Iterator();
}

// Явная инстанциация шаблонов для предотвращения ошибок линковки
template class CSVParser<int, std::string, std::string>;
