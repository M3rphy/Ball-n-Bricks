class blocks
{
private: 
public:
	int block_position_x, block_position_y;
	unsigned int color1,color2;
	bool is_hit = true;
	void draw_block()
	{
		draw_rect(block_position_x,block_position_y,10,3, color1);
		draw_rect(block_position_x, block_position_y, 9, 2, color2);
	}

	bool collisions(int ball_position_x, int ball_position_y)
	{
		if (ball_position_y - 1 < block_position_y + 1 &&
			ball_position_y + 1 > block_position_y - 1 &&
			ball_position_x + 1 > block_position_x - 10 &&
			ball_position_x - 1 < block_position_x + 10)
		{
			is_hit = false;
			return true;
		}
		return false;
	}
	
	blocks(int x, int y,unsigned int color1,unsigned int color2)
	{
		this->block_position_x = x;
		this->block_position_y = y;
		this->color1 = color1;
		this->color2 = color2;
	}
};