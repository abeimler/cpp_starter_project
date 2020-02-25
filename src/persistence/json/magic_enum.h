#ifndef PERSISTENCE_JSON_ENUM_ENUM_H
#define PERSISTENCE_JSON_ENUM_ENUM_H

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#define NLOHMANN_JSON_SERIALIZE_MAGIC_ENUM_LOWERCASE(ENUM_TYPE) \
  NLOHMANN_JSON_SERIALIZE_MAGIC_ENUM_LOWERCASE_2(ENUM_TYPE, true)

#define NLOHMANN_JSON_SERIALIZE_MAGIC_ENUM(ENUM_TYPE) \
  NLOHMANN_JSON_SERIALIZE_MAGIC_ENUM_LOWERCASE_2(ENUM_TYPE, false)

#define NLOHMANN_JSON_SERIALIZE_MAGIC_ENUM_LOWERCASE_2(ENUM_TYPE, lowercase)                                            \
  static_assert(std::is_same<decltype(lowercase), bool>::value,                                                         \
    "lowercase must be bool");                                                                                          \
  inline void to_json(nlohmann::json &j, const ENUM_TYPE &e)                                                            \
  {                                                                                                                     \
    static_assert(std::is_enum<ENUM_TYPE>::value,                                                                       \
      #ENUM_TYPE " must be an enum!");                                                                                  \
    if constexpr (lowercase) {                                                                                          \
      auto estr = magic_enum::enum_name(e);                                                                             \
      std::string str(std::begin(estr), std::end(estr));                                                                \
      std::transform(std::begin(str), std::end(str), std::begin(str), [](unsigned char c) { return std::tolower(c); }); \
      j = magic_enum::enum_name(e);                                                                                     \
    } else {                                                                                                            \
      j = magic_enum::enum_name(e);                                                                                     \
    }                                                                                                                   \
  }                                                                                                                     \
  inline void from_json(const nlohmann::json &j, ENUM_TYPE &e)                                                          \
  {                                                                                                                     \
    static_assert(std::is_enum<ENUM_TYPE>::value,                                                                       \
      #ENUM_TYPE " must be an enum!");                                                                                  \
    if constexpr (lowercase) {                                                                                          \
      auto estr = magic_enum::enum_name(e);                                                                             \
      std::string str(std::begin(estr), std::end(estr));                                                                \
      std::transform(std::begin(str), std::end(str), std::begin(str), [](unsigned char c) { return std::tolower(c); }); \
      auto me = magic_enum::enum_cast<ENUM_TYPE>(str);                                                                  \
      if (me.has_value()) {                                                                                             \
        e = me.value();                                                                                                 \
      }                                                                                                                 \
    } else {                                                                                                            \
      auto me = magic_enum::enum_cast<ENUM_TYPE>(j.get<std::string>());                                                 \
      if (me.has_value()) {                                                                                             \
        e = me.value();                                                                                                 \
      }                                                                                                                 \
    }                                                                                                                   \
  }

#endif