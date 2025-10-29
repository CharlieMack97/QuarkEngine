set(CMAKE_WIN32_LONG_PATHS ON)
include(FetchContent)

# Output directory for your runtime binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/QuarkGame")

# Fetch dependencies
FetchContent_Declare(
  bx
  GIT_REPOSITORY https://github.com/bkaradzic/bx.git
  GIT_TAG master
)
FetchContent_MakeAvailable(bx)

FetchContent_Declare(
  bimg
  GIT_REPOSITORY https://github.com/bkaradzic/bimg.git
  GIT_TAG master
)
FetchContent_MakeAvailable(bimg)

FetchContent_Declare(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG master
)
FetchContent_MakeAvailable(bgfx)
set_target_properties(shaderc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${bgfx_BINARY_DIR}/bin/$<CONFIG>"
)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# ---- Engine library ----
add_library(QuarkEngine STATIC
    EngineCore.cpp
    EngineApp.cpp
    TimeManager.cpp
    Header/InterfaceRenderer.h
    Header/EngineApp.h
    Header/Renderer.h
    Header/TimeManager.h
    Header/EngineCore.h
    Header/GameObject.h
    Header/Component.h
    Compenents/TransformComp.h
    Compenents/RendererComp.h
    Compenents/RendererComp.cpp
    Renderer.cpp
    TextureManager.cpp
    shader/vs_shader.sc
    shader/fs_shader.sc
   

)
 
target_include_directories(QuarkEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Header)

target_link_libraries(QuarkEngine
    PUBLIC
        SDL3::SDL3
        bgfx
        bimg
        bx
)

# Required on Windows so SDL doesn't redefine main()
if(WIN32)
    target_compile_definitions(QuarkEngine PUBLIC SDL_MAIN_HANDLED)
endif()

# ---- Shader compilation using bgfx.cmake ----

# Shader source and output directories
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shader)
set(SHADER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/generated/shaders)
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

# Build bgfx shader compiler first
add_custom_target(build_shaderc
    COMMAND ${CMAKE_COMMAND} --build ${bgfx_BINARY_DIR} --target shaderc --config $<CONFIG>
    COMMENT "Building bgfx shader compiler"
)
message(STATUS "SHADER_DIR=${SHADER_DIR}")
message(STATUS "SHADER_OUTPUT_DIR=${SHADER_OUTPUT_DIR}")
message(STATUS "bgfx_BINARY_DIR = ${bgfx_BINARY_DIR}")

# Vertex shader compilation
bgfx_compile_shaders(
    TYPE VERTEX
    SHADERS ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/vs_shader.sc
    VARYING_DEF ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
    AS_HEADERS
    DEPENDS build_shaderc
    INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/bgfx-src/bgfx/src
    
)

# Fragment shader compilation
bgfx_compile_shaders(
    TYPE FRAGMENT
    SHADERS ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/fs_shader.sc
    VARYING_DEF ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
    AS_HEADERS
    DEPENDS build_shaderc
    INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/bgfx-src/bgfx/src
)

# Include generated shader headers
target_include_directories(QuarkEngine PRIVATE ${SHADER_OUTPUT_DIR})
