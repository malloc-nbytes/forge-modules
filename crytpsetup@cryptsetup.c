#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/cryptsetup.html

char *deps[] = {
        "JSON-C@JSON-C",
        "lvm2@lvm2",
        "rpm-software-management@popt",
        NULL,
};

char *msgs[] = {
        "To use this package, you must set these kernel options:",
        YELLOW "    [*]   MD" RESET,
        YELLOW "    <*/M> BLK_DEV_DM" RESET,
        YELLOW "    <*/M> DM_CRYPT" RESET,
        YELLOW "    -*-   CRYPTO" RESET,
        YELLOW "    <*/M> CRYPTO_AES" RESET,
        YELLOW "    <*/M> CRYPTO_TWOFISH" RESET,
        YELLOW "    <*/M> CRYPTO_XTS" RESET,
        YELLOW "    <*/M> CRYPTO_SHA256" RESET,
        YELLOW "    <*/M> CRYPTO_USER_API_SKCIPHER" RESET,
        NULL,
};

char **getdeps(void) { return deps; }
char **getmsgs(void) { return msgs; }
char *getname(void)  { return "cryptsetup@cryptsetup"; }
char *getver(void)   { return "2.8.1"; }
char *getdesc(void)  { return "Set up transparent encryption of block devices using the kernel crypto API"; }
char *getweb(void)   { return "https://www.linuxfromscratch.org/blfs/view/stable/postlfs/cryptsetup.html"; }

char *
download(void)
{
        if (!cmd("wget -O cryptsetup.tar.xz https://www.kernel.org/pub/linux/utils/cryptsetup/v2.8/cryptsetup-2.8.1.tar.xz"))
                return NULL;

        mkdirp("cryptsetup");

        CMD("tar -vxf ./cryptsetup.tar.xz -C cryptsetup", {
                forge_io_rm_dir("cryptsetup.tar.xz");
                return NULL;
        });

        (void)cmd("rm cryptsetup.tar.xz");

        return "cryptsetup";
}

int
build(void)
{
        if (!cd("cryptsetup-2.8.1")) return 0;
        CMD("./configure --prefix=/usr       \
            --disable-ssh-token              \
            --disable-asciidoc", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!cd("cryptsetup-2.8.1")) return 0;
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
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
