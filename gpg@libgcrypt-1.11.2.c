#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libgcrypt.html

char *deps[] = {
        "gpg@libgpg-error-1.55.0",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "gpg@libgcrypt-1.11.2"; }
char *getver(void)   { return "1.11.2"; }
char *getdesc(void)  { return "General purpose crypto library based on the code used in GnuPG"; }
char *getweb(void)   { return "https://github.com/gpg/libgcrypt"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/libgcrypt/libgcrypt-1.11.2.tar.bz2", return NULL);
        CMD("tar -vxf libgcrypt-1.11.2.tar.bz2", return NULL);
        CMD("rm libgcrypt-1.11.2.tar.bz2", return NULL);
        return "libgcrypt-1.11.2";
}

int
build(void)
{
        CMD("./configure --prefix=/usr", return 0);
        return make(NULL);
        /* CMD("make -C doc html", return 0); */
        /* CMD("makeinfo --html --no-split -o doc/gcrypt_nochunks.html doc/gcrypt.texi", return 0); */
        /* return cmd("makeinfo --plaintext -o doc/gcrypt.txt doc/gcrypt.texi"); */
}

int
install(void)
{
        return make("install");
        /* if (!make("install")) return 0; */
        /* CMD("install -v -dm755 /usr/share/doc/libgcrypt-1.11.2", return 0); */
        /* CMD("install -v -m644 README doc/{README.apichanges,fips*,libgcrypt*} /usr/share/doc/libgcrypt-1.11.2", return 0); */
        /* CMD("install -v -dm755 /usr/share/doc/libgcrypt-1.11.2/html", return 0); */
        /* CMD("install -v -m644 doc/gcrypt.html/\* /usr/share/doc/libgcrypt-1.11.2/html", return 0); */
        /* CMD("install -v -m644 doc/gcrypt_nochunks.html /usr/share/doc/libgcrypt-1.11.2", return 0); */
        /* return cmd("install -v -m644 doc/gcrypt.{txt,texi} /usr/share/doc/libgcrypt-1.11.2"); */
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
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
