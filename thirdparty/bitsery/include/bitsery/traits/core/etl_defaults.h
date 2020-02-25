#ifndef MEMOC_PERSISTENCE_BITSERY_TRAITS_CORE_ETL_DEFAULTS_H
#define MEMOC_PERSISTENCE_BITSERY_TRAITS_CORE_ETL_DEFAULTS_H

#include <etl/type_traits.h>
#include <bitsery/traits/core/traits.h>
#include <bitsery/details/serialization_common.h>

namespace bitsery {
    namespace traits {

        /*
         * these are helper types, to easier write specializations for std types
         */

        template<typename T, bool Resizable, bool Contiguous>
        struct EtlContainer {
            using TValue = typename T::value_type;
            static constexpr bool isResizable = Resizable;
            static constexpr bool isContiguous = Contiguous;
            static size_t size(const T& container) {
                return container.size();
            }
        };

        //specialization for resizable
        template<typename T, bool Contiguous>
        struct EtlContainer<T, true, Contiguous> {
            using TValue = typename T::value_type;
            static constexpr bool isResizable = true;
            static constexpr bool isContiguous = Contiguous;
            static size_t size(const T& container) {
                return container.size();
            }
            static void resize(T& container, size_t size) {
                resizeImpl(container, size, etl::is_trivially_constructible<TValue>{});
            }
        private:
            static void resizeImpl(T& container, size_t size, std::true_type) {
                container.resize(size);
            }
            static void resizeImpl(T& container, size_t newSize, std::false_type) {
                const auto oldSize = size(container);
                for (auto it = oldSize; it < newSize; ++it) {
                    container.push_back(::bitsery::Access::create<TValue>());
                }
                if (oldSize > newSize) {
                    container.erase_at(newSize-1);
                }
            }

        };

        template <typename T, bool Resizable = ContainerTraits<T>::isResizable>
        struct EtlContainerForBufferAdapter {
            using TIterator = typename T::iterator;
            using TConstIterator = typename T::const_iterator;
            using TValue = typename ContainerTraits<T>::TValue;
        };

        //specialization for resizable buffers
        template <typename T>
        struct EtlContainerForBufferAdapter<T, true> {

            static void increaseBufferSize(T& container) {
                //since we're writing to buffer use different resize strategy than default implementation
                //when small size grow faster, to avoid thouse 2/4/8/16... byte allocations
                auto newSize = static_cast<size_t>(container.size() * 1.5 + 128);
                //make data cache friendly
                newSize -= newSize % 64;//64 is cache line size
                container.resize((std::min)(newSize, container.max_size()));
            }
            using TIterator = typename T::iterator;
            using TConstIterator = typename T::const_iterator;
            using TValue = typename ContainerTraits<T>::TValue;
        };

    }
}

#endif //BITSERY_TRAITS_CORE_STD_DEFAULTS_H