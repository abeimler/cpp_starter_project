
#ifndef BITSERY_TRAITS_ETL_STRING_H
#define BITSERY_TRAITS_ETL_STRING_H

#include "../core/etl_defaults.h"
#include <etl/cstring.h>

namespace bitsery {

    namespace traits {

        // specialization for string, because string is already included for std::char_traits

        template<typename CharT>
        struct ContainerTraits<etl::ibasic_string<CharT>>
            :public EtlContainer<etl::ibasic_string<CharT>, true, true> {};

        template <typename CharT>
        struct TextTraits<etl::ibasic_string<CharT>> {
            using TValue = typename ContainerTraits<etl::ibasic_string<CharT>>::TValue;
            //string is automatically null-terminated
            static constexpr bool addNUL = false;

            //is is not 100% accurate, but for performance reasons assume that string stores text, not binary data
            static size_t length(const etl::ibasic_string<CharT>& str) {
                return str.size();
            }
        };

        template<typename CharT>
        struct BufferAdapterTraits<etl::ibasic_string<CharT>>
                :public EtlContainerForBufferAdapter<etl::ibasic_string<CharT>> {};




        // specialization for string

        template<const size_t MAX_SIZE>
        struct ContainerTraits<etl::string<MAX_SIZE>>
            :public EtlContainer<etl::string<MAX_SIZE>, true, true> {};

        template <const size_t MAX_SIZE>
        struct TextTraits<etl::string<MAX_SIZE>> {
            using TValue = typename ContainerTraits<etl::string<MAX_SIZE>>::TValue;
            //string is automatically null-terminated
            static constexpr bool addNUL = false;

            //is is not 100% accurate, but for performance reasons assume that string stores text, not binary data
            static size_t length(const etl::string<MAX_SIZE>& str) {
                return str.size();
            }
        };

        template<const size_t MAX_SIZE>
        struct BufferAdapterTraits<etl::string<MAX_SIZE>>
                :public EtlContainerForBufferAdapter<etl::string<MAX_SIZE>> {};

    }

}

#endif // BITSERY_TRAITS_ETL_STRING_H