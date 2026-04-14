cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Engine)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
    # Core
    src/main.cpp
    
    # Camera
    src/Camera/Camera.cpp
    src/Camera/Camera.h
    
    # Core
    src/Core/Game.cpp
    src/Core/Game.h
    
    # extern
    src/extern/stb_image.cpp
    src/extern/stb_image.h
    
    # Input
    src/Input/CameraController.cpp
    src/Input/CameraController.h
    src/Input/InputManager.cpp
    src/Input/InputManager.h
    src/Input/KeyCodes.h
    
    # Renderer
    src/Renderer/Renderer.cpp
    src/Renderer/Renderer.h
    src/Renderer/Shader.cpp
    src/Renderer/Shader.h
    src/Renderer/Sprite.cpp
    src/Renderer/Sprite.h
    src/Renderer/Texture2D.cpp
    src/Renderer/Texture2D.h
    src/Renderer/OpenGL.h
    
    # Resources
    src/Resources/ResourceManager.cpp
    src/Resources/ResourceManager.h
    
    # System
    src/System/Time.cpp
    src/System/Time.h
    src/System/Window.cpp
    src/System/Window.h

    #ECS
    src/ECS/ECSManager.cpp
    src/ECS/ECSManager.h

    src/ECS/Components/Transform.h
    src/ECS/Components/Gameplay.h
    src/ECS/Components/Render.h
    src/ECS/Components/Animation.h

    src/ECS/System/AnimationSystem.cpp
    src/ECS/System/AnimationSystem.h
    src/ECS/System/RendererSystem.cpp
    src/ECS/System/RendererSystem.h
    src/ECS/System/MovementSystem.h


)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)
include_directories(external/rapidjson/include)
include_directories(external/entt)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res) 