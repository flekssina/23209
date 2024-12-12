#include "circular.h"
#include <gtest/gtest.h>

TEST(CircularBufferTest, DefaultConstructor) {
    CircularBuffer buffer;
    EXPECT_EQ(buffer.size(), 0); // Размер должен быть 0
    EXPECT_TRUE(buffer.empty()); // Буфер должен быть пустым
}
TEST(CircularBufferTest, CopyConstructor) {
    // Создаем исходный буфер
    CircularBuffer original(5); // Буфер емкостью 5
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    // Создаем копию с помощью конструктора копирования
    CircularBuffer copy(original);

    // Проверяем, что копия имеет такие же свойства, как оригинал
    EXPECT_EQ(copy.size(), original.size());           // Размеры должны совпадать
    EXPECT_EQ(copy.capacity(), original.capacity());   // Емкости должны совпадать
    EXPECT_EQ(copy.front(), original.front());         // Первый элемент должен совпадать
    EXPECT_EQ(copy.back(), original.back());           // Последний элемент должен совпадать

    // Проверяем, что содержимое совпадает
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }

    // Проверяем, что изменения в копии не затрагивают оригинал
    copy.push_back(4);
    EXPECT_NE(copy.size(), original.size());           // Размеры не должны совпадать после изменения копии
    EXPECT_NE(copy.back(), original.back());           // Последний элемент не должен совпадать
}

TEST(CircularBufferTest, CapacityConstructor) {
    CircularBuffer buffer(5);
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 5);
    EXPECT_TRUE(buffer.empty());
}

TEST(CircularBufferTest, FillValueConstructor){
    CircularBuffer buffer(3, 'L');
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.capacity(), 3);

    for(int i = 0; i < 3; ++i) {
        EXPECT_EQ(buffer[i], 'L');
    }
}

TEST(CircularBufferTest, Operator) {
    CircularBuffer buffer(2);

    buffer.push_back('A');
    buffer.push_back('L');

    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'L');
}

TEST(CircularBufferTest, At) {
    CircularBuffer buffer(2);

    buffer.push_back('A');
    buffer.push_back('L');

    EXPECT_EQ(buffer.at(0), 'A');
    EXPECT_EQ(buffer.at(1), 'L');
}
TEST(CircularBufferTest, AtWrong) {
    CircularBuffer buffer(1);
    buffer.push_back('L');

    EXPECT_THROW(buffer.at(1), std::out_of_range);
}

TEST(CircularBufferTest, FrontAndBack) {
    CircularBuffer buffer(2);
    buffer.push_back('A');
    buffer.push_back('L');

    EXPECT_EQ(buffer.front(),'A');
    EXPECT_EQ(buffer.back(), 'L');
}

TEST(CircularBufferTest, LinearizeTest) {
    // Создаем буфер с емкостью 5
    CircularBuffer buffer(5);

    // Добавляем элементы
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    // Удаляем первый элемент
    buffer.pop_front(); // Теперь head != 0

    // Проверяем, что буфер не линейный
    EXPECT_FALSE(buffer.is_linearized());

    // Преобразуем в линейный
    buffer.linearize();

    // Проверяем, что буфер стал линейным
    EXPECT_TRUE(buffer.is_linearized());

    // Проверяем данные
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
}
TEST(CircularBufferTest, IsLinearized) {
    CircularBuffer buffer(5);
    EXPECT_TRUE(buffer.is_linearized());
}
TEST(CircularBufferTest, Rotate) {
    CircularBuffer buffer(5);
    buffer.push_back('N');
    buffer.push_back('A');
    buffer.push_back('A');
    buffer.push_back('L');
    buffer.push_back('I');

    buffer.rotate(2);

    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'L');
    EXPECT_EQ(buffer[2], 'I');
    EXPECT_EQ(buffer[3], 'N');
    EXPECT_EQ(buffer[4], 'A');
}
TEST(CircularBufferTest, Size) {
    CircularBuffer buffer(10);

    EXPECT_EQ(buffer.size(), 0);

    buffer.push_back('L');
    EXPECT_EQ(buffer.size(), 1);

    buffer.pop_back();
    EXPECT_EQ(buffer.size(), 0);
}

TEST(CircularBufferTest, Empty) {
    CircularBuffer buffer(10);

    EXPECT_TRUE(buffer.empty());

    buffer.push_back('A');
    EXPECT_FALSE(buffer.empty());

    buffer.pop_back();
    EXPECT_TRUE(buffer.empty());
}

