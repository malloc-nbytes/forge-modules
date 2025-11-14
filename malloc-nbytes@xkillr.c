#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@xkillr"; }
char *getver(void)  { return "rolling"; }
char *getdesc(void) { return "Kill processes"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/xkillr.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "xkillr");
}

int build(void) {
        CMD("autoreconf --install", return 0);
        mkdirp("build");
        cd("build");
        if (!configure("../", NULL)) return 0;
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
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .deps            = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
