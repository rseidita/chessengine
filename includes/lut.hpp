/** @file */
#pragma once
#include <iostream>
#include <cstdint>
#include <array>
#include <stdexcept> // Required to throw errors
#include "types.hpp"
#include "position.hpp"

/*
8   56 # # # # # # # # 63
7   48 # # # # # # # # 55
6   40 # # # # # # # # 47
5   32 # # # # # # # # 39
4   24 # # # # # # # # 31
3   16 # # # # # # # # 23
2   8  # # # # # # # # 15
1   0  # # # # # # # # 7 
    A       ...        H
*/

// 2 types of pieces
// sliding: rook, bishop, queens
// can go to a certain square if
// 1. It's on their sliding direction
// 2. There are no obstructing pieces along that direct
// leaping: king, pawn, knight
// can go to a certain square if
// 1. It's on their leaping direction
// for each piece, calculate the landing squares
// no chess rules

/// LUT with magic bitboard attacks for the rook
/// first index is the square index, second the magic index 
/// 4096 is the largest number of blockers
extern uint64_t Rattacks[nCols*nRows][4096];
/// LUT with magic bitboard attacks for the bishop
/// first index is the square index, second the magic index 
/// 4096 is the largest number of blockers
extern uint64_t Battacks[nCols*nRows][4096];

/// LUT containing the squares in between.
/// If A and B are on the same (file,rank,diagonal)
/// BetweenBB[A][B] returns a bitboard containing the 
/// squares connecting them
/// else it return NULL Bitboard
extern Bitboard BetweenBB[nCols*nRows][nCols*nRows];

/// Initialize the lut (used only for the BetweenBB so far)
void init_lut();

/// Fill the BetweenBB LUT
void generate_inBetweenLUT();

/// calculate the in between bitboard between sq1 and sq2
Bitboard calculate_inBetween(Square sq1, Square sq2);

// to generate the LUT from scratch
/*! Generates a LUT for the straight landings of white pawns. 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> wpawn_straight_lut();

/*! Generates a LUT for the landings of white pawn that moves 2 squares (first move). 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> wpawn_doublestraight_lut();
/*! Generates a LUT for the straight landings of black pawns. 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> bpawn_straight_lut();
/*! Generates a LUT for the landings of black pawn that moves 2 squares (first move). 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> bpawn_doublestraight_lut();
/*! Generates a LUT for the landings of white pawn that diagonally for captures. 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> wpawn_diagcapture_lut();
/*! Generates a LUT for the landings of black pawn that diagonally for captures. 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> bpawn_diagcapture_lut();
/*! Generates a LUT for the knight landings. 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> knight_position_lut();
/*! Generates a LUT for the king landings. 
    \return array<uint64_t,64>
*/  
std::array<uint64_t,64> king_position_lut();

/*! Generates a LUT for landings along straight lines. Lines must NOT intersect friendly or opponent's pieces. Lines must NOT land on friendly pieces. Lines can land on opponent's pieces.
    \param Square Square to be considered (0-63)
    \param uint64_t Occupancy of the opponent's pieces as a bitboard
    \param uint64_t Occupancy of friendly pieces as a bitboard
    \return uint64_t
*/  
uint64_t straight_lines(Square, uint64_t, uint64_t);
/*! Generates a LUT for landings along diagonal lines. Lines must NOT intersect friendly or opponent's pieces. Lines must NOT land on friendly pieces. Lines can land on opponent's pieces.
    \param Square Square to be considered (0-63)
    \param uint64_t Occupancy of the opponent's pieces as a bitboard
    \param uint64_t Occupancy of friendly pieces as a bitboard
    \return uint64_t BitBoard with possible landings
*/  
uint64_t diago_lines(Square, uint64_t, uint64_t);
/*! Generates a LUT for landings of rooks. Lines must NOT intersect friendly or opponent's pieces. Lines must NOT land on friendly pieces. Lines can land on opponent's pieces.
    \param Square Square to be considered (0-63)
    \param uint64_t Occupancy of friendly pieces as a bitboard
    \param uint64_t Occupancy of the opponent's pieces as a bitboard
    \return uint64_t BitBoard with possible landings
*/  
uint64_t rook_landings(Square, uint64_t, uint64_t);
/*! Generates a LUT for landings of bishops. Lines must NOT intersect friendly or opponent's pieces. Lines must NOT land on friendly pieces. Lines can land on opponent's pieces.
    \param Square Square to be considered (0-63)
    \param uint64_t Occupancy of friendly pieces as a bitboard
    \param uint64_t Occupancy of the opponent's pieces as a bitboard
    \return uint64_t BitBoard with possible landings
*/  
uint64_t bishop_landings(Square, uint64_t, uint64_t);
/*! Generates a LUT for landings of queens. Lines must NOT intersect friendly or opponent's pieces. Lines must NOT land on friendly pieces. Lines can land on opponent's pieces.
    \param Square Square to be considered (0-63)
    \param uint64_t Occupancy of friendly pieces as a bitboard
    \param uint64_t Occupancy of the opponent's pieces as a bitboard
    \return uint64_t BitBoard with possible landings
*/  
uint64_t queen_landings(Square, uint64_t, uint64_t);
/*! Conveniente function to get landings for sliding pieces
    \param PieceType Sliding piece type
    \param Square Square to be considered (0-63)
    \param uint64_t Occupancy of friendly pieces as a bitboard
    \param uint64_t Occupancy of the opponent's pieces as a bitboard
    \return uint64_t BitBoard with possible landings
*/  
Bitboard sliding_peices_landings(PieceType, Square, uint64_t, uint64_t);

