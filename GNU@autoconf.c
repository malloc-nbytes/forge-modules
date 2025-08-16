#include <stdlib.h>
#include <stdio.h>

#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "GNU@autoconf"; }
char *getver(void) { return "2.72.0"; }
char *getdesc(void) { return "Extensible package of M4 macros"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone git://git.sv.gnu.org/autoconf");
        return "autoconf";
}
int build(void) {
        configure("./", NULL);
        make(NULL);
        return make("check");
}
int install(void) {
        return make("install");
}
int uninstall(void) {
        return make("uninstall");
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
        .get_changes = forge_pkg_git_pull,
};
