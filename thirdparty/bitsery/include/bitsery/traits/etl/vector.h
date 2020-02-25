#ifndef BITSERY_TRAITS_ETL_VECTOR_H
#define BITSERY_TRAITS_ETL_VECTOR_H

#include "../core/etl_defaults.h"
#include <etl/vector.h>

namespace bitsery {

namespace traits {
template <typename T, const size_t MAX_SIZE>
struct ContainerTraits<etl::vector<T, MAX_SIZE>>
    : public EtlContainer<etl::vector<T, MAX_SIZE>, true, true> {};

// bool vector is not contiguous, do not copy it directly to buffer
template <const size_t MAX_SIZE>
struct ContainerTraits<etl::vector<bool, MAX_SIZE>>
    : public EtlContainer<etl::vector<bool, MAX_SIZE>, true, false> {};

template <typename T, const size_t MAX_SIZE>
struct BufferAdapterTraits<etl::vector<T, MAX_SIZE>>
    : public EtlContainerForBufferAdapter<etl::vector<T, MAX_SIZE>> {};

} // namespace traits

} // namespace bitsery

#endif // BITSERY_TRAITS_ETL_VECTOR_H