cmake_minimum_required(VERSION 3.10)

project(Projekat)

set(CMAKE_CXX_STANDARD 17)

file(GLOB MAIN_SRC "./src/*.cpp")
file(GLOB INVENTORY_SRC "./src/inventory/*.cpp")
file(GLOB ITEM_TYPE_SRC "./src/inventory/item_type/*.cpp")
file(GLOB ITEM_TYPE_LOADER_SRC "./src/inventory/item_type/loader/*.cpp")
file(GLOB CATEGORY_SRC "./src/inventory/category/*.cpp")
file(GLOB CATEGORY_LOADER_SRC "./src/inventory/category/loader/*.cpp")
file(GLOB UTILITY_SRC_CPP "./src/utility/*.cpp")
file(GLOB UTILITY_SRC_H "./src/utility/*.h")
file(GLOB UTILITY_DATABASE_SRC "./src/utility/*.cpp")
file(GLOB UTILITY_DATABASE_SRC_CPP "./src/utility/database/*.cpp")
file(GLOB UTILITY_DATABASE_SRC_H "./src/utility/database/*.h")
file(GLOB UTILITY_CATEGORY_PRINTER "./src/utility/category/*.cpp")
file(GLOB UTILITY_STRING "./src/utility/string/*.cpp")
file(GLOB MENU_SRC "./src/menu/*.cpp")
file(GLOB SESSION_SRC "./src/session/*.cpp")

set(SRC 
    ${MAIN_SRC}
    ${INVENTORY_SRC}
    ${ITEM_TYPE_SRC}
    ${ITEM_TYPE_LOADER_SRC}
    ${CATEGORY_SRC}
    ${CATEGORY_LOADER_SRC}
    ${UTILITY_SRC}
    ${UTILITY_DATABASE_SRC}
    ${UTILITY_DATABASE_SRC_CPP}
    ${UTILITY_DATABASE_SRC_H}
    ${UTILITY_STRING}
    ${MENU_SRC}
    ${SESSION_SRC}
    ${UTILITY_CATEGORY_PRINTER}
)

add_executable(exe ${SRC})


