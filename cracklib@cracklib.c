#include <forge/forge.h>

#include <stdio.h>

// TODO: rebuild shadow
// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/cracklib.html

char *rebuilds[] = {
        "shadow-maint@shadow",
        NULL,
};

char *msgs[] = {
        "Additional word lists are available at " YELLOW "https://www.skullsecurity.org/wiki/Passwords" RESET,
        "See this package's " YELLOW "download()" RESET " and " YELLOW "install()" RESET " functions for how to install them.",
        NULL,
};

char **getrebuilds(void) { return rebuilds; }
char **getmsgs(void) { return msgs; }
char *getname(void)  { return "cracklib@cracklib"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "CrackLib Library and Dictionaries"; }
char *getweb(void)   { return "https://github.com/cracklib/cracklib/"; }

char *
download(void)
{
        printf(RED BOLD "CRACKLIB IS CURRENTLY BROKEN" RESET "\n");
        return NULL;

        char *dir = git_clone("cracklib", "cracklib");
        //CD(dir, return NULL);
        CMD("wget https://github.com/cracklib/cracklib/releases/download/v2.10.3/cracklib-words-2.10.3.xz", return 0);
        cmd_builder("mv cracklib-words-2.10.3.xz", dir);
        return dir;
}

int
build(void)
{
        printf(RED BOLD "CRACKLIB IS CURRENTLY BROKEN" RESET "\n");
        return 0;

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
        printf(RED BOLD "CRACKLIB IS CURRENTLY BROKEN" RESET "\n");
        return 0;

        CD("src", return 0);
        if (!make("install")) return 0;
        CMD("xzcat ../cracklib-words-2.10.3.xz > $DESTDIR/usr/share/dict/cracklib-words", return 0);
        CMD("ln -v -sf cracklib-words $DESTDIR/usr/share/dict/words", return 0);
        CMD("echo $(hostname) >> $DESTDIR/usr/share/dict/cracklib-extra-words", return 0);
        CMD("install -v -m755 -d $DESTDIR/usr/lib/cracklib", return 0);
        return cmd("$DESTDIR/bin/create-cracklib-dict /usr/share/dict/cracklib-words /usr/share/dict/cracklib-extra-words");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
