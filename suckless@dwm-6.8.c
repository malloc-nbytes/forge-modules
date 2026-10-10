#include <forge/forge.h>

char *getname(void)     { return "suckless@dwm-6.8"; }
char *getver(void)      { return "6.8"; }
char *getdesc(void)     { return "A simple window manager"; }
char *getweb(void)      { return "https://dwm.suckless.org/"; }

char *
download(void)
{
        CMD("wget https://dl.suckless.org/dwm/dwm-6.8.tar.gz", return NULL);

        if (!mkdirp("dwm-6.8")) {
                forge_io_rm_dir("dwm-6.8.tar.gz");
                return NULL;
        }

        CMD("tar -vxf ./dwm-6.8.tar.gz -C dwm-6.8", {
                forge_io_rm_dir("dwm-6.8.tar.gz");
                forge_io_rm_dir("dwm-6.8");
                return NULL;
        });

        forge_io_rm_dir("dwm-6.8.tar.gz");
        return "dwm-6.8";
}

int
build(void)
{
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
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
