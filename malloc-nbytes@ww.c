#include <forge/pkg.h>
#include <forge/cmd.h>

char *getname(void)  { return "malloc-nbytes@ww"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A WIP text editor"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/wintr.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "wintr");
}

int build(void) {
        CMD("autoreconf --install", return 0);
        if (!configure("./", NULL)) return 0;
        return make(NULL);
}

int install(void) {
        return make("install");
}

int uninstall(void) {
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
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
