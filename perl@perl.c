#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "perl@perl"; }
char *getver(void) { return "5.40.2"; }
char *getdesc(void) {
        return "Highly capable, feature-rich programming language with over 37 years of development";
}
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("git clone https://github.com/Perl/perl5.git perl --depth=1");
        return "perl";
}
void build(void) {
        cmd("sh Configure -des                            \
             -D prefix=/usr                               \
             -D vendorprefix=/usr                         \
             -D useshrplib                                \
             -D privlib=/usr/lib/perl5/5.40/core_perl     \
             -D archlib=/usr/lib/perl5/5.40/core_perl     \
             -D sitelib=/usr/lib/perl5/5.40/site_perl     \
             -D sitearch=/usr/lib/perl5/5.40/site_perl    \
             -D vendorlib=/usr/lib/perl5/5.40/vendor_perl \
             -D vendorarch=/usr/lib/perl5/5.40/vendor_perl");
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
