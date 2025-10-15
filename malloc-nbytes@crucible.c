#include <forge/forge.h>

char *getname(void)  { return "malloc-nbytes@crucible"; }
char *getver(void)   { return "0.0.1"; }
char *getdesc(void)  { return "A language devloped at: https://www.twitch.tv/malloc_nbytes"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/crucible.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "crucible");
}

int build(void) {
        cmd("/bin/sh autogen.sh");
        configure("./", NULL);
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
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
