#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void)  { return "malloc-nbytes@sten"; }
char *getver(void)   { return "WIP"; }
char *getdesc(void)  { return "A WIP text editor"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/sten.git/"; }
char *download(void) { return git_clone("malloc-nbytes", "sten"); }

int build(void)     { return cmd("/bin/sh build.sh"); }
int install(void)   { return cmd("cp ./sten " FORGE_PREFERRED_INSTALL_PREFIX "/bin"); }
int uninstall(void) { return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/sten"); }

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .web = getweb,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
