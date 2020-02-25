#include "GpIO.h"
#include <ui/ui_util.h>

#if defined(USE_BCM2835)
#elif defined(USE_WIRING_PI)
#else
#include <thread>// for sleep
#endif

namespace gpio {

auto GpIO::init() -> uint8_t
{
#if defined(USE_BCM2835)
  if (!::bcm2835_init()) {
    ui::log_info("bcm2835 init failed  !!!");
    return 1;
  } else {
    ui::log_info("bcm2835 init success !!!");
  }
#elif defined(USE_WIRING_PI)
  if (::wiringPiSetupGpio() < 0) {// use BCM2835 Pin number table
    ui::log_info("set wiringPi lib failed	!!!");
    return 1;
  } else {
    ui::log_info("set wiringPi lib success  !!!");
  }
#else
  ui::log_info("no GPIO to init, do nothing !!!");
#endif
  return 0;
}

auto GpIO::spiSetup([[maybe_unused]] int spi_speed) -> uint8_t
{
#if defined(USE_BCM2835)
  ::bcm2835_spi_begin();// Start spi interface, set spi pin for the reuse
    // function
  ::bcm2835_spi_setBitOrder(
    BCM2835_SPI_BIT_ORDER_MSBFIRST);// High first transmission
  ::bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);// spi mode 0
  ::bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);// Frequency
  ::bcm2835_spi_chipSelect(BCM2835_SPI_CS0);// set CE0
  ::bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);// enable cs0
  return 0;
#elif defined(USE_WIRING_PI)
  if (!wiringPiSPISetup(0, spi_speed)) {
    ui::log_info("setup SPI init failed  !!!");
    return 1;
  } else {
    ui::log_info("setup SPI init success !!!");
  }
#else
  ui::log_info("no SPI to init, do nothing !!!");
#endif
  return 0;
}

auto GpIO::initWithSPI(int spi_speed) -> uint8_t
{
  init();
  return spiSetup(spi_speed);
}

void GpIO::uninit()
{
#if defined(USE_BCM2835)
  ::bcm2835_spi_end();
  ::bcm2835_close();
#elif defined(USE_WIRING_PI)
  /// nothing todo
#endif
}

void GpIO::digitalWrite([[maybe_unused]] pin_t pin,
  [[maybe_unused]] byte_t value)
{
#if defined(USE_BCM2835)
  ::bcm2835_gpio_write(pin, value);
#elif defined(USE_WIRING_PI)
  ::digitalWrite(pin, value);
#endif
}

auto GpIO::digitalRead([[maybe_unused]] pin_t pin) -> uint8_t
{
#if defined(USE_BCM2835)
  return ::bcm2835_gpio_lev(pin);
#elif defined(USE_WIRING_PI)
  return ::digitalRead(pin);
#else
  // do nothing
  return 0;
#endif
}

void GpIO::setGPIOMode([[maybe_unused]] pin_t pin,
  [[maybe_unused]] mode_t mode)
{
#if defined(USE_BCM2835)
  if (mode == 0 || mode == BCM2835_GPIO_FSEL_INPT) {
    ::bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
  } else {
    ::bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
  }
#elif defined(USE_WIRING_PI)
  if (mode == 0 || mode == INPUT) {
    ::pinMode(pin, INPUT);
    ::pullUpDnControl(pin, PUD_UP);
  } else {
    ::pinMode(pin, OUTPUT);
    // printf (" %d OUT \r\n",Pin);
  }
#endif
}

void GpIO::setGPIOMode([[maybe_unused]] pin_t pin,
  [[maybe_unused]] PinMode mode)
{
#if defined(USE_BCM2835)
  switch (mode) {
  case PinMode::Input:
    ::bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    break;
  case PinMode::Output:
    ::bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    break;
  }
#elif defined(USE_WIRING_PI)
  switch (mode) {
  case PinMode::Input:
    ::pinMode(pin, INPUT);
    ::pullUpDnControl(pin, PUD_UP);
    break;
  case PinMode::Output:
    ::pinMode(pin, OUTPUT);
    // printf (" %d OUT \r\n",Pin);
    break;
  }
#endif
}

void GpIO::delay_ms(delay_t ms)
{
#if defined(USE_BCM2835)
  ::bcm2835_delay(ms);
#elif defined(USE_WIRING_PI)
  ::delay(ms);
#else
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}
void GpIO::delay(std::chrono::milliseconds ms)
{
#if defined(USE_BCM2835)
  ::bcm2835_delay(ms.count());
#elif defined(USE_WIRING_PI)
  ::delay(ms.count());
#else
  std::this_thread::sleep_for(ms);
#endif
}

void GpIO::writeByte([[maybe_unused]] pin_t cs, [[maybe_unused]] byte_t value)
{
#if defined(USE_BCM2835)
  ::bcm2835_spi_chipSelect(cs);
  ::bcm2835_spi_transfer(value);
#elif defined(USE_WIRING_PI)
  ::wiringPiSPIDataRW(cs, &value, 1);
#endif
}

}// namespace gpio