/**
 * @file ads7952_spi_interface.hpp
 * @brief CRTP-based SPI bus interface for ADS7952 driver
 * @copyright Copyright (c) 2024-2025 HardFOC. All rights reserved.
 */
#pragma once
#include <cstddef>
#include <cstdint>

namespace ads7952 {

/**
 * @brief CRTP-based template interface for SPI bus operations
 *
 * This template class provides a hardware-agnostic interface for SPI
 * communication using the CRTP pattern. Platform-specific implementations
 * should inherit from this template with themselves as the template parameter.
 *
 * Benefits of CRTP:
 * - Compile-time polymorphism (no virtual function overhead)
 * - Static dispatch instead of dynamic dispatch
 * - Better optimization opportunities for the compiler
 *
 * Example usage:
 * @code
 * class MySPI : public ads7952::SpiInterface<MySPI> {
 * public:
 *   void transfer(const uint8_t* tx, uint8_t* rx, std::size_t len) {
 *     // Platform-specific SPI implementation
 *   }
 * };
 * @endcode
 *
 * @tparam Derived The derived class type (CRTP pattern)
 */
template <typename Derived> class SpiInterface {
public:
  /**
   * @brief Perform a full-duplex SPI data transfer.
   *
   * Sends `len` bytes from `tx` and simultaneously receives `len` bytes into
   * `rx`. Implementations should assert the device's chip select for the
   * duration of the transfer.
   *
   * @param tx Pointer to data to transmit (len bytes). If nullptr, zeros can be
   * sent.
   * @param rx Pointer to buffer for received data (len bytes). If nullptr,
   * received data can be ignored.
   * @param len Number of bytes to transfer.
   */
  void transfer(const uint8_t *tx, uint8_t *rx, std::size_t len) {
    return static_cast<Derived *>(this)->transfer(tx, rx, len);
  }

  // Prevent copying
  SpiInterface(const SpiInterface &) = delete;
  SpiInterface &operator=(const SpiInterface &) = delete;

protected:
  /**
   * @brief Protected constructor to prevent direct instantiation
   */
  SpiInterface() = default;

  // Allow moving
  SpiInterface(SpiInterface &&) = default;
  SpiInterface &operator=(SpiInterface &&) = default;

  /**
   * @brief Protected destructor
   * @note Derived classes can have public destructors
   */
  ~SpiInterface() = default;
};

} // namespace ads7952
