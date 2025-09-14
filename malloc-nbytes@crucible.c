#include <forge/forge.h>

char *getname(void)  { return "malloc-nbytes@crucible"; }
char *getver(void)   { return "0.0.1"; }
char *getdesc(void)  { return "A language devloped at: https://www.twitch.tv/malloc_nbytes"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/crucible.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "crucible");
}

int build(void) {
        cd("src");
        return cmd("sh build.sh");
}

int install(void) {
        cd("src");
        return cmd("mv ./cruc " FORGE_PREFERRED_INSTALL_PREFIX "/bin/");
}

int uninstall(void) {
        return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/cruc");
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
