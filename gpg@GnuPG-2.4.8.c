#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/gnupg.html

char *deps[] = {
        "gpg@libassuan-3.0.2",
        "gpg@libgcrypt-1.11.2",
        "gpg@libksba-1.6.7",
        "gpg@nPth-1.8.0",
        "OpenLDAP@OpenLDAP-2.6.10",
        NULL,
};

char *sugg[] = {
        "GnuTLS-3.8.10 https://www.linuxfromscratch.org/blfs/view/stable/postlfs/gnutls.html",
        "pinentry-1.3.2 https://www.linuxfromscratch.org/blfs/view/stable/general/pinentry.html",
        NULL,
};

char **getdeps(void) { return deps; }
char **getsugg(void) { return sugg; }
char *getname(void)  { return "gpg@GnuPG-2.4.8"; }
char *getver(void)   { return "2.4.8"; }
char *getdesc(void)  { return "Implementation of the OpenPGP standard"; }
char *getweb(void)   { return "https://github.com/gpg/gnupg"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/gnupg/gnupg-2.4.8.tar.bz2", return NULL);
        CMD("tar -vxf gnupg-2.4.8.tar.bz2", return NULL);
        CMD("rm gnupg-2.4.8.tar.bz2", return NULL);
        return "gnupg-2.4.8";
}

int
build(void)
{
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("../configure --prefix=/usr        \
             --localstatedir=/var              \
             --sysconfdir=/etc                 \
             --docdir=/usr/share/doc/gnupg-2.4.8", return 0);
        return make(NULL);
        /* CMD("makeinfo --html --no-split -I doc -o doc/gnupg_nochunks.html ../doc/gnupg.texi", return 0); */
        /* CMD("makeinfo --plaintext -I doc -o doc/gnupg.txt ../doc/gnupg.texi", return 0); */
        /* return cmd("make -C doc html"); */
}

int
install(void)
{
        CD("build", return 0);
        return make("install");
        /* if (!make("install")) return 0; */
        /* CMD("install -v -m755 -d /usr/share/doc/gnupg-2.4.8/html", return 0); */
        /* CMD("install -v -m644 doc/gnupg_nochunks.html /usr/share/doc/gnupg-2.4.8/html/gnupg.html", return 0); */
        /* CMD("install -v -m644 ../doc/\*.texi doc/gnupg.txt /usr/share/doc/gnupg-2.4.8", return 0); */
        /* return cmd("install -v -m644 doc/gnupg.html/\* /usr/share/doc/gnupg-2.4.8/html"); */
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
