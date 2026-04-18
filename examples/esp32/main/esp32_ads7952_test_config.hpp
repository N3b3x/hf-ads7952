/**
 * @file esp32_ads7952_test_config.hpp
 * @brief Hardware configuration for ADS7952 driver on ESP32
 * @ingroup ads7952_examples_support
 *
 * @details
 * This file contains the hardware and runtime configuration used by the ESP32
 * transport and example applications. Modify these values to match your board.
 */

#pragma once

#include <cstdint>

//==============================================================================
// COMPILE-TIME CONFIGURATION FLAGS
//==============================================================================

/**
 * @brief Enable detailed SPI transaction logging.
 *
 * When enabled (set to 1), Esp32Ads7952SpiBus logs per-transfer TX/RX bytes.
 * Set to 0 to reduce runtime log volume.
 */
#ifndef ESP32_ADS7952_ENABLE_DETAILED_SPI_LOGGING
#define ESP32_ADS7952_ENABLE_DETAILED_SPI_LOGGING 1
#endif

namespace ADS7952_TestConfig {

/**
 * @brief SPI Configuration for ESP32-S3
 *
 * These pins use SPI2_HOST native IOMUX on ESP32-S3.
 * GPIO10-13 are dedicated SPI2 pins for maximum performance.
 */
struct SPIPins {
    static constexpr uint8_t MISO = 13;          ///< GPIO13 - SPI2 MISO (native IOMUX)
    static constexpr uint8_t MOSI = 11;          ///< GPIO11 - SPI2 MOSI (native IOMUX)
    static constexpr uint8_t SCLK = 12;          ///< GPIO12 - SPI2 CLK (native IOMUX)
    static constexpr uint8_t CS   = 10;          ///< GPIO10 - SPI2 CS (native IOMUX)
};

/**
 * @brief SPI Communication Parameters
 *
 * The ADS7952 supports SPI frequencies up to 20MHz.
 *
 * SPI Mode: CPOL=0, CPHA=0 (Mode 0)
 * Data format: 16-bit frames
 */
struct SPIParams {
    static constexpr uint32_t FREQUENCY = 4000000;    ///< 4MHz SPI frequency (conservative default)
    static constexpr uint8_t MODE = 0;                ///< SPI Mode 0 (CPOL=0, CPHA=0)
    static constexpr uint8_t QUEUE_SIZE = 1;          ///< Transaction queue size
    static constexpr uint8_t CS_ENA_PRETRANS = 1;     ///< CS asserted N clock cycles before transaction
    static constexpr uint8_t CS_ENA_POSTTRANS = 1;    ///< CS held N clock cycles after transaction
    /// SPI host: 1 = SPI2_HOST (GPIO10-13 IOMUX on ESP32-S3)
    static constexpr uint8_t SPI_HOST_ID = 1;
};

/**
 * @brief ADC Specifications
 *
 * ADS7952 is a 12-channel, 12-bit SAR ADC.
 */
struct ADCSpecs {
    static constexpr uint8_t  NUM_CHANNELS    = 12;       ///< Number of analog input channels
    static constexpr uint8_t  RESOLUTION_BITS = 12;       ///< ADC resolution in bits
    static constexpr uint16_t MAX_COUNT       = 4095;     ///< Maximum ADC count (2^12 - 1)
    static constexpr float    VREF            = 2.5f;     ///< Reference voltage (V)
};

} // namespace ADS7952_TestConfig
