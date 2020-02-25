
#ifndef BITSERY_BRIEF_SYNTAX_TYPE_ETL_VECTOR_H
#define BITSERY_BRIEF_SYNTAX_TYPE_ETL_VECTOR_H

#include "../../traits/etl/vector.h"
#include "bitsery/details/brief_syntax_common.h"

namespace bitsery {
    template<typename S, typename T, const size_t N>
    void serialize(S &s, etl::vector<T, N> &obj) {
        brief_syntax::processContainer(s, obj);
    }
}

#endif // BITSERY_BRIEF_SYNTAX_TYPE_ETL_VECTOR_H

