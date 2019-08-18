/*
This file runs using SDL (Simple Directmedia Layer).
This is a simple Tic-Tac-Toe game using mouse click events.
The background will flash the color of the next person's turn and turn dark grey when there has been a winner.
Updates on whether there has been a winner is displayed in the terminal.
*/
#include <iostream>
#include <SDL2/SDL.h>
#define fps 120
using namespace std;

const int SQR = 100;//the side of squares
const int BUFF = 75;//buffer between edges of screen
const int SIDE = (SQR*3) + BUFF*2;//side of the screen

SDL_Window *myWindow = NULL;//winoow and renderer
SDL_Renderer *myRenderer = NULL;

SDL_Rect quads[ 9 ];//position of our squares

bool pressedTiles[ 9 ] = {false,false,false,false,false,false,false,false,false};
int playerPressed[ 9 ] = {2,2,2,2,2,2,2,2,2};

void init();
void loadMedia();
bool decidePlayer();
bool check( int tile[9], int player );
void renderFilledQuad( SDL_Rect myRect, int r, int g, int b );
void renderOutlineQuad( SDL_Rect myRect, int r, int g, int b );
void renderBasicQuad( SDL_Rect myRect[9] );
void render();
bool mouseIn( SDL_Rect myRect );
void cleanUp();

void capFrames( Uint32 start_tick ); 

void init()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	myWindow = SDL_CreateWindow( "Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SIDE, SIDE, SDL_WINDOW_SHOWN );
	myRenderer = SDL_CreateRenderer( myWindow, -1, SDL_RENDERER_ACCELERATED );
	
	SDL_SetRenderDrawColor( myRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( myRenderer );
}



void loadMedia()
{
	quads[ 0 ] = { BUFF + 0    , BUFF +     0, SQR, SQR };
	quads[ 1 ] = { BUFF + SQR  , BUFF +     0, SQR, SQR };
	quads[ 2 ] = { BUFF + SQR*2, BUFF +     0, SQR, SQR };

	quads[ 3 ] = { BUFF + 0    , BUFF +   SQR, SQR, SQR };
	quads[ 4 ] = { BUFF + SQR  , BUFF +   SQR, SQR, SQR };
	quads[ 5 ] = { BUFF + SQR*2, BUFF +   SQR, SQR, SQR };

	quads[ 6 ] = { BUFF + 0    , BUFF + SQR*2, SQR, SQR };
	quads[ 7 ] = { BUFF + SQR  , BUFF + SQR*2, SQR, SQR };
	quads[ 8 ] = { BUFF + SQR*2, BUFF + SQR*2, SQR, SQR };

	SDL_Surface* loadedSurface = NULL;
}


bool decidePlayer()
{
	bool playerOne = true;
	bool running = true;
	SDL_Event event;

	SDL_Rect quadPicker[2];

	quadPicker[0] = { 0       , 0 , SIDE/2, SIDE };
	quadPicker[1] = { (SIDE/2), 0 , SIDE/2, SIDE };

	while(running)
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				running = false;
			}
		}
		SDL_SetRenderDrawColor( myRenderer, 255, 255, 255, 255 );
		SDL_RenderClear( myRenderer );

		renderFilledQuad( quadPicker[0], 200, 50, 50 );
		renderFilledQuad( quadPicker[1], 50 , 50, 200);

		if( mouseIn(quadPicker[0]) )
		{
			renderFilledQuad( quadPicker[0], 150, 25, 25 );
			if( event.type == SDL_MOUSEBUTTONDOWN)
			{
				playerOne = true;
				running = false;
			}
		} else if( mouseIn(quadPicker[1]) )
		{
			renderFilledQuad( quadPicker[1], 25, 25, 150 );
			if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				playerOne = false;
				running  = false;
			}
		}	

		SDL_RenderPresent( myRenderer );
		capFrames( SDL_GetTicks() );
	}
	return playerOne;
}




bool check( int tile[9], int player )
{
	bool winner = false;
	
	for(int i = 0; i < 3; i++)
	{
		if( tile[i] == player && tile[i+3] == player && tile[i+6] == player )
		{
			winner = true;
			break;
		} else if( tile[0] == player && tile[0+4] == player && tile[0+8] == player )
		{
			winner = true;
			break;
		} else if( tile[2] == player && tile[2+2] == player && tile[2+4] == player )
		{
			winner = true;
			break;
		}
	}

	for( int i = 0; i <= 6; i+=3 )
	{
		if( tile[i] == player && tile[i+1] == player && tile[i+2] == player )
		{
			winner = true;
			break;
		}
	}

	return winner;
}



