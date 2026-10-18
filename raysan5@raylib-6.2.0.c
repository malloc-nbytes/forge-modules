#include <forge/forge.h>

char *deps[] = {"Kitware@cmake", NULL};

char **getdeps(void) { return deps; }
char *getname(void)  { return "raysan5@raylib-6.2.0"; }
char *getver(void)   { return "6.2.0"; }
char *getdesc(void)  { return "A simple and easy-to-use library for videogames programming"; }
char *getweb(void)   { return "https://github.com/raysan5/raylib"; }

char *
download(void)
{
        CMD("wget https://github.com/raysan5/raylib/archive/refs/tags/6.2.tar.gz", return NULL);
        CMD("tar -vxf 6.2.tar.gz", return NULL);
        CMD("rm 6.2.tar.gz", return NULL);
        CMD("mv raylib-6.2 raylib-6.2.0", {
                (void)cmd("rm raylib-6.2");
                return NULL;
        })
        return "raylib-6.2";
}

int
build(void)
{
        if (!cd("raylib-6.2")) return 0;
        CMD("cmake -B build -S .                    \
                -D CMAKE_BUILD_TYPE=Release          \
                -D CMAKE_INSTALL_PREFIX=/usr         \
                -D BUILD_SHARED_LIBS=ON               \
                -D BUILD_EXAMPLES=OFF", return 0);
        CMD("cmake --build build --parallel", return 0);
        return 1;
}

int
install(void)
{
        if (!cd("raylib-6.2/build")) return 0;
        return cmd("cmake --install .");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
