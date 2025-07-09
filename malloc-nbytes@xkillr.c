#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@xkillr"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Kill processes"; }
char *download(void) {
        git_clone("malloc-nbytes", "xkillr");
        return "xkillr";
}
void build(void) {
        cmd("autoreconf --install");
        mkdirp("build");
        cd("build");
        configure("../", NULL);
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
        .update = forge_pkg_git_update,
};
