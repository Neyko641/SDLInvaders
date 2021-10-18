#include <Windows.h>
#include <GL/gl.h>
#include <SDL.h>
#include <assert.h>
#include <iostream>
#include <cmath>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

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


void DrawPlayer(float x, float y) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.1+x, 0.0+y);
	glVertex2f( 0.1+x, 0.0+y);
	glVertex2f( 0.0+x, 0.1+y);
	glEnd();
}
int main(int argc, char* argv[]) {
	
	//Vector holding the x and y coordinates so that can be reused
	struct Vec2f {
		float x,y;
	};
	struct Player {
		Vec2f position;
	};
	
	Player player;
	player.position.x = 0;
	player.position.y = -0.5;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	assert(window);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	assert(glContext);
	bool keyLeft = false;
	bool keyRight = false;
	bool isWindowOpen = true;
	while (isWindowOpen) {
		SDL_Event event;
		//listens for events.
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { // check if the window is closed
				isWindowOpen = false;
			}
			
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					keyLeft = true;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					keyRight = true;
				}
			}
			else if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_a) {
					keyLeft = false;
				}
				else if (event.key.keysym.sym == SDLK_d) {
					keyRight = false;
				}
			}
		}
		if (keyLeft) {
			player.position.x -= 0.01;
		}
		else if (keyRight) {
			player.position.x += 0.01;
		}
		//background color
		glClearColor(0, 0, 0.1, 1);
		//background/foreground clear
		glClear(GL_COLOR_BUFFER_BIT);
		
		DrawPlayer(player.position.x, player.position.y);
		
		//Display objects
		SDL_GL_SwapWindow(window); 
	}
	return 0;
}