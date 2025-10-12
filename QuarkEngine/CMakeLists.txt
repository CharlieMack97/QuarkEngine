
add_library(QuarkEngine STATIC
    EngineCore.cpp
    EngineCore.h
)

target_include_directories(QuarkEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

