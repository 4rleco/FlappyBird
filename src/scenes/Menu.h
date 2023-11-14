#pragma once

enum class Screen
{
	MENU,
	GAME,
	CREDITS
};

// dibuja el men�
void DrawMenu(Screen& screen);

// bot�n que vuelve al men�
void DrawReturnButton(Screen& screen, bool& returnToMenu);