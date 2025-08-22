#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@far"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Find and replace"; }
char *getweb(void) { return "https://github.com/malloc-nbytes/far.git"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://github.com/malloc-nbytes/far.git");
        return "far";
}
int build(void) { return 1; }
int install(void) {
        return cmd("./install.sh");
}
int uninstall(void) {
        return cmd("rm /usr/local/bin/far.py");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .web = getweb,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
