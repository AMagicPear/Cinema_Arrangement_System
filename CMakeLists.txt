cmake_minimum_required(VERSION 3.18)
project(CinemaCpp)

set(CMAKE_CXX_STANDARD 17)


set(SDL_H /opt/homebrew/Cellar/sdl2/2.26.4/include) # 这个SDL开发包的路径，可以通过brew info sdl2查出来
set(SDL_TTF_H /opt/homebrew/Cellar/sdl2_ttf/2.20.2/include)
include_directories(${SDL_H} ${SDL_TTF_H}) # 添加SDL头文件搜索路径
set(SDL_LIB /opt/homebrew/Cellar/sdl2/2.26.4/lib/libSDL2-2.0.0.dylib)
set(SDL_TTF_LIB /opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib/libSDL2_ttf-2.0.0.dylib)
link_libraries(${SDL_LIB} ${SDL_TTF_LIB}) # 增加SDL链接库目录
add_executable(CinemaCpp main.cpp "Basic Information.hpp" "Audience Info.hpp" "Admin Info.hpp" welcome.cpp)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
