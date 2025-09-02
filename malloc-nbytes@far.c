#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@far"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "Find and replace"; }
char *getweb(void)  { return "https://github.com/malloc-nbytes/far.git"; }

char *download(void) {
        return git_clone("malloc-nbytes", "far");
}

int build(void) { return 1; }

int install(void) {
        return cmd("/bin/sh ./install.sh");
}

int uninstall(void) {
        return cmd("rm /usr/local/bin/far.py");
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
