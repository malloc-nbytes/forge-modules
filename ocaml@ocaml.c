#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "ocaml@ocaml"; }
char *getver(void) { return "4.14.2"; }
char *getdesc(void) { return "The core OCaml system"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("ocaml", "ocaml");
}
void build(void) {
        cmd("OBJECT_MODE=64 /bin/sh configure --build=x86_64-pc-linux-gnu --prefix=" FORGE_PREFERRED_INSTALL_PREFIX " --libdir=" FORGE_PREFERRED_LIB_PREFIX);
        cmd("OBJECT_MODE=64 make -j" FORGE_PREFERRED_MAKEFILE_JFLAGS);
}
void install(void) {
        make("install");
}
void uninstall(void) {
        make("uninstall");
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
        .update = forge_pkg_git_update, // or define your own if not using git
        .get_changes = forge_pkg_git_pull,
};
