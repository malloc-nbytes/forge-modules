#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/gnupg.html

char *deps[] = {
        "gpg@libassuan",
        "gpg@libgcrypt",
        "gpg@libksba",
        "gpg@nPth",
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
char *getname(void)  { return "gpg@GnuPG"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Implementation of the OpenPGP standard"; }
char *getweb(void)   { return "https://github.com/gpg/gnupg"; }

char *
download(void)
{
        CMD("git clone https://github.com/gpg/gnupg.git --depth=1", return NULL);
        return "gnupg";
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("../configure --prefix=/usr        \
             --localstatedir=/var              \
             --sysconfdir=/etc                 \
             --docdir=/usr/share/doc/gnupg-2.4.8", return 0);
        if (!make(NULL)) return 0;
        CMD("makeinfo --html --no-split -I doc -o doc/gnupg_nochunks.html ../doc/gnupg.texi", return 0);
        CMD("makeinfo --plaintext -I doc -o doc/gnupg.txt ../doc/gnupg.texi", return 0);
        return cmd("make -C doc html");
}

int
install(void)
{
        if (!mkdirp("build")) return 0;
        if (!make("install")) return 0;
        CMD("install -v -m755 -d /usr/share/doc/gnupg/html", return 0);
        CMD("install -v -m644 doc/gnupg_nochunks.html /usr/share/doc/gnupg/html/gnupg.html", return 0);
        CMD("install -v -m644 ../doc/*.texi doc/gnupg.txt /usr/share/doc/gnupg", return 0);
        return cmd("install -v -m644 doc/gnupg.html/* /usr/share/doc/gnupg/html");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = getsugg,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
