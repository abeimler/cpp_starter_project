#ifndef PERSISTENCE_JSON_ETL_CSTRING_H
#define PERSISTENCE_JSON_ETL_CSTRING_H

#include <etl/cstring.h>
#include <nlohmann/json.hpp>

namespace nlohmann {

template<const size_t MAX_SIZE>
struct adl_serializer<etl::string<MAX_SIZE>>
{
  static void to_json(json &j, const etl::string<MAX_SIZE> &p)
  {
    j = std::string(p.begin(), p.end());
  }

  static void from_json(const json &j, etl::string<MAX_SIZE> &p)
  {
    auto str = j.get<std::string>();
    p.assign(str.begin(), str.end());
  }
};

}// namespace nlohmann

#endif