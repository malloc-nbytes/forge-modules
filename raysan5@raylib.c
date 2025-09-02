#include <forge/forge.h>

char *getname(void) { return "raysan5@raylib"; }
char *getver(void)  { return "5.5.0"; }
char *getdesc(void) { return "A simple and easy-to-use library to enjoy videogames programming"; }
char *getweb(void)  { return "https://github.com/raysan5/raylib.git"; }

char *download(void) {
        CMD("git clone https://github.com/raysan5/raylib.git --depth=1", return NULL);
        return "raylib";
}

int build(void) {
        mkdirp("build");
        cd("build");
        CMD("cmake ..", return 0);
        return make(NULL);
}

int install(void) {
        cd("build");
        if (!make("install")) return 0;
        return cmd("ldconfig");
}

int uninstall(void) {
        cd("build");
        return make("uninstall");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
