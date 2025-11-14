#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libtasn1.html

char *getname(void)  { return "libtasn1@libtasn1"; }
char *getver(void)   { return "4.20.0"; }
char *getdesc(void)  { return "Portable C library that encodes and decodes DER/BER data"; }
char *getweb(void)   { return "https://ftp.gnu.org/gnu/libtasn1/"; }

char *
download(void)
{
        if (!cmd("wget -O libtasn1.tar.gz https://ftp.gnu.org/gnu/libtasn1/libtasn1-4.20.0.tar.gz"))
                return NULL;

        mkdirp("libtasn1");

        CMD("tar -vxf ./libtasn1.tar.gz -C libtasn1", {
                forge_io_rm_dir("libtasn1.tar.gz");
                return NULL;
        });

        (void)cmd("rm libtasn1.tar.gz");

        return "libtasn1";
}

int
build(void)
{
        if (!cd("libtasn1-4.20.0")) return 0;
        CMD("./configure --prefix=/usr --disable-static", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!cd("libtasn1-4.20.0")) return 0;
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
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
