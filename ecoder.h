#ifndef __ABIENCODER_H__
#define __ABIENCODER_H__

// Commands to LS7366R
#define OP_CLEAR                	0b00000000
#define OP_READ                 	0b01000000
#define OP_WRITE                	0b10000000
#define OP_LOAD                 	0b11000000

// Registres of LS7366R
#define REG_MDR0                	0b00001000
#define REG_MDR1                	0b00010000
#define REG_DTR                 	0b00011000
#define REG_CNTR                	0b00100000
#define REG_OTR                 	0b00101000
#define REG_STR                 	0b00110000

// Parameters to MDR0
// Quadrature mode
#define	MDR0_B1B0_CLOCK_DIR			  0b00000000		// A = clock, B = direction
#define	MDR0_B1B0_X1				      0b00000001		// x1 quadrature mode (one count per quadrature cycle)
#define	MDR0_B1B0_X2				      0b00000010		// x2 quadrature mode (two count per quadrature cycle)
#define	MDR0_B1B0_X4				      0b00000011		// x3 quadrature mode (four count per quadrature cycle)
// Mode of counting
#define	MDR0_B3B2_FREE_RUNNING		0b00000000		// Free running
#define	MDR0_B3B2_SINGLE_CYCLE		0b00000100		// single-cycle count mode (counter disabled with carry or borrow, re-enabled with reset or load).
#define	MDR0_B3B2_RANGE_LIMIT		  0b00001000		// range-limit count mode (up and down count-ranges are limited between DTR and zero,respectively; counting freezes at these limits but resumes when direction reverses).
#define	MDR0_B3B2_MODULU_COUNT		0b00001100		// modulo-n count mode (input count clock frequency is divided by a factor of (n+1),where n = DTR, in both up and down directions).
// Index mode
#define	MDR0_B5B4_NO_INDEX			  0b00000000		// disable index.
#define	MDR0_B5B4_LOAD_CNTR			  0b00010000		// configure index as the "load CNTR" input (transfers DTR to CNTR)
#define	MDR0_B5B4_RESET_CNTR		  0b00100000		// configure index as the "reset CNTR" input (clears CNTR to 0)
#define	MDR0_B5B4_LOAD_OTR			  0b00110000		// configure index as the "load OTR" input (transfers CNTR to OTR)
// index syncron
#define	MDR0_B6_ASYNC_INDEX			  0b00000000		// Asynchronous Index
#define	MDR0_B6_SYNC_INDEX			  0b01000000		// Synchronous Index (overridden in non-quadrature mode)
// Filtrage
#define	MDR0_B7_FILTER_CLOCK_F1		0b00000000		// Clock division factor = 1
#define	MDR0_B7_FILTER_CLOCK_F2		0b10000000		// Clock division factor = 2

// Parameters of MDR1
// n-bit counter
#define	MDR1_B1B0_COUNT_32_BITS		0b00000000		//  4-byte counter mode
#define	MDR1_B1B0_COUNT_24_BITS		0b00000001		//  3-byte counter mode
#define	MDR1_B1B0_COUNT_16_BITS		0b00000010		//  2-byte counter mode
#define	MDR1_B1B0_COUNT_8_BITS		0b00000011		//  1-byte counter mode
// Enable counting
#define	MDR1_B2_ENABLE_COUNTING		0b00000000		// Enable counting
#define	MDR1_B2_DISABLE_COUNTING	0b00000100		// Disable counting
// Flag index
#define	MDR1_B4_NO_FLAG_INDEX		  0b00000000		// Nop
#define	MDR1_B4_FLAG_INDEX			  0b00010000		// FLAG on IDX (B4 of STR)
#define	MDR1_B5_NO_FLAG_COMPARE		0b00000000		// Nop
#define	MDR1_B5_FLAG_COMPARE		  0b00100000		// FLAG on CMP (B5 of STR)
#define	MDR1_B6_NO_FLAG_UNDERFLOW	0b00000000		// Nop
#define	MDR1_B6_FLAG_UNDERFLOW		0b01000000		// FLAG on BW (B6 of STR)
#define	MDR1_B7_NO_FLAG_OVERFLOW	0b00000000		// Nop
#define	MDR1_B7_FLAG_OVERFLOW		  0b10000000		// FLAG on CY (B7 of STR)

// Configuration default LS7366R (MDR0 + MDR1)
#define MDR0_INITIAL_VALUE      	(MDR0_B7_FILTER_CLOCK_F1 | MDR0_B6_ASYNC_INDEX | MDR0_B5B4_NO_INDEX | MDR0_B3B2_FREE_RUNNING | MDR0_B1B0_X4)
#define MDR1_INITIAL_VALUE      	(MDR1_B7_NO_FLAG_OVERFLOW | MDR1_B6_NO_FLAG_UNDERFLOW | MDR1_B5_NO_FLAG_COMPARE | MDR1_B4_NO_FLAG_INDEX | MDR1_B2_ENABLE_COUNTING | MDR1_B1B0_COUNT_32_BITS)

int WriteSPI2(int i);
void Init_encoder(void);
void write_encoder(BYTE write_register, BYTE data);
BYTE read_encoder(BYTE read_register);
BYTE read_counter(void);

#endif	// __ABIENCODER_H__