#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/popt.html

char *getname(void)  { return "rpm-software-management@popt"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "C library for parsing command line parameters"; }
char *getweb(void)   { return "https://ftp.osuosl.org/pub/rpm/popt/"; }

char *
download(void)
{
        if (!cmd("wget -O popt.tar.gz https://ftp.osuosl.org/pub/rpm/popt/releases/popt-1.x/popt-1.19.tar.gz"))
                return NULL;

        if (!mkdirp("popt")) return 0;

        CMD("tar -vxf ./popt.tar.gz -C popt", {
                forge_io_rm_dir("popt.tar.gz");
                return NULL;
        });

        (void)cmd("rm popt.tar.gz");

        return "popt";

}

int
build(void)
{
        if (!cd("popt-1.19")) return 0;
        CMD("./configure --prefix=/usr --disable-static", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!cd("popt-1.19")) return 0;
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
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
