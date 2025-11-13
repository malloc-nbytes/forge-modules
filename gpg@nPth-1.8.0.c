#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/npth.html

char *getname(void)  { return "gpg@nPth-1.8.0"; }
char *getver(void)   { return "1.8.0"; }
char *getdesc(void)  { return "Library that provides non-preemptive priority-based scheduling for multiple threads"; }
char *getweb(void)   { return "https://github.com/gpg/npth"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/npth/npth-1.8.tar.bz2", return NULL);
        CMD("tar -vxf npth-1.8.tar.bz2", return NULL);
        CMD("rm npth-1.8.tar.bz2", return NULL);
        return "npth-1.8";
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
        return make("install");
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
