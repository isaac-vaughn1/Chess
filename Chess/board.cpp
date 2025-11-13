#include <cctype>
#include "board.h"
#include "bitboard.h"

Engine::Board::Board() {
	load_fen();
	white_pieces = white_p_bb | white_r_bb | white_n_bb | white_b_bb | white_q_bb | white_k_bb;
	black_pieces = black_p_bb | black_r_bb | black_n_bb | black_b_bb | black_q_bb | black_k_bb;
	all_pieces = white_pieces | black_pieces;
	print_board();  // testing only; remove later
}

Engine::Board::Board(const std::string& fen) {
	load_fen(fen);
	white_pieces = white_p_bb | white_r_bb | white_n_bb | white_b_bb | white_q_bb | white_k_bb;
	black_pieces = black_p_bb | black_r_bb | black_n_bb | black_b_bb | black_q_bb | black_k_bb;
	all_pieces = white_pieces | black_pieces;
	print_board();  // testing only; remove later
}

void Engine::Board::load_fen(const std::string& fen) {
	std::vector<std::string> sections = delimited_str_to_vector(fen, " ");
	int file = 0;
	int rank = 7;

	// FEN piece placement
	for (auto& c : sections[0]) {
		if (c == '/') {
			file = 0;
			rank--;
		}
		else {
			if (std::isdigit(c)) {
				int digit = c - '0';  // simple conversion to integer value
				file += digit;
			}
			else {
				int square = 8 * rank + file;
				if (c == 'p') { Bitboard::set_bit(black_p_bb, square); }
				else if (c == 'r') { Bitboard::set_bit(black_r_bb, square); }
				else if (c == 'n') { Bitboard::set_bit(black_n_bb, square); }
				else if (c == 'b') { Bitboard::set_bit(black_b_bb, square); }
				else if (c == 'q') { Bitboard::set_bit(black_q_bb, square); }
				else if (c == 'k') { Bitboard::set_bit(black_k_bb, square); }
				else if (c == 'P') { Bitboard::set_bit(white_p_bb, square); }
				else if (c == 'R') { Bitboard::set_bit(white_r_bb, square); }
				else if (c == 'N') { Bitboard::set_bit(white_n_bb, square); }
				else if (c == 'B') { Bitboard::set_bit(white_b_bb, square); }
				else if (c == 'Q') { Bitboard::set_bit(white_q_bb, square); }
				else if (c == 'K') { Bitboard::set_bit(white_k_bb, square); }

				file++;
			}
		}
	}

	white_to_move = sections[1] == "w" ? true : false;

	// FEN castling rights
	if (sections[2] != "-") {
		for (auto& c : sections[2]) {
			if (c == 'K') { castling_rights |= (1ULL << 3); }
			else if (c == 'Q') { castling_rights |= (1ULL << 2); }
			else if (c == 'k') { castling_rights |= (1ULL << 1); }
			else if (c == 'q') { castling_rights |= (1ULL << 0); }
		}
	}

	// FEN en passant square
	if (sections[3] != "-") {
		en_passant_sq = get_square_index(sections[3]);
	}

	half_move_clock = std::stoi(sections[4]);
	full_move_num = std::stoi(sections[5]);
}

void Engine::Board::print_board() {
	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 0; file < 8; file++) {
			int square = rank * 8 + file; 
			char piece = '.';

			if (Bitboard::get_bit(black_p_bb, square)) { piece = 'p'; }
			else if (Bitboard::get_bit(black_r_bb, square)) { piece = 'r'; }
			else if (Bitboard::get_bit(black_n_bb, square)) { piece = 'n'; }
			else if (Bitboard::get_bit(black_b_bb, square)) { piece = 'b'; }
			else if (Bitboard::get_bit(black_q_bb, square)) { piece = 'q'; }
			else if (Bitboard::get_bit(black_k_bb, square)) { piece = 'k'; }
			else if (Bitboard::get_bit(white_p_bb, square)) { piece = 'P'; }
			else if (Bitboard::get_bit(white_r_bb, square)) { piece = 'R'; }
			else if (Bitboard::get_bit(white_n_bb, square)) { piece = 'N'; }
			else if (Bitboard::get_bit(white_b_bb, square)) { piece = 'B'; }
			else if (Bitboard::get_bit(white_q_bb, square)) { piece = 'Q'; }
			else if (Bitboard::get_bit(white_k_bb, square)) { piece = 'K'; }

			std::cout << piece << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


std::vector<std::string> Engine::Board::delimited_str_to_vector(const std::string& str, std::string delimiter)
{
	std::vector<std::string> res;
	size_t pos = 0;

	while (str.substr(pos).find(delimiter) != std::string::npos)
	{
		res.push_back(str.substr(pos, str.substr(pos).find(delimiter)));
		pos += str.substr(pos).find(delimiter) + delimiter.size();
	}

	res.push_back(str.substr(pos));

	return res;
}