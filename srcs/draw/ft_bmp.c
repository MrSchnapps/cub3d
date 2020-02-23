#include "cub3d.h"

void    ft_bzero(void *tab, unsigned int size)
{
	unsigned int    i;
	unsigned char   *tmp;

	tmp = (unsigned char *)tab;
	i = -1;
	while (++i < size)
		tmp[i] = 0;
}

void    draw_screenshot(int fd, t_cub *c, t_prtsc *p, unsigned char *tab_pix)
{
	int t;
	int y;
	int x;

	write(fd, &p->tab_bmp, BMP_HEADER);
	write(fd, &p->tab_dip, DIB_HEADER);
	y = c->win_h;
	while (--y >= 0)
	{
		x = -1;
		while (++x < c->win_w)
		{
			t = y * c->win_w + x;
			p->b = c->pix[t] % 256;
			p->g = ((c->pix[t] - p->b) / 256) % 256;
			p->r = ((c->pix[t] - p->b) / (256 * 256)) - p->g / 256;
			tab_pix[3 * x + 0] = p->b;
			tab_pix[3 * x + 1] = p->g;
			tab_pix[3 * x + 2] = p->r;
		}
		write(fd, tab_pix, c->win_w * 3);
		write(fd, p->tab_pad, p->p_size);
	}
}

void	set_header(t_cub *c, t_prtsc *p)
{
	p->tab_bmp[0] = 'B';
	p->tab_bmp[1] = 'M';
	p->tab_bmp[2] = (unsigned char)(p->filesize);
	p->tab_bmp[3] = (unsigned char)(p->filesize >> 8);
	p->tab_bmp[4] = (unsigned char)(p->filesize >> 16);
	p->tab_bmp[5] = (unsigned char)(p->filesize >> 24);
	p->tab_bmp[10] = (unsigned char)(BMP_HEADER + DIB_HEADER);
	p->tab_dip[0] = (unsigned char)(DIB_HEADER);
	p->tab_dip[4] = (unsigned char)(c->win_w);
	p->tab_dip[5] = (unsigned char)(c->win_w >> 8);
	p->tab_dip[6] = (unsigned char)(c->win_w >> 16);
	p->tab_dip[7] = (unsigned char)(c->win_w >> 24);
	p->tab_dip[8] = (unsigned char)(c->win_h);
	p->tab_dip[9] = (unsigned char)(c->win_h >> 8);
	p->tab_dip[10] = (unsigned char)(c->win_h >> 16);
	p->tab_dip[11] = (unsigned char)(c->win_h >> 24);
	p->tab_dip[12] = (unsigned char)(1);
	p->tab_dip[14] = (unsigned char)(3 * 8);
}

int     ft_bmp(t_cub *c)
{
	int             fd;
	t_prtsc    		p;
	unsigned char   *tab_pix;

	p.w = 3 * c->win_w;
	p.p_size = (4 - p.w % 4) % 4;
	p.filesize = BMP_HEADER + DIB_HEADER + ((p.w + p.p_size) * c->win_h);
	ft_bzero(p.tab_bmp, BMP_HEADER);
	ft_bzero(p.tab_dip, DIB_HEADER);
	ft_bzero(p.tab_pad, 3);
	set_header(c, &p);
	if (!(fd = open(PATH_SCREEN_SAVE, (O_CREAT | O_WRONLY), 0644)))
		return (ft_errors(1, c, 1));
	if (!(tab_pix = (unsigned char *)malloc(p.w * sizeof(unsigned char))))
	{
		close(fd);
		return (ft_errors(11, c, 1));
	}
	draw_screenshot(fd, c, &p, tab_pix);
	free(tab_pix);
	close(fd);
	return (ft_exit(c, 0));
}