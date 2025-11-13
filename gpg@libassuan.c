#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libassuan.html

char *deps[] = {
        "gpg@libgpg-error",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "gpg@libassuan"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Inter process communication library"; }
char *getweb(void)   { return "https://github.com/gpg/libassuan"; }

char *
download(void)
{
        return git_clone("gpg", "libassuan");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr", return 0);
        if (!make(NULL)) return 0;
        CMD("make -C doc html", return 0);
        CMD("makeinfo --html --no-split -o doc/assuan_nochunks.html doc/assuan.texi", return 0);
        CMD("makeinfo --plaintext -o doc/assuan.txt doc/assuan.texi", return 0);
}

int
install(void)
{
        if (!make("install")) return 0;
        CMD("install -v -dm755 /usr/share/doc/libassuan/html", return 0);
        CMD("install -v -m644 doc/assuan.html/* /usr/share/doc/libassuan/html", return 0);
        CMD("install -v -m644 doc/assuan_nochunks.html /usr/share/doc/libassuan", return 0);
        return cmd("install -v -m644 doc/assuan.{txt,texi} /usr/share/doc/libassuan");
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
