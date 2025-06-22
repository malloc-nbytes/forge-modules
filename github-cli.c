#include <stdlib.h>
#include <stdio.h>

#include <forge/forge.h>

char *deps[] = {/*"golang"*/NULL}; // Must be NULL terminated

char *getname(void) { return "Github/github-cli"; }
char *getver(void) { return "2.68.1"; }
char *getdesc(void) { return "GitHub’s official command line tool "; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("cli", "cli");
}
void build(void) {}
void install(void) {
        cmd("make install prefix=/usr");
}
void uninstall(void) {
        cmd("make uninstall");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update,
};
