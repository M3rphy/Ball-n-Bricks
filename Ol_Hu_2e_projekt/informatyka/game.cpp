#include "blocks.cpp"
#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

int lives = 3;

float player_pos_x = 0.f,player_pos_y = -40;
float player_size = 20,half_player_size = player_size/2;
float arena_size_x = 90;
float arena_half_size = arena_size_x / 2;
static float ball_p_x, ball_p_y, ball_dp_x, ball_dp_y = -50, ball_half_size = 1;
blocks block[] = { blocks(0, 40,0x4e0707,0xe3242b), blocks(25, 40,0x4e0707,0xe3242b), blocks(-25, 40,0x4e0707,0xe3242b), blocks(-50, 40,0x4e0707,0xe3242b), blocks(50, 40,0x4e0707,0xe3242b), blocks(-75, 40,0x4e0707,0xe3242b),blocks(75, 40,0x4e0707,0xe3242b),
					blocks(0, 31,0x2832c2,0x0492c2), blocks(25, 31,0x2832c2,0x0492c2), blocks(-25, 31,0x2832c2,0x0492c2), blocks(-50, 31,0x2832c2,0x0492c2), blocks(50, 31,0x2832c2,0x0492c2), blocks(-75, 31,0x2832c2,0x0492c2),blocks(75, 31,0x2832c2,0x0492c2),
					blocks(0, 22,0x028a0f,0x03c04a), blocks(25, 22,0x028a0f,0x03c04a), blocks(-25, 22,0x028a0f,0x03c04a), blocks(-50, 22,0x028a0f,0x03c04a), blocks(50, 22,0x028a0f,0x03c04a), blocks(-75, 22,0x028a0f,0x03c04a),blocks(75, 22,0x028a0f,0x03c04a),
					blocks(0, 13,0xffff00,0xfbec5d), blocks(25, 13,0xffff00,0xfbec5d), blocks(-25, 13,0xffff00,0xfbec5d), blocks(-50, 13,0xffff00,0xfbec5d), blocks(50, 13,0xffff00,0xfbec5d), blocks(-75, 13,0xffff00,0xfbec5d),blocks(75, 13,0xffff00,0xfbec5d) };
bool win = false, lose = false;


static void 
simulate_game(Input* input, float dt)
{
	
		int count = 0;
	for (int i = 0; i < 28; i++)
	{
		if(!block[i].is_hit)
		{
			count++;
		}
		
	}
	if (count == 28)
		{
			win = true;
			clear_screen(0x3a3a3a);
			draw_rect(0, -2, arena_size_x, 49, 0x000000);
			draw_rect(0, -40, player_size, 1, 0xffffff);
		}
	if (lives == 0)
	{
		lose = true;
	}
	if (!win && !lose)
	{
		float speed = 70.f;
		clear_screen(0x3a3a3a);
		draw_rect(0, -2, arena_size_x, 49, 0x000000);
		if (is_down(BUTTON_LEFT))
		{
			player_pos_x -= speed * dt;
		}
		if (is_down(BUTTON_RIGHT))
		{
			player_pos_x += speed * dt;
		}
		if (player_pos_x + player_size > arena_size_x)
		{
			player_pos_x = arena_size_x - player_size;
			speed = 0;
		}
		if (player_pos_x - player_size < (arena_size_x * -1))
		{
			player_pos_x = (arena_size_x * -1) + player_size;
			speed = 0;
		}

		ball_p_x += ball_dp_x * dt;
		ball_p_y += ball_dp_y * dt;
		if (ball_p_y + ball_half_size > player_pos_y + 0.5 &&
			ball_p_y - ball_half_size < player_pos_y - 0.5 &&
			ball_p_x + ball_half_size > player_pos_x - player_size &&
			ball_p_x - ball_half_size < player_pos_x + player_size)
		{
			ball_p_y = player_pos_y + 0.5 + ball_half_size;
			ball_dp_y *= -1;
			ball_dp_x = (ball_p_x - player_pos_x) * 2;
		}
		else if (ball_p_y + ball_half_size > 46.8)
		{
			ball_p_y = 46.8 - ball_half_size;
			ball_dp_y *= -1;
		}
		else if (ball_p_x + ball_half_size > 90)
		{
			ball_p_x = 90 - ball_half_size;
			ball_dp_x *= -1;
		}
		else if (ball_p_x - ball_half_size < -90)
		{
			ball_p_x = -90 + ball_half_size;
			ball_dp_x *= -1;
		}
		else if (ball_p_y < -50)
		{
			ball_p_x = 0;
			ball_p_y = 0;
			ball_dp_x = 0;
			player_pos_x = 0;
			lives--;

		}
		for (int i = 0; i < lives; i++)
		{
			draw_rect(70 + (i * 5), -45, 1, 1, 0xd0312d);
		}
		for (int i = 0; i < 28; i++)
		{
			if (block[i].is_hit)
			{
				block[i].draw_block();
				if (block[i].collisions(ball_p_x, ball_p_y))
				{
					if (((((block[i].block_position_x - ball_p_x) - 5) || (block[i].block_position_x - ball_p_x) + 5) && ((block[i].block_position_y - ball_p_y) - 1.5) || ((block[i].block_position_y - ball_p_y) + 1.5)) <= 5)
					{
						if (block[i].block_position_y < ball_p_y)
						{
							ball_p_y = block[i].block_position_y + 0.5 + ball_half_size;
						}
						else
						{
							ball_p_y = block[i].block_position_y - 0.5 - ball_half_size;
						}
						ball_dp_y *= -1;
					}
					else
					{
						if (block[i].block_position_x < ball_p_x)
						{
							ball_p_x = block[i].block_position_x + 0.5 + ball_half_size;
						}
						else
						{
							ball_p_x = block[i].block_position_x - 0.5 - ball_half_size;
						}
						ball_dp_x *= -1;
					}
				}
			}
		}

		if (lives > 0)
		{
			draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xffffff);
		}
		draw_rect(player_pos_x, player_pos_y, player_size, 1, 0xffffff);
		
	}
	else if (lose)
	{
		draw_lose();
	}
	else if (win)
	{
		draw_win();
	}
}