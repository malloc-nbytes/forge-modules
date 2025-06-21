#include <forge/forge.h>

char *deps[] = {"malloc-nbytes/earl", NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes/earlmgr"; }
char *getver(void) { return "0.0.1"; }
char *getdesc(void) { return "A helper script for the earl language"; }
char *download(void) {
        return git_clone("malloc-nbytes", "earlmgr");
}
void build(void) {}
void install(void) {
        char *user = get_prev_user();
        cd("src");
        cmd_as("earl ./earlmgr.rl", user);
}
void uninstall(void) {
        char *user = get_prev_user();
        cmd_as("earlmgr -- uninstall", user);
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
};
