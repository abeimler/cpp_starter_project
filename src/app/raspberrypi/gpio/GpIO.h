#ifndef GPIO_GPIO_H
#define GPIO_GPIO_H

#include <chrono>// for milliseconds
#include <cstddef>// for size_t
#include <cstdint>// for uint16_t, uint8_t
#include <etl/array.h>// for array
#include <etl/array_view.h>// for array_view
#include <etl/vector.h>
#include <type_traits>// for __underlying_type_impl<>::type, underlyi...
#include <unistd.h>

#if defined(USE_BCM2835)
#include <bcm2835.h>
#elif defined(USE_WIRING_PI)
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif

/**
 * @see: https://www.waveshare.com/wiki/1.44inch_LCD_HAT and
 * https://www.waveshare.com/wiki/File:1.44inch-LCD-HAT-Code.7z
 ***/
namespace gpio {

#if defined(USE_BCM2835)
constexpr bool USE_BCM2835_LIB = true;
constexpr bool USE_WIRINGPI_LIB = false;
#elif defined(USE_WIRING_PI)
constexpr bool USE_BCM2835_LIB = false;
constexpr bool USE_WIRINGPI_LIB = true;
#else
constexpr bool USE_BCM2835_LIB = false;
constexpr bool USE_WIRINGPI_LIB = false;
#endif

enum class PinMode : uint8_t {
  Input = 0,
  Output = 1,
  /*
  PWMOutput = 2,
  GPIOClock = 3,
  SOFTPWMOutput = 4,
  SOFTToneOutput = 5,
  PWMToneOutput = 6
  */
};

enum class PinLevel : uint8_t { Low = 0,
  High = 1 };

enum class InitSPI : uint8_t { SkipInitSPI,
  InitSPI };

class GpIO
{
public:
  using pin_t = uint16_t;
  using mode_t = uint16_t;
#if defined(USE_BCM2835)
  using delay_t = unsigned int;
#else
  using delay_t = uint32_t;
#endif
  using byte_t = uint8_t;

  static uint8_t init();
  static uint8_t initWithSPI(int spi_speed);
  static uint8_t spiSetup(int speed);

  template<typename GPIOInitFunc>
  uint8_t initWithSPI(int spi_speed, GPIOInitFunc initGPIO)
  {
    init();
    initGPIO(*this);
    return spiSetup(spi_speed);
  }

  void uninit();

  void digitalWrite(pin_t pin, byte_t value);
  static uint8_t digitalRead(pin_t pin);
  inline void digitalWrite(pin_t pin, PinLevel value)
  {
    this->digitalWrite(
      pin, static_cast<typename std::underlying_type<PinLevel>::type>(value));
  }

  void setGPIOMode(pin_t pin, mode_t mode);
  void setGPIOMode(pin_t pin, PinMode mode);
  inline void pinMode(pin_t pin, mode_t mode) { this->setGPIOMode(pin, mode); }
  inline void pinMode(pin_t pin, PinMode mode) { this->setGPIOMode(pin, mode); }

  static void delay_ms(delay_t ms);
  static void delay(std::chrono::milliseconds ms);

  void writeByte(pin_t pin, byte_t value);

  template<size_t MAX_RDATA_SIZE>
  void writeNBytes(pin_t pin, etl::array<byte_t, MAX_RDATA_SIZE> &data)
  {
#if defined(USE_BCM2835)
    etl::vector<uint8_t, MAX_RDATA_SIZE> rData;
    ::bcm2835_spi_chipSelect(pin);
    ::bcm2835_spi_transfernb(data.data(), rData, data.size());
#elif defined(USE_WIRING_PI)
    ::wiringPiSPIDataRW(pin, data.data(), data.size());
#endif
  }

  template<class DataArray>
  void writeNBytes(pin_t pin, DataArray &data)
  {
#if defined(USE_BCM2835)
    DataArray rData;
    rData.resize(data.size());
    ::bcm2835_spi_transfernb(data.data(), rData, data.size());
#elif defined(USE_WIRING_PI)
    ::wiringPiSPIDataRW(pin, data.data(), data.size());
#endif
  }
  template<class DataArray>
  void writeNBytes(pin_t pin, const DataArray &data)
  {
#if defined(USE_BCM2835)
    DataArray rData;
    rData.resize(data.size());
    auto data_copy = data;
    ::bcm2835_spi_transfernb(data_copy.data(), rData, data_copy.size());
#elif defined(USE_WIRING_PI)
    auto data_copy = data;
    ::wiringPiSPIDataRW(pin, data_copy.data(), data_copy.size());
#endif
  }
};

}// namespace gpio

#endif