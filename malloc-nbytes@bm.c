#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@bm"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "Bookmark directories in the terminal"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/bm.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "bm");
}

int build(void) {
        mkdirp("build");
        CD("build", return 0);
        CMD("cmake -S .. -B .", return 0);
        return make(NULL);
}

int install(void) {
        CD("build", return 0);
        return make("install");
}

int uninstall(void) {
        CD("build", return 0);
        return make("uninstall");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
