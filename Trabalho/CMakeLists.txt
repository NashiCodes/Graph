add_executable(main.cpp main.cpp src/Menu.h)
target_link_libraries(main.cpp ${OpenCV_LIBS})

add_executable(aresta src/models/Aresta.cpp src/models/AGrafo.h)
target_link_libraries(aresta ${OpenCV_LIBS})

add_executable(No src/models/No.cpp)
target_link_libraries(No ${OpenCV_LIBS})

add_executable(Grafo src/Grafo.cpp src/models/AGrafo.h)
target_link_libraries(Grafo ${OpenCV_LIBS})