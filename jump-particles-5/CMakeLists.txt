add_executable(jump-particles-5 src/main.cpp src/game.cpp src/particle.cpp src/particleSystem.cpp)
target_compile_features(jump-particles-5 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-5 PRIVATE SFML::Graphics)
