#define __STDC_WANT_DEC_FP__
#include <math.h>
#include <float.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>


static uintmax_t integer_pow(uintmax_t base, uintmax_t exp) {
	uintmax_t out = 1;

	for(uintmax_t i = 0; i < exp; i++) {
		out *= base;
	}

	return out;
}

/**
 * \brief transform from oracle number database type to _Decimal128
 * ORACLE FORMAT: SEEEEEE MMMMMMMM MMMMMMMMM in big endian
 * the base of the mantisa is 100
 * related documentation [oracle](https://docs.oracle.com/en/database/oracle/oracle-database/19/lnpcc/c-c-programmers-guide.pdf)
 * Number format explanation [random internet guy](https://gotodba.com/2015/03/24/how-are-numbers-saved-in-oracle/)
 * _Decimal128 format [wikipedia] (https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format)
 * \todo look for other source about oracle nuber format
 * \todo In the math library exist some combination of functions that do this work better
 */
static _Decimal128 positive_number_to_Decimal128(const unsigned char* number, int size) {
	_Decimal128 doublet, number_mantisa = 0.0dl, sum = 100.0dl;
	uint16_t number_exponent;

	assert(size > 1);
	if(size <= 1) { return 0.0dl; }

	// exponent
	number_exponent = (uint16_t)(((*(uint8_t*)number & ( 0xff >> 1)) - 64));
	assert(number_exponent < INT16_MAX);

	// mantisa
	// The oracle mantisa is in base 100, for move to binary representation
	for(unsigned i = 1; i < (unsigned)size; i++) {
		// todo Check overflow
		number_mantisa += (_Decimal128)(*(((uint8_t*)number)+i) - UINT8_C(1)) / sum;
		sum *= 100.0dl;
	}

	// Calcuate the number representation in base 2
	doublet = number_mantisa * (_Decimal128)integer_pow(100, number_exponent); // simple approach

	return doublet;
}

// Transform the number a positive and change sign after computate
static _Decimal128 negative_number_to_Decimal128(const unsigned char* number, int size) {
	_Decimal128 doublet;

	// TODO check latest bytes is 102
	assert(*((uint8_t*)number+size-1) == 102);
	size = size - 1; // ignore latest byte
	assert(size > 1);
	if(size <= 1) { return 0.0dl; }

	// exponent
	*(uint8_t*)number = (uint8_t)~(*(uint8_t*)number);

	// mantisa
	for(unsigned i = (unsigned)(size-1); i >= 1; i--) {
		*((uint8_t*)number + i) = (uint8_t)(102 - *((uint8_t*)number + i));
	}

	doublet = positive_number_to_Decimal128(number, size);

	// sign negative
	doublet *= -1.0dl;

	return doublet;
}

_Decimal128 number_to_Decimal128(const unsigned char* number, int size) {
	// sign
	if(!(*(uint8_t*)number & (1 << 7))) {
		return negative_number_to_Decimal128(number, size);
		// Oracle format negative is inverse to double and use 1 for mark a number as positive
		// if oracle number left bit is 0 mark the output as negative
	};

	return positive_number_to_Decimal128(number, size);
}

