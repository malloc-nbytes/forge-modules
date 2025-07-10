#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@earl-portable"; }
char *getver(void) { return "0.9.7"; }
char *getdesc(void) { return "The portable version of earl"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/earl.git earl-portable");
        return "earl-portable";
}
void build(void) {
        mkdirp("build");
        cd("build");
        cmd("cmake -S .. -B . -DPORTABLE=ON");
        make(NULL);
}
void install(void) {
        cd("build");
        make("install");
}
void uninstall(void) {
        cd("build");
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
        .update = forge_pkg_git_update, // or define your own if not using git
        .get_changes = forge_pkg_git_pull,
};
