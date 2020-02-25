#ifndef PERSISTENCE_JSON_ETL_VECTOR_H
#define PERSISTENCE_JSON_ETL_VECTOR_H

#include <etl/vector.h>
#include <nlohmann/json.hpp>
#include <vector>

namespace nlohmann {

template<typename T, const size_t MAX_SIZE>
struct adl_serializer<etl::vector<T, MAX_SIZE>>
{
  static void to_json(json &j, const etl::vector<T, MAX_SIZE> &p)
  {
    j = std::vector<T>(p.begin(), p.end());
  }

  static void from_json(const json &j, etl::vector<T, MAX_SIZE> &p)
  {
    auto arr = j.get<std::vector<T>>();
    p = etl::vector<T, MAX_SIZE>(arr.begin(), arr.end());
  }
};

}// namespace nlohmann

#endif