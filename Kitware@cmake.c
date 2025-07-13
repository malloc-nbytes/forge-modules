#include <forge/forge.h>

char *getname(void) { return "Kitware@cmake"; }
char *getver(void) { return "3.31.7"; }
char *getdesc(void) { return "Software build system"; }
char *download(void) {
        cmd("git clone https://gitlab.kitware.com/cmake/cmake.git");
        return "cmake";
}
void build(void) {
        cmd("/bin/sh bootstrap --parallel=" FORGE_PREFERRED_MAKEFILE_JFLAGS);
        make(NULL);
}
void install(void) {
        make("install");
}
void uninstall(void) {
        make("uninstall");
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
