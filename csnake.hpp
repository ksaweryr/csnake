#ifndef SNAKE_GAME
#define SNAKE_GAME

#ifndef CSNAKE_NO_TUI
#include <ncurses.h>
#endif
#include <vector>

namespace csnake {
	/**
	 *	Represents 2-dimensional point/vector.
	 *	Two instances of vec2 can be added with + operator or compared with == operator.
	 */
	struct vec2 {
	    int x, y;

	    vec2 operator+(vec2 v);
	    bool operator==(vec2 v);
	};

	class SnakeGame {
	private:
		/**
		 *	The direction in which snake's head will go; eg. { 1, 0 } means up and { 0, 1 } means right
		 */
		vec2 direction;
		/**
		 *	Position of food.
		 */
		vec2 food;
		/**
		 *	Current score (snake's length - 1)
		 */
		int score;
		/**
		 *	Height and width of board.
		 */
		int height, width;
		/**
		 *	Are walls impenetrable?
		 *	@see #SnakeGame(int height, int width, WINDOW *win, bool impenetrable_walls)
		 */
		bool impenetrable_walls;

		/**
		 *	Move food to new random position. Is called automatically when snake collects food.
		 */
		void moveFood(void);
	public:
		/**
		 *	Contains positions of all snake's nodes.
		 */
		std::vector<vec2> snake;

		/**
		 *	Constructor.
		 *	Note: PRNG should be initialized using srand function before any instances of SnakeGame are created.
		 *
		 *	@param height game board height
		 *	@param width game board width
		 *	@param impenetrable_walls upon hitting walls snake:
		 *		dies if true
		 *		moves to the other side if false
		 */
		SnakeGame(int width, int height, bool impenetrable_walls);

		/**
		 *	Change movement direction if possible ie. when direction is changed by 90 deg.
		 *
		 *	@param new_direction new movement direction:
		 *		w - up
		 *		d - right
		 *		s - down
		 *		a - left
		 */
		void changeDirection(char new_direction);
		/**
		 *	Get movement direvtion.
		 *
		 *	@return movement direction
		 */
		vec2 getDirection(void);
		/**
		 *	Get food position.
		 *
		 *	@return food position
		 */
		vec2 getFood(void);
		/**
		 *	Get board height.
		 *
		 *	@return board height
		 */
		int getHeight(void);
		/**
		 *	Get current score.
		 *
		 *	@return current score
		 */
		int getScore(void);
		/**
		 *	Get board width.
		 *
		 *	@return board width
		 */
		int getWidth(void);
		/**
		 *	Move snake by one tile. If food is collected score and snake's length get increased and #_move_food(void) is called.
		 *
		 *	@return false if snake hits its own body, true otherwise.
		 */
		bool update(void);
	};

#ifndef CSNAKE_NO_TUI
	class Renderer {
	private:
		/**
		 *	Pointer to ncurses window.
		 */
		WINDOW *win;
		/**
		 *	Pointer to game drawn by renderer.
		 */
		SnakeGame *game;
		/**
		 *	Used for rendering board to screen.
		 */
		std::vector<std::vector<char>> board;
	public:
		Renderer(SnakeGame *game, WINDOW *win);
		/**
		 *	Call #SnakeGame::changeDirection(char new_direction) with wgetch(win) as argument
		 */
		void handleInput(void);
		/**
		 *	Draw board to ncurses window. Shouldn't be called before #initRendering(void).
		 */
		void render(void);
		/**
		 *	Change rendered game.
		 *
		 *	@param game new game
		 */
		void setGame(SnakeGame *game);
	};

	/**
	 *	Run new game as TUI application.
	 */
	void run(void);
#endif
}

#endif