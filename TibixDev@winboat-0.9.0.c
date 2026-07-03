#include <stdio.h>
#include <stdlib.h>

#include <forge/forge.h>

#define VERSION "0.9.0"

static const char *desktop = "[Desktop Entry]\n"
        "Version=" VERSION "\n"
        "Name=winboat\n"
        "GenericName=Emulator\n"
        "Keywords=emulator;Windows;\n"
        "Exec=/opt/winboat/winboat %u\n"
        "Terminal=false\n"
        "Type=Application\n"
        "Categories=Emulator;\n"
        "StartupNotify=true";

char *getname(void)  { return "TibixDev@winboat" VERSION; }
char *getver(void)   { return VERSION; }
char *getdesc(void)  { return "A Windows Emulator for Linux"; }
char *getweb(void)   { return "https://github.com/TibixDev/winboat/releases/tag/v0.9.0"; }

char *download(void) {
        CMD("wget -O winboat-zipped.tar.gz https://github.com/TibixDev/winboat/releases/download/v0.9.0/winboat-0.9.0-x64.tar.gz", {
                forge_io_rm_dir("winboat-zipped.tar.gz");
                return NULL;
        });
        mkdirp("winboat-" VERSION);
        CMD("tar -vxf ./winboat-zipped.tar.gz -C winboat-" VERSION, {
                forge_io_rm_dir("winboat-zipped.tar.gz");
                return NULL;
        });
        cmd("rm winboat-zipped.tar.gz");
        return "winboat-"  VERSION;
}

int install(void) {
        cd("winboat");
        CMD("mkdir -p $DESTDIR/opt/winboat",                                                        return 0);
        CMD("cp -r ./* $DESTDIR/opt/winboat",                                                       return 0);
        CMD("chmod -R 755 $DESTDIR/opt/winboat",                                                    return 0);
        CMD("chmod +x $DESTDIR/opt/winboat/winboat",                                                return 0);
        CMD("ln -sf $DESTDIR/opt/winboat/winboat " FORGE_PREFERRED_INSTALL_PREFIX "/bin/winboat",   return 0);
        CMD("ln -sf /opt/winboat/winboat " FORGE_PREFERRED_INSTALL_PREFIX "/bin/winboat",           return 0);

        // Desktop Entry
        CMD("mkdir -p $DESTDIR/usr/share/applications", return 0);

        char *desktop_fp = forge_cstr_builder(env("DESTDIR"), "/usr/share/applications/winboat.desktop", NULL);
        forge_io_create_file(desktop_fp, 1);
        forge_io_write_file(desktop_fp, desktop);

        char *chmod_cmd = forge_cstr_builder("chmod 644 ", desktop_fp, NULL);
        CMD(chmod_cmd, goto bad);

        free(chmod_cmd);
        free(desktop_fp);
        return 1;

 bad:
        free(chmod_cmd);
        free(desktop_fp);
        return 0;
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
