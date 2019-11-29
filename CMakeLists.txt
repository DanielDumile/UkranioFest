cmake_minimum_required(VERSION 3.15)
project(UKfest)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Proyecto)

add_executable(sortDic sortDiccionario.cpp)

add_executable(findWord findWord.cpp)


set(COMMON_SRC "PaqueteDatagrama.cpp" "respuesta.cpp" "SocketDatagrama.cpp" "Solicitud.cpp" "mensaje.h")

add_executable(server servidor.cpp ${COMMON_SRC})

file(COPY diccionario.txt DESTINATION "${UKfest_BINARY_DIR}")
file(COPY textos_pruebas DESTINATION "${UKfest_BINARY_DIR}")
