#include <forge/forge.h>

// TODO: rebuild shadow
// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/cracklib.html

char *msgs[] = {
        "Additional word lists are available at " YELLOW "https://www.skullsecurity.org/wiki/Passwords" RESET,
        "See this package's " YELLOW "download()" RESET " and " YELLOW "install()" RESET " functions for how to install them.",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void)  { return "cracklib@cracklib"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "CrackLib Library and Dictionaries"; }
char *getweb(void)   { return "https://github.com/cracklib/cracklib/"; }

char *
download(void)
{
        char *dir = git_clone("cracklib", "cracklib");
        //CD(dir, return NULL);
        CMD("wget https://github.com/cracklib/cracklib/releases/download/v2.10.3/cracklib-words-2.10.3.xz", return 0);
        cmd_builder("mv cracklib-words-2.10.3.xz", dir);
        return dir;
}

int
build(void)
{
        CD("src", return 0);
        CMD("/bin/bash autogen.sh", return 0);
        CMD("CPPFLAGS+=' -I /usr/include/python3.13' \
                ./configure --prefix=/usr            \
                --disable-static                     \
                --with-default-dict=/usr/lib/cracklib/pw_dict", return 0);
        return make(NULL);
}

int
install(void)
{
        CD("src", return 0);
        if (!make("install")) return 0;
        CMD("xzcat ../cracklib-words-2.10.3.xz > /usr/share/dict/cracklib-words", return 0);
        CMD("ln -v -sf cracklib-words /usr/share/dict/words", return 0);
        CMD("echo $(hostname) >> /usr/share/dict/cracklib-extra-words", return 0);
        CMD("install -v -m755 -d /usr/lib/cracklib", return 0);
        return cmd(FORGE_PREFERRED_INSTALL_PREFIX "/bin/create-cracklib-dict /usr/share/dict/cracklib-words /usr/share/dict/cracklib-extra-words");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
