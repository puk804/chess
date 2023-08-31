#pragma once

enum class Unit{
	None = 0,
	Pawn = 1,
	Rook = 2,
	Knight = 3,
	Bishop = 4,
	Queen = 5,
	King = 6
};

enum class Team {
	None = 0,
	White = 1,	// 체스판 위쪽 팀
	Black = 2	// 체스판 아래쪽 팀
};

enum class Move {
	None = 0,
	STRAIGHT = 1,	// 체스판 위쪽 팀
	DIAGONAL = 2	// 체스판 아래쪽 팀
};