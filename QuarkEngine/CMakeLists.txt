set(CMAKE_WIN32_LONG_PATHS ON)
include(FetchContent)

# Output directory for your runtime binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/QuarkGame")

# Fetch dependencies
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS ON CACHE BOOL "" FORCE)
add_subdirectory(lib/bgfx.cmake)

# ---- Engine library ----
add_library(QuarkEngine STATIC
    EngineCore.cpp
    EngineApp.cpp
    TimeManager.cpp
    GameObject.cpp
    Header/InterfaceRenderer.h
    Header/EngineApp.h
    Header/Renderer.h
    Header/TimeManager.h
    Header/EngineCore.h
    Header/GameObject.h
    Header/Component.h
    Components/TransformComp.h
    Components/TransformComp.cpp
    Components/RendererComp.h
    Components/RendererComp.cpp
    Renderer.cpp
    TextureManager.cpp
    shader/vs_shader.sc
    shader/fs_shader.sc
    
 "Header/bgfxUtils.h" "bgfxUtils.cpp")


target_include_directories(QuarkEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Header
    ${CMAKE_CURRENT_SOURCE_DIR}/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/bgfx.cmake/
    
)

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


# Vertex shader compilation
bgfx_compile_shaders(
    INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}lib/bgfx.cmake/bgfx/src/bgfx_shader.sh 
    TYPE VERTEX
    SHADERS ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/vs_shader.sc
    VARYING_DEF ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
    AS_HEADERS  
)

# Fragment shader compilation
bgfx_compile_shaders(
    INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}lib/bgfx.cmake/bgfx/src/bgfx_shader.sh 
    TYPE FRAGMENT
    SHADERS ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/fs_shader.sc
    VARYING_DEF ${CMAKE_SOURCE_DIR}/QuarkEngine/shader/varying.def.sc
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
    AS_HEADERS
   
)

# Include generated shader headers
target_include_directories(QuarkEngine PRIVATE ${SHADER_OUTPUT_DIR})
