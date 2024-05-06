project(TestSpriteBatch)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED IMPORTED_TARGET sfml-all)
add_executable(main 
    test.cpp 
    ../Sprite.cpp
    ../SpriteBatch.cpp)
include_directories(../)

target_link_libraries(main PUBLIC PkgConfig::SFML)
