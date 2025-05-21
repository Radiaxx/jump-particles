add_executable(jump-particles-2 src/main.cpp src/game.cpp src/particle.cpp)
target_compile_features(jump-particles-2 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-2 PRIVATE SFML::Graphics)
