# =============================================================================
# ADS7952 Driver Examples - Main Component CMakeLists.txt
# =============================================================================
# This CMakeLists.txt is designed to work with the build_app.sh script
# which handles app type validation and source file discovery.
#
# The component supports ESP-IDF's two-phase build process:
# 1. Requirements phase: Uses defaults to allow component discovery
# 2. Build phase: Enforces proper usage with helpful error messages
# =============================================================================

# =============================================================================
# Variable Validation and Defaults
# =============================================================================
# Set defaults for requirements phase, validate during build phase
if(NOT DEFINED APP_TYPE)
    # During requirements phase, use a default to allow component discovery
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        # This is the requirements phase - use default
        set(APP_TYPE "${DEFAULT_APP_TYPE}")
        message(STATUS "APP_TYPE not defined during requirements phase, using default: ${APP_TYPE}")
    else()
        # This is the actual build phase - fail with helpful error
        message(FATAL_ERROR 
            "APP_TYPE not defined. Please use build_app.sh to build this project.\n"
            "Example: ./scripts/build_app.sh ${DEFAULT_APP_TYPE} Release\n"
            "Use './scripts/build_app.sh list' to see available app types."
        )
    endif()
endif()

if(NOT DEFINED APP_SOURCE_FILE)
    # During requirements phase, use a default to allow component discovery
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        # This is the requirements phase - use default
        set(APP_SOURCE_FILE "${DEFAULT_SOURCE_FILE}")
        message(STATUS "APP_SOURCE_FILE not defined during requirements phase, using default: ${APP_SOURCE_FILE}")
    else()
        # This is the actual build phase - fail with helpful error
        message(FATAL_ERROR 
            "APP_SOURCE_FILE not defined. Please use build_app.sh to build this project.\n"
            "Example: ./scripts/build_app.sh ${DEFAULT_APP_TYPE} ${DEFAULT_BUILD_TYPE}\n"
            "Use './scripts/build_app.sh list' to see available app types."
        )
    endif()
endif()

# =============================================================================
# Build Configuration and Status Messages
# =============================================================================
message(STATUS "Building app type: ${APP_TYPE}")
message(STATUS "Using source file: ${APP_SOURCE_FILE}")

# =============================================================================
# Include Directories Configuration
# =============================================================================
# Set include paths relative to current repository structure (main is examples/esp32/main; driver root is ../../..)
set(INC_BASE_PATH "../../../inc")

# Define include directories for the main component
set(MAIN_INCLUDE_DIRS
    "."                                    # Current directory (main/)
    "${INC_BASE_PATH}"                     # Main driver headers
)

# =============================================================================
# Component Dependencies
# =============================================================================
# Define required ESP-IDF components for the main application
set(MAIN_REQUIRES
    driver              # ESP-IDF driver framework (SPI, GPIO)
    esp_timer           # ESP-IDF timer functionality
    freertos            # FreeRTOS for threading and synchronization
    spi_flash           # SPI flash (for ADS7952 SPI bus)
    nvs_flash           # NVS (optional for app use)
    hf_ads7952          # ADS7952 driver component
)

# =============================================================================
# Component Registration
# =============================================================================
# Register the main component with ESP-IDF build system
# Single app source (from build_app.sh); ESP32 bus implementation is header-only
idf_component_register(
    SRCS "${APP_SOURCE_FILE}"
    INCLUDE_DIRS ${MAIN_INCLUDE_DIRS}
    REQUIRES ${MAIN_REQUIRES}
)

# =============================================================================
# Compiler Configuration
# =============================================================================
# Set C++ standard (ADS7952 examples use C++20)
target_compile_features(${COMPONENT_LIB} PRIVATE cxx_std_20)

# =============================================================================
# Build Type Specific Compiler Flags
# =============================================================================
# Set compiler flags based on build type (Debug vs Release)
if(BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${COMPONENT_LIB} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -O0
        -g3
        -DDEBUG
        -DADS7952_DEBUG
    )
else()
    target_compile_options(${COMPONENT_LIB} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -O2
        -g
        -DNDEBUG
        -DADS7952_RELEASE
    )
endif()
