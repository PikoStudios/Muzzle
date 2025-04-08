#include <Muzzle.h>
#include <string.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#ifndef ASSETS_DIR
#define ASSETS_DIR "../"
#endif

#ifndef OUTFILE
#define OUTFILE "out.bin"
#endif


int main(void)
{
    mz_applet applet = mz_initialize_applet("Muzzle [SPRITE] - Read Shader Pixels", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);

    mz_sprite sprite = mz_load_sprite(ASSETS_DIR "muzzle_logo.png");
    size_t size = mz_read_sprite_pixels(&sprite, NULL, 0);

    unsigned char* data = MZ_MALLOC(size * sizeof(unsigned char));

    if (data == NULL)
    {
        return -1;
    }

    mz_read_sprite_pixels(&sprite, data, size);

    FILE* file = fopen("out.bin", "wb");

    if (file == NULL)
    {
        MZ_FREE(data);
        return -1;
    }

    size_t bytes = fwrite(data, sizeof(unsigned char), size, file);

    printf("Wrote %zu bytes to " OUTFILE "\n", bytes);

    fclose(file);
    MZ_FREE(data);

    mz_terminate_applet(&applet);
    return 0;
}
