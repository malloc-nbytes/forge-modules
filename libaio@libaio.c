#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libaio.html

char *getname(void)  { return "libaio@libaio"; }
char *getver(void)   { return "0.3.113"; }
char *getdesc(void)  { return "An asynchronous I/O facility"; }
char *getweb(void)   { return "https://pagure.io/libaio/archive/libaio-0.3.113/libaio-0.3.113.tar.gz"; }

char *
download(void)
{
        if (!cmd("wget -O libaio.tar.gz https://pagure.io/libaio/archive/libaio-0.3.113/libaio-0.3.113.tar.gz"))
                return NULL;

        mkdirp("libaio");

        CMD("tar -vxf ./libaio.tar.gz -C libaio", {
                forge_io_rm_dir("json-c.tar.gz");
                return NULL;
        });

        (void)cmd("rm libaio.tar.gz");

        return "libaio";
}

int
build(void)
{
        if (!cd("libaio-0.3.113")) return 0;
        CMD("sed -i '/install.*libaio.a/s/^/#/' src/Makefile", return 0);
        CMD("case \"$(uname -m)\" in\n"
                "i?86) sed -e \"s/off_t/off64_t/\" -i harness/cases/23.t ;;\n"
            "esac", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!cd("libaio-0.3.113")) return 0;
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
