inline int clamp(int min, int val, int max)
{
	if (val < min)
	{
		return min;
	}
	if (val > max)
	{
		return max;
	}
	return val;
}

static void clear_screen(unsigned int color)
{
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel++ = color;
		}
	}
}

static void draw_rect_in_pixels(int x0, int y0, int x1, int y1, unsigned int color)
{
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);
	for (int y = y0; y < y1; y++)
	{
		unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
}
float render_scale = 0.01f;

static void draw_rect(float x, float y, float half_size_x, float half_size_y, unsigned int color)
{
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}
static void draw_lose()
{
	draw_rect(-30, 5, 2, 10, 0xFF0000);
	draw_rect(-27, -5, 5, 2, 0xFF0000);


	draw_rect(-11, -5, 6, 2, 0xFF0000);
	draw_rect(-15, 5, 2, 10, 0xFF0000);
	draw_rect(-7, 5, 2, 10, 0xFF0000);
	draw_rect(-12, 13, 5, 2, 0xFF0000);

	draw_rect(5, 13, 5, 2, 0xFF0000);
	draw_rect(5, -5, 5, 2, 0xFF0000);
	draw_rect(5, 4, 5, 2, 0xFF0000);
	draw_rect(2, 10, 2, 5, 0xFF0000);
	draw_rect(8, 0, 2, 5, 0xFF0000);

	draw_rect(20, 13, 5, 2, 0xFF0000);	
	draw_rect(17, 3, 2, 10, 0xFF0000);
	draw_rect(20, -5, 5, 2, 0xFF0000);
	draw_rect(20, 4, 5, 2, 0xFF0000);
}
static void draw_win()
{
	draw_rect(-20, 2, 2, 8, 0x00FF00);
	draw_rect(-4, 2, 2, 8, 0x00FF00);
	draw_rect(-12, -2, 2, 4, 0x00FF00);
	draw_rect(-16, -6, 2, 4, 0x00FF00);
	draw_rect(-8, -6, 2, 4, 0x00FF00);

	draw_rect(6, 0, 2, 10, 0x00FF00);

	draw_rect(16, 0, 2, 10, 0x00FF00);
	draw_rect(20, 0, 2, 2, 0x00FF00);
	draw_rect(24, -4, 2, 2, 0x00FF00);
	draw_rect(28, 0, 2, 10, 0x00FF00);

}