#include <forge/forge.h>

char *getname(void) { return "bls"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "An alternative to `ls`"; }
char *download(void) {
        return git_clone("malloc-nbytes", "bls");
}
void build(void) {
        cd("src/build");
        cmd("make");
}
void install(void) {
        cd("src/build");
        cmd("make install");
        cmd("make clean");
}
void uninstall(void) {
        cmd("rm /usr/local/bin/bls");
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
