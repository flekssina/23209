#include <iostream>
#include <cstring>



class String
{
private:
    char* m_storage;
    std::size_t m_size;
public:
    String (const char* str = "") //Консруктор по умолчанию
    {
        m_size = std::strlen(str);
        m_storage = new char[m_size + 1];
        std::strcpy(m_storage, str);
    }
    String (const String& other)//Конструктор копирования
    {
    m_size = other.m_size;
    m_storage = new char[m_size + 1];
    std::strcpy(m_storage, other.m_storage);
    }
    ~String()//Деструктор 
    {
        delete[] m_storage;
    }
    static std::size_t size(const char* str)//Длина строки
    {
        return std::strlen(str);
    }
    const String& operator += (const String& right)
    {
        std::size_t new_size = m_size + right.m_size; // Суммируем размеры двух строк
        char* new_storage = new char[new_size + 1]; // Выделяем новую память для конкатенированной строки

        std::strcpy(new_storage, m_storage); // Копируем старую строку
        std::strcat(new_storage, right.m_storage); // Добавляем новую строку к старой

        delete[] m_storage; // Освобождаем старую память

        m_storage = new_storage; // Обновляем указатель на новую строку
        m_size = new_size; // Обновляем размер
        return *this; // Возвращаем текущий объект  
    }
    const char* c_str() const
    {
        return m_storage;
    }
};

int main()
{
    String s1("Hello");
    String s2(" World");

    s1 += s2; 

    std::cout << s1.c_str() << std::endl; 

    return 0;
} 
