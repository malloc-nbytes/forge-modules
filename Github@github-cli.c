#include <stdlib.h>
#include <stdio.h>

#include <forge/forge.h>

char *deps[] = {/*"golang"*/NULL}; // Must be NULL terminated

char *getname(void)  { return "Github@github-cli"; }
char *getver(void)   { return "2.68.1"; }
char *getdesc(void)  { return "GitHub’s official command line tool"; }
char *getweb(void)   { return "https://github.com/cli/cli"; }
char **getdeps(void) { return deps; }

char *download(void) {
        return git_clone("cli", "cli");
}

int build(void) { return 1; }

int install(void) {
        return cmd("make install prefix=/usr");
}

int uninstall(void) {
        return cmd("make uninstall");
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
