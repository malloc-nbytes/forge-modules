#include <stdlib.h>
#include <stdio.h>

#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "GNU@gdb"; }
char *getver(void) { return "16.2.0"; }
char *getdesc(void) { return "The GNU Project Debugger"; }
char **getdeps(void) { return deps; }
char *download(void) {
        printf("%s is unimplemented\n", getname());
        return "binutils-gdb";
        cmd("git clone https://sourceware.org/git/binutils-gdb.git --depth=1");
}
void build(void) {
        mkdirp("build");
        cd("build");
        cmd("../configure \
  --enable-gdb \
  --disable-binutils \
  --disable-ld \
  --disable-gas \
  --disable-gprof \
  --disable-gprofng \
  --disable-gold \
  --disable-sim \
  --disable-rda \
  --enable-targets=host-only \
  --prefix=/usr/local");
        cmd("../configure");
        make(NULL);
}
void install(void) {
        printf("%s is unimplemented\n", getname());
        return;
        make("install");
}
void uninstall(void) {
        printf("%s is unimplemented\n", getname());
        return;
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
