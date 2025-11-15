#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/gnutls.html

char *getname(void)  { return "GNU@nettle-3.10.2"; }
char *getver(void)   { return "3.10.2"; }
char *getdesc(void)  { return "A low-level cryptographic library"; }
char *getweb(void)   { return "https://ftp.gnu.org/gnu/nettle"; }

char *
download(void)
{
        CMD("wget https://ftp.gnu.org/gnu/nettle/nettle-3.10.2.tar.gz", return NULL);
        CMD("tar -vxf nettle-3.10.2.tar.gz", return NULL);
        CMD("rm nettle-3.10.2.tar.gz", return NULL);
        return "nettle-3.10.2";
}

int
build(void)
{
        CMD("./configure --prefix=/usr --libdir=/usr/lib --disable-static", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;
        (void)cmd("chmod -v 755 $DESTDIR/usr/lib/lib{hogweed,nettle}.so");
        return 1;
        //CMD("install -v -m755 -d $DESTDIR/usr/share/doc/nettle-3.10.2", return 0);
        //return cmd("install -v -m644 nettle.{html,pdf} $DESTDIR/usr/share/doc/nettle-3.10.2");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
