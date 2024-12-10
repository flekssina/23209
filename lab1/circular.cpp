#include "circular.h"

#include <iostream>
#include <algorithm> 


CircularBuffer::CircularBuffer()://конструктор по умолчанию 
     buffer(nullptr),
     head(0),//начало очереди
     tail(0),//конеч очереди данных
     buffer_size(0),//размер
     buffer_capacity(0) {} //емкость буфера


CircularBuffer::~CircularBuffer() //деструктор 
{
     delete[] buffer;
}

CircularBuffer::CircularBuffer(const CircularBuffer &cb): //конструктор копирования
     buffer(new value_type[cb.buffer_capacity]),
     head(cb.head),
     tail(cb.tail),
     buffer_size(cb.buffer_size),
     buffer_capacity(cb.buffer_capacity)
{
     std::copy(cb.buffer, cb.buffer+cb.buffer_capacity, buffer);
}

CircularBuffer::CircularBuffer(int capacity)://конструктор с параметром 
    buffer(new value_type[capacity]),
    head(0),
    tail(0),
    buffer_size(0),
    buffer_capacity(capacity){}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem)://конструтор с заполненнием
    buffer(new value_type[capacity]),
    head(0),
    tail(0), 
    buffer_size(capacity),
    buffer_capacity(capacity)
{
    std::fill(buffer, buffer + capacity, elem);
}

value_type &CircularBuffer::operator[](int i)
{
    if (i < 0 || i >= buffer_size)
    {
        throw std::out_of_range("Index out of range");
    }
    if(!buffer) 
    {
        throw std::runtime_error("Buffer not initialized");
    }
    return buffer[(head + i) % buffer_capacity];
}

const value_type &CircularBuffer::operator[](int i) const
{
    if (i < 0 || i >= buffer_size) 
    {
        throw std::out_of_range("Index out of range");
    }
    if(!buffer)
    {
        throw std::runtime_error("Buffer not initialized");
    }
    return buffer[(head + i) % buffer_capacity];
}

value_type &CircularBuffer::at(int i)
{
    if (i < 0 || i >= buffer_size)
    {
        throw std::out_of_range("Index out of range");
    }
    return buffer[(head + i) % buffer_size];
}

const value_type &CircularBuffer::at(int i) const
{
    if(i < 0 || i >= buffer_size) 
    {
        throw std::out_of_range("Index out of range");
    }
    return buffer[(head + i) % buffer_size];
}

value_type &CircularBuffer::front()
{
    if (empty()) 
    {
        throw std::out_of_range("CircularBuffer is empty");
    }
    return buffer[head];
}

value_type &CircularBuffer::back()
{
    if (empty())
    {
        throw std::out_of_range("CircularBuffer is empty");
    }
    return buffer[(tail - 1 + buffer_capacity) % buffer_capacity];
}

const value_type &CircularBuffer::front() const
{
    if (empty())
    {
        throw std::out_of_range("CircularBuffer is empty");
    }
    return buffer[head];
}

const value_type &CircularBuffer::back() const
{
    if (empty())
    {
        throw std::out_of_range("CircularBuffer is empty");
    }
    return buffer[(tail - 1 + buffer_capacity) % buffer_capacity];
}

value_type *CircularBuffer::linearize()
{
    if (!is_linearized()) 
    {
        value_type* new_buffer = new value_type[buffer_capacity];
        for(int i = 0; i < buffer_size; i++) 
        {
            new_buffer[i] = buffer[(head + i) % buffer_capacity];
        }
        delete[] buffer;
        buffer = new_buffer;
        head = 0;
        tail = buffer_size;
    }
    return buffer;
}

bool CircularBuffer::is_linearized() const
{
    return head == 0;
}

void CircularBuffer::rotate(int new_begin)
{
    if (buffer_capacity == 0) 
    {
        throw std::out_of_range("CircularBuffer is empty");
    }

    if (new_begin < 0 || new_begin >= buffer_size) 
    {
        throw std::out_of_range("Index out of range");
    }

    value_type *new_buffer = new value_type[buffer_capacity];
    for (int i = 0; i < buffer_size; i++) 
    {
        new_buffer[i] = (*this)[(i + new_begin) % buffer_size];
    }

    std::swap(buffer, new_buffer);
    delete[] new_buffer;

    head = 0;
    tail = buffer_size;  
}

int CircularBuffer::size() const
{
    return buffer_size;
}

bool CircularBuffer::empty() const
{
    return buffer_size == 0;
}

bool CircularBuffer::full() const
{
    return buffer_size == buffer_capacity;
}

int CircularBuffer::reserve() const
{
    return buffer_capacity - buffer_size;
}

int CircularBuffer::capacity() const
{
    return buffer_capacity;
}

