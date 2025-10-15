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

int build(void) { return 1; }

int install(void) {
        mkdirp("/opt/discord");
        CMD("cp -r ./* /opt/discord", {
                cmd("rm /opt/discord");
                return 0;
        });
        CMD("chmod -R 755 /opt/discord", {
                cmd("rm /opt/discord");
                return 0;
        });
        CMD("chmod +x /opt/discord/Discord", {
                cmd("rm /opt/discord");
                return 0;
        });
        CMD("ln -s /opt/discord/Discord " FORGE_PREFERRED_INSTALL_PREFIX "/bin/discord", {
                cmd("rm /opt/discord");
                return 0;
        });
        return 1;
}

int uninstall(void) {
        CMD("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/discord", return 0);
        return cmd("rm -r /opt/discord");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
