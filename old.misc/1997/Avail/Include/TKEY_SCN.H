/*
 *	Scan Codes Head File
 *	DanSei/TopCroak-Software	2000.3.4
 *
 *	ScanCode-macros using:
 *		SCAN_keyname(combined-key)
 *	Examples:
 *		SCAN_F2(SCAN_NORMAL) means key: "<F2>"
 *		SCAN_SLASH(SCAN_ALT) means key: "<Alt>-</>"
 */

#define SCAN_NORMAL		1000
#define SCAN_SHIFT		1001
#define SCAN_CTRL		1002
#define SCAN_ALT		1003

#define SCAN_REPLACE(m, vnormal, vshift, vctrl, valt) \
  ((m)==SCAN_NORMAL)?(vnormal):\
  ((m)==SCAN_SHIFT)?(vshift):\
  ((m)==SCAN_CTRL)?(vctrl):(valt)

#define NOSCAN			999999

#define SCAN_A(m)		(SCAN_REPLACE((m), 0x1e61, 0x1e41, 0x1e01, 0x1e00))
#define SCAN_B(m)		(SCAN_REPLACE((m), 0x3062, 0x3042, 0x3002, 0x3000))
#define SCAN_C(m)		(SCAN_REPLACE((m), 0x2e63, 0x2e43, 0x2e03, 0x2e00))
#define SCAN_D(m)		(SCAN_REPLACE((m), 0x2064, 0x2044, 0x2004, 0x2000))
#define SCAN_E(m)		(SCAN_REPLACE((m), 0x1265, 0x1245, 0x1205, 0x1200))
#define SCAN_F(m)		(SCAN_REPLACE((m), 0x2166, 0x2146, 0x2106, 0x2100))
#define SCAN_G(m)		(SCAN_REPLACE((m), 0x2267, 0x2247, 0x2207, 0x2200))
#define SCAN_H(m)		(SCAN_REPLACE((m), 0x2368, 0x2348, 0x2308, 0x2300))
#define SCAN_I(m)		(SCAN_REPLACE((m), 0x1769, 0x1749, 0x1709, 0x1700))
#define SCAN_J(m)		(SCAN_REPLACE((m), 0x246a, 0x244a, 0x240a, 0x2400))
#define SCAN_K(m)		(SCAN_REPLACE((m), 0x256b, 0x254b, 0x250b, 0x2500))
#define SCAN_L(m)		(SCAN_REPLACE((m), 0x266c, 0x264c, 0x260c, 0x2600))
#define SCAN_M(m)		(SCAN_REPLACE((m), 0x326d, 0x324d, 0x320d, 0x3200))
#define SCAN_N(m)		(SCAN_REPLACE((m), 0x316e, 0x314e, 0x310e, 0x3100))
#define SCAN_O(m)		(SCAN_REPLACE((m), 0x186f, 0x184f, 0x180f, 0x1800))
#define SCAN_P(m)		(SCAN_REPLACE((m), 0x1970, 0x1950, 0x1910, 0x1900))
#define SCAN_Q(m)		(SCAN_REPLACE((m), 0x1071, 0x1051, 0x1011, 0x1000))
#define SCAN_R(m)		(SCAN_REPLACE((m), 0x1372, 0x1352, 0x1312, 0x1300))
#define SCAN_S(m)		(SCAN_REPLACE((m), 0x1f73, 0x1f53, 0x1f13, 0x1f00))
#define SCAN_T(m)		(SCAN_REPLACE((m), 0x1474, 0x1454, 0x1414, 0x1400))
#define SCAN_U(m)		(SCAN_REPLACE((m), 0x1675, 0x1655, 0x1615, 0x1600))
#define SCAN_V(m)		(SCAN_REPLACE((m), 0x2f76, 0x2f56, 0x2f16, 0x2f00))
#define SCAN_W(m)		(SCAN_REPLACE((m), 0x1177, 0x1157, 0x1117, 0x1100))
#define SCAN_X(m)		(SCAN_REPLACE((m), 0x2d78, 0x2d58, 0x2d18, 0x2d00))
#define SCAN_Y(m)		(SCAN_REPLACE((m), 0x1579, 0x1559, 0x1519, 0x1500))
#define SCAN_Z(m)		(SCAN_REPLACE((m), 0x2c7a, 0x2c5a, 0x2c1a, 0x2c00))

