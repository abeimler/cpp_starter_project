
#ifndef BITSERY_EXT_UNITS_H
#define BITSERY_EXT_UNITS_H

#include <bitsery/traits/core/traits.h>
#include <units.h>                 // for kilogram_t, meter_t

namespace bitsery {
    namespace ext {

        class UnitsLengthMeter {
        public:

            template<typename Ser, typename Fnc>
            void serialize(Ser& ser, const units::length::meter_t& obj, Fnc&& fnc) const {
                auto res = obj.value();
                fnc(ser, res);
            }

            template<typename Des, typename Fnc>
            void deserialize(Des& des, units::length::meter_t& obj, Fnc&& fnc) const {
                units::length::meter_t::value_type res{};
                fnc(des, res);
                obj = units::make_unit<units::length::meter_t>(res);
            }
        };

        class UnitsMassKilogram {
        public:

            template<typename Ser, typename Fnc>
            void serialize(Ser& ser, const units::mass::kilogram_t& obj, Fnc&& fnc) const {
                auto res = obj.value();
                fnc(ser, res);
            }

            template<typename Des, typename Fnc>
            void deserialize(Des& des, units::mass::kilogram_t& obj, Fnc&& fnc) const {
                units::mass::kilogram_t::value_type res{};
                fnc(des, res);
                obj = units::make_unit<units::mass::kilogram_t>(res);
            }
        };
    }

    namespace traits {
        template<>
        struct ExtensionTraits<ext::UnitsLengthMeter, units::length::meter_t> {
            using TValue = units::length::meter_t::value_type;
            static constexpr bool SupportValueOverload = true;
            static constexpr bool SupportObjectOverload = false;
            static constexpr bool SupportLambdaOverload = false;
        };

        template<>
        struct ExtensionTraits<ext::UnitsMassKilogram, units::mass::kilogram_t> {
            using TValue = units::mass::kilogram_t::value_type;
            static constexpr bool SupportValueOverload = true;
            static constexpr bool SupportObjectOverload = false;
            static constexpr bool SupportLambdaOverload = false;
        };
    }

}


#endif // BITSERY_EXT_UNITS_H