#include <forge/forge.h>

char *deps[] = {"Kitware@cmake", NULL}; // Must be NULL terminated

char *getname(void) { return "ninja-build@ninja"; }
char *getver(void) { return "1.13.1"; }
char *getdesc(void) { return "A small build system focused on speed "; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("ninja-build", "ninja");
}
int build(void) {
        cmd("cmake -Bbuild-cmake -DBUILD_TESTING=OFF");
        return cmd("cmake --build build-cmake");
}
int install(void) {
        return cmd("make install");
}
int uninstall(void) {
        return cmd("make uninstall");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .deps = getdeps,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update, // or define your own if not using git
        .get_changes = forge_pkg_git_pull,
};
