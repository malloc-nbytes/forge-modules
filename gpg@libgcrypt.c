#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libgcrypt.html

char *deps[] = {
        "gpg@libgpg-error",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "gpg@libgcrypt"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "General purpose crypto library based on the code used in GnuPG"; }
char *getweb(void)   { return "https://github.com/gpg/libgcrypt"; }

char *
download(void)
{
        return git_clone("gpg", "libgcrypt");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr", return 0);
        if (!make(NULL)) return 0;
        CMD("make -C doc html", return 0);
        CMD("makeinfo --html --no-split -o doc/gcrypt_nochunks.html doc/gcrypt.texi", return 0);
        return cmd("makeinfo --plaintext -o doc/gcrypt.txt doc/gcrypt.texi");
}

int
install(void)
{
        if (!make("install")) return 0;
        CMD("install -v -dm755 /usr/share/doc/libgcrypt", return 0);
        CMD("install -v -m644 README doc/{README.apichanges,fips*,libgcrypt*} /usr/share/doc/libgcrypt", return 0);
        CMD("install -v -dm755 /usr/share/doc/libgcrypt/html", return 0);
        CMD("install -v -m644 doc/gcrypt.html/* /usr/share/doc/libgcrypt/html", return 0);
        CMD("install -v -m644 doc/gcrypt_nochunks.html /usr/share/doc/libgcrypt", return 0);
        return cmd("install -v -m644 doc/gcrypt.{txt,texi} /usr/share/doc/libgcrypt");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
