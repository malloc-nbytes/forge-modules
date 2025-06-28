#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@ampire"; }
char *getver(void) { return "0.1.5"; }
char *getdesc(void) { return "A music player in the terminal"; }
char *download(void) {
        cmd("git clone https://www.github.com/malloc-nbytes/ampire.git/ --recursive");
        return "ampire";
}
void build(void) {
        mkdirp("build");
        cd("build");
        cmd("cmake -S .. -B .");
        make(NULL);
}
void install(void) {
        cd("build");
        make("install");
        cmd("ldconfig");
}
void uninstall(void) {
        cd("build");
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
};
