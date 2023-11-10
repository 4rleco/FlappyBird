#pragma once

struct Obstacle
{
	float initPosX;
	float initPosY;

	float posY;
	float posX;

	int width;
	int height;

	float speed;
};

// inicializa los obst�culos
void InitObstacle(Obstacle& obstacle, float posY, int height);

// resetea la posicion del obst�culo
void ResetObstaclePosition(Obstacle& obstacle, float posY, int height);