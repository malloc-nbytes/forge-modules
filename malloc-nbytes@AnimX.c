#include <forge/pkg.h>
#include <forge/cmd.h>

char *getname(void) { return "malloc-nbytes@AnimX"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Animated Wallpapers for X"; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/AnimX.git/");
        return "AnimX";
}
void build(void) {
        cmd("autoreconf --install");
        configure("./", NULL);
        make(NULL);
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
        .update = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
