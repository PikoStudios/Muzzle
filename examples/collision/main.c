#define MUZZLE_DEPS
#define MZ_DEPS_COLLISION
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet collision;

void OnAppletUpdate()
{
    collision_manager coll_manager;
    coll_manager.updates = 0;
    coll_manager.last = MZ_GET_TIME();
    coll_manager.delta = 0;
    coll_manager.now = 0;
    coll_manager.timer = coll_manager.last;
    coll_manager.fps = 30; // Run collision at 30 fps

    int obj_length = 1;
    rectangle objects[obj_length];

    objects[0] = (rectangle){170,170,60,60};  

    while (keep_applet(collision.window_handle))
    {
        begin_collision_manager(&coll_manager);
        
            begin_drawing();
                
            end_drawing(&collision);

        end_collision_manager(&coll_manager);
    }
}

int main(void)
{
    collision = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Collision", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&collision);

    QuitMuzzle(collision);
    return 0;
}