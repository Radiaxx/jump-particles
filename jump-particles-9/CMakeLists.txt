add_executable(jump-particles-9 src/main.cpp src/game.cpp src/particle.cpp src/particleSystem.cpp src/physicsSolver.cpp src/button.cpp)
target_compile_features(jump-particles-9 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-9 PRIVATE SFML::Graphics)

add_custom_target(copy_resources-9
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:jump-particles-9>/resources"
)

add_dependencies(jump-particles-9 copy_resources-9)