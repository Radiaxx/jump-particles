add_executable(jump-particles-3 src/main.cpp src/game.cpp src/particle.cpp)
target_compile_features(jump-particles-3 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-3 PRIVATE SFML::Graphics)
