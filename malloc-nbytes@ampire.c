#include <forge/forge.h>

char *getname(void)  { return "malloc-nbytes@ampire"; }
char *getver(void)   { return "0.1.5"; }
char *getdesc(void)  { return "A music player in the terminal"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/ampire.git/"; }

char *download(void) {
        CMD("git clone https://www.github.com/malloc-nbytes/ampire.git/ --recurse-submodules --shallow-submodules --depth=1", return NULL);
        return "ampire";
}

int build(void) {
        mkdirp("build");
        cd("build");
        CMD("cmake -S .. -B .", return 0);
        return make(NULL);
}

int install(void) {
        cd("build");
        if (!make("install")) return 0;
        return cmd("ldconfig");
}

int uninstall(void) {
        cd("build");
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
