#ifndef BITSERY_TRAITS_ETL_ARRAY_H
#define BITSERY_TRAITS_ETL_ARRAY_H

#include "../core/etl_defaults.h"
#include <etl/array.h>

namespace bitsery {

namespace traits {
template <typename T, const size_t N>
struct ContainerTraits<etl::array<T, N>>
    : public EtlContainer<etl::array<T, N>, false, true> {};

template <typename T, const size_t N>
struct BufferAdapterTraits<etl::array<T, N>>
    : public EtlContainerForBufferAdapter<etl::array<T, N>> {};
} // namespace traits

} // namespace bitsery

#endif // BITSERY_TRAITS_ETL_ARRAY_H