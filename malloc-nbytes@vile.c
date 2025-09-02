#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@vile"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "Manipulate C files easily"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/vile.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "vile");
}

int build(void) {
        cd("src");
        return cmd("/bin/sh build.sh");
}

int install(void) {
        cd("src");
        return cmd("cp vile " FORGE_PREFERRED_INSTALL_PREFIX "/bin");
}

int uninstall(void) {
        return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/vile");
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
