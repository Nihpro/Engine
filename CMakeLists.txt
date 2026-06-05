cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Engine)
project(${PROJECT_NAME})

# 1. Выносим все твои файлы в отдельную переменную SOURCES
set(SOURCES
    # Core
    src/main.cpp
    src/Core/Game.cpp
    src/Core/Game.h
    
    # Camera
    src/Camera/Camera.cpp
    src/Camera/Camera.h
    
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
    src/Renderer/ShaderProgram.cpp
    src/Renderer/ShaderProgram.h    
    src/Renderer/Texture2D.h    
    src/Renderer/Texture2D.cpp    
    src/Renderer/Sprite.h    
    src/Renderer/Sprite.cpp    
    src/Renderer/VertexBuffer.h    
    src/Renderer/VertexBuffer.cpp    
    src/Renderer/VertexArray.h    
    src/Renderer/VertexArray.cpp    
    src/Renderer/IndexBuffer.h    
    src/Renderer/IndexBuffer.cpp    
    src/Renderer/VertexBufferLayout.h    
    src/Renderer/VertexBufferLayout.cpp    
    src/Renderer/Renderer.h    
    src/Renderer/Renderer.cpp    
    src/Renderer/SpriteAnimator.h    
    src/Renderer/SpriteAnimator.cpp
    src/Renderer/OpenGL.h
    
    # Resources
    src/Resources/ResourceManager.cpp
    src/Resources/ResourceManager.h
    
    # System
    src/System/Time.cpp
    src/System/Time.h
    src/System/Window.cpp
    src/System/Window.h

    # ECS
    src/ECS/ECSManager.cpp
    src/ECS/ECSManager.h

    # ECS Components
    src/ECS/Components/Transform.h
    src/ECS/Components/Render.h
    src/ECS/Components/Animation.h
    src/ECS/Components/Collision.h
    src/ECS/Components/Physics.h

    # ECS Systems
    src/ECS/System/AnimationSystem.cpp
    src/ECS/System/AnimationSystem.h
    src/ECS/System/RendererSystem.cpp
    src/ECS/System/RendererSystem.h
    src/ECS/System/MovementSystem.h
    src/ECS/System/PlayerControlSystem.cpp
    src/ECS/System/PlayerControlSystem.h
    src/ECS/System/CollisionSystem.cpp
    src/ECS/System/CollisionSystem.h
    src/ECS/System/PhysicsSystem.cpp
    src/ECS/System/PhysicsSystem.h
)

# 2. МАГИЯ ДЛЯ VISUAL STUDIO:
# Строим дерево папок. PREFIX "" убирает папку "src" из обозревателя решений,
# чтобы папки Camera, ECS, Renderer и т.д. лежали прямо в корне проекта.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "" FILES ${SOURCES})

# 3. Передаем переменную SOURCES в executable
add_executable(${PROJECT_NAME} ${SOURCES})

# --- ОСТАЛЬНЫЕ НАСТРОЙКИ БЕЗ ИЗМЕНЕНИЙ ---

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