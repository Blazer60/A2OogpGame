cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME A2OOPGame)
project(${PROJECT_NAME})

set(FORCE_X86_MODE OFF)

set(MAIN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/Main.cpp)

add_executable(${PROJECT_NAME}
        ${MAIN_SOURCE_DIR}
        src/state-machines/StateMachineManager.cpp include/state-machines/StateMachineManager.h
        src/state-machines/StateMachine.cpp include/state-machines/StateMachine.h
        src/state-machines/renderer/Renderer.cpp include/state-machines/renderer/Renderer.h
        src/state-machines/MenuState.cpp include/state-machines/MenuState.h
        src/HelperFunctions.cpp include/HelperFunctions.h
        src/entities/Entity.cpp include/entities/Entity.h
        src/entities/Player.cpp include/entities/Player.h
        src/state-machines/GameState.cpp include/state-machines/GameState.h
        src/entities/BaseEnemy.cpp include/entities/BaseEnemy.h
        include/quad-tree/QuadTree.h include/quad-tree/QuadTreeNode.h
        include/quad-tree/QuadTreeHelpers.h src/quad-tree/QuadTreeHelpers.cpp
        src/entities/projectiles/BaseProjectile.cpp include/entities/projectiles/BaseProjectile.h
        src/entities/MechaChad.cpp include/entities/MechaChad.h
        src/entities/Barrier/BarrierImage.cpp include/entities/barrier/BarrierImage.h
        src/entities/Barrier/BarrierCollider.cpp include/entities/barrier/BarrierCollider.h
        src/SoundFx.cpp include/SoundFx.h
        src/Music.cpp include/Music.h
        src/hud/HudElement.cpp include/hud/HudElement.h
        src/hud/HudText.cpp include/hud/HudText.h
        src/hud/Timer.cpp include/hud/Timer.h
        src/hud/LifeGauge.cpp include/hud/LifeGauge.h
        src/hud/HudImage.cpp include/hud/HudImage.h
        src/state-machines/overlays/PauseState.cpp include/state-machines/overlays/PauseState.h
        src/state-machines/overlays/DeathState.cpp include/state-machines/overlays/DeathState.h
        src/state-machines/overlays/OverlayState.cpp include/state-machines/overlays/OverlayState.h
        src/entities/projectiles/RicochetProjectile.cpp include/entities/projectiles/RicochetProjectile.h
        src/entities/projectiles/TrackingProjectile.cpp include/entities/projectiles/TrackingProjectile.h
        src/entities/projectiles/MomentumProjectile.cpp include/entities/projectiles/MomentumProjectile.h
        src/entities/projectiles/HexedProjectile.cpp include/entities/projectiles/HexedProjectile.h
        src/ai/Ai.cpp include/ai/Ai.h
        src/ai/Node.cpp include/ai/Node.h
        src/ai/ChargeNode.cpp include/ai/ChargeNode.h
        src/ai/ShootInCircleNode.cpp include/ai/ShootInCircleNode.h
        src/ai/ShootAtTargetNode.cpp include/ai/ShootAtTargetNode.h
        src/ai/ShootNode.cpp include/ai/ShootNode.h
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        include/state-machines
        include/state-machines/renderer
        include/state-machines/overlays
        include/entities
        include/entities/projectiles
        include/entities/barrier
        include/quad-tree
        include/hud
        include/ai
        )

target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG_DRAW_HIT_BOXES=0)

#---------- Adding Vendor elements to project. ----------#

target_compile_definitions(${PROJECT_NAME} PUBLIC -DSDL_MAIN_HANDLED)
# Getting information for machine type. Assembling compiler 'triplet' to load correct files.
string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
if (${FORCE_X86_MODE})
    string(TOLOWER "x86" ARCH)
else()
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)
endif ()
set(COMPILER_TRIPLET "${COMP}-${PLATFORM}-${ARCH}")
message(STATUS "Compiling For: ${COMPILER_TRIPLET}")

# Check to see if vendor include folder exists. Bail out if it doesn't.
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/include)
message(CHECK_START "Looking for Vendor Includes at: ${INCLUDE_DIR}")
if (IS_DIRECTORY ${INCLUDE_DIR})
    message(CHECK_PASS "Found")
else()
    message(CHECK_FAIL "Failed")
    message(FATAL_ERROR "Vendor include does not exists for type: ${COMPILER_TRIPLET}.\n
                        Check path exist: ${INCLUDE_DIR}\n
                        You can compile in x86 mode by turning on FORCE_X86_MODE on line 6 in CMakeLists.txt")
endif()

# Link vendor includes to the project.
target_include_directories(${PROJECT_NAME} PUBLIC
        ${INCLUDE_DIR}
        ${INCLUDE_DIR}/sdl2
        ${INCLUDE_DIR}/sdl2-image
        ${INCLUDE_DIR}/glm
        ${INCLUDE_DIR}/sdl2-mixer
        ${INCLUDE_DIR}/sdl2-ttf
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
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${VENDOR_LIB}/SDL2.lib
        ${VENDOR_LIB}/SDL2_image.lib
        ${VENDOR_LIB}/SDL2_mixer.lib
        ${VENDOR_LIB}/SDL2_ttf.lib
        )

set(VENDOR_DLL ${CMAKE_SOURCE_DIR}/vendor/${COMPILER_TRIPLET}/dll)
message(CHECK_START "Looking for Vendor dll at:" ${VENDOR_DLL})
if (IS_DIRECTORY ${VENDOR_DLL})
    message(CHECK_PASS "Found")
else()
    message(CHECK_PASS "Failed")
    message(FATAL_ERROR "Vendor dll does not exist for type: ${COMPILER_TRIPLET}.\n Check path exist: ${VENDOR_DLL}")
endif ()

# Potentially not needed? Keeping here in case anything happens in the future.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${VENDOR_DLL}
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        )

# Copying resources over.
set(ASSET_DIR ${CMAKE_SOURCE_DIR}/assets)
message(CHECK_START "Looking for Assets folder")
if (IS_DIRECTORY ${ASSET_DIR})
    message(CHECK_PASS "Found")
else()
    message(CHECK_FAIL "Failed")
    message(FATAL_ERROR "Assets dir not found. \nCheck that the path exist.")
endif()
file(COPY ${ASSET_DIR} DESTINATION ${CMAKE_BINARY_DIR})