#define SCAN_1(m)		(SCAN_REPLACE((m), 0x0231, 0x0221, NOSCAN, 0x7800))
#define SCAN_2(m)		(SCAN_REPLACE((m), 0x0332, 0x0340, 0x0300, 0x7900))
#define SCAN_3(m)		(SCAN_REPLACE((m), 0x0433, 0x0423, NOSCAN, 0x7a00))
#define SCAN_4(m)		(SCAN_REPLACE((m), 0x0534, 0x0524, NOSCAN, 0x7b00))
#define SCAN_5(m)		(SCAN_REPLACE((m), 0x0635, 0x0625, NOSCAN, 0x7c00))
#define SCAN_6(m)		(SCAN_REPLACE((m), 0x0736, 0x075e, 0x071e, 0x7d00))
#define SCAN_7(m)		(SCAN_REPLACE((m), 0x0837, 0x0826, NOSCAN, 0x7e00))
#define SCAN_8(m)		(SCAN_REPLACE((m), 0x0938, 0x092a, NOSCAN, 0x7f00))
#define SCAN_9(m)		(SCAN_REPLACE((m), 0x0a39, 0x0a28, NOSCAN, 0x8000))
#define SCAN_0(m)		(SCAN_REPLACE((m), 0x0b30, 0x0b29, NOSCAN, 0x8100))

#define SCAN_MINUS(m)		(SCAN_REPLACE((m), 0x0c2d, 0x0c5f, 0x0c1f, 0x8200))
#define SCAN_EQUAL(m)		(SCAN_REPLACE((m), 0x0d3d, 0x0d2b, NOSCAN, 0x8300))
#define SCAN_LEFTBRACKET(m)	(SCAN_REPLACE((m), 0x1a5b, 0x1a7b, 0x1a1b, 0x1a00))
#define SCAN_RIGHTBRACKET(m)	(SCAN_REPLACE((m), 0x1b5d, 0x1b7d, 0x1b1d, 0x1b00))
#define SCAN_SEMICOLON(m)	(SCAN_REPLACE((m), 0x273b, 0x273a, NOSCAN, 0x2700))
#define SCAN_QUOTE(m)		(SCAN_REPLACE((m), 0x2827, 0x2822, NOSCAN, NOSCAN))
#define SCAN_BACKQUOTE(m)	(SCAN_REPLACE((m), 0x2960, 0x297e, NOSCAN, NOSCAN))
#define SCAN_BACKSLASH(m)	(SCAN_REPLACE((m), 0x2b5c, 0x2b7c, 0x2b1c, 0x2600))
#define SCAN_COMMA(m)		(SCAN_REPLACE((m), 0x332c, 0x333c, NOSCAN, NOSCAN))
#define SCAN_PERIOD(m)		(SCAN_REPLACE((m), 0x342e, 0x343e, NOSCAN, NOSCAN))
#define SCAN_SLASH(m)		(SCAN_REPLACE((m), 0x352f, 0x353f, NOSCAN, NOSCAN))

