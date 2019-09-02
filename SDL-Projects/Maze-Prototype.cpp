#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

class Mouse
{
	public:
		SDL_Rect myRect;
};

class Wall
{
	public:
		SDL_Rect myRect;
		bool hardWall;
};



void init();
void loadMedia();
void renderFilledQuad( SDL_Rect myRect, int r, int g, int b );
void promptWait();

bool cursorIn( SDL_Rect myRect );
bool pickMaze();

void moveUp(  );
void moveDown( );
void moveLeft( );
void moveRight(  );


void cleanUp();
void capFrames( Uint32 start_tick );

const int fps = 10;
const int BORDER_SIZE = 5;
const int MOUSE_SIZE = 50;

const int NUM_W = 5; 
const int NUM_H = 3;

const int WIDTH = (MOUSE_SIZE*NUM_W) + (BORDER_SIZE*(NUM_W+1));
const int HEIGHT = (MOUSE_SIZE*NUM_H) + (BORDER_SIZE*(NUM_H+1));

int posX = 0;
int posY = 0;

SDL_Window *myWindow = NULL;
SDL_Renderer *myRenderer = NULL;

Mouse myMouse;
Wall yWall[(NUM_W-1)*(NUM_H)];
Wall xWall[(NUM_H-1)*(NUM_W)];

void init()
{
	SDL_Init( SDL_INIT_VIDEO );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	myWindow = SDL_CreateWindow( "Maze 3.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	 WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
	myRenderer = SDL_CreateRenderer( myWindow, -1, SDL_RENDERER_ACCELERATED );

	SDL_SetRenderDrawColor( myRenderer, 255, 255, 255, 255 );
	SDL_RenderClear( myRenderer ); SDL_RenderClear( myRenderer );
}


void loadMedia()
{
	myMouse.myRect = { BORDER_SIZE, BORDER_SIZE, MOUSE_SIZE, MOUSE_SIZE };

	int myX = 0;
	int myY = 0;

	for( int i = 0; i < (NUM_W-1)*(NUM_H); i++)
	{
		yWall[i].myRect.x = ((myX+1)*MOUSE_SIZE)+(BORDER_SIZE*(myX+1));
		yWall[i].myRect.y = (myY*MOUSE_SIZE)+(BORDER_SIZE*(myY+1)) - BORDER_SIZE;
		
		if( myX != NUM_W-2 )
		{
			myX++;
		} else
		{
			myX = 0;
			myY++;
		}

		yWall[i].myRect.w = BORDER_SIZE;
		yWall[i].myRect.h = MOUSE_SIZE + BORDER_SIZE*2;
		yWall[i].hardWall = true;
	}

	myX = 0;
	myY = 0;

	for( int i = 0; i < (NUM_H-1)*(NUM_W); i++)
	{
		xWall[i].myRect.x = ((myX)*MOUSE_SIZE)+(BORDER_SIZE*(myX+1)) - BORDER_SIZE;
		xWall[i].myRect.y = ((myY+1)*MOUSE_SIZE)+(BORDER_SIZE*(myY+1));
		
		if( myX != NUM_W-1 )
		{
			myX++;
		} else
		{
			myX = 0;
			myY++;
		}

		xWall[i].myRect.w = MOUSE_SIZE + BORDER_SIZE*2;
		xWall[i].myRect.h = BORDER_SIZE;
		xWall[i].hardWall = true;
	}

}


bool cursorIn( SDL_Rect myRect )
{
	bool cursorIn = false;
	int x = 0; int y = 0; 
	SDL_GetMouseState( &x, &y );
	if( x > myRect.x && x < (myRect.x + myRect.w) && y > myRect.y && y < (myRect.y + myRect.h) )
	{
		cursorIn = true;
	}
	return cursorIn;
}



void renderFilledQuad( SDL_Rect myRect, int r, int g, int b )
{
	SDL_SetRenderDrawColor( myRenderer, r, g, b, 255 );
	SDL_RenderFillRect( myRenderer, &myRect );
}



void moveUp()
{
	myMouse.myRect.y = myMouse.myRect.y - myMouse.myRect.h - BORDER_SIZE;
//	cout << posX << ", " << posY << endl;
}
void moveDown()
{
	myMouse.myRect.y = myMouse.myRect.y + myMouse.myRect.h + BORDER_SIZE;
//	cout << posX << ", " << posY << endl;
}
void moveLeft()
{
	myMouse.myRect.x = myMouse.myRect.x - myMouse.myRect.w - BORDER_SIZE;
//	cout << posX << ", " << posY << endl;
}
void moveRight()
{
	myMouse.myRect.x = myMouse.myRect.x + myMouse.myRect.w + BORDER_SIZE;
//	cout << posX << ", " << posY << endl;
}













bool pickMaze()
{
	bool gameOut = false;
	SDL_Event event;
	bool running = true;

	while(running)
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				gameOut = true;
				running = false;
			}else if ( event.key.keysym.sym == SDLK_RETURN )
			{
				running = false;
			}else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				for( int i = 0; i < (NUM_W-1)*(NUM_H); i++ )
				{
					if( cursorIn(yWall[i].myRect) == true )
						yWall[i].hardWall = false;
				}
				for( int i = 0; i < (NUM_H-1)*(NUM_W); i++ )
				{
					if( cursorIn(xWall[i].myRect) == true )
						xWall[i].hardWall = false;
				}
			} 
		SDL_SetRenderDrawColor( myRenderer, 255, 255, 255, 255 );
		SDL_RenderClear( myRenderer );
		for( int i = 0; i < (NUM_W-1)*(NUM_H); i++ )
		{
			if( yWall[i].hardWall == true )
				renderFilledQuad( yWall[i].myRect, 0, 0, 0 );
			else
				renderFilledQuad( yWall[i].myRect, 210, 210, 210 );
		}

		for( int i = 0; i < (NUM_H-1)*(NUM_W); i++ )
		{
			if( xWall[i].hardWall == true )
				renderFilledQuad( xWall[i].myRect, 0, 0, 0 );
			else
				renderFilledQuad( xWall[i].myRect, 210, 210, 210 );
		}
		}	
		SDL_RenderPresent( myRenderer );
		capFrames( SDL_GetTicks() );
	}
	return gameOut;
}





























