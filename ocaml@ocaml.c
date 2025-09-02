#include <forge/forge.h>

char *getname(void)  { return "ocaml@ocaml"; }
char *getver(void)   { return "4.14.2"; }
char *getdesc(void)  { return "The core OCaml system"; }
char *getweb(void)   { return "https://www.github.com/ocaml/ocaml.git/"; }

char *download(void) {
        return git_clone("ocaml", "ocaml");
}

int build(void) {
        CMD("OBJECT_MODE=64 /bin/sh configure --build=x86_64-pc-linux-gnu --prefix=" FORGE_PREFERRED_INSTALL_PREFIX " --libdir=" FORGE_PREFERRED_LIB_PREFIX, return 0);
        return cmd("OBJECT_MODE=64 make -j" FORGE_PREFERRED_MAKEFILE_JFLAGS);
}

int install(void) {
        return make("install");
}

int uninstall(void) {
        return make("uninstall");
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
