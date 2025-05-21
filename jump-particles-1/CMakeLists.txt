add_executable(jump-particles-1 src/main.cpp src/game.cpp)
target_compile_features(jump-particles-1 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-1 PRIVATE SFML::Graphics)
