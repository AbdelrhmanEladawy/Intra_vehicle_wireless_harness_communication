
// F:/Pico_Project/Intra_vehicle_wireless_harness_communication/build/src/generated/le_central.h generated from F:/Pico_Project/Intra_vehicle_wireless_harness_communication/src/le_central.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated. 

// To generate F:/Pico_Project/Intra_vehicle_wireless_harness_communication/build/src/generated/le_central.h:
// F:/pico/pico-sdk/lib/btstack/tool/compile_gatt.py F:/Pico_Project/Intra_vehicle_wireless_harness_communication/src/le_central.gatt F:/Pico_Project/Intra_vehicle_wireless_harness_communication/build/src/generated/le_central.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#include <stdint.h>

// Reference: https://en.cppreference.com/w/cpp/feature_test
#if __cplusplus >= 200704L
constexpr
#endif
const uint8_t profile_data[] =
{
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME - READ
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE CHARACTERISTIC-GAP_DEVICE_NAME - READ -'SM LED Central'
    // READ_ANYBODY
    0x16, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x2a, 0x53, 0x4d, 0x20, 0x4c, 0x45, 0x44, 0x20, 0x43, 0x65, 0x6e, 0x74, 0x72, 0x61, 0x6c, 
    // 0x0004 PRIMARY_SERVICE-GATT_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x01, 0x18, 
    // 0x0005 CHARACTERISTIC-GATT_DATABASE_HASH - READ
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x02, 0x06, 0x00, 0x2a, 0x2b, 
    // 0x0006 VALUE CHARACTERISTIC-GATT_DATABASE_HASH - READ -''
    // READ_ANYBODY
    0x18, 0x00, 0x02, 0x00, 0x06, 0x00, 0x2a, 0x2b, 0x8b, 0x09, 0xd3, 0xba, 0x02, 0xd0, 0xd6, 0xd8, 0x82, 0x05, 0x94, 0x95, 0x27, 0xd1, 0xa5, 0x83, 
    // END
    0x00, 0x00, 
}; // total size 48 bytes 


//
// list service handle ranges
//
#define ATT_SERVICE_GAP_SERVICE_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_END_HANDLE 0x0003
#define ATT_SERVICE_GAP_SERVICE_01_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_01_END_HANDLE 0x0003
#define ATT_SERVICE_GATT_SERVICE_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_END_HANDLE 0x0006
#define ATT_SERVICE_GATT_SERVICE_01_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_01_END_HANDLE 0x0006

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_GATT_DATABASE_HASH_01_VALUE_HANDLE 0x0006
