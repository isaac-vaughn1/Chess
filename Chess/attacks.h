#ifndef ATTACKS_H
#define ATTACKS_H

typedef unsigned long long U64;

namespace Engine {
	class Attacks {
		private:
			static U64 pawn_attacks[2][64];  // 0 = Black, 1 = White
			static U64 knight_attacks[64];
			static U64 king_attacks[64];

			// generate pseudo-legal leaper attacks
			static void generate_pawn_attacks();

			static void generate_knight_attacks();

			static void generate_king_attacks();

			// generate pseudo-legal slider attacks
			static void generate_bishop_attacks();

			static void generate_rook_attacks();

			static void generate_queen_attacks();

		public:
			static void generate_attacks();

			// getters
			static U64 get_pawn_attacks(bool white_to_move, int square) { return pawn_attacks[white_to_move][square]; }

			static U64 get_knight_attacks(int square) { return knight_attacks[square]; }

			static U64 get_king_attacks(int square) { return king_attacks[square]; }

			static U64 get_bishop_attacks(int square, U64 blockers);

			static U64 get_rook_attacks(int square, U64 blockers);

			static U64 get_queen_attacks(int square, U64 blockers) { return get_bishop_attacks(square, blockers) | get_rook_attacks(square, blockers); }

	};
}

#endif