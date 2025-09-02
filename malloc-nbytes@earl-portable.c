#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@earl-portable"; }
char *getver(void)  { return "0.9.7"; }
char *getdesc(void) { return "The portable version of earl"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/earl.git"; }

char *download(void) {
        CMD("git clone https://www.github.com/malloc-nbytes/earl.git earl-portable", return NULL);
        return "earl-portable";
}

int build(void) {
        mkdirp("build");
        cd("build");
        CMD("cmake -S .. -B . -DPORTABLE=ON", return 0);
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
        .deps            = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
