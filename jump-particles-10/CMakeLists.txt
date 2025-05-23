add_executable(jump-particles-10 src/main.cpp src/game.cpp src/particle.cpp src/particleSystem.cpp src/physicsSolver.cpp src/button.cpp src/magnet.cpp)
target_compile_features(jump-particles-10 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-10 PRIVATE SFML::Graphics)

add_custom_target(copy_resources-10
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:jump-particles-10>/resources"
)

add_dependencies(jump-particles-10 copy_resources-10)