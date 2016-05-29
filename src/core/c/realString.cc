#include "dtoa/double-conversion.h"

extern "C" {

#include "pandalib.h"
#include "math.h"

using namespace double_conversion;

#define BUFFER_SIZE 40
#define INFINITY_STRING "infinity"
#define NAN_STRING "NaN"
#define EXP 'e'

String* panda$core$Real32Wrapper$pandaReal32ToString(Real32 r) {
    static DoubleToStringConverter* converter = new DoubleToStringConverter(0,
            INFINITY_STRING, NAN_STRING, EXP, -6, 21, 0, 0);
    char buffer[BUFFER_SIZE];
    StringBuilder result_builder(buffer, BUFFER_SIZE);
    converter->ToShortestSingle(r, &result_builder);
    char* result = result_builder.Finalize();
    return pandaNewString(result, strlen(result));
}

String* panda$core$Real64Wrapper$pandaReal64ToString(Real64 r) {
    static DoubleToStringConverter* converter = new DoubleToStringConverter(0,
            INFINITY_STRING, NAN_STRING, EXP, -6, 21, 0, 0);
    char buffer[BUFFER_SIZE];
    StringBuilder result_builder(buffer, BUFFER_SIZE);
    converter->ToShortest(r, &result_builder);
    char* result = result_builder.Finalize();
    return pandaNewString(result, strlen(result));
}

Real32 panda$core$String$pandaStringToReal32(String* s) {
    static StringToDoubleConverter* converter = new StringToDoubleConverter(0,
        NAN, NAN, INFINITY_STRING, NAN_STRING);
    char* buffer = pandaGetString(s);
    int count;
    double result = converter->StringToFloat(buffer, strlen(buffer), &count);
    return result;
}

Real64 panda$core$String$pandaStringToReal64_class_panda$core$String_$Rpanda$core$Real64(String* s) {
    static StringToDoubleConverter* converter = new StringToDoubleConverter(0,
        NAN, NAN, INFINITY_STRING, NAN_STRING);
    char* buffer = pandaGetString(s);
    int count;
    double result = converter->StringToDouble(buffer, strlen(buffer), &count);
    return result;
}

}