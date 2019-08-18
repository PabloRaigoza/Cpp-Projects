/*
This is a Mega-Tic-Tac-Toe game made with SDL (Simple Directmedia Layer). This game is composed of a large
Tic-Tac-Toe game with regular Tic-Tac-Toe games in it's quadrants.
The background will flash the color of the next player's turn, and turn dark grey if there has been a winner.
Updates on who won and as well as who who a specific square, will be displayed in the terminal.

**RULES**
Rules are simple and are easier to describe when playing. TWO PLAYER GAME
1. Player 1 is decided at the start, RED or BLUE
2. The player going first can go anywhere they want on their first move.
3. After the Player 1 has gone, the position in the small sqaure determines which quadrant the next player has to go.
	The game will highlight the quadrant were the next player has to move in.
4. The position the player chose determines the next quadrant and ect.
5. Once a quadrant has been conquered, it will turn the color of the player who won it.
6. The objective is to capture three quadrants in a row like a regualer game of Tic-Tac-Toe
7. If player's position matches a quadrant that has already been conquered (by either player).
	Then the next player can move in whatever quadrant they like, so long as it hasn't been conquered.
*/
#include <iostream>
#include <SDL2/SDL.h>
#define fps 120
using namespace std;

const int SQ_SMALL = 50;
const int SQ_BIG = SQ_SMALL*3;
const int BUFF = 40;
const int LINE_WIDTH = 2;

const int SCR_SIDE = (SQ_BIG*3) + (BUFF*2) + (LINE_WIDTH*2);

SDL_Window *myWindow = NULL;
SDL_Renderer *myRenderer = NULL;

SDL_Rect quads[9][9];
SDL_Rect background[4];

void init();
void loadMedia();

bool decidePlayer();

bool mouseIn( SDL_Rect myRect );

void renderFilledQuad( SDL_Rect myRect, int r, int g, int b );
void renderAllQuads( bool pressedTiles[][9], int playerPressed[][9], int playerWon[9], int playerMove, bool winnerDeclared, bool firstMove, bool p1);

bool checkSquare( int tile[9], int player );
void cleanUp();



void capFrames( Uint32 start_tick );

void init()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	myWindow = SDL_CreateWindow( "Mega-Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
								SCR_SIDE, SCR_SIDE, SDL_WINDOW_SHOWN );
	myRenderer = SDL_CreateRenderer( myWindow, -1, SDL_RENDERER_ACCELERATED );

	SDL_SetRenderDrawColor( myRenderer, 255,255,255,255 );
	SDL_RenderClear( myRenderer );
}



