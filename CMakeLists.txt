cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME A2OOPGame)
project(${PROJECT_NAME})

set(MAIN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/Main.cpp)

add_executable(${PROJECT_NAME}
        ${MAIN_SOURCE_DIR}
        src/state-machines/StateMachineManager.cpp include/state-machines/StateMachineManager.h
        src/state-machines/StateMachine.cpp include/state-machines/StateMachine.h
        src/state-machines/renderer/Renderer.cpp include/state-machines/renderer/Renderer.h
        src/state-machines/MenuState.cpp include/state-machines/MenuState.h
        src/HelperFunctions.cpp include/HelperFunctions.h
        src/entities/Entity.cpp include/entities/Entity.h
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        include/state-machines
        include/state-machines/renderer
        include/entities
        )


#---------- Adding Vendor elements to project. ----------#

target_compile_definitions(${PROJECT_NAME} PUBLIC -DSDL_MAIN_HANDLED)
# Getting information for machine type. Assembling compiler 'triplet' to load correct files.
string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)
set(COMPILER_TRIPLET "${COMP}-${PLATFORM}-${ARCH}")
message(STATUS "Compiling For: ${COMPILER_TRIPLET}")

# Check to see if vendor include folder exists. Bail out if it doesn't.
set(VENDOR_INCLUDE ${CMAKE_SOURCE_DIR}/vendor/${COMPILER_TRIPLET}/include)
message(CHECK_START "Looking for Vendor Includes at: ${VENDOR_INCLUDE}")
if (IS_DIRECTORY ${VENDOR_INCLUDE})
    message(CHECK_PASS "Found")
else()
    message(CHECK_FAIL "Failed")
    message(FATAL_ERROR "Vendor include does not exists for type: ${COMPILER_TRIPLET}.\n Check path exist: ${VENDOR_INCLUDE}")
endif()

# Link vendor includes to the project.
target_include_directories(${PROJECT_NAME} PUBLIC
        ${VENDOR_INCLUDE}
        ${VENDOR_INCLUDE}/sdl2
        ${VENDOR_INCLUDE}/glm
        )

# Check to see if vendor lib folder exists. Bail out if it doesn't.
set(VENDOR_LIB ${CMAKE_SOURCE_DIR}/vendor/${COMPILER_TRIPLET}/lib)
message(CHECK_START "Looking for Vendor Lib at: ${VENDOR_LIB}")
if (IS_DIRECTORY ${VENDOR_LIB})
    message(CHECK_PASS "Found")
else()
    message(CHECK_FAIL "Failed")
    message(FATAL_ERROR "Vendor lib does not exist for type: ${COMPILER_TRIPLET}.\n Check path exist: ${VENDOR_LIB}")
endif ()

# Dynamic link to the SDL2 Library.
target_link_libraries(${PROJECT_NAME} PUBLIC ${VENDOR_LIB}/SDL2.lib)

# Potentially not needed? Keeping here in case anything happens in the future.
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${VENDOR_LIB}
#        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
#        )

