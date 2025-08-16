#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@camelCase_to_snake"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Kill those camels!"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://github.com/malloc-nbytes/camelCase_to_snake.git");
        return "camelCase_to_snake";
}
int build(void) {
        cd("src");
        return cmd("./build.sh");
}
int install(void) {
        cd("src");
        return cmd("./install.sh");
}
int uninstall(void) {
        return cmd("rm /usr/local/bin/ccts");
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
