#include "pandalib.h"

extern "C" {
    String* pandaReal32ToString(Real32 r);

    String* pandaReal64ToString(Real64 r);

    Real32 pandaStringToReal32(String* s);

    Real64 pandaStringToReal32(String* s);
}