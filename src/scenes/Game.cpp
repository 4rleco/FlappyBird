#include "Game.h"


#include <iostream>

using namespace std;


void DrawObjects(Player player, Obstacle obstacle1, Obstacle obstacle2)
{
	DrawRectangle(static_cast<int>(player.posX), static_cast<int>(player.posY), player.width, player.height, RED);

	DrawRectangle(static_cast<int>(obstacle1.posX), static_cast<int>(obstacle1.posY), obstacle1.width, obstacle1.height, ORANGE);

	DrawRectangle(static_cast<int>(obstacle2.posX), static_cast<int>(obstacle2.posY), obstacle2.width, obstacle2.height, ORANGE);
}

// mov del jugador
void PlayerMovement(Player& player)
{
	if (IsKeyDown(KEY_W))
	{
		player.posY -= player.speed * GetFrameTime();
	}

	else
	{
		player.posY += player.speed * GetFrameTime();
	}
}

// el jugador no desaparece por arriba y avisa si se va para abajo
void PlayerScreenLimits(Player& player)
{
	if (player.posY <= 0)
	{
		player.posY = 0;
	}

	if (player.posY + player.height >= GetScreenHeight())
	{
		player.fall = true;
	}
}

// mov del obst�culo
void ObstacleMovement(Obstacle& obstacle1, Obstacle& obstacle2, Player player)
{
	obstacle1.posX -= obstacle1.speed * GetFrameTime();

	obstacle2.posX -= obstacle2.speed * GetFrameTime();

	if (obstacle1.posX <= 0)
	{
		obstacle1.posX = obstacle1.initPosX;

		obstacle1.height = rand() % GetScreenHeight() - (player.height + player.height / 2);
	}

	if (obstacle2.posX <= 0)
	{
		obstacle2.posX = obstacle2.initPosX;

		obstacle2.posY = static_cast<float>(rand() % GetScreenHeight() + (obstacle1.height + player.height + player.height / 2));

		if (obstacle2.posY >= GetScreenHeight())
		{
			obstacle2.posY = static_cast<float>(GetScreenHeight() - 10);
		}
	}
}

// colision del juagador con el obst�culo
bool PlayerObstacleCollision(Player& player, Obstacle& obstacle)
{
	if ((player.posX + player.width >= obstacle.posX) &&
		(player.posX <= obstacle.posX + obstacle.width) &&
		(player.posY + player.height >= obstacle.posY) &&
		(player.posY <= obstacle.posY + obstacle.height))
	{
		return true;
	}

	return false;
}


void ResetGame(Player& player, Obstacle& obstacle1, Obstacle& obstacle2)
{
	if (PlayerObstacleCollision(player, obstacle1) || player.fall)
	{
		ResetPlayer(player);
		ResetObstacle(obstacle1, 0.0f, 300);
		ResetObstacle(obstacle2, static_cast<float>(GetScreenHeight() / 2), GetScreenHeight());
	}

	if (PlayerObstacleCollision(player, obstacle2) || player.fall)
	{
		ResetPlayer(player);
		ResetObstacle(obstacle1, 0.0f, 300);
		ResetObstacle(obstacle2, static_cast<float>(GetScreenHeight() / 2 + player.height), GetScreenHeight());
	}
}

void Update(Player& player, Obstacle& obstacle1, Obstacle& obstacle2, Texture2D& foreground, Texture2D& midground, float& scrollingFore, float& scrollingMid)
{
	scrollingFore -= 100.0f * GetFrameTime();
	scrollingMid -= 50.0f * GetFrameTime();

	if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;
	if (scrollingMid <= -midground.width * 2) scrollingMid = 0;

	PlayerMovement(player);

	PlayerScreenLimits(player);

	ObstacleMovement(obstacle1, obstacle2, player);

	ResetGame(player, obstacle1, obstacle2);

	DrawTextureEx(midground, Vector2{ scrollingMid, 300 }, 0.0f, 2.0f, WHITE);
	DrawTextureEx(midground, Vector2{ midground.width * 2 + scrollingMid, 300 }, 0.0f, 2.0f, WHITE);

	DrawTextureEx(foreground, Vector2{ scrollingFore, 350 }, 0.0f, 2.0f, WHITE);
	DrawTextureEx(foreground, Vector2{ foreground.width * 2 + scrollingFore, 350 }, 0.0f, 2.0f, WHITE);
}