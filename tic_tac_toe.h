#pragma once
class tic_tac_toe
{
public:
	tic_tac_toe(int size_ = 3);
	~tic_tac_toe();
	
	void start_game();


private:
	int size;
	bool turn;
	int size_rows;
	int size_cols;
	bool map_created;
	char **map;


	void ask_map_size();
	void clear_map();
	void draw_map();
	bool check_winner();
	void execute_move();

};

