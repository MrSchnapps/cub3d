#include "cub3d.h"

void    ft_bzero(void *tab, unsigned int size)
{
    unsigned int i;

    i = -1;
    while (++i < size)
        tab[i] = 0;
}

int     ft_bmp(t_cub *c)
{
    int             fd;
    int             filesize;
    int             w;
    int             p_size;
    unsigned char   tab_bmp[BMP_HEADER];
    unsigned char   tab_bip[DIB_HEADER];
    int y;
    int x;
    unsigned char   *tab_pix;
    unsigned char   tab_pad[3];

    w = 3 * c->win_width;
    p_size = (4 - w % 4) % 4;
    ft_bzero(tab_bmp, BMP_HEADER);
    ft_bzero(tab_bip, DIB_HEADER);
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
    tab_dib[0] = (unsigned char)(DIB_HEADER);
    tab_dib[4] = (unsigned char)(c->win_width);
    tab_dib[5] = (unsigned char)(c->win_width >> 8);
    tab_dib[6] = (unsigned char)(c->win_width >> 16);
    tab_dib[7] = (unsigned char)(c->win_width >> 24);
    tab_dib[8] = (unsigned char)(c->win_height);
    tab_dib[9] = (unsigned char)(c->win_height >> 8);
    tab_dib[10] = (unsigned char)(c->win_height >> 16);
    tab_dib[11] = (unsigned char)(c->win_height >> 24);
    tab_dib[12] = (unsigned char)(1);
    tab_dib[14] = (unsigned char)(3 * 8);
    write(fd, &tab_bmp, BMP_HEADER);
    write(fd, &tab_bip, DIB_HEADER);
    y = c->win_height;
    if (!(tab_pix = (unsigned char *)malloc(w * sizeof(unsigned char))))
    {
        close(fd);
        return (11);
    }
    ft_bzero(tab_pad);
    while (--y >= 0)
    {
        x = -1;
        while (++x < c->win_width)
        {
            tab_pix[3 * x + 0] = c->pix[];
            tab_pix[3 * x + 1] = c->pix[];
            tab_pix[3 * x + 2] = c->pix[];
        }
        write(fd, tab_pix, c->win_width);
        write(fd, tab_pad, p_size);
    }
    close(fd);
    return (0);
}