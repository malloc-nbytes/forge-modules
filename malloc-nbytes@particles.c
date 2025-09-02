#include <forge/forge.h>

char *deps[] = {"raysan5@raylib", NULL};

char *getname(void)  { return "malloc-nbytes@particles"; }
char *getver(void)   { return "1.0.0"; }
char *getdesc(void)  { return "Just a fun graphics application"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/particles.git/"; }
char **getdeps(void) { return deps; }

char *download(void) {
        return git_clone("malloc-nbytes", "particles");
}

int build(void) {
        return cmd("./build.sh");
}

int install(void) {
        return cmd("cp ./particles " FORGE_PREFERRED_INSTALL_PREFIX "/bin");
}

int uninstall(void) {
        return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/particles");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update, // or define your own if not using git
        .get_changes     = forge_pkg_git_pull,
};
