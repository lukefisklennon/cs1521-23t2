// input = 0000000000000MMMMMM0000000000000
//      => 00000000000000000000000000MMMMMM
// mask  = 00000000000000000000000000111111
uint32_t six_middle_bits(uint32_t input) {
	uint32_t mask = 0b111111;
	uint32_t result = input & (mask << 13);
	result = result >> 13;
	return result;
}
