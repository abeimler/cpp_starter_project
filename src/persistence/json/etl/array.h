#ifndef PERSISTENCE_JSON_ETL_ARRAY_H
#define PERSISTENCE_JSON_ETL_ARRAY_H

#include <etl/array.h>
#include <nlohmann/json.hpp>

namespace nlohmann {

template<typename T, const size_t SIZE>
struct adl_serializer<etl::array<T, SIZE>>
{
  static void to_json(json &j, const etl::array<T, SIZE> &p)
  {
    j = std::array<T, SIZE>(p.begin(), p.end());
  }

  static void from_json(const json &j, etl::array<T, SIZE> &p)
  {
    auto arr = j.get<std::array<T, SIZE>>();
    p = etl::array<T, SIZE>(arr.begin(), arr.end());
  }
};

}// namespace nlohmann

#endif