#ifndef PERSISTENCE_JSON_UTILS_UTILS_H
#define PERSISTENCE_JSON_UTILS_UTILS_H

#include <nlohmann/json.hpp>
#include <units.h>

namespace nlohmann {

template<>
struct adl_serializer<units::mass::kilogram_t>
{
  static void to_json(json &j, const units::mass::kilogram_t &p)
  {
    j = p.to<double>();
  }

  static void from_json(const json &j, units::mass::kilogram_t &p)
  {
    p = units::make_unit<units::mass::kilogram_t>(j.get<double>());
  }
};

template<>
struct adl_serializer<units::length::meter_t>
{
  static void to_json(json &j, const units::length::meter_t &p)
  {
    j = p.to<double>();
  }

  static void from_json(const json &j, units::length::meter_t &p)
  {
    p = units::make_unit<units::length::meter_t>(j.get<double>());
  }
};

}// namespace nlohmann

#endif