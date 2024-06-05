#include "IRremote.h"

//==============================================================================
//    MMMMM  IIIII TTTTT   SSSS  U   U  BBBB   IIIII   SSSS  H   H  IIIII
//    M M M    I     T    S      U   U  B   B    I    S      H   H    I
//    M M M    I     T     SSS   U   U  BBBB     I     SSS   HHHHH    I
//    M   M    I     T        S  U   U  B   B    I        S  H   H    I
//    M   M  IIIII   T    SSSS    UUU   BBBBB  IIIII  SSSS   H   H  IIIII
//==============================================================================

// Looks like Sony except for timings, 48 chars of data and time/space different

#define MITSUBISHI_BITS 16

// Mitsubishi RM 75501
// 14200 7 41 7 42 7 42 7 17 7 17 7 18 7 41 7 18 7 17 7 17 7 18 7 41 8 17 7 17 7 18 7 17 7
// #define MITSUBISHI_HEADER_MARK	250  // seen range 3500
#define MITSUBISHI_HEADER_SPACE	350 //  7*50+100
#define MITSUBISHI_ONE_MARK	1950 // 41*50-100
#define MITSUBISHI_ZERO_MARK  750 // 17*50-100
// #define MITSUBISHI_DOUBLE_SPACE_USECS  800  // usually see 713 - not using ticks as get number wrap around
// #define MITSUBISHI_RPT_LENGTH 45000

//+=============================================================================
#if DECODE_MITSUBISHI
bool IRrecv::decodeMitsubishi() {
    // Serial.print("?!? decoding Mitsubishi:");Serial.print(irparams.rawlen); Serial.print(" want "); Serial.println( 2 * MITSUBISHI_BITS + 2);
    long data = 0;
    if (results.rawlen < 2 * MITSUBISHI_BITS + 2)
        return false;
    unsigned int offset = 1; // Skip first space
    // Initial space

#if 0
  // Put this back in for debugging - note can't use #DEBUG as if Debug on we don't see the repeat cos of the delay
  Serial.print("IR Gap: ");
  Serial.println( results.rawbuf[0]);
  Serial.println( "test against:");
  Serial.println(results.rawbuf[0]);
#endif

#if 0
  // Not seeing double keys from Mitsubishi
  if (results.rawbuf[0] < MITSUBISHI_DOUBLE_SPACE_USECS) {
    // Serial.print("IR Gap found: ");
    results.bits = 0;
    results.value = REPEAT;
    results.decode_type = MITSUBISHI;
    return true;
  }
#endif

    // Typical
    // 14200 7 41 7 42 7 42 7 17 7 17 7 18 7 41 7 18 7 17 7 17 7 18 7 41 8 17 7 17 7 18 7 17 7

    // Initial Space
    if (!MATCH_MARK(results.rawbuf[offset], MITSUBISHI_HEADER_SPACE))
        return false;
    offset++;

    while (offset + 1 < irparams.rawlen) {
        if (MATCH_MARK(results.rawbuf[offset], MITSUBISHI_ONE_MARK))
            data = (data << 1) | 1;
        else if (MATCH_MARK(results.rawbuf[offset], MITSUBISHI_ZERO_MARK))
            data <<= 1;
        else
            return false;
        offset++;

        if (!MATCH_SPACE(results.rawbuf[offset], MITSUBISHI_HEADER_SPACE))
            break;
        offset++;
    }

    // Success
    results.bits = (offset - 1) / 2;
    if (results.bits < MITSUBISHI_BITS) {
        results.bits = 0;
        return false;
    }

    results.value = data;
    results.decode_type = MITSUBISHI;
    return true;
}
bool IRrecv::decodeMitsubishi(decode_results *aResults) {
    bool aReturnValue = decodeMitsubishi();
    *aResults = results;
    return aReturnValue;
}
#endif

