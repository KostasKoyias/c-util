#ifndef _bmap_H
#define _bmap_H
    #include <stdint.h>

    typedef struct bmap{
        uint8_t *data;
        uint32_t bits;
    }bmap_t;

    void bmap_init(void *, uint32_t);
    void bmap_free(void *);

    void bmap_print(const void *);

    int8_t bmap_set(void *, uint32_t);
    int8_t bmap_reset(void *, uint32_t);
    int8_t bmap_toggle(void *, uint32_t);

    int8_t bmap_get(void *, uint32_t);
#endif