// hard coded LUT
/*! Hard coded King LUT
*/  
const LUT king_lut = {
770ULL, 1797ULL, 3594ULL, 7188ULL, 14376ULL, 28752ULL, 57504ULL, 49216ULL, 197123ULL, 460039ULL, 920078ULL, 1840156ULL, 3680312ULL, 7360624ULL, 14721248ULL, 12599488ULL, 
50463488ULL, 117769984ULL, 235539968ULL, 471079936ULL, 942159872ULL, 1884319744ULL, 3768639488ULL, 3225468928ULL, 12918652928ULL, 30149115904ULL, 60298231808ULL, 120596463616ULL, 241192927232ULL, 482385854464ULL, 964771708928ULL, 825720045568ULL, 3307175149568ULL, 7718173671424ULL, 15436347342848ULL, 30872694685696ULL, 61745389371392ULL, 123490778742784ULL, 246981557485568ULL, 211384331665408ULL, 846636838289408ULL, 1975852459884544ULL, 3951704919769088ULL, 7903409839538176ULL, 15806819679076352ULL, 31613639358152704ULL, 63227278716305408ULL, 54114388906344448ULL, 216739030602088448ULL, 505818229730443264ULL, 1011636459460886528ULL, 2023272918921773056ULL, 4046545837843546112ULL, 8093091675687092224ULL, 16186183351374184448ULL, 13853283560024178688ULL, 144959613005987840ULL, 362258295026614272ULL, 724516590053228544ULL, 1449033180106457088ULL, 2898066360212914176ULL, 5796132720425828352ULL, 11592265440851656704ULL, 4665729213955833856ULL};

/*! Hard coded black Pawn capture LUT
*/  
const LUT bpawn_cap_lut = {0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 2ULL, 5ULL, 10ULL, 20ULL, 40ULL, 80ULL, 160ULL, 64ULL, 512ULL, 1280ULL, 2560ULL, 5120ULL, 10240ULL, 20480ULL, 40960ULL, 16384ULL, 131072ULL, 327680ULL, 655360ULL, 1310720ULL, 2621440ULL, 5242880ULL, 10485760ULL, 4194304ULL, 33554432ULL, 83886080ULL, 167772160ULL, 335544320ULL, 671088640ULL, 1342177280ULL, 2684354560ULL, 1073741824ULL, 8589934592ULL, 21474836480ULL, 42949672960ULL, 85899345920ULL, 171798691840ULL, 343597383680ULL, 687194767360ULL, 274877906944ULL, 2199023255552ULL, 5497558138880ULL, 10995116277760ULL, 21990232555520ULL, 43980465111040ULL, 87960930222080ULL, 175921860444160ULL, 70368744177664ULL, 562949953421312ULL, 1407374883553280ULL, 2814749767106560ULL, 5629499534213120ULL, 11258999068426240ULL, 22517998136852480ULL, 45035996273704960ULL, 18014398509481984};
/*! Hard coded black Pawn forward LUT
*/  
const LUT bpawn_fw_lut = {0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 1ULL, 2ULL, 4ULL, 8ULL, 16ULL, 32ULL, 64ULL, 128ULL, 256ULL, 512ULL, 1024ULL, 2048ULL, 4096ULL, 8192ULL, 16384ULL, 32768ULL, 65536ULL, 131072ULL, 262144ULL, 524288ULL, 1048576ULL, 2097152ULL, 4194304ULL, 8388608ULL, 16777216ULL, 33554432ULL, 67108864ULL, 134217728ULL, 268435456ULL, 536870912ULL, 1073741824ULL, 2147483648ULL, 4294967296ULL, 8589934592ULL, 17179869184ULL, 34359738368ULL, 68719476736ULL, 137438953472ULL, 274877906944ULL, 549755813888ULL, 1099511627776ULL, 2199023255552ULL, 4398046511104ULL, 8796093022208ULL, 17592186044416ULL, 35184372088832ULL, 70368744177664ULL, 140737488355328ULL, 281474976710656ULL, 562949953421312ULL, 1125899906842624ULL, 2251799813685248ULL, 4503599627370496ULL, 9007199254740992ULL, 18014398509481984ULL, 36028797018963968ULL};
/*! Hard coded black Pawn double forward LUT
*/  
const LUT bpawn_doublefw_lut = {0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 4294967296ULL, 8589934592ULL, 17179869184ULL, 34359738368ULL, 68719476736ULL, 137438953472ULL, 274877906944ULL, 549755813888ULL, 1099511627776ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL};

