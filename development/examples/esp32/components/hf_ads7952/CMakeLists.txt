###############################################################################
# HF ADS7952 Driver - ESP-IDF Component Wrapper
###############################################################################
# Purpose:
#   Adapt the generic, hardware-agnostic driver target contract to ESP-IDF's
#   component model using idf_component_register().
#
# Key Rule:
#   Do not duplicate source/include/dependency definitions here.
#   Always consume the shared build settings from driver root.
#
# Note:
#   cmake_minimum_required() is intentionally omitted here — ESP-IDF's
#   project.cmake already sets it and adding another can cause policy conflicts.
###############################################################################

# =============================================================================
# Shared Build Contract Import
# =============================================================================
set(HF_ADS7952_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../../.." CACHE PATH
    "Path to root of hf-ads7952-driver (auto-detected from component location)")

# Normalise and validate the resolved path
get_filename_component(HF_ADS7952_ROOT "${HF_ADS7952_ROOT}" ABSOLUTE)
if(NOT EXISTS "${HF_ADS7952_ROOT}/cmake/hf_ads7952_build_settings.cmake")
    message(FATAL_ERROR
        "Cannot find ADS7952 driver root.\n"
        "  Resolved path: ${HF_ADS7952_ROOT}\n"
        "  Expected file: ${HF_ADS7952_ROOT}/cmake/hf_ads7952_build_settings.cmake\n"
        "  Fix: set HF_ADS7952_ROOT to the correct driver checkout path.")
endif()

include("${HF_ADS7952_ROOT}/cmake/hf_ads7952_build_settings.cmake")

# =============================================================================
# ESP-IDF Component Registration
# =============================================================================
idf_component_register(
    SRCS ${HF_ADS7952_SOURCE_FILES}
    INCLUDE_DIRS ${HF_ADS7952_PUBLIC_INCLUDE_DIRS}
    REQUIRES ${HF_ADS7952_IDF_REQUIRES}
)

# =============================================================================
# C++ Standard Contract
# =============================================================================
if(HF_ADS7952_SOURCE_FILES)
    target_compile_features(${COMPONENT_LIB} PRIVATE cxx_std_20)
else()
    target_compile_features(${COMPONENT_LIB} INTERFACE cxx_std_20)
endif()
