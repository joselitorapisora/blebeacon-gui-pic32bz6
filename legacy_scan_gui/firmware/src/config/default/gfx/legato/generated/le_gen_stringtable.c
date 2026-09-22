#include "gfx/legato/generated/le_gen_assets.h"

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   6
 *****************************************************************************/

/*****************************************************************************
 * string table data
 * 
 * this table contains the raw character data for each string
 * 
 * unsigned short - number of indices in the table
 * unsigned short - number of languages in the table
 * 
 * index array (size = number of indices * number of languages
 * 
 * for each index in the array:
 *   unsigned byte - the font ID for the index
 *   unsigned byte[3] - the offset of the string codepoint data in
 *                      the table
 * 
 * string data is found by jumping to the index offset from the start
 * of the table
 * 
 * string data entry:
 *     unsigned short - length of the string in bytes (encoding dependent)
 *     codepoint data - the string data
 ****************************************************************************/

const uint8_t stringTable_data[92] =
{
    0x06,0x00,0x01,0x00,0x01,0x1C,0x00,0x00,0x01,0x26,0x00,0x00,0x01,0x30,0x00,0x00,
    0x00,0x3E,0x00,0x00,0x00,0x44,0x00,0x00,0x01,0x54,0x00,0x00,0x07,0x00,0x43,0x6F,
    0x75,0x6E,0x74,0x65,0x72,0x00,0x07,0x00,0x4E,0x6F,0x64,0x65,0x20,0x49,0x44,0x00,
    0x0B,0x00,0x54,0x65,0x6D,0x70,0x65,0x72,0x61,0x74,0x75,0x72,0x65,0x00,0x03,0x00,
    0x2D,0x2D,0x2D,0x00,0x0E,0x00,0x50,0x49,0x43,0x33,0x32,0x2D,0x42,0x5A,0x36,0x20,
    0x44,0x65,0x6D,0x6F,0x06,0x00,0x53,0x77,0x69,0x74,0x63,0x68,
};

/* font asset pointer list */
leFont* fontList[2] =
{
    (leFont*)&aptos_light_l,
    (leFont*)&aptos_light_s,
};

const leStringTable stringTable =
{
    {
        LE_STREAM_LOCATION_ID_INTERNAL, // data location id
        (void*)stringTable_data, // data address pointer
        92, // data size
    },
    (void*)stringTable_data, // string table data
    fontList, // font lookup table
    LE_STRING_ENCODING_ASCII // encoding standard
};


// string list
leTableString string_CounterString;
leTableString string_IDString;
leTableString string_TemperatureString;
leTableString string_NullString;
leTableString string_TitleString;
leTableString string_SwitchString;

void initializeStrings(void)
{
    leTableString_Constructor(&string_CounterString, stringID_CounterString);
    leTableString_Constructor(&string_IDString, stringID_IDString);
    leTableString_Constructor(&string_TemperatureString, stringID_TemperatureString);
    leTableString_Constructor(&string_NullString, stringID_NullString);
    leTableString_Constructor(&string_TitleString, stringID_TitleString);
    leTableString_Constructor(&string_SwitchString, stringID_SwitchString);
}
