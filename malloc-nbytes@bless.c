#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@bless"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Better `less`"; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/bless.git/");
        return "bless";
}
int build(void) {
        mkdirp("build");
        cd("build");
        cmd("cmake -S .. -B .");
        return make(NULL);
}
int install(void) {
        cd("build");
        return make("install");
}
int uninstall(void) {
        cd("build");
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
