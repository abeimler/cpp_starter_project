
#ifndef BITSERY_BRIEF_SYNTAX_TYPE_ETL_ARRAY_H
#define BITSERY_BRIEF_SYNTAX_TYPE_ETL_ARRAY_H

#include "../../traits/etl/array.h"
#include <bitsery/details/brief_syntax_common.h>

namespace bitsery {
template <typename S, typename T, const size_t N>
void serialize(S &s, etl::array<T, N> &obj) {
  brief_syntax::processContainer(s, obj);
}
} // namespace bitsery

#endif // BITSERY_BRIEF_SYNTAX_TYPE_ETL_ARRAY_H