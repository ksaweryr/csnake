#include <string>
#ifndef CSNAKE_NO_TUI
#include <unistd.h>
#endif

#include "csnake.hpp"

namespace csnake {
	vec2 vec2::operator+(vec2 v) {
	    return { x + v.x, y + v.y };
	}

	bool vec2::operator==(vec2 v) {
	    return (x == v.x) && (y == v.y);
	}

	SnakeGame::SnakeGame(int width, int height, bool impenetrable_walls) {
		this->width = width;
		this->height = height;
		this->impenetrable_walls = impenetrable_walls;

	    score = 0;
	    snake.resize(1, { width >> 1, height >> 1 });
	    direction = { 0, 1 };
	    moveFood();
	}

	void SnakeGame::changeDirection(char new_direction) {
		switch(new_direction) {
	        case 'w':
	            if(direction.y != 1)
	                direction = { 0, -1 };
	            break;

	        case 's':
	            if(direction.y != -1)
	                direction = { 0, 1 };
	            break;

	        case 'a':
	            if(direction.x != 1)
	                direction = { -1, 0 };
	            break;
	        
	        case 'd':
	            if(direction.x != -1)
	                direction = { 1, 0 };
	            break;

	        default:
	            break;
	    }
	}

	vec2 SnakeGame::getDirection(void) {
		return direction;
	}

	vec2 SnakeGame::getFood(void) {
		return food;
	}

	int SnakeGame::getHeight(void) {
		return height;
	}

	int SnakeGame::getScore(void) {
		return score;
	}

	int SnakeGame::getWidth(void) {
		return width;
	}

	void SnakeGame::moveFood(void) {
	    food = { rand() % width, rand() % height };
	}

	bool SnakeGame::update(void) {
	    vec2 new_head_pos = snake[0] + direction;

	    if(impenetrable_walls) {
	    	if(new_head_pos.x < 0 || new_head_pos.y < 0 || new_head_pos.x >= width || new_head_pos.y >= height)
	    		return 0;
	    }
	    else {
	    	if(new_head_pos.x < 0)
		        new_head_pos.x = width - 1;
		    else if(new_head_pos.x >= width)
		        new_head_pos.x = 0;

		    if(new_head_pos.y < 0)
		        new_head_pos.y = height - 1;
		    else if(new_head_pos.y >= height)
		        new_head_pos.y = 0;
	    }

	    for(auto i = snake.rbegin(); i != snake.rend() - 1; i++) {
	        *i = *(i + 1);
	        if(*i == new_head_pos) {
	            return 0;
	        }
	    }

	    snake[0] = new_head_pos;

	    if(snake[0] == food) {
	        snake.push_back(*snake.rbegin());
	        moveFood();
	        score++;
	    }

	    return 1;
	}

#ifndef CSNAKE_NO_TUI
	Renderer::Renderer(SnakeGame *game, WINDOW *win) {
		this->win = win;
		setGame(game);
	}

	void Renderer::handleInput(void) {
	    game->changeDirection(wgetch(win));
	}

	void Renderer::render(void) {
	    for(std::vector<char>& r : board)
	        std::fill(r.begin(), r.end(), '.');

	    board[game->getFood().y][game->getFood().x] = '$';
	    
	    for(vec2& node : game->snake)
	        board[node.y][node.x] = '@';

	    move(0, 0);
	    for(std::vector<char>& r : board) {
	        wprintw(win, "%s\n", std::string(r.begin(), r.end()).c_str());
	    }
	    wprintw(win, "\nScore: %d", game->getScore());
	    wrefresh(win);
	}

	void Renderer::setGame(SnakeGame *game) {
		this->game = game;
		if(game != nullptr)
			board.resize(game->getHeight(), std::vector<char>(game->getWidth(), '.'));
	}

	void run(void) {
		WINDOW *win = initscr();
		srand(time(0));
		noecho();
	    curs_set(0);

	    Renderer *renderer = new Renderer(nullptr, win);

	    while(1) {
	    	nodelay(win, 1);
	    	SnakeGame *game = new SnakeGame(32, 16, 0);
	    	renderer->setGame(game);

	        while(1) {
	            renderer->handleInput();

	            if(!game->update()) {
	                break;
	            }

	            renderer->render();
	            usleep(100 * 1000);
	        }

	        delete game;
	        
	        erase();
		    move(0, 0);
		    wprintw(win, "You lost! Your score was %d.\n", game->getScore());
		    wrefresh(win);
		    usleep(1000 * 1000);
		    flushinp();
		    wprintw(win, "Press esc to exit. Press any other key to restart...\n");
		    wrefresh(win);
		    nodelay(win, 0);
		    char c = getch();
		    if(c == 0x1b)
		    	break;
	    }

	    delete renderer;

	    endwin();
	}
#endif
}