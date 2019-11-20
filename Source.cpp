
// Pong Colin Thomas 2019

// includes
#include <Windows.h>


// declare

int screenWidth = 120;
int screenHeight = 40;

float ballX = 40.0f;
float ballY = 15.0f;

float playerX = 15.0f;
float playerY = 25.0f;

float opponentX = 105;
float opponentY = 25;

float moveX = -0.03f;
float moveY = -0.02f;

float ballSpeed = 0.03f;



// init



int main() {

	// Get console handle
	wchar_t *screen = new wchar_t[screenWidth * screenHeight];
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	DWORD dwBytesWritten = 0;

	wchar_t block = 0x2588;

	while (1) {

		int iBx = (int)(ballX);
		int iBy = (int)(ballY);

		int iPx = (int)(playerX);
		int iPy = (int)(playerY);

		int iOx = (int)(opponentX);
		int iOy = (int)(opponentY);

	
		
		// Keyboard input moving player and handling collision

		if(GetAsyncKeyState((unsigned short) 'W' ))
		{
			if (screen[(iPy - 3) * screenWidth + iPx] != block)
			{
				playerY -= .02f;
			}
		}

		if (GetAsyncKeyState((unsigned short) 'S'))
		{
			if (screen[(iPy + 3) * screenWidth + iPx] != block)
			{
				playerY += .02f;
			}
		}



		

		//Draw the map outline
		for (int x = 0; x < screenWidth; x++) {
			for (int y = 0; y < screenHeight; y++) {
				if (x == 0 || x == screenWidth - 1)
				{
					screen[y * screenWidth + x] = block;
				}
				else if (y == 0 || y == screenHeight - 1) {
					screen[y * screenWidth + x] = block;
				}
				else {
					screen[y * screenWidth + x] = ' ';
				}

			}
		}


		// Draw the ball
		wchar_t ball = 'O';

		if (screen[iBy * screenWidth + iBx] != block)
		{
			screen[iBy * screenWidth + iBx] = ball;
		}

		// Draw the player

		if(screen[(iPy + 2) * screenWidth + iPx] != block && screen[(iPy - 2) * screenWidth + iPx] != block)
		{
			wchar_t paddle = 0x2588; 
			screen[iPy * screenWidth + iPx] = paddle;
			screen[(iPy + 2) * screenWidth + iPx] = paddle;
			screen[(iPy + 1) * screenWidth + iPx] = paddle;
			screen[(iPy - 1) * screenWidth + iPx] = paddle;
			screen[(iPy - 2) * screenWidth + iPx] = paddle;
		}

		// Draw the opponent

		if (screen[(iOy + 2) * screenWidth + iOx] != block && screen[(iOy - 2) * screenWidth + iOx] != block)
		{
			wchar_t paddle = 0x2588;
			screen[iOy * screenWidth + iOx] = paddle;
			screen[(iOy + 2) * screenWidth + iOx] = paddle;
			screen[(iOy + 1) * screenWidth + iOx] = paddle;
			screen[(iOy - 1) * screenWidth + iOx] = paddle;
			screen[(iOy - 2) * screenWidth + iOx] = paddle;
		}

		// Move the opponent

		int destY;
		float slope = moveX/moveY;
		
		destY = (int)(opponentX*(slope) + ballY);
		
		if(destY < iOy)
		{
			if (screen[(iOy - 3) * screenWidth + iOx] != block)
			{
				opponentY -= .02f;
			}
		}
		if (destY > iOy)
		{
			if (screen[(iOy + 3) * screenWidth + iOx] != block)
			{
				opponentY += .02f;
			}
		}



		// Start the ball
		
		ballX += moveX;
		ballY += moveY;

		//Bounce the ball
		
		if (screen[iBy * screenWidth + iBx - 1] == block)
		{
			moveX = ballSpeed;
		}
		if (screen[iBy * screenWidth + iBx + 1] == block )
		{
			moveX = -ballSpeed;
		}
		if (screen[(iBy + 1) * screenWidth + iBx] == block)
		{
			moveY = -ballSpeed;
		}
		if (screen[(iBy - 1) * screenWidth + iBx] == block)
		{
			moveY = ballSpeed;
		}

		WriteConsoleOutputCharacter(console, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}
}



