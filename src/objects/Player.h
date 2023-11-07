#pragma once

struct Player
{
	float initPosX;
	float initPosY;

	float posX;
	float posY;

	float speed;

	int width;
	int height;
};

// inicializa el jugador
void InitPlayer(Player& player);

// resetea la posici�n del jugador
void ResetPlayerPosition(Player& player);