void CircularBuffer::set_capacity(int new_capacity) 
{
    if (new_capacity < buffer_size) 
    {
        throw std::invalid_argument("New capacity cannot be less than the current size of the buffer");
    }

    value_type* new_buffer = new value_type[new_capacity];

    for (int i = 0; i < buffer_size; i++)
    {
        new_buffer[i] = (*this)[i];
    }

    // Сохраняем старый буфер для безопасного удаления
    value_type* old_buffer = buffer;

    buffer = new_buffer;  // Обновляем указатель на новый буфер

    delete[] old_buffer;  // Удаляем старую память

    head = 0;
    tail = buffer_size;
    buffer_capacity = new_capacity;
}


void CircularBuffer::resize(int new_size, const value_type& item) 
{
    if (new_size > buffer_capacity)
    {
        throw std::invalid_argument("New size exceeds buffer capacity");
    }
    if (new_size > buffer_size) 
    {
        for (int i = buffer_size; i < new_size; i++) 
        {
            buffer[(tail + i) % buffer_capacity] = item;
        }
    }

    buffer_size = new_size;
    tail = buffer_size % buffer_capacity;
}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &cb)
{
     if (this != &cb) {
        CircularBuffer temp(cb);
        swap(temp);
    }

    return *this;
}


void CircularBuffer::swap(CircularBuffer & cb) 
{
    std::swap(buffer, cb.buffer);
    std::swap(head, cb.head);
    std::swap(tail, cb.tail);
    std::swap(buffer_size, cb.buffer_size);
    std::swap(buffer_capacity, cb.buffer_capacity);  
}


void CircularBuffer::push_back(const value_type & item) 
{
    if (full()) 
    {
        throw std::overflow_error("Buffer is full. Cannot add new element at the back.");
    }

    buffer[tail] = item;
    tail = (tail + 1) % buffer_capacity;
    buffer_size++;
}

void CircularBuffer::push_front(const value_type &item) 
{
    if (full()) 
    {
        throw std::overflow_error("Buffer is full. Cannot add new element at the front.");
    }

    head = (head + buffer_capacity - 1) % buffer_capacity;
    buffer[head] = item;
    buffer_size++;
}
void CircularBuffer::pop_back() 
{
    if (empty()) 
    {
        throw std::underflow_error("Buffer is empty");
    }

    tail = (tail - 1 + buffer_capacity) % buffer_capacity;
    buffer_size--;
}

void CircularBuffer::pop_front() 
{
    if (empty()) {
        throw std::underflow_error("Buffer is empty");
    }

    head = (head + 1) % buffer_capacity;
    buffer_size--;
}
void CircularBuffer::insert(int pos, const value_type & item) {
    if (pos < 0 || pos > buffer_size) 
    {
        throw std::invalid_argument("Index out of range");   
    }

    if (full()) 
    {
        throw std::overflow_error("Buffer is full");
    }
 
    if (pos < buffer_size / 2) 
    {
        head = (head - 1 + buffer_capacity) % buffer_capacity;
        for (int i = 0; i < pos; ++i) 
        {
            int from = (head + i +1) % buffer_capacity;
            int to = (head + i) % buffer_capacity;
            buffer[to] = buffer[from];
        }
    }
    else 
    {
        tail = (tail + 1) % buffer_capacity;
        for (int i = buffer_size - 1; i >= pos; --i) 
        {
            int from = (head + i) % buffer_capacity;
            int to = (head + i + 1) % buffer_capacity;
            buffer[to] = buffer[from];
        } 
    }

    int insert_index = (head + pos) % buffer_capacity;
    buffer[insert_index] = item;
    buffer_size++;
}

void CircularBuffer::erase(int first, int last) 
{
    if (first < 0 || last > buffer_size) 
    {
        throw std::invalid_argument("Index out of range");
    }

    if (first >= last) 
    {
        throw std::invalid_argument("Invalid range");
    }

    int count = last - first;
    
    for(int i = last; i < buffer_size; ++i) 
    {
        buffer[(head + i - count) % buffer_capacity] = buffer[(head + i) % buffer_capacity];
    }

    buffer_size -= count;
    tail = (tail + buffer_size) % buffer_capacity;
}

void CircularBuffer::clear() 
{
    head = 0;
    tail = 0;
    buffer_size = 0;
}

bool operator==(const CircularBuffer & a, const CircularBuffer & b) 
{
    if (a.size() != b.size()) 
    {
        return false;
    }

    for (int i = 0; i < a.size(); i++) 
    {
        if (a[i] != b[i]) 
        {
            return false;
        }
    }

    return true;
}

bool operator!=(const CircularBuffer & a, const CircularBuffer & b) 
{
    return !(a == b);
}