/*! Hard coded white Pawn double forward LUT
*/  
const LUT wpawn_cap_lut = {512ULL, 1280ULL, 2560ULL, 5120ULL, 10240ULL, 20480ULL, 40960ULL, 16384ULL, 131072ULL, 327680ULL, 655360ULL, 1310720ULL, 2621440ULL, 5242880ULL, 10485760ULL, 4194304ULL, 33554432ULL, 83886080ULL, 167772160ULL, 335544320ULL, 671088640ULL, 1342177280ULL, 2684354560ULL, 1073741824ULL, 8589934592ULL, 21474836480ULL, 42949672960ULL, 85899345920ULL, 171798691840ULL, 343597383680ULL, 687194767360ULL, 274877906944ULL, 2199023255552ULL, 5497558138880ULL, 10995116277760ULL, 21990232555520ULL, 43980465111040ULL, 87960930222080ULL, 175921860444160ULL, 70368744177664ULL, 562949953421312ULL, 1407374883553280ULL, 2814749767106560ULL, 5629499534213120ULL, 11258999068426240ULL, 22517998136852480ULL, 45035996273704960ULL, 18014398509481984ULL, 144115188075855872ULL, 360287970189639680ULL, 720575940379279360ULL, 1441151880758558720ULL, 2882303761517117440ULL, 5764607523034234880ULL, 11529215046068469760ULL, 4611686018427387904ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL};
/*! Hard coded white Pawn forward LUT
*/  
const LUT wpawn_fw_lut = {256ULL,512ULL,1024ULL,2048ULL,4096ULL,8192ULL,16384ULL,32768ULL,65536ULL,131072ULL,262144ULL,524288ULL,1048576ULL,2097152ULL,4194304ULL,8388608ULL,16777216ULL,33554432ULL,67108864ULL,134217728ULL,268435456ULL,536870912ULL,1073741824ULL,2147483648ULL,4294967296ULL,8589934592ULL,17179869184ULL,34359738368ULL,68719476736ULL,137438953472ULL,274877906944ULL,549755813888ULL,1099511627776ULL,2199023255552ULL,4398046511104ULL,8796093022208ULL,17592186044416ULL,35184372088832ULL,70368744177664ULL,140737488355328ULL,281474976710656ULL,562949953421312ULL,1125899906842624ULL,2251799813685248ULL,4503599627370496ULL,9007199254740992ULL,18014398509481984ULL,36028797018963968ULL,72057594037927936ULL,144115188075855872ULL,288230376151711744ULL,576460752303423488ULL,1152921504606846976ULL,2305843009213693952ULL,4611686018427387904ULL,9223372036854775808ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
/*! Hard coded white Pawn double forward LUT
*/  
const LUT wpawn_doublefw_lut = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,16777216ULL,33554432ULL,67108864ULL,134217728ULL,268435456ULL,536870912ULL,1073741824ULL,2147483648ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
/*! Hard coded knight LUT
*/  
const LUT knight_lut{132096ULL,329728ULL,659712ULL,1319424ULL,2638848ULL,5277696ULL,10489856ULL,4202496ULL,33816580ULL,84410376ULL,168886289ULL,337772578ULL,675545156ULL,1351090312ULL,2685403152ULL,1075839008ULL,8657044482ULL,21609056261ULL,43234889994ULL,86469779988ULL,172939559976ULL,345879119952ULL,687463207072ULL,275414786112ULL,2216203387392ULL,5531918402816ULL,11068131838464ULL,22136263676928ULL,44272527353856ULL,88545054707712ULL,175990581010432ULL,70506185244672ULL,567348067172352ULL,1416171111120896ULL,2833441750646784ULL,5666883501293568ULL,11333767002587136ULL,22667534005174272ULL,45053588738670592ULL,18049583422636032ULL,145241105196122112ULL,362539804446949376ULL,725361088165576704ULL,1450722176331153408ULL,2901444352662306816ULL,5802888705324613632ULL,11533718717099671552ULL,4620693356194824192ULL,288234782788157440ULL,576469569871282176ULL,1224997833292120064ULL,2449995666584240128ULL,4899991333168480256ULL,9799982666336960512ULL,1152939783987658752ULL,2305878468463689728ULL,1128098930098176ULL,2257297371824128ULL,4796069720358912ULL,9592139440717824ULL,19184278881435648ULL,38368557762871296ULL,4679521487814656ULL,9077567998918656ULL};


/// LUT containing Pawn attacks, not all moves
const LUT PawnAttacks[COLOR_NB] = {wpawn_cap_lut,bpawn_cap_lut};
/// LUT containing Pawn fw moves, not all moves
const LUT PawnFW[COLOR_NB] = {wpawn_fw_lut,bpawn_fw_lut};
/// LUT containing Pawn 2fw moves, not all moves
const LUT Pawn2FW[COLOR_NB] = {wpawn_doublefw_lut,bpawn_doublefw_lut};