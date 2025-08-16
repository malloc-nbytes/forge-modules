#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "raysan5@raylib"; }
char *getver(void) { return "5.5.0"; }
char *getdesc(void) { return "A simple and easy-to-use library to enjoy videogames programming"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://github.com/raysan5/raylib.git --depth=1");
        return "raylib";
}
int build(void) {
        mkdirp("build");
        cd("build");
        cmd("cmake ..");
        return make(NULL);
}
int install(void) {
        cd("build");
        make("install");
        return cmd("ldconfig");
}
int uninstall(void) {
        cd("build");
        return make("uninstall");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
