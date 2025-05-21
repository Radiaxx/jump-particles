add_executable(jump-particles-6 src/main.cpp src/game.cpp src/particle.cpp src/particleSystem.cpp src/physicsSolver.cpp)
target_compile_features(jump-particles-6 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-6 PRIVATE SFML::Graphics)
