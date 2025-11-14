#include <forge/forge.h>

char *msgs[] = {
        "To use this package, you must set these kernel configurations:",
        YELLOW,
        "    [*]   BLK_DEV",
        "    <*/M> BLK_DEV_RAM",
        "    [*]   MD",
        "    <*/M> BLK_DEV_DM",
        "    <*/M> DM_CRYPT",
        "    <*/M> DM_SNAPSHOT",
        "    <*/M> DM_THIN_PROVISIONING",
        "    <*/M> DM_CACHE",
        "    <*/M> DM_MIRROR",
        "    <*/M> MD_ZERO",
        "    <*/M> DM_DELAY",
        "    [*]   MAGIC_SYSRQ",
        RESET,
        ""
        "After installation, remove this file:",
        YELLOW "    rm -fv /usr/lib/udev/rules.d/69-dm-lvm.rules" RESET,
        NULL,
};

char *deps[] = {
        "libaio@libaio",
        NULL,
};

char **getdeps(void) { return deps; }
char **getmsgs(void) { return msgs; }
char *getname(void)  { return "lvm2@lvm2"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A set of tools that manage logical partitions"; }
char *getweb(void)   { return "https://github.com/lvmteam/lvm2"; }

char *
download(void)
{
        return git_clone("lvmteam", "lvm2");
}

int
build(void)
{
        CMD("PATH+=:/usr/sbin          \
             ./configure --prefix=/usr \
                --enable-cmdlib        \
                --enable-pkgconfig     \
                --enable-udev_sync",
            return 0);
        return make(NULL);
}

int
install(void)
{
        return make("install");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
