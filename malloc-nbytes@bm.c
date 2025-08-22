#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@bm"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Bookmark directories in the terminal"; }
char *getweb(void) { return "https://www.github.com/malloc-nbytes/bm.git/"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/bm.git/");
        return "bm";
}
int build(void) {
        cmd("mkdir build");
        cd("build");
        cmd("cmake -S .. -B .");
        return cmd("make");
}
int install(void) {
        cd("build");
        return cmd("make install");
}
int uninstall(void) {
        cd("build");
        return cmd("make uninstall");
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
