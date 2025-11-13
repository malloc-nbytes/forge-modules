#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libassuan.html

char *deps[] = {
        "gpg@libgpg-error-1.55.0",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "gpg@libassuan-3.0.2"; }
char *getver(void)   { return "3.0.2"; }
char *getdesc(void)  { return "Inter process communication library"; }
char *getweb(void)   { return "https://github.com/gpg/libassuan"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/libassuan/libassuan-3.0.2.tar.bz2", return NULL);
        CMD("tar -vxf libassuan-3.0.2.tar.bz2", return NULL);
        CMD("rm libassuan-3.0.2.tar.bz2", return NULL);
        return "libassuan-3.0.2";
}

int
build(void)
{
        CMD("./configure --prefix=/usr", return 0);
        return make(NULL);
        /* CMD("make -C doc html", return 0); */
        /* CMD("makeinfo --html --no-split -o doc/assuan_nochunks.html doc/assuan.texi", return 0); */
        /* return cmd("makeinfo --plaintext -o doc/assuan.txt doc/assuan.texi"); */
}

int
install(void)
{
        return make("install");
        /* if (!make("install")) return 0; */
        /* CMD("install -v -dm755 /usr/share/doc/libassuan-3.0.2/html", return 0); */
        /* CMD("install -v -m644 doc/assuan.html/\* /usr/share/doc/libassuan-3.0.2/html", return 0); */
        /* CMD("install -v -m644 doc/assuan_nochunks.html /usr/share/doc/libassuan-3.0.2", return 0); */
        /* return cmd("install -v -m644 doc/assuan.{txt,texi} /usr/share/doc/libassuan-3.0.2"); */
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
