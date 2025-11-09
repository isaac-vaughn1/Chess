#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

typedef unsigned __int64 U64;  // bitboard representation

namespace Engine {
	class Board {
		private:
			// piece BB's
			U64 white_p_bb = 0ULL;
			U64 white_r_bb = 0ULL;
			U64 white_n_bb = 0ULL;
			U64 white_b_bb = 0ULL;
			U64 white_k_bb = 0ULL;
			U64 white_q_bb = 0ULL;

			U64 black_p_bb = 0ULL;
			U64 black_r_bb = 0ULL;
			U64 black_n_bb = 0ULL;
			U64 black_b_bb = 0ULL;
			U64 black_k_bb = 0ULL;
			U64 black_q_bb = 0ULL;

			U64 white_pieces = 0ULL;
			U64 black_pieces = 0ULL;
			U64 all_pieces = 0ULL;

			bool white_to_move;
			int en_passant_sq = -1;
			unsigned int castling_rights = 0b0000;  // 4-bit bitmask: WK, WQ, BK, BQ
			int half_move_clock;
			int full_move_num;

		public:
			Board();

			// construct board using a custom fen string
			Board(const std::string& fen);

			void load_fen(const std::string& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			// prints the current board state to the console (debugging); lowercase letters for black, uppercase for white
			void print_board();

			// helper function to split fen
			std::vector<std::string> delimited_str_to_vector(const std::string& str, std::string delimiter);
	};
}
#endif