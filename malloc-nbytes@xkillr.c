#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@xkillr"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Kill processes"; }
char *getweb(void) { return "https://www.github.com/malloc-nbytes/xkillr.git/"; }
char *download(void) {
        git_clone("malloc-nbytes", "xkillr");
        return "xkillr";
}
int build(void) {
        cmd("autoreconf --install");
        mkdirp("build");
        cd("build");
        configure("../", NULL);
        return make(NULL);
}
int install(void) {
        cd("build");
        return make("install");
}
int uninstall(void) {
        cd("build");
        return make("uninstall");
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
