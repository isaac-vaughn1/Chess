#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>

typedef unsigned __int64 U64;  // bitboard representation

namespace Engine {
	class Bitboard {
		private:
			// file masks
			static constexpr U64 file_a = 0x0101010101010101ULL;
			static constexpr U64 file_b = file_a << 1;
			static constexpr U64 file_c = file_a << 2;
			static constexpr U64 file_d = file_a << 3;
			static constexpr U64 file_e = file_a << 4;
			static constexpr U64 file_f = file_a << 5;
			static constexpr U64 file_g = file_a << 6;
			static constexpr U64 file_h = file_a << 7;

			// rank masks
			static constexpr U64 rank_1 = 0xFF;
			static constexpr U64 rank_2 = rank_1 << (8 * 1);
			static constexpr U64 rank_3 = rank_1 << (8 * 2);
			static constexpr U64 rank_4 = rank_1 << (8 * 3);
			static constexpr U64 rank_5 = rank_1 << (8 * 4);
			static constexpr U64 rank_6 = rank_1 << (8 * 5);
			static constexpr U64 rank_7 = rank_1 << (8 * 6);
			static constexpr U64 rank_8 = rank_1 << (8 * 7);

			// piece BB's
			U64 white_p_bb;
			U64 white_r_bb;
			U64 white_n_bb;
			U64 white_b_bb;
			U64 white_k_bb;
			U64 white_q_bb;

			U64 black_p_bb;
			U64 black_r_bb;
			U64 black_n_bb;
			U64 black_b_bb;
			U64 black_k_bb;
			U64 black_q_bb;

			U64 white_pieces;
			U64 black_pieces;
			U64 all_pieces;

		public:
			// set the given BB's bit at the given position
			inline void set_bit(U64& bb, int sq) { bb |= (1ULL << sq); }

			// clear the given BB's bit at the given position
			inline void clear_bit(U64& bb, int sq) { bb &= ~(1ULL << sq); }

			// true if the bit is high, false otherwise
			inline bool get_bit(U64 bb, int sq) { return bb & (1ULL << sq); }

			// return the number of pieces remaining in the given BB
			inline int pop_count(U64 bb) { return __popcnt64(bb); }

			// return the "index" of the given BB's LSB
			inline int lsb_index(U64 bb) { return _tzcnt_u64(bb); }

			// clear the LSB
			inline void pop_lsb(U64& bb) { return clear_bit(bb, lsb_index(bb)); }
	};
}
#endif