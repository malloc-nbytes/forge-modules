#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@gitcheck"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Check for unstaged git changes in directories"; }
char *getweb(void) { return "https://www.github.com/malloc-nbytes/gitcheck.git/"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/gitcheck.git/");
        return "gitcheck";
}
int build(void) {
        cd("src");
        return make(NULL);
}
int install(void) {
        cd("src");
        return make("install");
}
int uninstall(void) {
        return cmd("rm /usr/local/bin/gitcheck");
}

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