void loadMedia()
{
	quads[0][0] = { BUFF                          , BUFF             , SQ_SMALL, SQ_SMALL};
	quads[0][1] = { BUFF + SQ_SMALL               , BUFF             , SQ_SMALL, SQ_SMALL};
	quads[0][2] = { BUFF + SQ_SMALL*2             , BUFF             , SQ_SMALL, SQ_SMALL};

	quads[0][3] = { BUFF                          , BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};
	quads[0][4] = { BUFF + SQ_SMALL               , BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};
	quads[0][5] = { BUFF + SQ_SMALL*2             , BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};

	quads[0][6] = { BUFF                          , BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};
	quads[0][7] = { BUFF + SQ_SMALL               , BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};
	quads[0][8] = { BUFF + SQ_SMALL*2             , BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};

	quads[1][0] = { LINE_WIDTH + SQ_BIG + BUFF                 ,  BUFF             , SQ_SMALL, SQ_SMALL};
	quads[1][1] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL      ,  BUFF             , SQ_SMALL, SQ_SMALL};
	quads[1][2] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2    ,  BUFF             , SQ_SMALL, SQ_SMALL};

	quads[1][3] = { LINE_WIDTH + SQ_BIG + BUFF                 ,  BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};
	quads[1][4] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL      ,  BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};
	quads[1][5] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2    ,  BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};

	quads[1][6] = { LINE_WIDTH + SQ_BIG + BUFF                 ,  BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};
	quads[1][7] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL      ,  BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};
	quads[1][8] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2    ,  BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};

	quads[2][0] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF             , BUFF             , SQ_SMALL, SQ_SMALL};
	quads[2][1] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL  , BUFF             , SQ_SMALL, SQ_SMALL};
	quads[2][2] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2, BUFF             , SQ_SMALL, SQ_SMALL};

	quads[2][3] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF             , BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};
	quads[2][4] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL  , BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};
	quads[2][5] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2, BUFF + SQ_SMALL  , SQ_SMALL, SQ_SMALL};

	quads[2][6] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF             , BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};
	quads[2][7] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL  , BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};
	quads[2][8] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2, BUFF + SQ_SMALL*2, SQ_SMALL, SQ_SMALL};




	quads[3][0] = { BUFF                           , LINE_WIDTH + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[3][1] = { BUFF + SQ_SMALL                , LINE_WIDTH + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[3][2] = { BUFF + SQ_SMALL*2              , LINE_WIDTH + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};

	quads[3][3] = { BUFF                           , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[3][4] = { BUFF + SQ_SMALL                , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[3][5] = { BUFF + SQ_SMALL*2              , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};

	quads[3][6] = { BUFF                           , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[3][7] = { BUFF + SQ_SMALL                , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[3][8] = { BUFF + SQ_SMALL*2              , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};

	quads[4][0] = { LINE_WIDTH + SQ_BIG + BUFF                  , LINE_WIDTH + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[4][1] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL       , LINE_WIDTH + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[4][2] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2     , LINE_WIDTH + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};

	quads[4][3] = { LINE_WIDTH + SQ_BIG + BUFF                  , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[4][4] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL       , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[4][5] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2     , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};

	quads[4][6] = { LINE_WIDTH + SQ_BIG + BUFF                  , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[4][7] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL       , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[4][8] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2     , LINE_WIDTH + (SQ_BIG) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};

	quads[5][0] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF              , (LINE_WIDTH) + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[5][1] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL   , (LINE_WIDTH) + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[5][2] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2 , (LINE_WIDTH) + (SQ_BIG) + BUFF               , SQ_SMALL, SQ_SMALL};

	quads[5][3] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF              , (LINE_WIDTH) + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[5][4] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL   , (LINE_WIDTH) + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[5][5] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2 , (LINE_WIDTH) + (SQ_BIG) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};

	quads[5][6] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF              , (LINE_WIDTH) + (SQ_BIG) + BUFF + (SQ_SMALL*2), SQ_SMALL, SQ_SMALL};
	quads[5][7] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL   , (LINE_WIDTH) + (SQ_BIG) + BUFF + (SQ_SMALL*2), SQ_SMALL, SQ_SMALL};
	quads[5][8] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2 , (LINE_WIDTH) + (SQ_BIG) + BUFF + (SQ_SMALL*2), SQ_SMALL, SQ_SMALL};




	quads[6][0] = { BUFF                           , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[6][1] = { BUFF + SQ_SMALL                , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[6][2] = { BUFF + SQ_SMALL*2              , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};

	quads[6][3] = { BUFF                           , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[6][4] = { BUFF + SQ_SMALL                , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[6][5] = { BUFF + SQ_SMALL*2              , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};

	quads[6][6] = { BUFF                           , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[6][7] = { BUFF + SQ_SMALL                , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[6][8] = { BUFF + SQ_SMALL*2              , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};

	quads[7][0] = { LINE_WIDTH + SQ_BIG + BUFF                  , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[7][1] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL       , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[7][2] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2     , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};

	quads[7][3] = { LINE_WIDTH + SQ_BIG + BUFF                  , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[7][4] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL       , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[7][5] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2     , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};

	quads[7][6] = { LINE_WIDTH + SQ_BIG + BUFF                  , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[7][7] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL       , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};
	quads[7][8] = { LINE_WIDTH + SQ_BIG + BUFF + SQ_SMALL*2     , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2  , SQ_SMALL, SQ_SMALL};

	quads[8][0] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF              , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[8][1] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL   , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};
	quads[8][2] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2 , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF               , SQ_SMALL, SQ_SMALL};

	quads[8][3] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF              , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[8][4] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL   , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};
	quads[8][5] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2 , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL    , SQ_SMALL, SQ_SMALL};

	quads[8][6] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF              , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + (SQ_SMALL*2), SQ_SMALL, SQ_SMALL};
	quads[8][7] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL   , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + (SQ_SMALL*2), SQ_SMALL, SQ_SMALL};
	quads[8][8] = { (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + SQ_SMALL*2 , (LINE_WIDTH*2) + (SQ_BIG*2) + BUFF + (SQ_SMALL*2), SQ_SMALL, SQ_SMALL};

	background[0] = { 0                 , 0                 , SCR_SIDE, BUFF - LINE_WIDTH              };
	background[1] = { 0                 , (SCR_SIDE - BUFF) + LINE_WIDTH , SCR_SIDE, BUFF - LINE_WIDTH };
	background[2] = { 0                 , BUFF  - LINE_WIDTH            , BUFF - LINE_WIDTH    , (SCR_SIDE - BUFF) + LINE_WIDTH };
	background[3] = { (SCR_SIDE - BUFF) + LINE_WIDTH , BUFF - LINE_WIDTH            , BUFF - LINE_WIDTH   , (SCR_SIDE - BUFF) - (LINE_WIDTH*4) };

}


void renderFilledQuad( SDL_Rect myRect, int r, int g, int b )
{
	SDL_SetRenderDrawColor( myRenderer, r,g,b,255 );
	SDL_RenderFillRect( myRenderer, &myRect );
}



bool mouseIn( SDL_Rect myRect )
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


bool decidePlayer()
{
	bool playerOne = true;
	bool running = true;
	SDL_Event event;

	SDL_Rect quadPicker[2];

	quadPicker[0] = { 0           , 0 , SCR_SIDE/2, SCR_SIDE };
	quadPicker[1] = { (SCR_SIDE/2), 0 , SCR_SIDE/2, SCR_SIDE };

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






void renderAllQuads( bool pressedTiles[][9], int playerPressed[][9], int playerWon[9], int playerMove, bool winnerDeclared, bool firstMove, bool p1 )
{
	for( int i = 0; i < 4; i++ )
	{
		if( p1 == true && winnerDeclared == false )
		{
			renderFilledQuad( background[i], 150, 0, 0 );
		} else if( p1 == false && winnerDeclared == false)
		{
			renderFilledQuad( background[i], 0, 0, 150 );
		} else if( winnerDeclared == true )
		{
			renderFilledQuad( background[i], 46, 46, 46 );
		}
	}

	for( int i = 0; i < 9; i++ )
	{

		for( int j = 0; j < 9; j++ )
		{
			if( pressedTiles[i][j] == true )
			{
				if( playerPressed[i][j] == 1 )
				{
					renderFilledQuad( quads[i][j], 255 ,0 ,0  );
				} else if( playerPressed[i][j] == 0 )
				{
					renderFilledQuad( quads[i][j], 0 ,0 ,255 );
				}
			}else if( mouseIn(quads[i][j]) == true && playerWon[i] == 2 && playerMove == i && winnerDeclared == false && firstMove == false )//Highligh
			{
				renderFilledQuad( quads[i][j], 200, 200, 200 );
			} else if( playerWon[i] == 1 )
			{
				renderFilledQuad( quads[i][j], 200, 100, 100 );
			} else if( playerWon[i] == 0 )
			{
				renderFilledQuad( quads[i][j], 100, 100, 200 );
			}else if( playerMove == i && winnerDeclared == false && firstMove == false )//Highlight required sqaure
			{
				renderFilledQuad( quads[i][j], 150, 150, 150 );
			} else
			{
				renderFilledQuad( quads[i][j], 255, 255, 255 );
			}
		}
	}
}




bool checkSquare( int tile[9], int player )
{
	bool winner = false;// Player is a number and tile is playerPressed
	
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



int main( int argc, char *args[] )
{
	init(); loadMedia();
	SDL_Event e;
	bool run = true;
	bool pressedTiles[9][9];
	int playerPressed[9][9];
	int playerWon[9];
	int playerMove = 9;
	bool p1 = true;
	bool firstMove = true;

	bool winnerDeclared = false;

	for(int i = 0; i < 9; i++)
	{
		for( int j = 0; j < 9; j++ )
		{
			pressedTiles[i][j] = false;
			playerPressed[i][j] = 2;
		}
	playerWon[i] = 2;
	}
	
	if( decidePlayer() == false )
	{
		p1 = false;
	}


	while(run)
	{
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT )
			{
				run = false;
			}
		}
		SDL_SetRenderDrawColor( myRenderer, 0, 0, 0, 255 );
		SDL_RenderClear( myRenderer );

		

		if( e.type == SDL_MOUSEBUTTONDOWN && winnerDeclared == false)
		{
			for( int i = 0; i < 9; i++ )
			{
				if( firstMove == true )
				{
					playerMove = i;
				}

				if( playerWon[i] == 1 && playerMove == i )
				{
					firstMove = true;
				} else if( playerWon[i] == 0 && playerMove == i )
				{
					firstMove = true;
				} else
				{
					firstMove == false;
				}
				for( int j = 0 ; j < 9; j++ )
				{
					if( mouseIn(quads[i][j]) == true && pressedTiles[i][j] == false && playerWon[i] == 2 && playerMove == i )
					{
						pressedTiles[i][j] = true;/* && playerMove == i*/
						playerMove = j;
						firstMove = false;
						if( p1 == true )
						{
							renderFilledQuad( quads[i][j], 255, 0, 0 );
							playerPressed[i][j] = 1;
							p1 = false;
						} else
						{
							renderFilledQuad( quads[i][j], 0, 0, 255 );
							playerPressed[i][j] = 0;
							p1 = true;
						}
						for( int n = 0; n < 9; n++)
						{
							if( playerWon[n] == 2 )
							{
								if( checkSquare( playerPressed[n], 1 ) == true )
								{
									cout << "RED won square " << n+1 << endl;
									playerWon[n] = 1;
									if( checkSquare( playerWon, 1 ) == true )
									{
										cout << "RED won the GAME!!\n";
										winnerDeclared = true;
									}
								} else if( checkSquare( playerPressed[n], 0 ) == true )
								{
									cout << "BLUE won square " << n+1 << endl;
									playerWon[n] = 0;
									if( checkSquare( playerWon, 0 ) == true )
									{
										cout << "BLUE won the GAME!!\n";
										winnerDeclared = true;
									}
								}
							}
						}

					}
				}
			}
		}
		
		renderAllQuads( pressedTiles, playerPressed, playerWon, playerMove, winnerDeclared, firstMove, p1 );
		SDL_RenderPresent( myRenderer );
		capFrames( SDL_GetTicks() );
	}






	cleanUp();
	return 0;
}






void cleanUp(){
	SDL_DestroyRenderer( myRenderer );
	myRenderer = NULL;
	SDL_DestroyWindow( myWindow );
	myWindow = NULL;

	SDL_Quit();}
void capFrames( Uint32 start_tick){
	if((1000/fps) -  (SDL_GetTicks() - start_tick) ){
		SDL_Delay( 1000 / fps - (SDL_GetTicks() - start_tick));
	}}
