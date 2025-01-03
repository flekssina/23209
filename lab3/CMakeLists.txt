cmake_minimum_required(VERSION 3.10)
project(lab3)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указать все исходные файлы
set(SOURCES
    main.cpp
    ConfigParser.cpp
    SoundProcessor.cpp
    MuteConverter.cpp
    MixerConverter.cpp
    CustomConverter.cpp
    WavFile.cpp
)

# Указать заголовочные файлы
set(HEADERS
    ConfigParser.h
    SoundProcessor.h
    Exceptions.h
    WavFile.h
    Converter.h
    MuteConverter.h
    MixerConverter.h
    CustomConverter.h
)

# Добавить исполняемый файл
add_executable(lab3 ${SOURCES} ${HEADERS})

# Установить вывод компиляции
set_target_properties(lab3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
