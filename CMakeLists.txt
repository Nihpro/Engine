cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Engine)
project(${PROJECT_NAME})

# ========== НАСТРОЙКИ ==========
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# ========== ПОДКЛЮЧАЕМ ЗАВИСИМОСТИ ==========
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# ========== НАХОДИМ ВСЕ .CPP ФАЙЛЫ АВТОМАТИЧЕСКИ ==========
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)



# ========== СОЗДАЁМ ИСПОЛНЯЕМЫЙ ФАЙЛ ==========
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# ========== НАСТРОЙКИ КОМПИЛЯЦИИ ==========
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# ========== ПОДКЛЮЧАЕМ ЗАГОЛОВКИ ==========
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/entt
)

# ========== ПОДКЛЮЧАЕМ БИБЛИОТЕКИ ==========
target_link_libraries(${PROJECT_NAME} 
    glfw 
    glad
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} 
        opengl32
        ${CMAKE_DL_LIBS}
    )
endif()

# ========== НАСТРОЙКИ ВЫВОДА ==========
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ========== КОПИРУЕМ РЕСУРСЫ (ИСПРАВЛЕНО) ==========
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMENT "Copying resources to output directory"
)

# ========== ВЫВОДИМ ИНФОРМАЦИЮ ==========
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output directory: ${CMAKE_BINARY_DIR}/bin")