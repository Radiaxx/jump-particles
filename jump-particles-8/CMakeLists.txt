add_executable(jump-particles-8 src/main.cpp src/game.cpp src/particle.cpp src/particleSystem.cpp src/physicsSolver.cpp src/button.cpp)
target_compile_features(jump-particles-8 PRIVATE cxx_std_17)
target_link_libraries(jump-particles-8 PRIVATE SFML::Graphics)

add_custom_target(copy_resources-8
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:jump-particles-8>/resources"
)

add_dependencies(jump-particles-8 copy_resources-8)