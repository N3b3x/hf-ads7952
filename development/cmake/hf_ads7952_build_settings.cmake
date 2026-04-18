#===============================================================================
# ADS7952 Driver - Build Settings
# Shared variables for target name, includes, sources, and dependencies.
# This file is the SINGLE SOURCE OF TRUTH for the driver version.
#===============================================================================

include_guard(GLOBAL)

# Target name
set(HF_ADS7952_TARGET_NAME "hf_ads7952")

#===============================================================================
# Versioning (single source of truth)
#===============================================================================
set(HF_ADS7952_VERSION_MAJOR 1)
set(HF_ADS7952_VERSION_MINOR 0)
set(HF_ADS7952_VERSION_PATCH 0)
set(HF_ADS7952_VERSION "${HF_ADS7952_VERSION_MAJOR}.${HF_ADS7952_VERSION_MINOR}.${HF_ADS7952_VERSION_PATCH}")

#===============================================================================
# Generate version header from template (into build directory)
#===============================================================================
# The generated header is placed in CMAKE_CURRENT_BINARY_DIR to keep the
# source tree clean.  This eliminates the need for a .gitignore entry and
# allows parallel builds with different version stamps.
set(HF_ADS7952_VERSION_TEMPLATE "${CMAKE_CURRENT_LIST_DIR}/../inc/ads7952_version.h.in")
set(HF_ADS7952_VERSION_HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}/hf_ads7952_generated")
set(HF_ADS7952_VERSION_HEADER     "${HF_ADS7952_VERSION_HEADER_DIR}/ads7952_version.h")

# Ensure the output directory exists before configure_file and before any
# consumer (e.g. ESP-IDF idf_component_register) validates include paths.
file(MAKE_DIRECTORY "${HF_ADS7952_VERSION_HEADER_DIR}")

if(EXISTS "${HF_ADS7952_VERSION_TEMPLATE}")
    configure_file(
        "${HF_ADS7952_VERSION_TEMPLATE}"
        "${HF_ADS7952_VERSION_HEADER}"
        @ONLY
    )
    message(STATUS "ADS7952 driver v${HF_ADS7952_VERSION} — generated ads7952_version.h in ${HF_ADS7952_VERSION_HEADER_DIR}")
else()
    message(WARNING "ads7952_version.h.in not found at ${HF_ADS7952_VERSION_TEMPLATE}")
endif()

#===============================================================================
# Public include directories
#===============================================================================
# Three include directories:
#   1. Source tree inc/ — hand-written headers (ads7952.hpp, etc.)
#   2. Source tree src/ — template implementation files (ads7952.ipp)
#   3. Build tree generated dir — configure_file outputs (ads7952_version.h)
set(HF_ADS7952_PUBLIC_INCLUDE_DIRS
    "${CMAKE_CURRENT_LIST_DIR}/../inc"
    "${CMAKE_CURRENT_LIST_DIR}/../src"
    "${HF_ADS7952_VERSION_HEADER_DIR}"
)

#===============================================================================
# Source files (empty for header-only)
#===============================================================================
set(HF_ADS7952_SOURCE_FILES)

#===============================================================================
# ESP-IDF component dependencies
#===============================================================================
set(HF_ADS7952_IDF_REQUIRES driver)