TEST(CircularBufferTest, Full) {
    CircularBuffer buffer(3);

    EXPECT_FALSE(buffer.full());

    buffer.push_back('L');
    EXPECT_FALSE(buffer.full());

    buffer.push_back('O');
    EXPECT_FALSE(buffer.full());

    buffer.push_back('L');
    EXPECT_TRUE(buffer.full());

    buffer.pop_back();
    EXPECT_FALSE(buffer.full());
}

TEST(CircularBufferTest, Reserve) {
    CircularBuffer buffer(5);

    EXPECT_EQ(buffer.reserve(), 5);

    buffer.push_back('L');
    EXPECT_EQ(buffer.reserve(), 4);

    buffer.push_back('O');
    EXPECT_EQ(buffer.reserve(), 3);

    buffer.push_back('L');
    EXPECT_EQ(buffer.reserve(), 2);

    buffer.pop_back();
    EXPECT_EQ(buffer.reserve(), 3);
}

TEST(CircularBufferTest, Capacity) {
    CircularBuffer buffer(5);
    EXPECT_EQ(buffer.capacity(), 5);

    buffer.push_back('O');
    buffer.push_back('K');
    EXPECT_EQ(buffer.capacity(), 5);

    buffer.pop_back();
    EXPECT_EQ(buffer.capacity(), 5);
}

TEST(CircularBufferTest, SetCapacity) {
    CircularBuffer buffer(4);
    buffer.set_capacity(3);
    EXPECT_EQ(buffer.capacity(), 3);

    buffer.set_capacity(2);
    EXPECT_EQ(buffer.capacity(), 2);
}

TEST(CircularBufferTest, ResizeTest) { 
    CircularBuffer buffer(3);
    buffer.resize(3, 'A');
    EXPECT_EQ(buffer.size(), 3);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(buffer[i], 'A');
    }

    buffer.resize(2);
    EXPECT_EQ(buffer.size(), 2);
}

TEST(CircularBufferTest, AssignOperator) {
    CircularBuffer buffer1(3);
    buffer1.push_back('A');
    buffer1.push_back('B');

    CircularBuffer buffer2 = buffer1;

    EXPECT_EQ(buffer2.front(), 'A');
    EXPECT_EQ(buffer2.back(), 'B');
    EXPECT_EQ(buffer2.size(), 2);
}
TEST(CircularBufferTest, SwapTest) {
    CircularBuffer buffer1(3);
    buffer1.push_back('A');
    buffer1.push_back('B');

    CircularBuffer buffer2(2);
    buffer2.push_back('C');

    buffer1.swap(buffer2);

    EXPECT_EQ(buffer1.size(), 1);       
    EXPECT_EQ(buffer1.front(), 'C');

    EXPECT_EQ(buffer2.size(), 2);
    EXPECT_EQ(buffer2.front(), 'A');
    EXPECT_EQ(buffer2.back(), 'B');
}

TEST(CircularBufferTest, PushBackTest) {
    CircularBuffer buffer(2);
    
    buffer.push_back('A');
    buffer.push_back('B');

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_TRUE(buffer.full());

    EXPECT_EQ(buffer.front(), 'A');
    EXPECT_EQ(buffer.back(), 'B');
}

TEST(CircularBufferTest, PushFrontTest) {
    CircularBuffer buffer(2);

    buffer.push_front('A');
    buffer.push_front('B');

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_TRUE(buffer.full());

    EXPECT_EQ(buffer.front(), 'B');
    EXPECT_EQ(buffer.back(), 'A');
}

TEST(CircularBufferTest, PopBackTest) {
    CircularBuffer buffer(2);

    buffer.push_back('A');
    buffer.push_back('B');

    buffer.pop_back();

    EXPECT_EQ(buffer.size(), 1);
    EXPECT_EQ(buffer.capacity(), 2);
    EXPECT_FALSE(buffer.full());

    EXPECT_EQ(buffer.front(), 'A');
    EXPECT_EQ(buffer.back(), 'A');
}
TEST(CircularBufferTest, PopFrontTest) {
    CircularBuffer buffer(2);

    buffer.push_back('A');
    buffer.push_back('B');

    buffer.pop_front();

    EXPECT_EQ(buffer.size(), 1);
    EXPECT_EQ(buffer.capacity(), 2);
    EXPECT_FALSE(buffer.full());

    EXPECT_EQ(buffer.front(), 'B');
    EXPECT_EQ(buffer.back(), 'B');
}

