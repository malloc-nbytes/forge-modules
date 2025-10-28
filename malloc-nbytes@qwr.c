#include <forge/forge.h>

#include <stdio.h>

char *getname(void) { return "malloc-nbytes@qwr"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "A qemu wrapper for managing VMs"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/qwr.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "qwr");
}

int build(void) {
        printf("CWD: %s\n", cwd());
        return cmd("/bin/sh build.sh");
}

int install(void) {
        return cmd("cp qwr " FORGE_PREFERRED_INSTALL_PREFIX "/bin");
}

int uninstall(void) {
        return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/qwr");
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
