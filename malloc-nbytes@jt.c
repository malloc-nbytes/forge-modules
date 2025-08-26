#include <forge/forge.h>

char *getname(void)  { return "malloc-nbytes@jt"; }
char *getver(void)   { return "1.0.0"; }
char *getdesc(void)  { return "A small script for job tracking"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/jt.git/"; }
char *download(void) { return git_clone("malloc-nbytes", "jt"); }

int build(void) {
        CMD("autoreconf -iv", return 0;);
        if (!configure("./", NULL)) return 0;
        return make(NULL);
}

int install(void)   { return make("install"); }
int uninstall(void) { return make("uninstall"); }

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
