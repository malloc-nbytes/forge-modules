#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "system76-power"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "1.2.4"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("pop-os", "system76-power");
}
void build(void) {
	cmd("make");
}
void install(void) {
	cmd("make install");
}
void uninstall(void) {
	cmd("make uninstall");
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
};