TEST(CircularBufferTest, Insert) {
    CircularBuffer buffer(7);

    buffer.push_back('A');
    buffer.push_back('B');
    buffer.push_back('C');

    buffer.insert(0, 'X');
    EXPECT_EQ(buffer.size(), 4);
    EXPECT_EQ(buffer[0], 'X');
    EXPECT_EQ(buffer[1], 'A');
    EXPECT_EQ(buffer[2], 'B');
    EXPECT_EQ(buffer[3], 'C');


    buffer.insert(1, 'Y');
    EXPECT_EQ(buffer.size(), 5);
    EXPECT_EQ(buffer[0], 'X');
    EXPECT_EQ(buffer[1], 'Y');
    EXPECT_EQ(buffer[2], 'A');
    EXPECT_EQ(buffer[3], 'B');
    EXPECT_EQ(buffer[4], 'C');

    buffer.insert(5, 'Z');
    EXPECT_EQ(buffer.size(), 6);
    EXPECT_EQ(buffer[0], 'X');
    EXPECT_EQ(buffer[1], 'Y');
    EXPECT_EQ(buffer[2], 'A');
    EXPECT_EQ(buffer[3], 'B');
    EXPECT_EQ(buffer[4], 'C');
    EXPECT_EQ(buffer[5], 'Z');

    buffer.insert(4, 'Z');
    EXPECT_EQ(buffer.size(), 7);
    EXPECT_EQ(buffer[0], 'X');
    EXPECT_EQ(buffer[1], 'Y');
    EXPECT_EQ(buffer[2], 'A');
    EXPECT_EQ(buffer[3], 'B');
    EXPECT_EQ(buffer[4], 'Z');
    EXPECT_EQ(buffer[5], 'C');
    EXPECT_EQ(buffer[6], 'Z');

    EXPECT_THROW(buffer.insert(-1, 'W'), std::invalid_argument);
    EXPECT_THROW(buffer.insert(8, 'W'), std::invalid_argument);
    EXPECT_THROW(buffer.insert(1, 'W'), std::overflow_error);
}

TEST(CircularBufferTest, Erase) {
    CircularBuffer buffer(5);

    buffer.push_back('A');
    buffer.push_back('B');
    buffer.push_back('C');
    buffer.push_back('D');
    buffer.push_back('E');

    buffer.erase(1, 3);
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'D');
    EXPECT_EQ(buffer[2], 'E');

    buffer.erase(0, 1);
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 'D');
    EXPECT_EQ(buffer[1], 'E');

    buffer.erase(0, 2);
    EXPECT_TRUE(buffer.empty());

    EXPECT_THROW(buffer.erase(0, 1), std::invalid_argument);
    buffer.push_back('X');
    EXPECT_THROW(buffer.erase(1, 1), std::invalid_argument);
}

TEST(CircularBufferTest, Clear) {
    CircularBuffer buffer(5);
    buffer.push_back('A');
    buffer.push_back('B');
    buffer.push_back('C');

    EXPECT_EQ(buffer.size(), 3);

    buffer.clear();
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 5);
}

TEST(CircularBufferTest, EqualityOperator) {
    CircularBuffer buffer1(5);
    CircularBuffer buffer2(5);

    buffer1.push_back('A');
    buffer1.push_back('B');
    buffer1.push_back('C');

    buffer2.push_back('A');
    buffer2.push_back('B');
    buffer2.push_back('C');

    EXPECT_TRUE(buffer1 == buffer2);

    buffer2.push_back('D');
    EXPECT_FALSE(buffer1 == buffer2);

    buffer1.push_back('C');
    EXPECT_FALSE(buffer1 == buffer2);

    CircularBuffer firstNewBuffer;
    CircularBuffer secondNewBuffer;
    EXPECT_TRUE(firstNewBuffer == secondNewBuffer);
}

TEST(CircularBufferTest, InequalityOperator) {
    CircularBuffer buffer1(5);
    CircularBuffer buffer2(5);

    buffer1.push_back('A');
    buffer1.push_back('B');
    buffer1.push_back('C');

    buffer2.push_back('A');
    buffer2.push_back('B');
    buffer2.push_back('C');

    EXPECT_FALSE(buffer1 != buffer2);

    buffer2.push_back('D');
    EXPECT_TRUE(buffer1 != buffer2);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);      
    return RUN_ALL_TESTS();                     
}

