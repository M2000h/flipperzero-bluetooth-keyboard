#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <furi_hal_version.h>

#define GAP_MAC_ADDR_SIZE (6)
#define GAP_KEY_SIZE      (0x10)

/*
 * GAP helpers - background thread that handles BLE GAP events and advertising.
 */

#ifdef __cplusplus
extern "C" {
#endif

//static const uint8_t adv_swift_bootstrap[] = {
//    0x02, 0x01, 0x06,

    // Swift Pair Manufacturer Specific Data:
    // len = 1(type) + 2(CID) + 3(03 00 80) + 10("Flipper KB") = 16 = 0x10
//    0x10, 0xFF,
//    0x06, 0x00, 0x03, 0x00, 0x80,
//    'F','l','i','p','p','e','r',' ','K','B',

//    0x02, 0x0A, 0x00,
//};


typedef enum {
    GapEventTypeConnected,
    GapEventTypeDisconnected,
    GapEventTypeStartAdvertising,
    GapEventTypeStopAdvertising,
    GapEventTypePinCodeShow,
    GapEventTypePinCodeVerify,
    GapEventTypeUpdateMTU,
    GapEventTypeBeaconStart,
    GapEventTypeBeaconStop,
} GapEventType;

typedef union {
    uint32_t pin_code;
    uint16_t max_packet_size;
} GapEventData;

typedef struct {
    GapEventType type;
    GapEventData data;
} GapEvent;

typedef bool (*GapEventCallback)(GapEvent event, void* context);

typedef enum {
    GapStateUninitialized,
    GapStateIdle,
    GapStateStartingAdv,
    GapStateAdvFast,
    GapStateAdvLowPower,
    GapStateConnected,
} GapState;

typedef enum {
    GapPairingNone,
    GapPairingPinCodeShow,
    GapPairingPinCodeVerifyYesNo,
} GapPairing;

typedef struct {
    uint16_t conn_interval;
    uint16_t slave_latency;
    uint16_t supervisor_timeout;
} GapConnectionParams;

typedef struct {
    uint16_t conn_int_min;
    uint16_t conn_int_max;
    uint16_t slave_latency;
    uint16_t supervisor_timeout;
} GapConnectionParamsRequest;

typedef struct {
    struct {
        uint8_t UUID_Type;
        uint16_t Service_UUID_16;
        uint8_t Service_UUID_128[16];
    } adv_service;
    uint8_t mfg_data[23];
    uint8_t mfg_data_len;
    uint16_t appearance_char;
    bool bonding_mode;
    GapPairing pairing_method;
    uint8_t mac_address[GAP_MAC_ADDR_SIZE];
    char adv_name[FURI_HAL_VERSION_DEVICE_NAME_LENGTH];
    GapConnectionParamsRequest conn_param;
    bool enable_swift_pair;   // NEW
    bool swift_pair_bootstrap;
} GapConfig;

typedef struct {
    // Encryption Root key. Must be unique per-device (or app)
    uint8_t erk[GAP_KEY_SIZE];
    // Identity Root key. Used for resolving RPAs, if configured
    uint8_t irk[GAP_KEY_SIZE];
} GapRootSecurityKeys;

bool gap_init(
    GapConfig* config,
    const GapRootSecurityKeys* root_keys,
    GapEventCallback on_event_cb,
    void* context);

void gap_start_advertising(void);

void gap_stop_advertising(void);

GapState gap_get_state(void);

void gap_thread_stop(void);

void gap_emit_ble_beacon_status_event(bool active);

#ifdef __cplusplus
}
#endif
