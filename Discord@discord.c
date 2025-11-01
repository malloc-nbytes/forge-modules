#include <stdio.h>
#include <stdlib.h>

#include <forge/forge.h>

char *getname(void)  { return "Discord@discord"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Voice, video, and text communication platform"; }
char *getweb(void)   { return "https://discord.com/"; }

char *download(void) {
        CMD("wget -O discord-zipped.tar.gz \"https://discord.com/api/download?platform=linux&format=tar.gz\"", {
                forge_io_rm_dir("discord-zipped.tar.gz");
                return NULL;
        });
        mkdirp("discord");
        CMD("tar -xpvf ./discord-zipped.tar.gz -C discord", {
                forge_io_rm_dir("discord");
                return NULL;
        });
        CMD("rm discord-zipped.tar.gz", return NULL);
        return "discord";
}

int install(void) {
        CMD("mkdir -p $DESTDIR/opt/discord", return 0);
        CMD("cp -r ./* $DESTDIR/opt/discord", {
                /* cmd("rm -rf /opt/discord"); */
                return 0;
        });
        CMD("chmod -R 755 $DESTDIR/opt/discord", {
                /* cmd("rm -rf /opt/discord"); */
                return 0;
        });
        CMD("chmod +x $DESTDIR/opt/discord/Discord", {
                /* cmd("rm -rf /opt/discord"); */
                return 0;
        });
        CMD("ln -sf $DESTDIR/opt/discord/Discord/Discord " FORGE_PREFERRED_INSTALL_PREFIX "/bin/discord", {
                cmd("rm -rf /opt/discord");
                return 0;
        });
        return 1;
}

int uninstall(void) {
        CMD("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/discord", return 0);
        return cmd("rm -rf /opt/discord");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
