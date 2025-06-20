#include <forge/forge.h>

char *deps[] = {"earl", NULL}; // Must be NULL terminated

char *getname(void) { return "earlmgr"; }
char *getver(void) { return "0.0.1"; }
char *getdesc(void) { return "A helper application for the earl language"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "earlmgr");
}
void build(void) {}
void install(void) {
        cd("src");
        cmd("earl ./earlmgr.rl");
}
void uninstall(void) {
        cmd("earlmgr -- uninstall");
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
        .update = forge_pkg_git_update,
};
