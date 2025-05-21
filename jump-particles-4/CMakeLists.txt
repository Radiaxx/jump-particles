add_executable(jump-particles-4 src/main.cpp src/game.cpp src/particle.cpp)
target_compile_features(jump-particles-4 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-4 PRIVATE SFML::Graphics)
