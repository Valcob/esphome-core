//
//  dht12_component.cpp
//  esphomelib
//
//  Created by Otto Winter on 17.05.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//
// Implementation based on:
//  - ESPEasy: https://github.com/letscontrolit/ESPEasy/blob/mega/src/_P034_DHT12.ino
//  - DHT12_sensor_library: https://github.com/xreef/DHT12_sensor_library/blob/master/DHT12.cpp

#include "esphomelib/sensor/dht12_component.h"
#include "esphomelib/log.h"

#ifdef USE_DHT12_SENSOR

ESPHOMELIB_NAMESPACE_BEGIN

namespace sensor {

static const char *TAG = "sensor.dht12";

static const uint8_t DHT12_I2C_ADDRESS = 0x5C;

DHT12Component::DHT12Component(I2CComponent *parent,
                               const std::string &temperature_name, const std::string &humidity_name,
                               uint32_t update_interval)
    : PollingComponent(update_interval), I2CDevice(parent, DHT12_I2C_ADDRESS),
      temperature_sensor_(new DHT12TemperatureSensor(temperature_name, this)),
      humidity_sensor_(new DHT12HumiditySensor(humidity_name, this)) {

}

void DHT12Component::update() {
  uint8_t data[5];
  if (!this->read_data_(data))
    return;
  const uint16_t raw_temperature = uint16_t(data[2]) * 10 + (data[3] & 0x7F);
  float temperature = raw_temperature / 10.0f;
  if ((data[3] & 0x80) != 0) {
    // negative
    temperature *= -1;
  }

  const uint16_t raw_humidity = uint16_t(data[0]) * 10 + data[1];
  float humidity = raw_humidity / 10.0f;

  ESP_LOGD(TAG, "Got temperature=%.2°C humidity=%.2f%%", temperature, humidity);
  this->temperature_sensor_->push_new_value(temperature);
  this->humidity_sensor_->push_new_value(humidity);
}
void DHT12Component::setup() {
  ESP_LOGD(TAG, "Setting up DHT12...");
  uint8_t data[5];
  if (!this->read_data_(data)) {
    ESP_LOGE(TAG, "Communication with DHT12 on 0x%02X failed!", this->address_);
    this->mark_failed();
    return;
  }
}
float DHT12Component::get_setup_priority() const {
  return setup_priority::HARDWARE_LATE;
}
bool DHT12Component::read_data_(uint8_t *data) {
  if (!this->read_bytes(0, data, 5)) {
    ESP_LOGW(TAG, "Updating DHT12 failed!");
    return false;
  }

  uint8_t checksum = data[0] + data[1] + data[2] + data[3];
  if (data[4] != checksum) {
    ESP_LOGW(TAG, "DHT12 Checksum invalid!");
    return false;
  }

  return true;
}
DHT12TemperatureSensor *DHT12Component::get_temperature_sensor() const {
  return this->temperature_sensor_;
}
DHT12HumiditySensor *DHT12Component::get_humidity_sensor() const {
  return this->humidity_sensor_;
}

} // namespace sensor

ESPHOMELIB_NAMESPACE_END

#endif //USE_DHT12_SENSOR
