#include <forge/forge.h>

#define BISON_VERSION "3.8"

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void)  { return "GNU@bison"; }
char *getver(void)   { return BISON_VERSION; }
char *getdesc(void)  { return "General-purpose parser generator"; }
char *getweb(void)   { return "http://ftp.gnu.org/gnu/bison/"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("wget http://ftp.gnu.org/gnu/bisonww/bison-3.8.tar.xz");
        cmd("tar -vxf ./bison-" BISON_VERSION ".tar.xz");
        return "bison-" BISON_VERSION;
}
int build(void) {
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
        .name        = getname,
        .ver         = getver,
        .desc        = getdesc,
        .web         = getweb,
        .deps        = NULL,
        .download    = download,
        .build       = build,
        .install     = install,
        .uninstall   = uninstall,
        .update      = forge_pkg_update_manual_check,
        .get_changes = forge_pkg_get_changes_redownload,
};
