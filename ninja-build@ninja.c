#include <forge/forge.h>

char *deps[] = {"Kitware@cmake", NULL}; // Must be NULL terminated

char *getname(void)  { return "ninja-build@ninja"; }
char *getver(void)   { return "1.13.1"; }
char *getdesc(void)  { return "A small build system focused on speed"; }
char *getweb(void)   { return "https://www.github.com/ninja-build/ninja.git/"; }
char **getdeps(void) { return deps; }

char *download(void) {
        return git_clone("ninja-build", "ninja");
}

int build(void) {
        CMD("cmake -Bbuild-cmake -DBUILD_TESTING=OFF", return 0);
        return cmd("cmake --build build-cmake");
}

int install(void) {
        return cmd("make install");
}

int uninstall(void) {
        return cmd("make uninstall");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
