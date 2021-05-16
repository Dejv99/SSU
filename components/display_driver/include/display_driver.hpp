#ifndef __DISPLAY_DRIVER_HPP__
#define __DISPLAY_DRIVER_HPP__
#include <cstdint>

constexpr uint8_t STRIPS_NUMBER = 7;
constexpr uint8_t STRIP_LEDS_NUMBER = 36;

/**
 * @brief Pointer to symbol data (array of 7 uint8_t elements).
 * 
 * @return typedef const uint8_t(*)[7] 
 */
typedef const uint8_t (*p_symbol_data_t)[7];

/**
 * @brief Display RGB pixel coded 8:8:8
 * 
 */
typedef struct
{
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
} rgb888_pixel_t;

/**
 * @brief Reference to text to display (array of 6 symbols (uint8_t elements)).
 * 
 * @return typedef uint8_t(&)[6] 
 */
typedef const char (&r_symbols_t)[6];

class display_driver
{
public: // public methods
	/**
	 * @brief Display one specified symbol (aSymbol) with background color (aColor) at position (aPosition).
	 * 
	 * @param aSymbol 
	 * @param aColor 
	 * @param aPosition 
	 * @return esp_err_t 
	 */
	esp_err_t Display_symbol(const char &aSymbol, const rgb888_pixel_t &aColor, const uint8_t &aPosition);

	/**
	 * @brief Display the specified text (aText) with background color (aColor).
	 * 
	 * @param aText 
	 * @param aColor 
	 * @return esp_err_t 
	 */
	esp_err_t Display_text(const uint16_t (&aText)[3], const rgb888_pixel_t &aColor);



	// Rotate_text (dir)


	// Led_strip_driver_task()




private: // private methods

	/**
	 * @brief Obtain the symbol data from the font table - ascii_tab_5x7[256][7].
	 * 	The table contains fonts for symbol codes from 0x20 (space) to 0x7f (✓).
	 * 
	 * @param aSymbol Symbol to display.
	 * @return p_symbol_data_t
	 */
	p_symbol_data_t Get_symbol_data(const char *aSymbol) const;

	/**
	 * @brief Set the frame buffer mask for actual symbol.
	 * 
	 * @param aPosition Position of symbol on the display (range 1-6).
	 */
	void Set_frame_buffer_mask(const uint8_t &aPosition);

	/**
	 * @brief Algorythm for conversion from rgb565 color to rgb888 color
	 * 
	 * @param rgb_565_color RGB color coded 5:6:5
	 * @return rgb888_pixel_t
	 */
	rgb888_pixel_t display_driver::rgb565_to_rgb888(const uint16_t &rgb_565_color);

	/**
	 * @brief Fill the frame buffer.
	 * 
	 * @param aColor Background color
	 */
	void Fill_frame_buffer(const rgb888_pixel_t &aColor);

	/**
	 * @brief Initialization of LED strips WS2812B
	 * 
	 */
	void Led_strips_init(void);

	/**
	 * @brief Extract symbols stored in holding registers.
	 * 
	 * @param aText Text stored in holding registers
	 * @param aSymbols Reference to array of 6 chars to store the symbols
	 */
	void Extract_symbols_from_holding_regs(const uint16_t (&aText)[3], char (&aSymbols)[6]);

	/**
	 * @brief Update display from data stored in `frame_buffer`
	 * 
	 */
	void Update_display_from_frame_buffer(void);

public: // public data


private: // private data

	static bool frame_buffer_mask[STRIPS_NUMBER][STRIP_LEDS_NUMBER];

	static rgb888_pixel_t frame_buffer[STRIPS_NUMBER][2 * STRIP_LEDS_NUMBER];

	static p_symbol_data_t pSymbol_data;

