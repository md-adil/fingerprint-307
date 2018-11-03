#include "Adafruit_Fingerprint.h"

const char * parseStatus(uint8_t t) {
    switch(t) {
        case FINGERPRINT_OK:
            return "FINGERPRINT_OK";
        case FINGERPRINT_PACKETRECIEVEERR:
            return "FINGERPRINT_PACKETRECIEVEERR";
        case FINGERPRINT_NOFINGER:
            return "FINGERPRINT_NOFINGER";
        case FINGERPRINT_IMAGEFAIL:
            return "FINGERPRINT_IMAGEFAIL";
        case FINGERPRINT_IMAGEMESS:
            return "FINGERPRINT_IMAGEMESS";
        case FINGERPRINT_FEATUREFAIL:
            return "FINGERPRINT_FEATUREFAIL";
        case FINGERPRINT_NOMATCH:
            return "FINGERPRINT_NOMATCH";
        case FINGERPRINT_NOTFOUND:
            return "FINGERPRINT_NOTFOUND";
        case FINGERPRINT_ENROLLMISMATCH:
            return "FINGERPRINT_ENROLLMISMATCH";
        case FINGERPRINT_BADLOCATION:
            return "FINGERPRINT_BADLOCATION";
        case FINGERPRINT_DBRANGEFAIL:
            return "FINGERPRINT_DBRANGEFAIL";
        case FINGERPRINT_UPLOADFEATUREFAIL:
            return "FINGERPRINT_UPLOADFEATUREFAIL";
        case FINGERPRINT_PACKETRESPONSEFAIL:
            return "FINGERPRINT_PACKETRESPONSEFAIL";
        case FINGERPRINT_UPLOADFAIL:
            return "FINGERPRINT_UPLOADFAIL";
        case FINGERPRINT_DELETEFAIL:
            return "FINGERPRINT_DELETEFAIL";
        case FINGERPRINT_DBCLEARFAIL:
            return "FINGERPRINT_DBCLEARFAIL";
        case FINGERPRINT_PASSFAIL:
            return "FINGERPRINT_PASSFAIL";
        case FINGERPRINT_INVALIDIMAGE:
            return "FINGERPRINT_INVALIDIMAGE";
        case FINGERPRINT_FLASHERR:
            return "FINGERPRINT_FLASHERR";
        case FINGERPRINT_INVALIDREG:
            return "FINGERPRINT_INVALIDREG";
        case FINGERPRINT_ADDRCODE:
            return "FINGERPRINT_ADDRCODE";
        case FINGERPRINT_PASSVERIFY:
            return "FINGERPRINT_PASSVERIFY";
        case FINGERPRINT_TIMEOUT:
            return "FINGERPRINT_TIMEOUT";
        case FINGERPRINT_BADPACKET:
            return "FINGERPRINT_BADPACKET";
        default:
            return "Unknow error";
    }
}