#define SCAN_F1(m)		(SCAN_REPLACE((m), 0x3b00, 0x5400, 0x5e00, 0x6800))
#define SCAN_F2(m)		(SCAN_REPLACE((m), 0x3c00, 0x5500, 0x5f00, 0x6900))
#define SCAN_F3(m)		(SCAN_REPLACE((m), 0x3d00, 0x5600, 0x6000, 0x6a00))
#define SCAN_F4(m)		(SCAN_REPLACE((m), 0x3e00, 0x5700, 0x6100, 0x6b00))
#define SCAN_F5(m)		(SCAN_REPLACE((m), 0x3f00, 0x5800, 0x6200, 0x6c00))
#define SCAN_F6(m)		(SCAN_REPLACE((m), 0x4000, 0x5900, 0x6300, 0x6d00))
#define SCAN_F7(m)		(SCAN_REPLACE((m), 0x4100, 0x5a00, 0x6400, 0x6e00))
#define SCAN_F8(m)		(SCAN_REPLACE((m), 0x4200, 0x5b00, 0x6500, 0x6f00))
#define SCAN_F9(m)		(SCAN_REPLACE((m), 0x4300, 0x5c00, 0x6600, 0x7000))
#define SCAN_F10(m)		(SCAN_REPLACE((m), 0x4400, 0x5d00, 0x6700, 0x7100))
#define SCAN_F11(m)		(SCAN_REPLACE((m), 0x8500, 0x8700, 0x8900, 0x8b00))
#define SCAN_F12(m)		(SCAN_REPLACE((m), 0x8600, 0x8800, 0x8a00, 0x8c00))

#define SCAN_ESC(m)		(SCAN_REPLACE((m), 0x011b, 0x011b, 0x011b, 0x0100))
#define SCAN_BACKSPACE(m)	(SCAN_REPLACE((m), 0x0e08, 0x0e08, 0x0e7f, 0x0e00))
#define SCAN_ENTER(m)		(SCAN_REPLACE((m), 0x1c0d, 0x1c0d, 0x1c0a, 0xa600))
#define SCAN_SPACE(m)		(SCAN_REPLACE((m), 0x3920, 0x3920, 0x3920, 0x3920))
#define SCAN_TAB(m)		(SCAN_REPLACE((m), 0x0f09, 0x0f00, 0x9400, 0xa500))
#define SCAN_LEFT(m)		(SCAN_REPLACE((m), 0x4b00, 0x4b34, 0x7300, 0x9b00))
#define SCAN_RIGHT(m)		(SCAN_REPLACE((m), 0x4d00, 0x4d36, 0x7400, 0x9d00))
#define SCAN_UP(m)		(SCAN_REPLACE((m), 0x4800, 0x4838, 0x8d00, 0x9800))
#define SCAN_DOWN(m)		(SCAN_REPLACE((m), 0x5000, 0x5032, 0x9100, 0xa000))
#define SCAN_HOME(m)		(SCAN_REPLACE((m), 0x4700, 0x4737, 0x7700, 0x9700))
#define SCAN_END(m)		(SCAN_REPLACE((m), 0x4f00, 0x4f31, 0x7500, 0x9f00))
#define SCAN_PGUP(m)		(SCAN_REPLACE((m), 0x4900, 0x4939, 0x8400, 0x9900))
#define SCAN_PGDN(m)		(SCAN_REPLACE((m), 0x5100, 0x5133, 0x7600, 0xa100))
#define SCAN_PAD5(m)		(SCAN_REPLACE((m), NOSCAN, 0x4c35, 0x8f00, NOSCAN))
#define SCAN_PADPLUS(m)		(SCAN_REPLACE((m), 0x4e2b, 0x4e2b, NOSCAN, 0x4e00))
#define SCAN_PADMINUS(m)	(SCAN_REPLACE((m), 0x4a2d, 0x4a2d, 0x8e00, 0x4a00))
#define SCAN_PADASTERISK(m)	(SCAN_REPLACE((m), 0x372a, NOSCAN, 0x9600, 0x3700))
#define SCAN_PADSLASH(m)	(SCAN_REPLACE((m), 0x352f, 0x352f, 0x9500, 0xa400))
#define SCAN_INSERT(m)		(SCAN_REPLACE((m), 0x5200, 0x5230, 0x9200, 0xa200))
#define SCAN_DEL(m)		(SCAN_REPLACE((m), 0x5300, 0x532e, 0x9300, 0xa300))
#define SCAN_PRTSC(m)		(SCAN_REPLACE((m), NOSCAN, NOSCAN, 0x7200, NOSCAN))
