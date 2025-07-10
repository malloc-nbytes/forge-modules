#include <forge/forge.h>

char *deps[] = {"raysan5@raylib", NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@particles"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Just a fun graphics application"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "particles");
}
void build(void) {
        cmd("./build.sh");
}
void install(void) {
        cmd("cp ./particles /usr/local/bin");
}
void uninstall(void) {
        cmd("rm /usr/local/bin/particles");
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
        .update = forge_pkg_git_update, // or define your own if not using git
        .get_changes = forge_pkg_git_pull,
};