	/**
	 * @brief Declare the 2D array of 5x7 ASCII symbols.
	 * 
	 * 	Data are row oriented (from top to bottom), thus 7 bytes of data for each symbol.
	 * 	Data don't contain the spaces before and after the symbol.
	 * 	The 1st index is position (0-255) of symbol in the ASCII table.
	 * 	The 2nd index refers to the row (0-6) of the selected symbol in the 1st index.
	 * 
	 */
	const uint8_t ascii_tab_5x7_[256][7] = {
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x00		STANDARD ASCII (0-127)
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x01
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x02
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x03
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x04
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x05
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x06
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x07
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x08
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x09
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0a
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0b
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0c
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0d
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0e
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0f
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x10
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x11
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x12
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x13
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x14
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x15
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x16
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x17
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x18
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x19
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1a
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1b
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1c
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1d
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1e
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1f
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x20, space
		{0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04}, // 0x21, !
		{0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00}, // 0x22, "
		{0x0a, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x0a}, // 0x23, #
		{0x04, 0x0f, 0x14, 0x0e, 0x05, 0x1e, 0x04}, // 0x24, $
		{0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03}, // 0x25, %
		{0x0c, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0d}, // 0x26, &
		{0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00}, // 0x27, '
		{0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02}, // 0x28, (
		{0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08}, // 0x29, )
		{0x00, 0x04, 0x15, 0x0e, 0x15, 0x04, 0x00}, // 0x2a, *
		{0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00}, // 0x2b, +
		{0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x08}, // 0x2c, ,
		{0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00}, // 0x2d, -
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c}, // 0x2e, .
		{0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00}, // 0x2f, /
		{0x0e, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0e}, // 0x30, 0
		{0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e}, // 0x31, 1
		{0x0e, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1f}, // 0x32, 2
		{0x0e, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0e}, // 0x33, 3
		{0x02, 0x06, 0x0a, 0x12, 0x1f, 0x02, 0x02}, // 0x34, 4
		{0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e}, // 0x35, 5
		{0x06, 0x08, 0x10, 0x1e, 0x11, 0x11, 0x0e}, // 0x36, 6
		{0x1f, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}, // 0x37, 7
		{0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e}, // 0x38, 8
		{0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c}, // 0x39, 9
		{0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00}, // 0x3a, :
		{0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x04, 0x08}, // 0x3b, ;
		{0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02}, // 0x3c, <
		{0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00}, // 0x3d, =
		{0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08}, // 0x3e, >
		{0x0e, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04}, // 0x3f, ?
		{0x0e, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0f}, // 0x40, @
		{0x04, 0x0a, 0x11, 0x11, 0x1f, 0x11, 0x11}, // 0x41, A
		{0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e}, // 0x42, B
		{0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e}, // 0x43, C
		{0x1c, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1c}, // 0x44, D
		{0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x1f}, // 0x45, E
		{0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x10}, // 0x46, F
		{0x0e, 0x11, 0x10, 0x10, 0x13, 0x11, 0x0f}, // 0x37, G
		{0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11}, // 0x48, H
		{0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e}, // 0x49, I
		{0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0c}, // 0x4a, J
		{0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11}, // 0x4b, K
		{0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f}, // 0x4c, L
		{0x11, 0x1b, 0x15, 0x15, 0x11, 0x11, 0x11}, // 0x4d, M
		{0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11}, // 0x4e, N
		{0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e}, // 0x4f, O
		{0x1e, 0x11, 0x11, 0x1e, 0x10, 0x10, 0x10}, // 0x50, P
		{0x0e, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0d}, // 0x51, Q
		{0x1e, 0x11, 0x11, 0x1e, 0x14, 0x12, 0x11}, // 0x52, R
		{0x0e, 0x11, 0x10, 0x0e, 0x01, 0x11, 0x0e}, // 0x53, S
		{0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // 0x54, T
		{0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e}, // 0x55, U
		{0x11, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04}, // 0x56, V
		{0x11, 0x11, 0x11, 0x15, 0x15, 0x0a, 0x0a}, // 0x57, W
		{0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11}, // 0x58, X
		{0x11, 0x11, 0x0a, 0x04, 0x04, 0x04, 0x04}, // 0x59, Y
		{0x1f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1f}, // 0x5a, Z
		{0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e}, // 0x5b, [
		{0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00}, // 0x5c, \ .
		{0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e}, // 0x5d, ]
		{0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x00}, // 0x5e, ^
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f}, // 0x5f, _
		{0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00}, // 0x60, `
		{0x00, 0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f}, // 0x61, a
		{0x10, 0x10, 0x16, 0x1c, 0x19, 0x11, 0x1e}, // 0x62, b
		{0x00, 0x00, 0x0e, 0x10, 0x10, 0x10, 0x0e}, // 0x63, c
		{0x01, 0x01, 0x0d, 0x07, 0x09, 0x09, 0x07}, // 0x64, d
		{0x00, 0x00, 0x0e, 0x11, 0x1f, 0x10, 0x0e}, // 0x65, e
		{0x06, 0x09, 0x08, 0x1c, 0x08, 0x08, 0x08}, // 0x66, f
		{0x00, 0x0f, 0x11, 0x11, 0x0f, 0x01, 0x0e}, // 0x67, g
		{0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11}, // 0x68, h
		{0x04, 0x00, 0x0c, 0x04, 0x04, 0x04, 0x0e}, // 0x69, i
		{0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0c}, // 0x6a, j
		{0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12}, // 0x6b, k
		{0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e}, // 0x6c, l
		{0x00, 0x00, 0x1a, 0x15, 0x15, 0x11, 0x11}, // 0x6d, m
		{0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11}, // 0x6e, n
		{0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e}, // 0x6f, o
		{0x00, 0x00, 0x1e, 0x11, 0x1e, 0x10, 0x10}, // 0x70, p
		{0x00, 0x00, 0x0e, 0x11, 0x0e, 0x01, 0x01}, // 0x71, q
		{0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10}, // 0x72, r
		{0x00, 0x00, 0x0e, 0x10, 0x0e, 0x01, 0x1e}, // 0x73, s
		{0x08, 0x08, 0x1c, 0x08, 0x08, 0x09, 0x06}, // 0x74, t
		{0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0d}, // 0x75, u
		{0x00, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04}, // 0x76, v
		{0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0a}, // 0x77, w
		{0x00, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11}, // 0x78, x
		{0x00, 0x00, 0x11, 0x11, 0x0f, 0x01, 0x0e}, // 0x79, y
		{0x00, 0x00, 0x1f, 0x02, 0x04, 0x08, 0x1f}, // 0x7a, z
		{0x06, 0x08, 0x08, 0x10, 0x08, 0x08, 0x06}, // 0x7b, {
		{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // 0x7c, |
		{0x0c, 0x02, 0x02, 0x01, 0x02, 0x02, 0x0c}, // 0x7d, }
		{0x08, 0x15, 0x02, 0x00, 0x00, 0x00, 0x00}, // 0x7e, ~
		{0x00, 0x00, 0x01, 0x02, 0x14, 0x08, 0x00}, // 0x7f, ✓
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x80		EXTENDED ASCII (128-255)
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x81
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x82
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x83
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x84
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x85
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x86
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x87
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x88
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x89
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x8a
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x8b
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x8c
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x8d
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x8e
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x8f
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x90
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x91
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x92
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x93
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x94
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x95
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x96
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x97
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x98
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x99
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x9a
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x9b
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x9c
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x9d
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x9e
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x9f
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa0
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa1
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa2
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa3
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa4
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa5
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa6
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa7
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa8
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xa9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xaa
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xab
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xac
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xad
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xae
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xaf
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb0
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb1
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb2
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb3
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb4
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb5
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb6
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb7
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb8
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xb9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xba
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xbb
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xbc
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xbd
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xbe
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xbf
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc0
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc1
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc2
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc3
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc4
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc5
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc6
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc7
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc8
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xc9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xca
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xcb
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xcc
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xcd
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xce
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xcf
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd0
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd1
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd2
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd3
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd4
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd5
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd6
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd7
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd8
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xd9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xda
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xdb
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xdc
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xdd
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xde
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xdf
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe0
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe1
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe2
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe3
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe4
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe5
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe6
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe7
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe8
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xe9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xea
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xeb
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xec
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xed
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xee
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xef
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf0
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf1
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf2
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf3
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf4
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf5
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf6
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf7
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf8
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xf9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xfa
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xfb
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xfc
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xfd
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xfe
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0xff
	};
}; /* display_driver */

#endif /* __DISPLAY_DRIVER_HPP__ */