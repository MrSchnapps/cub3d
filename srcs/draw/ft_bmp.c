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

int     ft_bmp(t_cub *c)
{
    int             fd;
    int             filesize;
    int             w;
    int             p_size;
    unsigned char   tab_bmp[BMP_HEADER];
    unsigned char   tab_dip[DIB_HEADER];
    int y;
    int x;
    unsigned char   *tab_pix;
    unsigned char   tab_pad[3];

    w = 3 * c->win_width;
    p_size = (4 - w % 4) % 4;
    ft_bzero(tab_bmp, BMP_HEADER);
    ft_bzero(tab_dip, DIB_HEADER);
    filesize = BMP_HEADER + DIB_HEADER + ((w + p_size /*((4 - w % 4) % 4)*/) * c->win_height);
    if (!(fd = open("../screenshots/save.bmp", (O_CREAT | O_WRONLY), 0644)))
        return (1);

    tab_bmp[0] = 'B';
    tab_bmp[1] = 'M';
    tab_bmp[2] = (unsigned char)(filesize);
    tab_bmp[3] = (unsigned char)(filesize >> 8);
    tab_bmp[4] = (unsigned char)(filesize >> 16);
    tab_bmp[5] = (unsigned char)(filesize >> 24);
    tab_bmp[10] = (unsigned char)(BMP_HEADER + DIB_HEADER);
    tab_dip[0] = (unsigned char)(DIB_HEADER);
    tab_dip[4] = (unsigned char)(c->win_width);
    tab_dip[5] = (unsigned char)(c->win_width >> 8);
    tab_dip[6] = (unsigned char)(c->win_width >> 16);
    tab_dip[7] = (unsigned char)(c->win_width >> 24);
    tab_dip[8] = (unsigned char)(c->win_height);
    tab_dip[9] = (unsigned char)(c->win_height >> 8);
    tab_dip[10] = (unsigned char)(c->win_height >> 16);
    tab_dip[11] = (unsigned char)(c->win_height >> 24);
    tab_dip[12] = (unsigned char)(1);
    tab_dip[14] = (unsigned char)(3 * 8);
    write(fd, &tab_bmp, BMP_HEADER);
    write(fd, &tab_dip, DIB_HEADER);
    y = c->win_height;
    if (!(tab_pix = (unsigned char *)malloc(w * sizeof(unsigned char))))
    {
        close(fd);
        return (11);
    }
    ft_bzero(tab_pad, 3);
    int r;
    int g;
    int b;
    int p;

    while (--y >= 0)
    {
        x = -1;
        while (++x < c->win_width)
        {
            p = y * c->win_width + x;
            b = c->pix[p] % 256;
            g = ((c->pix[p] - b) / 256) % 256;
            r = ((c->pix[p] - b) / (256 * 256)) - (g / 256);   
            tab_pix[3 * x + 0] = b;
            tab_pix[3 * x + 1] = g;
            tab_pix[3 * x + 2] = r;
        }
        write(fd, tab_pix, c->win_width * 3);
        write(fd, tab_pad, p_size);
    }
    free(tab_pix);
    close(fd);
    return (0);
}