#include <forge/forge.h>

// TODO: rebuild shadow
// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/cracklib.html

char *deps[] = {
        "JSON-C@JSON-C",
        "lvm2@lvm2",
        "rpm-software-management@popt",
        NULL,
};

char *msgs[] = {
        "To use this package, you must set these kernel configurations:",
        YELLOW,
        "    [*]   MD",
        "    <*/M> BLK_DEV_DM",
        "    <*/M> DM_CRYPT",
        "    -*-   CRYPTO",
        "    <*/M> CRYPTO_AES",
        "    <*/M> CRYPTO_TWOFISH",
        "    <*/M> CRYPTO_XTS",
        "    <*/M> CRYPTO_SHA256",
        "    <*/M> CRYPTO_USER_API_SKCIPHER",
        RESET,
        NULL,
};

char **getdeps(void) { return deps; }
char **getmsgs(void) { return msgs; }
char *getname(void)  { return "cracklib@cracklib"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "CrackLib Library and Dictionaries"; }
char *getweb(void)   { return "https://github.com/cracklib/cracklib"; }

char *
download(void)
{
        char *dir = git_clone("cracklib", "cracklib");
        CD(dir, return NULL);
        CMD("wget https://github.com/cracklib/cracklib/releases/download/v2.10.3/cracklib-words-2.10.3.xz", return 0);
        return dir;
}

int
build(void)
{
        CMD("./configure --prefix=/usr       \
            --disable-ssh-token              \
            --disable-asciidoc", return 0);
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
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
