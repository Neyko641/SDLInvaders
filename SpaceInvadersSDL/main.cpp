#include <Windows.h>
#include <GL/gl.h>
#include <SDL.h>
#include <assert.h>
#include <iostream>



/*
TODO:
* Alien
-> What do aliens have
1 > position on the screen
2 > Dimension -> Width/Height
* Bullet
1 > position on the screen
2 > Dimension -> Width/Height
3 > Speed of bullet
4 > size

-> Create the previous 2 points
-> Change position -> draw it -> rinse and repeat
*/

void DrawBullet(float x, float y) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.01 + x, 0.01 + y);
	glVertex2f(0.01 + x, 0.01 + y);
	glVertex2f(0.0 + x, 0.0 + y);
	glEnd();
}
void DrawPlayer(float x, float y) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.1+x, 0.0+y);
	glVertex2f( 0.1+x, 0.0+y);
	glVertex2f( 0.0+x, 0.1+y);
	glEnd();
}

//TODO make a handleEvent function that will handle individual button presses
/*bool eventHandler(SDL_Event e) {
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT: return false;
			break;
		}
	}
}*/

int main(int argc, char* argv[]) {
	
	//Vector holding the x and y coordinates so that can be reused
	struct Vec2f {
		float x,y;
	};
	struct Size {
		int height;
		int width;
	};
	Size windowRes;
	
	windowRes.height = 600;
	windowRes.width = 800;
	struct Player {
		Vec2f position;
		Vec2f bullet;
		int score;
		int lives = 3;
	};
	struct Aliens {
		Vec2f position;
		int points; // range of 50 to 300 depending on the type of alien killed.
	};
	Player player;
	player.position.x = 0.0F;
	player.position.y = -0.8F;
	player.bullet.x = player.position.x;
	player.bullet.y = player.position.y;
	struct KeyPress {
		bool keyLeft = false;
		bool keyRight = false;
		bool keyShoot = false;
	};
	KeyPress keyPress;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowRes.width, windowRes.height, SDL_WINDOW_OPENGL);
	assert(window);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	assert(glContext);
	bool isWindowOpen = true;
	while (isWindowOpen) {
		SDL_Event event;
		//listens for events.
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { // check if the window is closed
				isWindowOpen = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					keyPress.keyShoot = true;
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					keyPress.keyLeft = true;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					keyPress.keyRight = true;
				}
			}
			else if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					keyPress.keyLeft = false;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					keyPress.keyRight = false;
				}
				else if (event.key.keysym.sym == SDLK_SPACE && player.bullet.y >= 0.1) {
					keyPress.keyShoot = false;
				}
				std::cout << player.bullet.y << std::endl;
			}
		}
		if (keyPress.keyLeft) {
			player.position.x -= 0.01F;
		}
		else if (keyPress.keyRight) {
			player.position.x += 0.01F;
		}
		if (keyPress.keyShoot) {
			player.bullet.y += 0.1F;
		}
		//background color
		glClearColor(0.0F, 0.0F, 0.1F, 1.0F);
		//background/foreground clear
		glClear(GL_COLOR_BUFFER_BIT);
		
		DrawPlayer(player.position.x, player.position.y);
		DrawBullet(player.bullet.x, player.bullet.y);
		
		//Display objects
		SDL_GL_SwapWindow(window); 
	}
	return 0;
}