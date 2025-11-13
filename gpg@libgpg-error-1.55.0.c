#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libgpg-error.html

char *getname(void)  { return "gpg@libgpg-error-1.55.0"; }
char *getver(void)   { return "1.55.0"; }
char *getdesc(void)  { return "Defines common error values for all GnuPG components"; }
char *getweb(void)   { return "https://www.gnupg.org/ftp/gcrypt/libgpg-error"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/libgpg-error/libgpg-error-1.55.tar.bz2",
            return NULL);
        CMD("tar -vxf libgpg-error-1.55.tar.bz2", return NULL);
        CMD("rm libgpg-error-1.55.tar.bz2", return NULL);
        return "libgpg-error-1.55";
}

int
build(void)
{
        CMD("./configure --prefix=/usr", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;
        return cmd("install -v -m644 -D README /usr/share/doc/libgpg-error/README");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
