cmake_minimum_required(VERSION 3.14)
project(cpp-project CXX)

# Dodaj katalog z nagłówkami TinyXML
include_directories("${CMAKE_SOURCE_DIR}/include")

# Dodaj pliki źródłowe projektu
set(SOURCE_FILES 
    src/main.cpp
    src/tinyxml2.cpp  # Zakładając, że plik tinyxml2.cpp znajduje się w folderze src
)
set(HPP_FILES 
    include/tinyxml2.h  
)
# Dodaj pliki nagłówkowe TinyXML
 # Aktualizuj tę ścieżkę do lokalizacji TinyXML
 set(xml_FILES 
 xml/vending_machine_config.xml
)
add_executable(cpp-project ${SOURCE_FILES} ${HPP_FILES} ${xml_FILES})

# Ustawienie standardu C++ na C++23
set_target_properties(cpp-project PROPERTIES CXX_STANDARD 23)