void renderFilledQuad( SDL_Rect myRect, int r, int g, int b )
{
	SDL_SetRenderDrawColor( myRenderer, r, g, b, 255 );
	SDL_RenderFillRect( myRenderer, &myRect );
}




void renderOutlineQuad( SDL_Rect myRect, int r, int g, int b )
{
	SDL_SetRenderDrawColor( myRenderer, r, g, b, 255 );
	SDL_RenderDrawRect( myRenderer, &myRect );
}



void render()
{
	for( int i = 0; i < 9; i++ )
	{
		renderOutlineQuad( quads[i], 0, 0, 0 );
		if( pressedTiles[i] == true && playerPressed[i] == 1)
		{
			renderFilledQuad( quads[i], 200, 50, 50 );
		}
		if( pressedTiles[i] == true && playerPressed[i] == 0)
		{
			renderFilledQuad( quads[i], 50, 50, 200 );
		}
	}
}




void renderBasicQuad( SDL_Rect myRect[9] )
{
	for( int i = 0; i < 9; i++ )
	{
		renderFilledQuad( quads[i], 255, 255, 255 );
	}
}




bool mouseIn( SDL_Rect myRect )
{
	bool buttonPressed = false;

	int x = 0; int y = 0;
	SDL_GetMouseState( &x, &y );

	if( x > myRect.x && x < (myRect.x + myRect.w) && y > myRect.y && y < (myRect.y + myRect.h) )
	{
		buttonPressed = true;
	}
	

	return buttonPressed;
}



void cleanUp()
{
	SDL_DestroyRenderer( myRenderer );
	myRenderer = NULL;
	SDL_DestroyWindow( myWindow );
	myWindow = NULL;

	SDL_Quit();
}



void capFrames( Uint32 start_tick)
{
	if((1000/fps) -  (SDL_GetTicks() - start_tick) ){
		SDL_Delay( 1000 / fps - (SDL_GetTicks() - start_tick));
	}
}




int main( int argc, char *args[] )
{
	system("clear");
	init();
	loadMedia();
	SDL_Event e;
	bool run = true;
	bool p1 = false;
	int pressedPos = 100;
	bool wasWinner = false;

	if(decidePlayer() == true)
	{
		p1 = true;
	} else if(decidePlayer() == false )
	{
		p1 = false;
	}
	while(run)
	{
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT )
				run = false;
		}

		SDL_SetRenderDrawColor( myRenderer, 128, 232, 206, 255 );
		SDL_RenderClear( myRenderer );

		if( wasWinner )
		{
			SDL_SetRenderDrawColor( myRenderer, 50, 50, 50, 255 );
			SDL_RenderClear( myRenderer );
		} 
		else if( p1 == true )
		{
			SDL_SetRenderDrawColor( myRenderer, 150, 25, 25, 255 );
			SDL_RenderClear( myRenderer );
		} else if ( p1 == false)
		{
			SDL_SetRenderDrawColor( myRenderer, 25, 25, 150, 255 );
			SDL_RenderClear( myRenderer );
		}

		
		renderBasicQuad( quads );

		for( int i = 0; i < 9; i++ )
		{
			if( mouseIn(quads[i]) && wasWinner == false )
			{
				renderFilledQuad( quads[i], 200, 200, 200 );
			}

			if ( mouseIn(quads[i]) && e.type == SDL_MOUSEBUTTONDOWN && pressedTiles[i] == false && wasWinner == false )
			{
				pressedTiles[ i ] = true;
				pressedPos = i;
				if( p1 == true )
				{
					p1 = false;
					playerPressed[ i ] = 1;
					break;
				} else
				{
					p1 = true;
					playerPressed[ i ] = 0;
					break;
				}

			}


		}
		render();
		SDL_RenderPresent( myRenderer );

		if( check( playerPressed, 1 ) == true && wasWinner == false )
		{
			cout << "Red Won!\n";
			wasWinner = true;
		} else if ( check( playerPressed, 0 ) == true && wasWinner == false )
		{
			cout << "Blue Won!\n";
			wasWinner = true;
		}

		capFrames( SDL_GetTicks() );
	}


	cleanUp();
	return 0;
}
