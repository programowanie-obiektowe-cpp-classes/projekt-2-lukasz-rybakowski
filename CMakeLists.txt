cmake_minimum_required(VERSION 3.14)
project(cpp-project CXX)

# Dodaj katalog z nagłówkami TinyXML
include_directories("${CMAKE_SOURCE_DIR}/include")

# Dodaj pliki źródłowe projektu
set(SOURCE_FILES 
    src/main.cpp
    src/tinyxml2.cpp  # Zakładając, że plik tinyxml2.cpp znajduje się w folderze src
)

# Dodaj pliki nagłówkowe TinyXML
include_directories("${CMAKE_SOURCE_DIR}/path/to/tinyxml") # Aktualizuj tę ścieżkę do lokalizacji TinyXML

add_executable(cpp-project ${SOURCE_FILES})

# Ustawienie standardu C++ na C++23
set_target_properties(cpp-project PROPERTIES CXX_STANDARD 23)