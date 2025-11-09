#include "bitboard.h"

int main() {
	Engine::Bitboard bb;

	U64 test = 0x000000000000FF00ULL;

	bb.clear_bit(test, 10);

	return 0;
}