#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/gnutls.html

char *deps[] = {
        "GNU@nettle-3.10.2",
        NULL,
};

char *sugg[] = {
        "make-ca@make-ca",
        "GNU@libunistring-1.3.0",
        "libtasn1@libtasn1",
        "p11-glue@p11-kit",
        NULL,
};

char **getsugg(void) { return sugg; }
char **getdeps(void) { return deps; }
char *getname(void)  { return "GNU@gnuTLS-3.8.10"; }
char *getver(void)   { return "3.8.10"; }
char *getdesc(void)  { return "Tools which provide a secure layer over a reliable transport layer"; }
char *getweb(void)   { return "https://www.gnupg.org/ftp/gcrypt/gnutls/v3.8"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/gnutls/v3.8/gnutls-3.8.10.tar.xz", return NULL);
        CMD("tar -vxf gnutls-3.8.10.tar.xz", return NULL);
        CMD("rm gnutls-3.8.10.tar.xz", return NULL);
        return "gnutls-3.8.10";
}

int
build(void)
{
        CMD("./configure --prefix=/usr \
            --docdir=/usr/share/doc/gnutls-3.8.10 \
            --with-default-trust-store-pkcs11=\"pkcs11:\"", return 0);
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
        .msgs            = NULL,
        .suggested       = getsugg,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
