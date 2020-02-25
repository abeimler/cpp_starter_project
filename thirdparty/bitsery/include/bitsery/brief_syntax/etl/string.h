
#ifndef BITSERY_BRIEF_SYNTAX_TYPE_ETL_STRING_H
#define BITSERY_BRIEF_SYNTAX_TYPE_ETL_STRING_H

#include "../../traits/etl/string.h"
#include <bitsery/details/brief_syntax_common.h>

namespace bitsery {
    template<typename S, typename CharT>
    void serialize(S &s, etl::ibasic_string<CharT> &str) {
        brief_syntax::processContainer(s, str);
    }
    template<typename S, const size_t MAX_SIZE>
    void serialize(S &s, etl::string<MAX_SIZE> &str) {
        brief_syntax::processContainer(s, str);
    }
}

#endif // BITSERY_BRIEF_SYNTAX_TYPE_ETL_STRING_H