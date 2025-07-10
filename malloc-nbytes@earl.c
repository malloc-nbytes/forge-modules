#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@earl"; }
char *getver(void) { return "0.9.7"; }
char *getdesc(void) { return "A scripting language to replace BASH"; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/earl.git/");
        return "earl";
}
void build(void) {
        cmd("mkdir build");
        cd("build");
        cmd("cmake -S .. -B .");
        make(NULL);
}
void install(void) {
        cd("build");
        make("install");
}
void uninstall(void) {
        cd("build");
        make("uninstall");
        cmd("rm -r /usr/local/include/EARL");
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
