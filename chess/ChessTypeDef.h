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
	White = 1,	// ü���� ���� ��
	Black = 2	// ü���� �Ʒ��� ��
};

enum class Move {
	None = 0,
	STRAIGHT = 1,	// ü���� ���� ��
	DIAGONAL = 2	// ü���� �Ʒ��� ��
};