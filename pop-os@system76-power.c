#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "pop-os@system76-power"; }
char *getver(void) { return "1.2.4"; }
char *getdesc(void) { return "Power profile management for Linux "; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("pop-os", "system76-power");
}
int build(void) {
        return cmd("make");
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
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update, // or define your own if not using git
        .get_changes = forge_pkg_git_pull,
};
