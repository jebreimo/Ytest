//****************************************************************************
// Copyright © 2025 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2025-01-01
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <cstdint>

namespace ystring
{
    constexpr uint8_t ASCII_CHAR_CLASSES[] =
    {
        0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
        0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
        0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
        0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
        0x16, 0x11, 0x11, 0x11, 0x13, 0x11, 0x11, 0x11,
        0x0D, 0x0E, 0x11, 0x12, 0x11, 0x0C, 0x11, 0x11,
        0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
        0x08, 0x08, 0x11, 0x11, 0x12, 0x12, 0x12, 0x11,
        0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x0D, 0x11, 0x0E, 0x14, 0x0B,
        0x14, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x0D, 0x12, 0x0E, 0x12, 0x19
    };

    constexpr uint32_t COMPLETE_CHAR_CLASSES[] =
    {
        0x00010357, 0x00012254, 0x0001424E, 0x000151F2, 0x00016272,
        0x0001680D, 0x00017812, 0x0001C809, 0x0001D812, 0x0001F013,
        0x00020012, 0x0002D82E, 0x0002EA4F, 0x0002FAAC, 0x00030015,
        0x0003D84E, 0x0003EA6F, 0x0003F013, 0x00050357, 0x00050812,
        0x00053296, 0x00054255, 0x000552C5, 0x00056213, 0x00057376,
        0x000582B6, 0x00058813, 0x0005A175, 0x0005A802, 0x0005C255,
        0x0005D165, 0x0005D811, 0x0005F972, 0x0006B833, 0x0006F001,
        0x0007B853, 0x0007F802, 0x0009B401, 0x0009C002, 0x000A3C01,
        0x000A4802, 0x000BBC02, 0x000BC801, 0x000BEC01, 0x000C0002,
        0x000C1001, 0x000C2C02, 0x000C4022, 0x000C5801, 0x000C6802,
        0x000C9022, 0x000CA822, 0x000CC001, 0x000CD802, 0x000CF022,
        0x000D0001, 0x000D2C02, 0x000D3801, 0x000D4C01, 0x000D5802,
        0x000D6C02, 0x000D8022, 0x000D9801, 0x000DB402, 0x000DC001,
        0x000DD845, 0x000DE001, 0x000DF802, 0x000E20A1, 0x000E2803,
        0x000E3C01, 0x000E4003, 0x000E5401, 0x000E5803, 0x000EDC01,
        0x000EE802, 0x000F7401, 0x000F8841, 0x000F9003, 0x000FAC02,
        0x000FC001, 0x00119401, 0x0011C802, 0x0011E022, 0x0011F001,
        0x00120002, 0x00121402, 0x00123001, 0x00127401, 0x0014A045,
        0x00157802, 0x00160804, 0x00162815, 0x00168804, 0x0016F815,
        0x00172004, 0x001762A4, 0x001772A4, 0x0017F815, 0x001B7806,
        0x001B9C02, 0x001BA895, 0x001BBC02, 0x001BD3C4, 0x001BF052,
        0x001BF801, 0x001C181E, 0x001C32A1, 0x001C3812, 0x001C583E,
        0x001C683E, 0x001C8022, 0x001D103E, 0x001D5801, 0x001E7841,
        0x001E8802, 0x001EA001, 0x001EB802, 0x001F7401, 0x001F9802,
        0x001FAC02, 0x001FB013, 0x001FC402, 0x001FD001, 0x001FE002,
        0x00217801, 0x0022F802, 0x00240C02, 0x00241016, 0x00243806,
        0x00244808, 0x0025FC02, 0x00260801, 0x00266C01, 0x00267802,
        0x00297C02, 0x0029801E, 0x002AB001, 0x002ACBC4, 0x002AF812,
        0x002C4852, 0x002C500D, 0x002C601E, 0x002C7AD4, 0x002C801E,
        0x002DF0CD, 0x002E00D2, 0x002E18D2, 0x002E30D2, 0x002E3806,
        0x002E781E, 0x002F5005, 0x002F701E, 0x002F9005, 0x002FA012,
        0x002FF81E, 0x0030281B, 0x00304013, 0x00305A54, 0x00306812,
        0x00307816, 0x0030D8D2, 0x0030E01B, 0x0030F812, 0x003200A4,
        0x00325005, 0x0032F806, 0x00334809, 0x00336812, 0x003380A6,
        0x0036A0B2, 0x0036A805, 0x0036E8DB, 0x0036F016, 0x00372006,
        0x00373004, 0x003748D6, 0x00376806, 0x00377805, 0x0037C809,
        0x0037E005, 0x0037FAC5, 0x0038725E, 0x00388365, 0x00388806,
        0x00397805, 0x003A5006, 0x003A601E, 0x003D2805, 0x003D88C5,
        0x003DF81E, 0x003E4809, 0x003F5005, 0x003F9806, 0x003FB096,
        0x003FD244, 0x003FEBC6, 0x003FF814, 0x0040A805, 0x0040D0C4,
        0x004120C4, 0x004140C4, 0x00416806, 0x0041781E, 0x0041FA5E,
        0x0042C005, 0x0042D806, 0x0042F3D2, 0x0042F81E, 0x00435005,
        0x0043781E, 0x004440B5, 0x004478BE, 0x0044881B, 0x0044B01E,
        0x0044F806, 0x004648A4, 0x004710DB, 0x004818C7, 0x0049D0A6,
        0x0049E0E6, 0x0049E805, 0x004A0007, 0x004A4006, 0x004A68E6,
        0x004A80E5, 0x004AB806, 0x004B0805, 0x004B1806, 0x004B2812,
        0x004B8132, 0x004B8804, 0x004C08A6, 0x004C20FE, 0x004C6005,
        0x004C701E, 0x004C8005, 0x004C901E, 0x004D48BE, 0x004D88BE,
        0x004D9005, 0x004DA81E, 0x004DC805, 0x004DE3C6, 0x004DE805,
        0x004E0007, 0x004E2006, 0x004E301E, 0x004E4007, 0x004E501E,
        0x004E68E6, 0x004E7005, 0x004EBBC7, 0x004ED81E, 0x004EF0BE,
        0x004F0805, 0x004F1806, 0x004F281E, 0x004F7809, 0x004F8805,
        0x004F9814, 0x004FD176, 0x004FE285, 0x004FF246, 0x0050001E,
        0x005018C7, 0x0050201E, 0x00505005, 0x0050701E, 0x00508005,
        0x0050901E, 0x005148BE, 0x005188BE, 0x0051A0BE, 0x0051B8BE,
        0x0051C805, 0x0051E3C6, 0x0051E81E, 0x00520007, 0x00521006,
        0x0052301E, 0x00524006, 0x0052501E, 0x00526806, 0x00528BC6,
        0x0052C01E, 0x0052E8BE, 0x0052F005, 0x0053281E, 0x00537809,
        0x00538806, 0x0053A8A6, 0x0053B012, 0x0054001E, 0x005418C7,
        0x0054201E, 0x005470BE, 0x005490BE, 0x005548BE, 0x005588BE,
        0x0055A0BE, 0x0055C805, 0x0055E3C6, 0x0055E805, 0x00560007,
        0x005630DE, 0x005648C7, 0x0056501E, 0x005668E6, 0x005683C5,
        0x0056F81E, 0x00570805, 0x00571806, 0x0057281E, 0x00578132,
        0x00578814, 0x0057CBC5, 0x005800DE, 0x00580806, 0x005820FE,
        0x00586005, 0x0058701E, 0x00588005, 0x0058901E, 0x005948BE,
        0x005988BE, 0x0059A0BE, 0x0059C805, 0x0059E3C6, 0x0059F0A7,
        0x005A00C7, 0x005A2006, 0x005A301E, 0x005A4007, 0x005A501E,
        0x005A68E6, 0x005AA01E, 0x005AB8C7, 0x005AD81E, 0x005AF0BE,
        0x005B0805, 0x005B1806, 0x005B281E, 0x005B8136, 0x005B8805,
        0x005BB80B, 0x005C13C6, 0x005C20BE, 0x005C5005, 0x005C681E,
        0x005C88BE, 0x005CA805, 0x005CC01E, 0x005CD8BE, 0x005CE8BE,
        0x005CF805, 0x005D101E, 0x005D2005, 0x005D381E, 0x005D5005,
        0x005D681E, 0x005DC805, 0x005DE81E, 0x005E00E6, 0x005E1007,
        0x005E281E, 0x005E48FE, 0x005E68E6, 0x005E83C5, 0x005EBBC7,
        0x005F281E, 0x005F7809, 0x005F900B, 0x005FCAD4, 0x005FD016,
        0x006003C6, 0x006020E6, 0x006068BE, 0x006088BE, 0x006148BE,
        0x0061C805, 0x0061E3C6, 0x0061E805, 0x00620006, 0x006228FE,
        0x006248DE, 0x00626806, 0x0062A01E, 0x0062B8DE, 0x0062D005,
        0x0062EBC5, 0x0062F81E, 0x00630805, 0x00631806, 0x0063281E,
        0x00637809, 0x0063BBD2, 0x0063F976, 0x006408A6, 0x006420F2,
        0x006468BE, 0x006488BE, 0x006548BE, 0x0065A0BE, 0x0065C805,
        0x0065E3C6, 0x0065F0A7, 0x0065F806, 0x006628FE, 0x00663006,
        0x006648FE, 0x00665807, 0x00666806, 0x0066A01E, 0x0066B007,
        0x0066E01E, 0x0066F8BE, 0x00670805, 0x00671806, 0x0067281E,
        0x0067813E, 0x006798A7, 0x0067F81E, 0x00680806, 0x00681807,
        0x006868BE, 0x006888BE, 0x0069D005, 0x0069E8C5, 0x006A0007,
        0x006A28DE, 0x006A48FE, 0x006A68E6, 0x006A78B6, 0x006A981E,
        0x006AB8A7, 0x006AF00B, 0x006B0805, 0x006B1806, 0x006B281E,
        0x006B7809, 0x006BC976, 0x006C00BE, 0x006C0806, 0x006C20FE,
        0x006CB005, 0x006CC81E, 0x006D90BE, 0x006DE0BE, 0x006DE805,
        0x006DF81E, 0x006E3005, 0x006E53C6, 0x006E701E, 0x006E8807,
        0x006EA8DE, 0x006EB8DE, 0x006EF807, 0x006F281E, 0x006F7809,
        0x006F881E, 0x006FA0F2, 0x0070001E, 0x007188A6, 0x00719805,
        0x0071D006, 0x0071FBD4, 0x007230A4, 0x007278D2, 0x0072C809,
        0x0072D812, 0x0074001E, 0x007418BE, 0x007428BE, 0x007458BE,
        0x007520BE, 0x007530BE, 0x007588A6, 0x00759805, 0x0075E8C5,
        0x0075F81E, 0x007628BE, 0x0076389E, 0x007678DE, 0x0076C809,
        0x0076D81E, 0x0076F805, 0x007803C5, 0x00781816, 0x00789A56,
        0x0078A012, 0x0078B816, 0x0078C806, 0x0078F816, 0x00794809,
        0x0079A176, 0x0079B0D6, 0x0079C0D6, 0x0079D0CE, 0x0079E1EE,
        0x0079E80F, 0x0079F807, 0x007A40BE, 0x007B6005, 0x007B801E,
        0x007BF8C7, 0x007C28D2, 0x007C3806, 0x007C6005, 0x007CC0DE,
        0x007DE8DE, 0x007E32C6, 0x007E6ADE, 0x007E7816, 0x007EA012,
        0x007EC016, 0x007ED012, 0x007FF81E, 0x00815005, 0x00816007,
        0x008188C7, 0x0081C0C7, 0x0081D006, 0x0081E007, 0x0081F8C5,
        0x00824809, 0x00827812, 0x0082A805, 0x0082B807, 0x0082C806,
        0x0082E805, 0x008308C5, 0x00832007, 0x00833005, 0x00836807,
        0x00838005, 0x0083A006, 0x008410A6, 0x00842007, 0x00843006,
        0x008468E6, 0x008478A7, 0x0084C809, 0x0084E8E6, 0x0084F816,
        0x0086303E, 0x00863801, 0x00866BC1, 0x0086781E, 0x0087D852,
        0x0087E004, 0x0087F802, 0x009248BE, 0x00926805, 0x0092781E,
        0x0092B8BE, 0x0092C8BE, 0x0092E805, 0x0092F81E, 0x009448BE,
        0x00946805, 0x0094781E, 0x009588BE, 0x0095A805, 0x0095B81E,
        0x0095F8BE, 0x009608BE, 0x00962805, 0x0096381E, 0x0096B8BE,
        0x009888BE, 0x0098A805, 0x0098B81E, 0x009AD005, 0x009AE01E,
        0x009AF806, 0x009B4012, 0x009BE00B, 0x009BF81E, 0x009C7805,
        0x009CC816, 0x009CF81E, 0x009FA801, 0x009FB81E, 0x009FE802,
        0x00A003CD, 0x00B368B6, 0x00B37012, 0x00B400B7, 0x00B4D8AE,
        0x00B4E00F, 0x00B4F81E, 0x00B75005, 0x00B76812, 0x00B7800A,
        0x00B7C005, 0x00B7F81E, 0x00B88805, 0x00B8A8C7, 0x00B8F01E,
        0x00B98805, 0x00B9A0C7, 0x00B9B012, 0x00B9F81E, 0x00BA8805,
        0x00BA9806, 0x00BAF81E, 0x00BB68BE, 0x00BB88BE, 0x00BB9806,
        0x00BBF81E, 0x00BD9805, 0x00BDB0C7, 0x00BDE806, 0x00BE30E6,
        0x00BE4007, 0x00BE9806, 0x00BEBA44, 0x00BEDA54, 0x00BEE8A6,
        0x00BEF81E, 0x00BF4809, 0x00BF781E, 0x00BFC80B, 0x00BFF81E,
        0x00C0324D, 0x00C05012, 0x00C070DB, 0x00C07806, 0x00C0C809,
        0x00C0F81E, 0x00C218A4, 0x00C3C005, 0x00C3F81E, 0x00C42005,
        0x00C43006, 0x00C548A6, 0x00C55005, 0x00C5781E, 0x00C7A805,
        0x00C7F81E, 0x00C8F8BE, 0x00C91006, 0x00C93007, 0x00C94006,
        0x00C95807, 0x00C9781E, 0x00C990E6, 0x00C9C007, 0x00C9D806,
        0x00CA03D6, 0x00CA181E, 0x00CA2812, 0x00CA7809, 0x00CB6805,
        0x00CB781E, 0x00CBA005, 0x00CBF81E, 0x00CD5805, 0x00CD781E,
        0x00CE4805, 0x00CE781E, 0x00CED12B, 0x00CEE81E, 0x00CFF816,
        0x00D0B005, 0x00D0C006, 0x00D0D8E6, 0x00D0E81E, 0x00D0F812,
        0x00D2A8A7, 0x00D2B8C7, 0x00D2F8DE, 0x00D308C7, 0x00D31006,
        0x00D32007, 0x00D36006, 0x00D39007, 0x00D3E006, 0x00D3FBC6,
        0x00D44809, 0x00D4781E, 0x00D4C809, 0x00D4F81E, 0x00D53A44,
        0x00D56812, 0x00D5781E, 0x00D5F0C8, 0x00D67006, 0x00D7F81E,
        0x00D820C7, 0x00D9A0A6, 0x00D9A807, 0x00D9D8C7, 0x00D9E006,
        0x00DA10E6, 0x00DA2007, 0x00DA68BE, 0x00DA7812, 0x00DAC809,
        0x00DB0012, 0x00DB5016, 0x00DB9806, 0x00DBE016, 0x00DBF812,
        0x00DC10C7, 0x00DD08A7, 0x00DD2806, 0x00DD3807, 0x00DD50C7,
        0x00DD6806, 0x00DD7805, 0x00DDC809, 0x00DF30A6, 0x00DF3807,
        0x00DF4806, 0x00DF68E6, 0x00DF7007, 0x00DF8806, 0x00DF9807,
        0x00DFD81E, 0x00DFF812, 0x00E11805, 0x00E15807, 0x00E19806,
        0x00E1A807, 0x00E1B806, 0x00E1D01E, 0x00E1F812, 0x00E24809,
        0x00E2601E, 0x00E27805, 0x00E2C809, 0x00E3B805, 0x00E3E804,
        0x00E3F812, 0x00E44002, 0x00E45402, 0x00E4781E, 0x00E5D001,
        0x00E5E01E, 0x00E5F801, 0x00E63812, 0x00E6781E, 0x00E698D2,
        0x00E708C7, 0x00E74006, 0x00E768A6, 0x00E7A0A6, 0x00E7B8A7,
        0x00E7D0C5, 0x00E7F81E, 0x00E95802, 0x00EB5004, 0x00EBC044,
        0x00ECD002, 0x00EDF804, 0x00EFF806, 0x00F4A401, 0x00F4E802,
        0x00F7F401, 0x00F83802, 0x00F87801, 0x00F8A802, 0x00F8B81E,
        0x00F8E801, 0x00F8F81E, 0x00F93802, 0x00F97801, 0x00F9B802,
        0x00F9F801, 0x00FA2802, 0x00FA381E, 0x00FA6801, 0x00FA781E,
        0x00FAC05E, 0x00FAD03E, 0x00FAE03E, 0x00FAF03E, 0x00FAF801,
        0x00FB3802, 0x00FB7801, 0x00FBE802, 0x00FBF81E, 0x00FC3802,
        0x00FC7803, 0x00FCB802, 0x00FCF803, 0x00FD3802, 0x00FD7803,
        0x00FDA85E, 0x00FDB802, 0x00FDE023, 0x00FDF2A2, 0x00FE0815,
        0x00FE285E, 0x00FE3802, 0x00FE6023, 0x00FE7815, 0x00FE9802,
        0x00FEA81E, 0x00FEB802, 0x00FEE03E, 0x00FEF815, 0x00FF3802,
        0x00FF6001, 0x00FF7815, 0x00FF881E, 0x00FFA85E, 0x00FFB802,
        0x00FFE023, 0x00FFFABE, 0x01005017, 0x0100781B, 0x0100A80D,
        0x0100C250, 0x0100D22E, 0x0100EA11, 0x0100F9D0, 0x01014258,
        0x01014819, 0x01017B77, 0x0101CA50, 0x0101D011, 0x0101F012,
        0x0102000C, 0x01022253, 0x010231CF, 0x01029253, 0x0102A24C,
        0x0102FA57, 0x01032B7E, 0x0103836B, 0x01038804, 0x0103981E,
        0x0103C80B, 0x0103EA6E, 0x0103F9E4, 0x0104480B, 0x01046A6E,
        0x010479FE, 0x0104E004, 0x0104F81E, 0x01060014, 0x0106781E,
        0x0106E006, 0x01070906, 0x01072008, 0x01078006, 0x0107F81E,
        0x010812C1, 0x01083AC1, 0x010852C2, 0x01086801, 0x01087802,
        0x01089822, 0x0108AAC1, 0x0108C2D3, 0x0108E801, 0x010922C1,
        0x010932C1, 0x010942C1, 0x01094816, 0x01097036, 0x01097802,
        0x0109A022, 0x0109C8A2, 0x0109D816, 0x0109E802, 0x0109F801,
        0x010A2A61, 0x010A5056, 0x010A5813, 0x010A72C2, 0x010A7816,
        0x010AF80B, 0x010C100A, 0x010C2402, 0x010C494B, 0x010C5816,
        0x010C781E, 0x010CA013, 0x010CC816, 0x010CD813, 0x010D02D3,
        0x010D1AD3, 0x010D32D3, 0x010D72D3, 0x010E6816, 0x010E7813,
        0x010E92D3, 0x010EA2D3, 0x010F9816, 0x0117F813, 0x011842CE,
        0x011851EE, 0x0118580F, 0x0118F816, 0x01190813, 0x01194ACE,
        0x0119500F, 0x011BE2D3, 0x011CD016, 0x011D9813, 0x011ED816,
        0x011F0813, 0x01214816, 0x0121F81E, 0x01225016, 0x0122F81E,
        0x0124D80B, 0x01274816, 0x0127F80B, 0x012DBAD3, 0x012E0AD3,
        0x012FB816, 0x012FF813, 0x01337AD3, 0x013B42CE, 0x013B51EE,
        0x013B61EE, 0x013B71EE, 0x013B81EE, 0x013B91EE, 0x013BA1EE,
        0x013BA80F, 0x013C980B, 0x013DF816, 0x013E2A6E, 0x013E300F,
        0x013F326E, 0x013F41EE, 0x013F51EE, 0x013F61EE, 0x013F71EE,
        0x013F780F, 0x013FF813, 0x0147F816, 0x014C1A6E, 0x014C29EE,
        0x014C39EE, 0x014C49EE, 0x014C59EE, 0x014C69EE, 0x014C79EE,
        0x014C89EE, 0x014C99EE, 0x014CA9EE, 0x014CB9EE, 0x014CC00F,
        0x014EC26E, 0x014ED1EE, 0x014ED80F, 0x014FE26E, 0x014FE80F,
        0x0157F813, 0x01597816, 0x015A2013, 0x015A3016, 0x015A6013,
        0x015B9816, 0x015BA81E, 0x015CB2DE, 0x015FF816, 0x01617801,
        0x0162F802, 0x01630C02, 0x01632001, 0x01633002, 0x01636402,
        0x01638001, 0x01639401, 0x0163A841, 0x0163D802, 0x0163E804,
        0x01640001, 0x01671401, 0x01672002, 0x01675016, 0x01677402,
        0x01678806, 0x01679C02, 0x0167C01E, 0x0167EA4B, 0x0167F812,
        0x0169305E, 0x01693802, 0x01696BC2, 0x0169781E, 0x016B3805,
        0x016B7BC4, 0x016B8012, 0x016BFBC6, 0x016CB005, 0x016CF81E,
        0x016D38BE, 0x016D78BE, 0x016DB8BE, 0x016DF8BE, 0x016E38BE,
        0x016E78BE, 0x016EB8BE, 0x016EF8BE, 0x016FF806, 0x01701250,
        0x01702230, 0x01702811, 0x01704A50, 0x01705A32, 0x01706A11,
        0x0170BA4D, 0x0170D24D, 0x0170E250, 0x0170E811, 0x01710250,
        0x0171122E, 0x017121EE, 0x017131EE, 0x017141EE, 0x0171480F,
        0x01717A44, 0x0171C812, 0x0171D80D, 0x0172024D, 0x0172124E,
        0x01727812, 0x01728816, 0x0172AA4E, 0x0172B9EE, 0x0172C9EE,
        0x0172D9EE, 0x0172E9ED, 0x0173F81E, 0x0174D2DE, 0x01779816,
        0x0177F81E, 0x017EA816, 0x017F781E, 0x018002D7, 0x01802256,
        0x01803085, 0x0180414E, 0x018051EE, 0x018061EE, 0x018071EE,
        0x018081EE, 0x0180880F, 0x0180A2CE, 0x0180B1EE, 0x0180C1EE,
        0x0180D1EE, 0x0180E1ED, 0x0180E80E, 0x018101F6, 0x0181480A,
        0x01816806, 0x018180ED, 0x0181A804, 0x0181B816, 0x0181D944,
        0x0181E8B2, 0x018202DE, 0x0184B005, 0x0184C01E, 0x0184D006,
        0x0184E015, 0x0184F885, 0x0185000D, 0x0187D8B2, 0x0187F885,
        0x0188201E, 0x018980BE, 0x018C78BE, 0x018C8816, 0x018CA80B,
        0x018CF816, 0x018DF805, 0x018F2816, 0x018F7BD6, 0x018FF805,
        0x0190FADE, 0x0191480B, 0x01923816, 0x01928176, 0x0192F80B,
        0x0193F816, 0x0194480B, 0x01958016, 0x0195F80B, 0x01A002C5,
        0x026DFBC5, 0x027002C5, 0x04FFF01E, 0x0500A8A4, 0x05246005,
        0x0524781E, 0x05263016, 0x0526781E, 0x0527B805, 0x0527E804,
        0x0527F812, 0x053060A4, 0x05307812, 0x0530F805, 0x05314809,
        0x05315805, 0x0531F81E, 0x05336C02, 0x053378A6, 0x05339912,
        0x0533F0D2, 0x0533F804, 0x0534DC02, 0x0534E804, 0x0534F806,
        0x05372805, 0x0537780A, 0x05378806, 0x0537B812, 0x0537F81E,
        0x0538B015, 0x0538F804, 0x05390815, 0x05397401, 0x05398802,
        0x053B7C02, 0x053B8004, 0x053BC002, 0x053BE402, 0x053BF001,
        0x053C3C02, 0x053C4004, 0x053C5015, 0x053C7402, 0x053C7805,
        0x053C9401, 0x053CA802, 0x053D4C02, 0x053D7822, 0x053DA001,
        0x053E1C02, 0x053E3801, 0x053E5402, 0x053E6822, 0x053E781E,
        0x053E8C02, 0x053E9BC2, 0x053EA01E, 0x053EE401, 0x053F881E,
        0x053FA004, 0x053FB402, 0x053FB805, 0x053FD082, 0x054010A6,
        0x054030A6, 0x054058A6, 0x05411005, 0x05412007, 0x054138C7,
        0x054162C6, 0x0541781E, 0x0541A80B, 0x0541C2D4, 0x0541C816,
        0x0541F81E, 0x05439805, 0x0543B812, 0x0543F81E, 0x05440807,
        0x05459805, 0x05461807, 0x05462806, 0x0546681E, 0x05467812,
        0x0546C809, 0x0546F81E, 0x05478806, 0x0547B805, 0x0547DA45,
        0x0547E012, 0x0547F8A6, 0x05484809, 0x05492805, 0x05496806,
        0x05497812, 0x054A3005, 0x054A8806, 0x054A9807, 0x054AFBD2,
        0x054BE005, 0x054BF81E, 0x054C18C7, 0x054D98A6, 0x054DA807,
        0x054DC806, 0x054DD807, 0x054DE806, 0x054E0007, 0x054E725E,
        0x054E7804, 0x054EC809, 0x054EE81E, 0x054EF812, 0x054F28A6,
        0x054F3004, 0x054F7805, 0x054FC809, 0x054FF8BE, 0x05514005,
        0x05517006, 0x05518007, 0x05519006, 0x0551A007, 0x0551B006,
        0x0551F81E, 0x055218A6, 0x055260A6, 0x05526807, 0x0552781E,
        0x0552C809, 0x0552D81E, 0x0552F812, 0x055380A4, 0x0553B005,
        0x0553D2C5, 0x0553E0E6, 0x0553E807, 0x055580A6, 0x05558805,
        0x0555A006, 0x0555B005, 0x0555C006, 0x0555E805, 0x055600C5,
        0x055610C5, 0x0556D01E, 0x0556E8A4, 0x0556F812, 0x055758A7,
        0x05576806, 0x05577807, 0x05579245, 0x0557A887, 0x0557B006,
        0x0558001E, 0x05583005, 0x0558401E, 0x05587005, 0x0558801E,
        0x0558B005, 0x0558F81E, 0x055938BE, 0x055978BE, 0x055AD855,
        0x055AF804, 0x055B4844, 0x055B5815, 0x055B781E, 0x055DF802,
        0x055F1005, 0x055F28E6, 0x055F40E6, 0x055F58F2, 0x055F68E6,
        0x055F781E, 0x055FC809, 0x055FF81E, 0x06BD1805, 0x06BD781E,
        0x06BE3005, 0x06BE501E, 0x06BFD805, 0x06BFF81E, 0x06FFF81C,
        0x07C7F81D, 0x07D36805, 0x07D3781E, 0x07D6C805, 0x07D7F81E,
        0x07D83002, 0x07D8901E, 0x07D8B802, 0x07D8EBC5, 0x07D8F006,
        0x07D948B3, 0x07D9B8BE, 0x07D9E8BE, 0x07D9F8BE, 0x07DA10BE,
        0x07DA28BE, 0x07DD8805, 0x07DE1015, 0x07DE901E, 0x07E9F0AF,
        0x07E9F80E, 0x07EA7816, 0x07EC7805, 0x07EC881E, 0x07EE3805,
        0x07EE7BD6, 0x07EF781E, 0x07EFE0B4, 0x07EFF816, 0x07F07806,
        0x07F0BA4E, 0x07F0C9F2, 0x07F0F81E, 0x07F180D2, 0x07F1900D,
        0x07F1A98E, 0x07F1B9EE, 0x07F1C9EE, 0x07F1D9EE, 0x07F1E9EE,
        0x07F1F9EE, 0x07F209EE, 0x07F219EE, 0x07F2200F, 0x07F23A4E,
        0x07F2400F, 0x07F26012, 0x07F2780C, 0x07F29A5E, 0x07F2C24D,
        0x07F2D1CF, 0x07F2E1CF, 0x07F2F1CF, 0x07F31253, 0x07F3180D,
        0x07F33A7E, 0x07F34A54, 0x07F35812, 0x07F3781E, 0x07F3A8BE,
        0x07F7E005, 0x07F7FBDB, 0x07F8001E, 0x07F82254, 0x07F8424E,
        0x07F851F2, 0x07F86272, 0x07F8680D, 0x07F87812, 0x07F8C809,
        0x07F8D812, 0x07F8F013, 0x07F90012, 0x07F9D82E, 0x07F9EA4F,
        0x07F9FAAC, 0x07FA0015, 0x07FAD84E, 0x07FAEA6F, 0x07FAFA6E,
        0x07FB09F2, 0x07FB19CF, 0x07FB2812, 0x07FB80A4, 0x07FCE805,
        0x07FCF804, 0x07FDF005, 0x07FE081E, 0x07FE3805, 0x07FE481E,
        0x07FE7805, 0x07FE881E, 0x07FEB805, 0x07FEC81E, 0x07FEE005,
        0x07FEF81E, 0x07FF1293, 0x07FF22B6, 0x07FF3A9E, 0x07FF4016,
        0x07FF6013, 0x07FF7016, 0x07FFC01E, 0x07FFD81B, 0x07FFE816,
        0x07FFF81E, 0x080060BE, 0x080138BE, 0x0801D8BE, 0x0801F0BE,
        0x08026805, 0x0802781E, 0x0802E805, 0x0803F81E, 0x0807D005,
        0x0807F81E, 0x08081012, 0x0808301E, 0x0809980B, 0x0809B01E,
        0x0809F816, 0x080BA00A, 0x080BC00B, 0x080C4816, 0x080C580B,
        0x080C7ADE, 0x080CE016, 0x080D03D6, 0x080E781E, 0x080FEAC6,
        0x0813F81E, 0x0814E005, 0x0814F81E, 0x08168005, 0x081703C6,
        0x0817D80B, 0x0817F81E, 0x0818F805, 0x0819180B, 0x0819601E,
        0x081A08AA, 0x081A50AA, 0x081A781E, 0x081BA805, 0x081BD006,
        0x081BF81E, 0x081CF0BE, 0x081CF812, 0x081E1805, 0x081E381E,
        0x081E80B2, 0x081EA80A, 0x081FF81E, 0x08213801, 0x08227802,
        0x0824E805, 0x0824F81E, 0x08254809, 0x0825781E, 0x08269801,
        0x0826B81E, 0x0827D802, 0x0827F81E, 0x08293805, 0x0829781E,
        0x082B1805, 0x082B7BD2, 0x082BD83E, 0x082C583E, 0x082C983E,
        0x082CB03E, 0x082D105E, 0x082D905E, 0x082DD05E, 0x082DE002,
        0x082DF81E, 0x082F9805, 0x082FF81E, 0x0839B005, 0x0839F81E,
        0x083AA805, 0x083AF81E, 0x083B3805, 0x083BF81E, 0x083C309E,
        0x083D889E, 0x083DD004, 0x083FF81E, 0x08402805, 0x084043C5,
        0x0840481E, 0x0841B0BE, 0x0841C005, 0x0841E3C5, 0x0841F01E,
        0x0842B0BE, 0x0842B812, 0x0842F80B, 0x0843B005, 0x0843C016,
        0x0843F80B, 0x0844F005, 0x0845301E, 0x0845780B, 0x0846F81E,
        0x084798BE, 0x0847A805, 0x0847D01E, 0x0847F80B, 0x0848A805,
        0x0848D80B, 0x0848FBD2, 0x0849C805, 0x0849FBD2, 0x084BF81E,
        0x084DB805, 0x084DD81E, 0x084DE80B, 0x084DF805, 0x084E780B,
        0x084E881E, 0x08500165, 0x085020DE, 0x08503006, 0x0850581E,
        0x08507806, 0x0850A0BE, 0x0850C0BE, 0x0851A805, 0x0851B81E,
        0x0851D006, 0x0851FBC6, 0x0852400B, 0x0852781E, 0x0852C012,
        0x0852F81E, 0x0853E005, 0x0853F972, 0x0854E005, 0x0854F80B,
        0x0855F81E, 0x085640B6, 0x08572005, 0x08573006, 0x0857501E,
        0x0857780B, 0x0857B012, 0x0857F81E, 0x0859A805, 0x0859C01E,
        0x0859F812, 0x085AA805, 0x085AB81E, 0x085AF80B, 0x085B9005,
        0x085BB81E, 0x085BF80B, 0x085C8805, 0x085CC01E, 0x085CE012,
        0x085D401E, 0x085D780B, 0x085FF81E, 0x08624005, 0x0863F81E,
        0x08659001, 0x0865F81E, 0x08679002, 0x0867C81E, 0x0867F80B,
        0x08691805, 0x08693806, 0x0869781E, 0x0869C809, 0x0869F81E,
        0x086A4809, 0x086A70A4, 0x086A7805, 0x086B2801, 0x086B401E,
        0x086B70CD, 0x086B7804, 0x086C2802, 0x086C681E, 0x086C7813,
        0x0872F81E, 0x0873F97E, 0x087550BE, 0x087568CD, 0x0875781E,
        0x08758805, 0x0876081E, 0x08762005, 0x0877D81E, 0x0877F806,
        0x0878E005, 0x08793965, 0x0879781E, 0x087A2805, 0x087A8006,
        0x087AA00B, 0x087AC812, 0x087B781E, 0x087C0805, 0x087C2806,
        0x087C4812, 0x087D781E, 0x087E2005, 0x087E580B, 0x087EF81E,
        0x087FB005, 0x088003C7, 0x088010C7, 0x0881B805, 0x08823006,
        0x08826812, 0x0882881E, 0x0883280B, 0x08838126, 0x08839005,
        0x0883A8C5, 0x0883F01E, 0x088410C7, 0x08857805, 0x08859007,
        0x0885B006, 0x0885C007, 0x0885D006, 0x0885EA5B, 0x08861246,
        0x08866BDB, 0x0886781E, 0x08874005, 0x0887781E, 0x0887C809,
        0x0887F81E, 0x08881006, 0x08893005, 0x088960C7, 0x0889A8DE,
        0x0889F809, 0x088A2245, 0x088A38E5, 0x088A781E, 0x088B98A6,
        0x088BB245, 0x088BF81E, 0x088C10C7, 0x088D9005, 0x088DA807,
        0x088DF006, 0x088E0007, 0x088E2005, 0x088E4012, 0x088E68D2,
        0x088E78E6, 0x088ED125, 0x088EE245, 0x088F025E, 0x088FA00B,
        0x088FF81E, 0x089090BE, 0x08915805, 0x08917007, 0x08918806,
        0x0891A0E6, 0x0891A807, 0x0891B806, 0x0891F246, 0x089208A6,
        0x0893F81E, 0x089438BE, 0x089448BE, 0x089470BE, 0x0894F0BE,
        0x089548B2, 0x0895781E, 0x0896F8A6, 0x08971007, 0x08975006,
        0x0897781E, 0x0897C809, 0x0897F81E, 0x08980806, 0x089820FE,
        0x08986005, 0x0898701E, 0x08988005, 0x0898901E, 0x089948BE,
        0x089988BE, 0x0899A0BE, 0x0899D0BE, 0x0899E8C5, 0x089A00E6,
        0x089A2007, 0x089A301E, 0x089A4007, 0x089A501E, 0x089A6807,
        0x089A83C5, 0x089ABBC7, 0x089AE01E, 0x089B0805, 0x089B1807,
        0x089B281E, 0x089B6006, 0x089B781E, 0x089BA006, 0x089BF81E,
        0x089C50BE, 0x089C5805, 0x089C73C5, 0x089C781E, 0x089DB0BE,
        0x089DB805, 0x089DD007, 0x089E08DE, 0x089E1007, 0x089E2BC7,
        0x089E301E, 0x089E58FE, 0x089E70E6, 0x089E80E6, 0x089E90A6,
        0x089E9805, 0x089EB25E, 0x089EC012, 0x089F001E, 0x089F1006,
        0x089FF81E, 0x08A1A005, 0x08A1B807, 0x08A1F806, 0x08A20807,
        0x08A228C7, 0x08A23006, 0x08A25005, 0x08A27812, 0x08A2C809,
        0x08A2E25E, 0x08A2F246, 0x08A30805, 0x08A3F81E, 0x08A57805,
        0x08A59007, 0x08A5C8C7, 0x08A5D006, 0x08A5F007, 0x08A608C7,
        0x08A61806, 0x08A630B2, 0x08A63805, 0x08A6781E, 0x08A6C809,
        0x08ABF81E, 0x08AD7005, 0x08AD8807, 0x08ADA806, 0x08ADB81E,
        0x08ADD807, 0x08ADF0C7, 0x08AE0006, 0x08AEB812, 0x08AED805,
        0x08AEE806, 0x08AFF81E, 0x08B17805, 0x08B19007, 0x08B1D006,
        0x08B1E8E6, 0x08B1F007, 0x08B20006, 0x08B22245, 0x08B2781E,
        0x08B2C809, 0x08B2F81E, 0x08B36012, 0x08B3F81E, 0x08B558A6,
        0x08B568E6, 0x08B57807, 0x08B5B0C7, 0x08B5C0C5, 0x08B5C812,
        0x08B5F81E, 0x08B64809, 0x08B6781E, 0x08B71809, 0x08B7F81E,
        0x08B8D005, 0x08B8EBC6, 0x08B8F8E6, 0x08B90807, 0x08B930C7,
        0x08B95806, 0x08B9781E, 0x08B9C809, 0x08B9D80B, 0x08B9FA56,
        0x08BA3005, 0x08BFF81E, 0x08C15805, 0x08C17007, 0x08C1C0C7,
        0x08C1D8D2, 0x08C4F81E, 0x08C5F801, 0x08C6F802, 0x08C74809,
        0x08C7900B, 0x08C7F01E, 0x08C83005, 0x08C84BC5, 0x08C8581E,
        0x08C8A0BE, 0x08C8B8BE, 0x08C97805, 0x08C9B0FE, 0x08C9C007,
        0x08C9D01E, 0x08C9E8C7, 0x08C9F8C5, 0x08CA08E5, 0x08CA18E6,
        0x08CA3012, 0x08CA781E, 0x08CAC809, 0x08CCF81E, 0x08CD3805,
        0x08CD481E, 0x08CE8005, 0x08CE9807, 0x08CEB806, 0x08CEC81E,
        0x08CED806, 0x08CF00E6, 0x08CF10B2, 0x08CF20A7, 0x08D003C5,
        0x08D05006, 0x08D19005, 0x08D1C8C7, 0x08D1D005, 0x08D1F006,
        0x08D23A46, 0x08D283C5, 0x08D2B006, 0x08D2C007, 0x08D2D806,
        0x08D44805, 0x08D4B8C7, 0x08D4C806, 0x08D4EA45, 0x08D51012,
        0x08D5781E, 0x08D7C005, 0x08D7F81E, 0x08D84812, 0x08DDF81E,
        0x08DF08B2, 0x08DF781E, 0x08DFC809, 0x08DFF81E, 0x08E048BE,
        0x08E178A7, 0x08E1B8DE, 0x08E1F0C7, 0x08E200C5, 0x08E22812,
        0x08E2781E, 0x08E2C809, 0x08E3600B, 0x08E3781E, 0x08E38812,
        0x08E47805, 0x08E4881E, 0x08E540DE, 0x08E54807, 0x08E588C7,
        0x08E5A0C7, 0x08E5B006, 0x08E7F81E, 0x08E838BE, 0x08E850BE,
        0x08E98005, 0x08E9B006, 0x08E9D3C6, 0x08E9D81E, 0x08E9F0DE,
        0x08EA30C5, 0x08EA3806, 0x08EA781E, 0x08EAC809, 0x08EAF81E,
        0x08EB30BE, 0x08EB48BE, 0x08EC4805, 0x08EC78FE, 0x08EC90DE,
        0x08ECA8E6, 0x08ECB8E6, 0x08ECC005, 0x08ECF81E, 0x08ED4809,
        0x08F6F81E, 0x08F79005, 0x08F7A006, 0x08F7B007, 0x08F7C012,
        0x08F7F81E, 0x08F810C5, 0x08F81807, 0x08F888BE, 0x08F99805,
        0x08F9A807, 0x08F9D006, 0x08F9E81E, 0x08FA00E6, 0x08FA10E6,
        0x08FA7812, 0x08FAD126, 0x08FD83C5, 0x08FDF81E, 0x08FEA00B,
        0x08FEE016, 0x08FF0014, 0x08FF8816, 0x08FFFBD2, 0x091CC805,
        0x091FF81E, 0x0923795E, 0x0923A012, 0x0923F81E, 0x092A1805,
        0x097C781E, 0x097F8005, 0x097F9012, 0x097FF81E, 0x09A17805,
        0x09A20366, 0x09A23005, 0x09A2A806, 0x09A2F81E, 0x0A1FD005,
        0x0A1FF81E, 0x0A323005, 0x0B07F81E, 0x0B08E805, 0x0B094806,
        0x0B096007, 0x0B097806, 0x0B09C809, 0x0B3FF81E, 0x0B51C005,
        0x0B51F81E, 0x0B52F8BE, 0x0B534809, 0x0B53681E, 0x0B537812,
        0x0B55F8BE, 0x0B564809, 0x0B56781E, 0x0B576805, 0x0B57781E,
        0x0B57A8D2, 0x0B57F81E, 0x0B597805, 0x0B59B006, 0x0B59D812,
        0x0B59F816, 0x0B5A2092, 0x0B5A2816, 0x0B5A781E, 0x0B5AD13E,
        0x0B5B117E, 0x0B5BB805, 0x0B5BE01E, 0x0B5C7805, 0x0B69F81E,
        0x0B6A1004, 0x0B6B5005, 0x0B6B6004, 0x0B6B7812, 0x0B6BC809,
        0x0B71F81E, 0x0B72F801, 0x0B73F802, 0x0B74B00B, 0x0B74D012,
        0x0B77F81E, 0x0B7A5005, 0x0B7A7BC6, 0x0B7A8005, 0x0B7C3807,
        0x0B7C701E, 0x0B7C9006, 0x0B7CF804, 0x0B7EF81E, 0x0B7F1092,
        0x0B7F2086, 0x0B7F781E, 0x0B7F8807, 0x0B8003C5, 0x0C3FBBC5,
        0x0C3FF81E, 0x0C66A805, 0x0C67F01E, 0x0C680005, 0x0C6843C5,
        0x0D7F781E, 0x0D7FA09E, 0x0D7FE09E, 0x0D7FF89E, 0x0D891005,
        0x0D8993C5, 0x0D8A781E, 0x0D8A9005, 0x0D8AABC5, 0x0D8B181E,
        0x0D8B3805, 0x0D8B781E, 0x0D97D805, 0x0DDFF81E, 0x0DE35005,
        0x0DE3781E, 0x0DE3E005, 0x0DE3F81E, 0x0DE44005, 0x0DE4781E,
        0x0DE4C805, 0x0DE4E3D6, 0x0DE4F8D2, 0x0DE5181B, 0x0E5FF81E,
        0x0E677816, 0x0E67C809, 0x0E67F81E, 0x0E759816, 0x0E77F81E,
        0x0E796806, 0x0E79781E, 0x0E7A3006, 0x0E7A781E, 0x0E7E1816,
        0x0E7FF81E, 0x0E87A816, 0x0E87F81E, 0x0E893016, 0x0E89401E,
        0x0E8B2016, 0x0E8B3007, 0x0E8B4806, 0x0E8B6016, 0x0E8B9007,
        0x0E8BD01B, 0x0E8C1006, 0x0E8C2016, 0x0E8C5806, 0x0E8D4816,
        0x0E8D6806, 0x0E8F5016, 0x0E8FF81E, 0x0E920816, 0x0E9228D6,
        0x0E95F81E, 0x0E96980B, 0x0E96F81E, 0x0E97980B, 0x0E97F81E,
        0x0E9AB016, 0x0E9AF81E, 0x0E9BC00B, 0x0E9FF81E, 0x0EA0C801,
        0x0EA19802, 0x0EA26801, 0x0EA2A85E, 0x0EA33802, 0x0EA40801,
        0x0EA4E041, 0x0EA4E81E, 0x0EA4F801, 0x0EA513C1, 0x0EA5201E,
        0x0EA53001, 0x0EA5401E, 0x0EA5683E, 0x0EA5A801, 0x0EA5D05E,
        0x0EA5E05E, 0x0EA6205E, 0x0EA67802, 0x0EA74801, 0x0EA81802,
        0x0EA8303E, 0x0EA85001, 0x0EA8601E, 0x0EA8A83E, 0x0EA8E83E,
        0x0EA9B802, 0x0EA9D03E, 0x0EA9F83E, 0x0EAA283E, 0x0EAA3001,
        0x0EAA481E, 0x0EAA883E, 0x0EAB5802, 0x0EAC2801, 0x0EACF802,
        0x0EADC801, 0x0EAE9802, 0x0EAF6801, 0x0EB03802, 0x0EB10801,
        0x0EB1D802, 0x0EB2A801, 0x0EB37802, 0x0EB44801, 0x0EB52802,
        0x0EB5381E, 0x0EB60833, 0x0EB6D853, 0x0EB70802, 0x0EB7D833,
        0x0EB8A853, 0x0EB8D802, 0x0EB9A833, 0x0EBA7853, 0x0EBAA802,
        0x0EBB7833, 0x0EBC4853, 0x0EBC7802, 0x0EBD4833, 0x0EBE1853,
        0x0EBE4802, 0x0EBE5C02, 0x0EBE681E, 0x0EBFF809, 0x0ECFF816,
        0x0ED1B006, 0x0ED1D016, 0x0ED36006, 0x0ED3AAC6, 0x0ED422C6,
        0x0ED43016, 0x0ED45812, 0x0ED4D01E, 0x0ED500DE, 0x0ED57806,
        0x0EF7F81E, 0x0EF85045, 0x0EF8F002, 0x0EF9201E, 0x0EF95002,
        0x0EFFF81E, 0x0F0038DE, 0x0F00C006, 0x0F00D01E, 0x0F0110DE,
        0x0F0128DE, 0x0F015006, 0x0F01781E, 0x0F036804, 0x0F047BC6,
        0x0F07F81E, 0x0F096005, 0x0F09781E, 0x0F09B006, 0x0F09E804,
        0x0F09F81E, 0x0F0A4809, 0x0F0A73C5, 0x0F0A7816, 0x0F14781E,
        0x0F1570A6, 0x0F15F81E, 0x0F175805, 0x0F177806, 0x0F17C809,
        0x0F17FBD4, 0x0F26781E, 0x0F2758A4, 0x0F277806, 0x0F27C809,
        0x0F2E781E, 0x0F2F6805, 0x0F2F80C5, 0x0F2FD009, 0x0F2FFBD2,
        0x0F3EF81E, 0x0F3F38BE, 0x0F3F60BE, 0x0F3F78BE, 0x0F3FF8BE,
        0x0F462005, 0x0F46301E, 0x0F46780B, 0x0F46B006, 0x0F47F81E,
        0x0F490801, 0x0F4A1802, 0x0F4A58C4, 0x0F4A781E, 0x0F4AC809,
        0x0F4AE81E, 0x0F4AF812, 0x0F63801E, 0x0F656176, 0x0F658174,
        0x0F65A00B, 0x0F68001E, 0x0F697176, 0x0F69E80B, 0x0F6FF81E,
        0x0F7020BE, 0x0F7100BE, 0x0F7118BE, 0x0F712005, 0x0F713BC5,
        0x0F71401E, 0x0F7198BE, 0x0F71C0BE, 0x0F71D0BE, 0x0F71D805,
        0x0F7213C5, 0x0F723BC5, 0x0F724BC5, 0x0F725BC5, 0x0F72601E,
        0x0F7280BE, 0x0F7298BE, 0x0F72A005, 0x0F72BBC5, 0x0F72CBC5,
        0x0F72DBC5, 0x0F72EBC5, 0x0F72FBC5, 0x0F73001E, 0x0F7318BE,
        0x0F732005, 0x0F73301E, 0x0F7358BE, 0x0F7398BE, 0x0F73C0BE,
        0x0F73E8BE, 0x0F73F8BE, 0x0F7450BE, 0x0F74D805, 0x0F75001E,
        0x0F7520BE, 0x0F7550BE, 0x0F75D805, 0x0F77781E, 0x0F778813,
        0x0F7FF81E, 0x0F815816, 0x0F81781E, 0x0F849816, 0x0F84F81E,
        0x0F857016, 0x0F85801E, 0x0F8602DE, 0x0F8682DE, 0x0F87A816,
        0x0F87F81E, 0x0F88600B, 0x0F8D6816, 0x0F8F281E, 0x0F901016,
        0x0F90781E, 0x0F91D816, 0x0F91F81E, 0x0F924016, 0x0F92781E,
        0x0F928816, 0x0F92F81E, 0x0F932816, 0x0F97F81E, 0x0F9FD016,
        0x0F9FF815, 0x0FB6B816, 0x0FB6D81E, 0x0FB76016, 0x0FB7781E,
        0x0FB7E016, 0x0FB7F81E, 0x0FBBB016, 0x0FBBD01E, 0x0FBEC816,
        0x0FBEF81E, 0x0FBF5816, 0x0FBF83D6, 0x0FBFF81E, 0x0FC05816,
        0x0FC0781E, 0x0FC23816, 0x0FC2781E, 0x0FC2C816, 0x0FC2F81E,
        0x0FC43816, 0x0FC4781E, 0x0FC56816, 0x0FC5781E, 0x0FC5D816,
        0x0FC5F81E, 0x0FC60816, 0x0FC7F81E, 0x0FD29816, 0x0FD2F81E,
        0x0FD36816, 0x0FD3781E, 0x0FD3E016, 0x0FD3F81E, 0x0FD44816,
        0x0FD4701E, 0x0FD63016, 0x0FD6681E, 0x0FD6E016, 0x0FD6F01E,
        0x0FD74816, 0x0FD7781E, 0x0FD7C016, 0x0FD7F81E, 0x0FDC9ADE,
        0x0FDF7816, 0x0FDFC809, 0x100003C5, 0x1536FBC5, 0x153803C5,
        0x15B9CBC5, 0x15B9F81E, 0x15C0E805, 0x15C103C5, 0x16750BC5,
        0x167583C5, 0x175F03C5, 0x175F83C5, 0x1772EBC5, 0x17BFF81E,
        0x17D0E805, 0x180003C5, 0x189A53C5, 0x189A83C5, 0x191D7BC5,
        0x70000BDB, 0x7000F81E, 0x7003F81B, 0x7007F81E, 0x700F7806,
        0x77FFF81E, 0x7FFFE81D, 0x7FFFF81E, 0x87FFE81D
    };
}

