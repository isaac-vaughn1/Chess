#include "attacks.h"
#include "board.h"
#include "bitboard.h"

// define static members
U64 Engine::Attacks::pawn_attacks[2][64] = {};
U64 Engine::Attacks::knight_attacks[64] = {};
U64 Engine::Attacks::king_attacks[64] = {};

void Engine::Attacks::generate_attacks() {
	generate_pawn_attacks();
	generate_knight_attacks();
	generate_king_attacks();
	generate_bishop_attacks();
	generate_rook_attacks();
	generate_queen_attacks();
}

void Engine::Attacks::generate_pawn_attacks() {
	// generate black pawn attacks
	for (int square = 8; square < 56; square++) {
		U64 pawn_location = (1ULL << square);
		U64 attack_mask = 0ULL;

		// capture left
		attack_mask |= (pawn_location & ~(Bitboard::file_h)) >> 9;


		// capture right
		attack_mask |= (pawn_location & ~(Bitboard::file_a)) >> 7;

		Engine::Attacks::pawn_attacks[0][square] = attack_mask;
	}

	// generate white pawn attacks
	for (int square = 8; square < 56; square++) {
		U64 pawn_location = (1ULL << square);
		U64 attack_mask = 0ULL;

		// capture left
		attack_mask |= (pawn_location & ~(Bitboard::file_h)) << 7;

		// capture right
		attack_mask |= (pawn_location & ~(Bitboard::file_a)) << 9;

		Engine::Attacks::pawn_attacks[1][square] = attack_mask;
	}
}

void Engine::Attacks::generate_knight_attacks() {
	for (int square = 0; square < 64; square++) {
		U64 knight_location = (1ULL << square);
		U64 attack_mask = 0ULL;

		attack_mask |= (knight_location & ~(Bitboard::file_h)) << 17;
		attack_mask |= (knight_location & ~(Bitboard::file_g | Bitboard::file_h)) << 10;
		attack_mask |= (knight_location & ~(Bitboard::file_g | Bitboard::file_h)) >> 6;
		attack_mask |= (knight_location & ~(Bitboard::file_h)) >> 15;
		attack_mask |= (knight_location & ~(Bitboard::file_a)) << 15;
		attack_mask |= (knight_location & ~(Bitboard::file_a | Bitboard::file_b)) << 6;
		attack_mask |= (knight_location & ~(Bitboard::file_a | Bitboard::file_b)) >> 10;
		attack_mask |= (knight_location & ~(Bitboard::file_a)) >> 17;

		Engine::Attacks::knight_attacks[square] = attack_mask;
	}
}

void Engine::Attacks::generate_king_attacks() {
	for (int square = 0; square < 64; square++) {
		U64 king_location = (1ULL << square);
		U64 attack_mask = 0ULL;

		attack_mask |= (king_location & ~(Bitboard::rank_8)) << 8;
		attack_mask |= (king_location & ~(Bitboard::file_h)) << 1;
		attack_mask |= (king_location & ~(Bitboard::file_h)) << 9;
		attack_mask |= (king_location & ~(Bitboard::file_a)) << 7;
		attack_mask |= (king_location & ~(Bitboard::rank_1)) >> 8;
		attack_mask |= (king_location & ~(Bitboard::file_a)) >> 1;
		attack_mask |= (king_location & ~(Bitboard::file_a)) >> 9;
		attack_mask |= (king_location & ~(Bitboard::file_h)) >> 7;

		Engine::Attacks::king_attacks[square] = attack_mask;
	}
}

void Engine::Attacks::generate_bishop_attacks() {
	return;
}

void Engine::Attacks::generate_rook_attacks() {
	return;
}

void Engine::Attacks::generate_queen_attacks() {
	return;
}