int main( int argc, char *args[] )
{
	init(); loadMedia();
	SDL_Event e;


	bool run = true;

	SDL_Rect topBorder = {0,0,WIDTH, BORDER_SIZE};
	SDL_Rect bottomBorder = {0, HEIGHT-BORDER_SIZE, WIDTH, BORDER_SIZE };

	SDL_Rect leftBorder = {0, BORDER_SIZE, BORDER_SIZE, (HEIGHT-(BORDER_SIZE*2)) };
	SDL_Rect rightBorder = { WIDTH-BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, (HEIGHT-(BORDER_SIZE*2)) };

	if(pickMaze() == true )
		run = false;

	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
	SDL_SetCursor(cursor);

	SDL_Delay(1500);

	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(cursor);

	while(run)
	{
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT )
			{
				run = false;
			} 

			else if( e.type == SDL_KEYDOWN )
				switch( e.key.keysym.sym )
				{
					case SDLK_UP:
						posY = posY - 1;
//						cout << posX + ((NUM_H-1)*posY*2) << endl;
						if( posY >= 0 && xWall[ posX + ((NUM_H-1)*posY*2) ].hardWall == false )
							moveUp();
						else
							posY = posY + 1;
						break;
					case SDLK_DOWN:
						posY = posY + 1;
//						cout << posX + ((NUM_H-1)*(posY-1)*2) << endl;
						if( posY < NUM_H && xWall[ posX + ((NUM_H-1)*(posY-1)*2) ].hardWall == false )
							moveDown();
						else
							posY = posY - 1;
						break;
					case SDLK_LEFT:
						posX = posX - 1;
//						cout << (posX) + (posY*(NUM_W-1)) << endl;
						if( posX >= 0 && yWall[(posX) + (posY*(NUM_W-1))].hardWall == false )	
							moveLeft();
						else
							posX = posX + 1;
						break;
					case SDLK_RIGHT:
						posX = posX + 1;
//						cout << (posX-1) + (posY*(NUM_W-1)) << endl;
						if( posX < NUM_W && yWall[ (posX-1) + (posY*(NUM_W-1)) ].hardWall == false )
							moveRight();
						else
							posX = posX - 1;
						break;
				}
		}
		SDL_SetRenderDrawColor( myRenderer, 75, 75, 75, 255 );
		SDL_RenderClear( myRenderer );

		for( int i = 0; i < (NUM_W-1)*(NUM_H); i++ )
		{
			if( yWall[i].hardWall == true )
				renderFilledQuad( yWall[i].myRect, 0, 0, 0 );
			else
				renderFilledQuad( yWall[i].myRect, 80, 80, 80 );
		}

		for( int i = 0; i < (NUM_H-1)*(NUM_W); i++ )
		{
			if( xWall[i].hardWall == true )
				renderFilledQuad( xWall[i].myRect, 0, 0, 0 );
			else
				renderFilledQuad( xWall[i].myRect, 80, 80, 80 );
		}

		renderFilledQuad( topBorder, 0, 0, 0 );
		renderFilledQuad( bottomBorder, 0, 0, 0 );
		renderFilledQuad( leftBorder, 0, 0, 0 );
		renderFilledQuad( rightBorder, 0, 0, 0 );

		renderFilledQuad( myMouse.myRect, 150, 0, 0 );
		
		SDL_RenderPresent( myRenderer );
		capFrames( SDL_GetTicks() );
	}


	cleanUp();promptWait();
	return 0;
}
void capFrames( Uint32 start_tick){
	if((1000/fps) -  (SDL_GetTicks() - start_tick) ){
		SDL_Delay( 1000 / fps - (SDL_GetTicks() - start_tick));
	}}
void promptWait(){
	cout << "Press Enter To Continue...";
	cin.get();}
void cleanUp(){
	SDL_DestroyRenderer(myRenderer);
	myRenderer = NULL;
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	SDL_Quit();}
