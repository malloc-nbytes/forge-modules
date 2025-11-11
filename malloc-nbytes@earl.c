#include <forge/forge.h>

char *deps[] = {"Kitware@cmake", NULL};

char **getdeps(void) { return deps; }
char *getname(void) { return "malloc-nbytes@earl"; }
char *getver(void)  { return "0.9.7"; }
char *getdesc(void) { return "A scripting language to replace BASH"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/earl.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "earl");
}

int build(void) {
        cmd("mkdir build");
        cd("build");
        CMD("cmake -S .. -B .", return 0);
        return make(NULL);
}

int install(void) {
        cd("build");
        return make("install");
}

int uninstall(void) {
        cd("build");
        if (!make("uninstall")) return 0;
        return cmd("rm -r /usr/local/include/EARL");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
