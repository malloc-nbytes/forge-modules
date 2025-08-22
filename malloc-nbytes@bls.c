#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@bls"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "An alternative to `ls`"; }
char *getweb(void) { return "https://www.gitub.com/malloc-nbytes/bls.git/"; }
char *download(void) {
        return git_clone("malloc-nbytes", "bls");
}
int build(void) {
        cd("src/build");
        return cmd("make");
}
int install(void) {
        cd("src/build");
        cmd("make install");
        return cmd("make clean");
}
int uninstall(void) {
        return cmd("rm /usr/local/bin/bls");
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
