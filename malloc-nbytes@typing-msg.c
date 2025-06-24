#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@typing-msg"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "A small program to simulate typing a message"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "typing-msg");
}
void build(void) {
	cmd("./build.sh");
}
void install(void) {
	cmd("cp ./typing-msg /usr/local/bin");
}
void uninstall(void) {
	cmd("rm /usr/local/bin/typing-msg");
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
