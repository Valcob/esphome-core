#ifndef ESPHOMELIB_CONTROLLER_H
#define ESPHOMELIB_CONTROLLER_H

#include "esphomelib/binary_sensor/binary_sensor.h"
#include "esphomelib/fan/fan_state.h"
#include "esphomelib/light/light_state.h"
#include "esphomelib/sensor/sensor.h"
#include "esphomelib/switch_/switch.h"
#include "esphomelib/cover/cover.h"
#include "esphomelib/text_sensor/text_sensor.h"
#include "esphomelib/esp32_camera.h"
#include "esphomelib/defines.h"

ESPHOMELIB_NAMESPACE_BEGIN

/// Controllers allow an object to be notified of every component that's added to the Application.
class Controller {
 public:
#ifdef USE_BINARY_SENSOR
  virtual void register_binary_sensor(binary_sensor::BinarySensor *obj);
#endif

#ifdef USE_FAN
  virtual void register_fan(fan::FanState *obj);
#endif

#ifdef USE_LIGHT
  virtual void register_light(light::LightState *obj);
#endif

#ifdef USE_SENSOR
  virtual void register_sensor(sensor::Sensor *obj);
#endif

#ifdef USE_SWITCH
  virtual void register_switch(switch_::Switch *obj);
#endif

#ifdef USE_COVER
 virtual void register_cover(cover::Cover *cover);
#endif

#ifdef USE_TEXT_SENSOR
  virtual void register_text_sensor(text_sensor::TextSensor *obj);
#endif

#ifdef USE_ESP32_CAMERA
  virtual void register_camera(ESP32Camera *obj);
#endif
};

/// A StoringController is a controller that automatically stores all components internally in vectors.
class StoringController : public Controller {
 public:
#ifdef USE_BINARY_SENSOR
  void register_binary_sensor(binary_sensor::BinarySensor *obj) override;

  binary_sensor::BinarySensor *get_binary_sensor_by_key(uint32_t key);
#endif

#ifdef USE_FAN
  void register_fan(fan::FanState *obj) override;

  fan::FanState *get_fan_by_key(uint32_t key);
#endif

#ifdef USE_LIGHT
  void register_light(light::LightState *obj) override;

  light::LightState *get_light_by_key(uint32_t key);
#endif

#ifdef USE_SENSOR
  void register_sensor(sensor::Sensor *obj) override;

  sensor::Sensor *get_sensor_by_key(uint32_t key);
#endif

#ifdef USE_SWITCH
  void register_switch(switch_::Switch *obj) override;

  switch_::Switch *get_switch_by_key(uint32_t key);
#endif

#ifdef USE_COVER
  void register_cover(cover::Cover *cover) override;

  cover::Cover *get_cover_by_key(uint32_t key);
#endif

#ifdef USE_TEXT_SENSOR
  void register_text_sensor(text_sensor::TextSensor *obj) override;

  text_sensor::TextSensor *get_text_sensor_by_key(uint32_t key);
#endif

#ifdef USE_ESP32_CAMERA
  virtual void register_camera(ESP32Camera *obj);
#endif

#ifdef USE_BINARY_SENSOR
  std::vector<binary_sensor::BinarySensor *> binary_sensors_;
#endif

#ifdef USE_FAN
  std::vector<fan::FanState *> fans_;
#endif

#ifdef USE_LIGHT
  std::vector<light::LightState *> lights_;
#endif

#ifdef USE_SENSOR
  std::vector<sensor::Sensor *> sensors_;
#endif

#ifdef USE_SWITCH
  std::vector<switch_::Switch *> switches_;
#endif

#ifdef USE_COVER
  std::vector<cover::Cover *> covers_;
#endif

#ifdef USE_TEXT_SENSOR
  std::vector<text_sensor::TextSensor *> text_sensors_;
#endif

#ifdef USE_ESP32_CAMERA
  std::vector<ESP32Camera *> cameras_;
#endif
};

class StoringUpdateListenerController : public StoringController {
 public:
#ifdef USE_BINARY_SENSOR
  void register_binary_sensor(binary_sensor::BinarySensor *obj) override;

  virtual void on_binary_sensor_update(binary_sensor::BinarySensor *obj, bool state) = 0;
#endif
#ifdef USE_FAN
  void register_fan(fan::FanState *obj) override;

  virtual void on_fan_update(fan::FanState *obj) = 0;
#endif

#ifdef USE_LIGHT
  void register_light(light::LightState *obj) override;

  virtual void on_light_update(light::LightState *obj) = 0;
#endif

#ifdef USE_SENSOR
  void register_sensor(sensor::Sensor *obj) override;

  virtual void on_sensor_update(sensor::Sensor *obj, float state) = 0;
#endif

#ifdef USE_SWITCH
  void register_switch(switch_::Switch *obj) override;

  virtual void on_switch_update(switch_::Switch *obj, bool state) = 0;
#endif

#ifdef USE_COVER
  void register_cover(cover::Cover *obj) override;

  virtual void on_cover_update(cover::Cover *obj);
#endif

#ifdef USE_TEXT_SENSOR
  void register_text_sensor(text_sensor::TextSensor *obj) override;

  virtual void on_text_sensor_update(text_sensor::TextSensor *obj, std::string state) = 0;
#endif

#ifdef USE_ESP32_CAMERA
  void register_camera(ESP32Camera *obj) override;

  virtual void on_camera_update(ESP32Camera *obj);
#endif
};

ESPHOMELIB_NAMESPACE_END

#endif //ESPHOMELIB_CONTROLLER_H
